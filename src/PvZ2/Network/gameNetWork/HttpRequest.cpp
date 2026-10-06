//
//  HttpRequest.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-03.
//

#include "gameNetWork/HttpRequest.h"

#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/events/NetWorkEvent.h"

const std::string HttpRequest::EmptyUrl;

HttpRequest::HttpRequest()
{
	_NetworkEventConfig config;
	m_Url = config.URL;
}

HttpRequest::~HttpRequest()
{
}

void HttpRequest::ServiceRequestCompleted(const Sexy::StructuredData* response, const void* context)
{
	if (context == this)
	{
		Sexy::AutoCrit lock(mHttpRequestCS);
		m_Buff.Clear();
		response->WriteToBuffer(&m_Buff);
		NetworkMgr::ReceivedMsgCallback(m_Buff.GetDataPtr(), m_Buff.GetDataLen());
	}
}

void HttpRequest::ServiceRequestFailed(const Sexy::StructuredData* response, const void* context)
{
	if (context != this)
		return;

	_PacketId packetId;
	Sexy::AutoCrit lock(mHttpRequestCS);
	m_Buff.Clear();

	Sexy::StructuredData data;
	data.BeginObject();
	std::string req = response->StringForPath("$.req", "");
	if (req != "V202")
		data.AddString("i", packetId.ID_LOCAL_MSG_ID);
	else
		data.AddString("i", req);
	data.AddString("req", req);
	data.AddInteger("r", -1);
	data.EndObject();

	data.WriteToBuffer(&m_Buff);
	NetworkMgr::ReceivedMsgCallback(m_Buff.GetDataPtr(), m_Buff.GetDataLen());
}

void HttpRequest::StartRequest(std::string& req, std::string& content, const std::string& strUrl)
{
	if (req.empty())
		return;
	if (req[0] == 'P')
		return;

	std::string url(strUrl);
	if (url.empty())
	{
		_NetworkEventConfig config;
		if (req[0] == 'P')
			url = config.PVPURL;
		else if (req[0] == 'C')
			url = config.UUIDURL;
		else
			url = config.URL;
	}

	Sexy::StructuredData data;
	data.BeginObject();
	data.AddString("trace", "VerifyReceipt11");
	data.AddString("url", url);
	data.BeginObject("formData");
	data.AddString("req", req);
	data.AddString("e", content);
	data.AddInteger("ev", 1);
	data.EndObject();
	if (req == "V219")
		data.AddInteger("timeout", 100);
	data.EndObject();

	Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&data, this, this);
}
