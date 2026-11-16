//
//  PVZRechargeCheckServer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "PVZRechargeCheckServer.h"

#include <climits>
#include <cstring>
#include <ctime>

#include "GameEventMgr.h"
#include "ProfileMgr.h"
#include "ServerConfig.h"
#include "UIEditor/StringHelper.h"
#include "gameNetWork/pcpEncrypty/PCPEncrypt.h"
#include "logServer/md5.h"

template <class T> T SafeTransferFromInt64(int64 src_value, T target_type_max)
{
	return static_cast<T>(src_value);
}


PVZRechargeCheckServer::PVZRechargeCheckServer()
	: m_playerRechargeAmount(-1)
	, m_playerGetFreeAmount(-1)
{
	m_randomSeed = 0;
	m_retriesLeft = 0;
	m_isHacker = false;
}

void PVZRechargeCheckServer::RequestRechargeCheck(int i_retries)
{
	if (m_randomSeed != 0)
		return;
	m_retriesLeft = i_retries;
	TryRequest();
}

void PVZRechargeCheckServer::ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context)
{
	if (i_context != this)
		return;
	Sexy::OutputDebugStrF("PVZRechargeCheckServer::ServiceRequestFailed error");
	TryRequest();
}

void PVZRechargeCheckServer::ServiceRequestCompleted(ImageLib::Image*&, const void* i_context)
{
	if (i_context == this)
		TryRequest();
}

void PVZRechargeCheckServer::ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context)
{
	if (i_context == this)
		TryRequest();
}

int32 PVZRechargeCheckServer::GetPlayerRechargeAmount()
{
	return m_playerGetFreeAmount + m_playerRechargeAmount;
}

int32 PVZRechargeCheckServer::GetFreeGemAmount()
{
	return m_playerGetFreeAmount;
}

int32 PVZRechargeCheckServer::GetRechargeGemAmount()
{
	return m_playerRechargeAmount;
}

void PVZRechargeCheckServer::ResetGemAmount()
{
	m_isHacker = false;
	m_playerGetFreeAmount = -1;
	m_playerRechargeAmount = -1;
}

bool PVZRechargeCheckServer::IsHacker()
{
	return m_isHacker;
}

void PVZRechargeCheckServer::TryRequest()
{
	if (m_retriesLeft < 0)
	{
		OnRequestFinished("");
		return;
	}

	std::string req = "V1";
	std::string accountName = ProfileMgr::GetInstance().GetAccountName();

	Sexy::SRand(time(NULL));
	m_randomSeed = Sexy::Rand();

	std::string s = Sexy::StrFormat("%s%dA7198D8B54ABE", accountName.c_str(), m_randomSeed);
	s = MD5(s).toString();

	std::string json;
	json = "{";
	json += " \"uu\" : \"" + accountName + "\",";
	json += " \"s\" : \"" + s + "\",";
	json += Sexy::StrFormat(" \"r\" : %d", m_randomSeed);
	json += "}";

	std::string e = "ila&master" + req;
	e = MD5(e).toString();

	char iv[32] = { 0 };
	memcpy(iv, e.c_str() + 1, 24);

	std::string encrypted = PCPEncryptStr(json.c_str(), json.length(), e.c_str(), iv);

	Sexy::StructuredData data;
	data.BeginObject();
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_SERVER_CONFIG);
	RechargeCheckConfig* cfg = table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("RechargeCheckConfig"))))->CastChecked<RechargeCheckConfig>();
	data.AddString("url", cfg->ShippingCheckServerURL);
	data.AddInteger("timeout", 30);
	data.BeginObject("formData");
	data.AddString("req", req);
	data.AddString("e", encrypted);
	data.EndObject();
	data.EndObject();
	Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&data, this, this);
	m_retriesLeft--;
}

void PVZRechargeCheckServer::OnRequestFinished(std::string i_json)
{
	if (i_json == "")
	{
		m_randomSeed = 0;
		gMessageRouter->Post(&Message::RechargeCheckOnServerComplete);
		return;
	}

	Sexy::StructuredData data;
	StringHelper::ReadJson(i_json, &data);
	const Sexy::StructuredData::Value* v = data.ObjectForPath("$.d");
	if (v)
	{
		m_playerGetFreeAmount = SafeTransferFromInt64(v->IntegerForPath(".f", -1), INT_MAX);
		m_playerRechargeAmount = SafeTransferFromInt64(v->IntegerForPath(".c", -1), INT_MAX);
		m_isHacker = v->IntegerForPath(".b", -1) == 1;

		std::string s = v->StringForPath(".s", "");
		std::string sign = Sexy::StrFormat("%d%d%dEA82E706D5A67", m_playerGetFreeAmount, m_playerRechargeAmount, m_randomSeed);
		sign = MD5(sign).toString();
		if (s == "" || s != sign)
		{
			m_isHacker = false;
			m_playerGetFreeAmount = -1;
			m_playerRechargeAmount = -1;
		}
	}

	m_randomSeed = 0;
	gMessageRouter->Post(&Message::RechargeCheckOnServerComplete);
}

void PVZRechargeCheckServer::ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context)
{
	if (i_context != this)
		return;

	Sexy::StructuredData::String reqId = i_response->StringForPath("$.i", "none");
	if ("V1" != std::string(reqId))
	{
		Sexy::OutputDebugStrF("PVZRechargeCheckServer::ServiceRequestCompleted reqId = [%s]", reqId);
		ServiceRequestFailed(i_response, this);
		return;
	}

	Sexy::StructuredData::Integer result = i_response->IntegerForPath("$.r", -1);
	if (result != 0)
	{
		Sexy::OutputDebugStrF("PVZRechargeCheckServer::ServiceRequestCompleted result = [%d]", result);
		ServiceRequestFailed(i_response, this);
		return;
	}

	Sexy::StructuredData::String encrypted = i_response->StringForPath("$.e", "none");

	char buff[256];
	memset(buff, 0, 256);

	if ("none" != std::string(encrypted))
	{
		std::string e = "ila&master" + std::string(reqId);
		e = MD5(e).toString();

		char iv[32] = { 0 };
		memcpy(iv, e.c_str() + 1, 24);

		PCPDecrypt(encrypted, buff, 256, e.c_str(), iv);
	}

	std::string json = buff;
	OnRequestFinished(json);
}
