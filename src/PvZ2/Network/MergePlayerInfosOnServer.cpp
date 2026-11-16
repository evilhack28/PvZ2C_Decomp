//
//  MergePlayerInfosOnServer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//
/////////////// MergePlayerInfosOnServer ///////////////

#include "SexyAppFramework/Common.h"
#include "MergePlayerInfosOnServer.h"
#include "GameEventMgr.h"

static const std::string kMergeRequestType = "merge";

MergePlayerInfosOnServer::MergePlayerInfosOnServer(MessageRouter& i_messageRouter, ServerConfigGetter& serverConfigGetter)
	: NetworkRequestor(serverConfigGetter, kMergeRequestType)
	, m_serviceListener(i_messageRouter)
{
	i_messageRouter.Subscribe(&Message::BindAskForMerge, Sexy::MakeDelegate(*this, &MergePlayerInfosOnServer::onBindAskForMerge));
}

void MergePlayerInfosOnServer::onBindAskForMerge(const Sexy::StructuredData* i_response)
{
	m_boundPcpId = i_response->StringForPath("$.boundpcpid", "");
	m_requestedPcpId = i_response->StringForPath("$.requestedpcpid", "");
}

bool MergePlayerInfosOnServer::isWaitingForResponse()
{
	return m_serviceListener.IsBlocked();
}

void MergePlayerInfosOnServer::addArguments(Sexy::StructuredData& request)
{
	request.BeginArray("pcpids");
	request.AddString(m_boundPcpId.c_str());
	request.AddString(m_requestedPcpId.c_str());
	request.EndArray();
}
