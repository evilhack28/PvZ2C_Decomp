//
//  NetworkMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-03.
//

#include "gameNetWork/NetworkMgr.h"

#include "gameNetWork/androidNetworkMsgProcess.h"
#include "logServer/sock_buffer.h"
#include "LawnApp.h"
#include "NetworkItemMgr.h"
#include "StringHelper.h"
#include "TimeMgr.h"

NetworkMgr* NetworkMgr::s_pNetworkMgr = NULL;
NetworkMgr* gNetworkMgr = NULL;

NetworkMgr::NetworkMgr()
{
	gNetworkMgr = this;
	m_pMsgQueue = NULL;
	m_pReceivedBuf = NULL;
	m_pNetWorkMsgProc = NULL;
	m_UpdateCacheTimer = 0.0f;
}

NetworkMgr::~NetworkMgr()
{
	gNetworkMgr = NULL;
	SAFE_DELETE(m_pReceivedBuf);
	SAFE_DELETE(m_pMsgQueue);
	SAFE_DELETE(m_pNetWorkMsgProc);
}

NetworkMgr* NetworkMgr::Instance()
{
	if (!s_pNetworkMgr)
		s_pNetworkMgr = new NetworkMgr();
	return s_pNetworkMgr;
}

INetworkMsgProcess* NetworkMgr::GetNewNetWorkProcess()
{
	return m_pNetWorkMsgProc;
}

INetworkMsgProcess* NetworkMgr::GetNetWorkProcess()
{
	return m_pNetWorkMsgProc;
}

int NetworkMgr::Init()
{
	m_iOutlen = MAX_BUF_LEN;
	m_pReceivedBuf = new char[MAX_BUF_LEN];
	m_pMsgQueue = new StreamBuffer(MAX_BUF_LEN);
	if (!m_pReceivedBuf)
		return -3;

	m_pNetWorkMsgProc = new androidNetworkMsgProcess();
	m_pNetWorkMsgProc->Initialize();
	m_pNetWorkMsgProc->RegisterCommonMessages();

	m_lastTime = SexyTime() / 1000;
	m_LoopCount = 0;
	return 1;
}

void NetworkMgr::Update()
{
	INetworkMsgProcess* proc = Instance()->GetNetWorkProcess();
	bool connected = gLawnApp->IsConnected();
	if (proc)
	{
		if (connected)
		{
			if (proc && proc->IsLogined())
			{
				if (NetworkItemMgr::GetInstance().NeedSync())
					NetworkItemMgr::GetInstance().DoSync();

				if (gLawnApp->GetWorldMap())
				{
					if (m_UpdateCacheTimer <= 0.0f)
					{
						proc->flushCache();
						m_UpdateCacheTimer = 30.0f;
					}
					m_UpdateCacheTimer -= PVZ_Dt();
				}
			}
		}
	}

	UpdateNetTime();

	int len;
	{
		Sexy::AutoCrit lock(mRecMsgQueueCS);
		len = m_pMsgQueue->CheckGetAPackage(m_pReceivedBuf, m_iOutlen);
	}
	if (len > 0)
		m_pNetWorkMsgProc->ProcessMsg((unsigned char*)m_pReceivedBuf, len);
}

void NetworkMgr::UpdateNetTime()
{
	m_LoopCount++;
	if (m_LoopCount > 29)
	{
		m_LoopCount = 0;
		uint64 now = SexyTime() / 1000;
		uint64 gap = now - m_lastTime;
		m_lastTime = now;
		m_NetTime += gap;
	}
}

void NetworkMgr::UpdateNetTime(const std::string& netData)
{
	Sexy::StructuredData data;
	if (!StringHelper::ReadJson(netData, &data))
	{
		// __FILE__/__LINE__ in the shipped build; the path is build-relative and
		// the line can't be reproduced from this tree, so both are pinned here.
		OutputDebugStrF("json parser failed [%s:%d]\n", "./../../../PvZ2/gameNetWork/NetworkMgr.cpp", 148);
		return;
	}

	const Sexy::StructuredData::Value* v = data.ValueForPath("$.d");
	if (!v)
		return;
	int64 t = v->IntegerForName("t", -1);
	if (t == -1)
		return;
	m_NetTime = t;
}

void NetworkMgr::ReceivedMsgCallback(const unsigned char* buffer, int bufLen)
{
	if (gNetworkMgr)
	{
		Sexy::AutoCrit lock(gNetworkMgr->mRecMsgQueueCS);
		gNetworkMgr->m_pMsgQueue->PushAPacket((const char*)buffer, (unsigned int)bufLen);
	}
}
