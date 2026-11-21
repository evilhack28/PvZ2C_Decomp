//
//  OfflineBoardMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "OfflineBoard.h"
#include "PVZDB.h"
#include "ServerConfig.h"

/////////////// Lifecycle ///////////////

OfflineBoardMgr::~OfflineBoardMgr()
{
}

/////////////// Logic ///////////////

void OfflineBoardMgr::CheckForNotice()
{
	m_currentIndex = 0;
	m_infoList.clear();
	TryRequest();
}

void OfflineBoardMgr::TryRequest()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_SERVER_CONFIG);
	UpdateServerConfig* cfg = table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("UpdateServerConfig"))))->CastChecked<UpdateServerConfig>();
	std::string baseUrl = cfg->GetUpdateURL();
	if (baseUrl[baseUrl.size() - 1] != '/')
		baseUrl += "/";
	baseUrl += "profile/";
	std::string fileName = Sexy::StrFormat("pvz2_nb_%d.txt", m_currentIndex + 1);
	Sexy::StructuredData request;
	request.BeginObject();
	request.AddString("url", baseUrl + fileName);
	request.AddInteger("timeout", 10);
	request.EndObject();
	Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&request, this, this);
}
