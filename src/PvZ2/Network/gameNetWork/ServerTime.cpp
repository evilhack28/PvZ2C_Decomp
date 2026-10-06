//
//  ServerTime.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "gameNetWork/ServerTime.h"

#include <climits>
#include <ctime>

#include "LawnApp.h"
#include "GameEventMgr.h"
#include "gameNetWork/events/NetWorkEvent.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

_NetworkEventConfig& GetTimeServerConfig(bool bForce);
long GetTimeTime(const char* i_str);

namespace Message { void ServerTimeReceived(); }

ServerTime* ServerTime::s_pServerTime = NULL;

static const int s_retryDelay[5] = { 10, 30, 60, 90, 100 };

ServerTime::ServerTime()
	: m_IsConnected(false)
	, m_heatBeatTimer(0)
	, m_failedCount(0)
	, m_bRequesting(false)
	, m_bShowConnectUI(false)
{
}

ServerTime::~ServerTime()
{
	std::list<CServerTimeHandler*>& handlers = m_pServerHandlers;
	std::list<CServerTimeHandler*>::iterator it = handlers.begin();
	std::list<CServerTimeHandler*>::iterator end = handlers.end();
	for (; it != end; ++it)
	{
		if (*it)
			delete *it;
	}
	handlers.clear();
}

ServerTime* ServerTime::Instance()
{
	if (!s_pServerTime)
	{
		s_pServerTime = new ServerTime();
		s_pServerTime->Init();
	}
	return s_pServerTime;
}

long ServerTime::GetServerTime()
{
	return m_ServerTime;
}

bool ServerTime::ValidServerTime()
{
	return m_ServerTime > 0;
}

const tm* ServerTime::GetServerTimeS()
{
	Sexy::AutoCrit lock(mHttpRequestCS);
	if (m_ServerTime == 0)
		return NULL;
	return localtime((const time_t*)&m_ServerTime);
}

void ServerTime::Init()
{
	_NetworkEventConfig& config = GetTimeServerConfig(false);
	m_srvURL = _NetworkEventConfig::HasStageURL() ? _NetworkEventConfig::GetStageURL() : config.PVPURL;
	m_ServerTime = 0;
	m_LoopCount = 0;
	m_lastTime = Android::Util::GetElapsedRealtime();
	m_ServerTimeHanlde = NULL;
	m_requestCount = 0;
	m_bRequesting = false;
	m_bShowConnectUI = false;
}

void ServerTime::StartRequest()
{
	if (m_requestCount > 0)
		return;

	m_requestCount++;

	Sexy::StructuredData data;
	data.BeginObject();
	data.AddString("trace", "TimeServerTrace");
	data.AddString("url", m_srvURL);
	data.BeginObject("formData");
	data.AddString("req", "I4");
	data.EndObject();
	data.EndObject();

	Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&data, this, this);
}

void ServerTime::ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context)
{
	Sexy::OutputDebugStrF("ServerTime::ServiceRequestCompleted");
	Sexy::AutoCrit lock(mHttpRequestCS);

	m_bRequesting = false;
	m_requestCount = 0;
	RemoveNetConnectUI();

	const Sexy::StructuredData::Value* v = i_response->ValueForPath("$.d");
	if (v == NULL)
		return;

	std::string t = v->StringForName("t", "");
	if (t == "")
		return;
	if (t.length() <= 18)
		return;

	m_ServerTime = GetTimeTime(t.c_str());
	if (m_ServerTimeHanlde)
	{
		m_ServerTimeHanlde(0, m_ServerTime);
		m_ServerTimeHanlde = NULL;
	}
	m_lastTime = Android::Util::GetElapsedRealtime();
	gMessageRouter->Post(&Message::ServerTimeReceived);
	m_IsConnected = true;
	m_failedCount = 0;
	m_heatBeatTimer = 600.0f;
	ProcessHandler(true);
}

void ServerTime::ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context)
{
	Sexy::OutputDebugStrF("ServerTime::ServiceRequestFailed");
	Sexy::AutoCrit lock(mHttpRequestCS);

	m_bRequesting = false;
	m_requestCount = 0;
	RemoveNetConnectUI();

	_NetworkEventConfig& config = GetTimeServerConfig(false);
	m_srvURL = _NetworkEventConfig::HasStageURL() ? _NetworkEventConfig::GetStageURL() : config.PVPURL;

	if (m_ServerTimeHanlde)
	{
		m_ServerTimeHanlde(-1, 0);
		m_ServerTimeHanlde = NULL;
	}

	m_IsConnected = false;

	int index = m_failedCount;
	if (m_failedCount <= 4)
	{
		m_failedCount++;
	}
	else
	{
		index = 4;
		m_failedCount = 5;
	}

	m_heatBeatTimer = (float)s_retryDelay[index];

	ProcessHandler(false);
}

void ServerTime::ProcessHandler(bool ret)
{
	std::list<CServerTimeHandler*>& handlers = m_pServerHandlers;
	std::list<CServerTimeHandler*>::iterator it = handlers.begin();
	std::list<CServerTimeHandler*>::iterator end = handlers.end();
	for (; it != end; ++it)
	{
		CServerTimeHandler* h = *it;
		Sexy::OutputDebugStrF("handle process : %d", handlers.size());
		if (h)
		{
			Sexy::OutputDebugStrF("handle process : OnServerTimeGet");
			h->OnServerTimeGet(ret, m_ServerTime);
			delete h;
		}
	}
	handlers.clear();
}

void ServerTime::SetServerTime(const std::string& strTime)
{
	if (strTime.length() <= 18)
		return;

	m_ServerTime = GetTimeTime(strTime.c_str());

	if (m_ServerTimeHanlde)
	{
		m_ServerTimeHanlde(0, m_ServerTime);
		m_ServerTimeHanlde = NULL;
	}

	m_lastTime = Android::Util::GetElapsedRealtime();
	gMessageRouter->Post(&Message::ServerTimeReceived);
	m_failedCount = 0;
	m_IsConnected = true;
	m_heatBeatTimer = 600.0f;

	ProcessHandler(true);
}

void ServerTime::StartRequest(bool bShowUI)
{
	if (!gLawnApp->IsConnected())
	{
		m_ServerTime = 0;
		Sexy::OutputDebugStrF("ServerTime StartRequest connect error");
		ProcessHandler(false);
		return;
	}

	Sexy::OutputDebugStrF("ServerTime StartRequest");
	m_bRequesting = true;

	Sexy::StructuredData data;
	data.BeginObject();
	data.AddString("trace", "TimeServerTrace");
	data.AddString("url", m_srvURL);
	data.BeginObject("formData");
	data.AddString("req", "I4");
	data.EndObject();
	data.EndObject();

	Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&data, this, this);

	if (bShowUI)
	{
		gLawnApp->ShowNetConnectingUI("[NET_CONNECTING]");
		m_bShowConnectUI = true;
	}
}

void ServerTime::RemoveNetConnectUI()
{
	if (m_bShowConnectUI)
		gLawnApp->KillNetConnectingUI();
	m_bShowConnectUI = false;
}

void ServerTime::GetServerTime(ServerTimeHandler hanlder)
{
	Sexy::AutoCrit lock(mHttpRequestCS);
	m_ServerTimeHanlde = hanlder;
	if (m_ServerTime == 0)
	{
		StartRequest();
	}
	else
	{
		m_ServerTimeHanlde(0, m_ServerTime);
		m_ServerTimeHanlde = NULL;
	}
}

void ServerTime::GetServerTimeFromNet(CServerTimeHandler* pHandler, bool bShowUI)
{
	Sexy::AutoCrit lock(mHttpRequestCS);
	m_pServerHandlers.push_back(pHandler);
	if (!m_bRequesting)
		StartRequest(bShowUI);
}

void ServerTime::Update(float dt)
{
	m_LoopCount++;
	m_heatBeatTimer -= dt;

	if (m_ServerTime == 0 && gLawnApp->IsConnected() && m_heatBeatTimer <= 0)
	{
		StartRequest();
		m_heatBeatTimer = 600.0f;
	}

	if (m_LoopCount > 29 && m_ServerTime != 0)
	{
		m_LoopCount = 0;

		long nowTime = Android::Util::GetElapsedRealtime();
		long gap = nowTime - m_lastTime;
		m_lastTime = SafeTransferFromInt64(nowTime, LONG_MAX);

		{
			Sexy::AutoCrit lock(mHttpRequestCS);
			m_ServerTime += gap;
		}

		if (m_heatBeatTimer <= 0)
		{
			StartRequest();
			m_heatBeatTimer = 600.0f;
		}
	}
}
