//
//  OnlineDataPersistor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "OnlineDataPersistor.h"
#include "PlayerIdentityService.h"
#include "PlayerInfoDeltaHandler.h"
#include "SexyAppFramework/StructuredData.h"

// own section: the game reaches it with a bare adrp/add, not an anchor+offset
static const std::string kSaveDeltaRequestType __attribute__((section(".bss.savedelta"))) = "savedelta";

/////////////// OnlineDataPersistor ///////////////

OnlineDataPersistor::OnlineDataPersistor(ServerConfigGetter& serverConfigGetter, PlayerIdentityService& playerIdentityService, IDataPersistor& offlineDataPersistor, PlayerInfoDeltaHandler& theHandler)
	: NetworkRequestor(serverConfigGetter, kSaveDeltaRequestType)
	, m_playerIdentityService(playerIdentityService)
	, m_offlineDataPersistor(offlineDataPersistor)
	, m_deltaHandler(theHandler)
	, m_loadListener(offlineDataPersistor)
	, m_saveListener(m_deltaHandler)
{
}

void OnlineDataPersistor::Load()
{
	m_offlineDataPersistor.Load();
	makeRequest(m_loadListener);
}

void OnlineDataPersistor::LoadWithNotify()
{
	Load();
}

bool OnlineDataPersistor::Save()
{
	bool result = m_offlineDataPersistor.Save();
	makeRequest(m_saveListener);
	return result;
}

bool OnlineDataPersistor::isWaitingForResponse()
{
	return m_loadListener.IsBlocked() || m_saveListener.IsBlocked();
}

std::string OnlineDataPersistor::dataAsJson(Sexy::RtSerialRtonWriter& i_rtWriter)
{
	std::string json;
	Sexy::RtSerial::RtonToJson(i_rtWriter.GetBuffer()->GetDataPtr(), i_rtWriter.GetBuffer()->GetDataSize(), json, false);
	return json;
}

void OnlineDataPersistor::addArguments(Sexy::StructuredData& request)
{
	m_deltaHandler.CreateDelta();
	request.AddString("account", m_playerIdentityService.GetAccount().c_str());
}
