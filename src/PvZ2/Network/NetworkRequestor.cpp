//
//  NetworkRequestor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "NetworkRequestor.h"
#include "ServerConfig.h"
#include "FakeHttpDriver.h"
#include "PvZ2NetworkServiceListener.h"
#include "SexyAppFramework/NetworkServiceManager.h"
#include "SexyAppFramework/StructuredData.h"

/////////////// NetworkRequestor ///////////////

NetworkRequestor::NetworkRequestor(ServerConfigGetter& serverConfigGetter, const std::string& requestType)
	: m_HttpDriverForTest(FakeHttpDriver::GetInstance()), m_serverConfigGetter(serverConfigGetter), m_requestType(requestType)
{
}

void NetworkRequestor::makeRequest(PvZ2NetworkServiceListener& listener)
{
	if (isWaitingForResponse())
	{
		return;
	}
	Sexy::StructuredData request;
	request.BeginObject();
	request.AddString("url", m_serverConfigGetter.IP().c_str());
	request.BeginObject("postData");
	request.AddString("execute", m_requestType.c_str());
	addArguments(request);
	request.EndObject();
	request.EndObject();
	sendRequest(&request, &listener);
}

void NetworkRequestor::sendRequest(Sexy::StructuredData* request, PvZ2NetworkServiceListener* listener)
{
	listener->SetBlocked();
	Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(request, listener, listener);
}

NetworkRequestor::~NetworkRequestor()
{
}
