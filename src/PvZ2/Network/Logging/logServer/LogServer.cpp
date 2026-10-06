//
//  LogServer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"
#include "core.h"

#include "logServer/LogServer.h"

#include "PVZDB.h"
#include "ServerConfig.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

#include <arpa/inet.h>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <netdb.h>
#include <pthread.h>

LogServer* LogServer::s_pLogServer = NULL;

LogServer::LogServer()
{
	m_tmpBuf = NULL;
	m_pTcpClient = NULL;
	m_pStreamBuff = NULL;
}

LogServer::~LogServer()
{
}

LogServer* LogServer::Instance()
{
	if (!s_pLogServer)
		s_pLogServer = new LogServer();
	return s_pLogServer;
}

void LogServer::Init()
{
	m_strIp = "pvz2logandroid.intelligent.popcap.com.cn";
	m_port = 4346;
	Sexy::LaunchThread(Thread_fun, this, (Sexy::SexyThreadPriority)2);
	printf("LogServer::Init() ip = %s", m_strIp.c_str());
}

void LogServer::Start()
{
	Init();
	puts("log start ");
}

void LogServer::Stop()
{
	pthread_mutex_lock(&m_stMutex);
	m_stop = true;
	pthread_cond_signal(&m_stCond);
	pthread_mutex_unlock(&m_stMutex);
	puts("log stop");
}

void LogServer::Clean()
{
	SAFE_DELETE(m_pStreamBuff);
	SAFE_DELETE(m_pTcpClient);
	if (m_tmpBuf)
	{
		delete[] m_tmpBuf;
		m_tmpBuf = NULL;
	}
}

void LogServer::Update()
{
	if (m_pTcpClient && m_pStreamBuff)
	{
		DeermineBlock();
		pthread_mutex_lock(&m_stMutex);
		int len = m_pStreamBuff->CheckGetAPackage(m_tmpBuf + 2, (unsigned short)(TMP_BUF_LEN - 2));
		pthread_mutex_unlock(&m_stMutex);
		if (len > 0)
			m_pTcpClient->SentMsg(m_tmpBuf, len + 2);
	}
}

void LogServer::SendMsg()
{
	if (m_pTcpClient && m_pStreamBuff && !m_stop)
	{
		m_sendMsg += "\n";
		SendMsg(m_sendMsg.c_str(), m_sendMsg.length());
		m_sendMsg.clear();
	}
}

LogServer& LogServer::AppendMsg(std::string msg)
{
	if (m_pTcpClient && m_pStreamBuff)
	{
		m_sendMsg += msg;
		m_sendMsg += "|";
	}
	return *this;
}

void LogServer::Init(const char* logServerAddr, unsigned short port)
{
	m_pTcpClient = new TcpClient();
	m_pStreamBuff = new StreamBuffer(TMP_BUF_LEN);
	m_tmpBuf = new char[TMP_BUF_LEN];
	memset(m_tmpBuf, 0, TMP_BUF_LEN);

	if (m_pTcpClient->InitSocket(logServerAddr, port) < 0)
		puts(" erro =================  tcp socket init failed");

	pthread_cond_init(&m_stCond, NULL);
	pthread_mutex_init(&m_stMutex, NULL);
	m_stop = false;
	m_bThradRun = true;
}

bool LogServer::InitNetSocket()
{
	struct hostent* host = gethostbyname(m_strIp.c_str());
	if (host == NULL)
	{
		puts("LogServer::Init() failed");
		return false;
	}

	Init(inet_ntoa(*(struct in_addr*)host->h_addr_list[0]), m_port);
	return true;
}

bool LogServer::SendMsg(const char* buff, unsigned short len)
{
	if (m_pTcpClient == NULL || m_pStreamBuff == NULL)
		return false;

	pthread_mutex_lock(&m_stMutex);
	bool ret = m_pStreamBuff->PushAPacket(buff, len);
	pthread_cond_signal(&m_stCond);
	pthread_mutex_unlock(&m_stMutex);
	return ret;
}

void LogServer::updateLogServerAddress()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_SERVER_CONFIG);
	LogServerConfig* cfg = table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("LogServerConfig"))))->CastChecked<LogServerConfig>();
	m_strIp = cfg->ShippingLogServerIp;
	m_port = cfg->LogServerPort;
	printf("LogServer::updateLogServerAddress() ip = %s", m_strIp.c_str());
	Sexy::OutputDebugStrF("LogServer::updateLogServerAddress() ip = %s", m_strIp.c_str());
}

void LogServer::DeermineBlock()
{
	if (m_pTcpClient == NULL)
		return;

	pthread_mutex_lock(&m_stMutex);

	unsigned int len = 0;
	char ret[64];
	while (m_pStreamBuff->GetBufReadStart(len) == NULL || m_stop)
	{
		if (m_stop && len == 0)
		{
			Clean();
			pthread_exit(ret);
		}
		pthread_cond_wait(&m_stCond, &m_stMutex);
	}

	pthread_mutex_unlock(&m_stMutex);
}

void LogServer::SendFakderNewUUI(const std::string& uuId, const std::string& newUUid)
{
	LogServer::Instance()->AppendMsg("fakernew_1").AppendMsg(uuId).AppendMsg(Sexy::gSexyAppBase->mProductVersion).AppendMsg(newUUid);
	LogServer::Instance()->AppendMsg(Android::Util::GetPackageName());
	LogServer::Instance()->SendMsg();
}

void LogServer::SendFakeInfo(const std::string& uuId, int fakeCode, int lastRechargeGems, int lastFreeGems, int lastCoins)
{
	std::stringstream ss;
	ss << fakeCode;
	LogServer::Instance()->AppendMsg("fake_1").AppendMsg(uuId).AppendMsg(Sexy::gSexyAppBase->mProductVersion).AppendMsg(ss.str());
	ss.str("");
	ss << lastRechargeGems;
	LogServer::Instance()->AppendMsg(ss.str());
	ss.str("");
	ss << lastFreeGems;
	LogServer::Instance()->AppendMsg(ss.str());
	ss.str("");
	ss << lastCoins;
	LogServer::Instance()->AppendMsg(ss.str());
	LogServer::Instance()->AppendMsg(Android::Util::GetPackageName());
	LogServer::Instance()->SendMsg();
}
