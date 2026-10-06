//
//  DataPersistorFactory.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "DataPersistorFactory.h"

OfflineDataPersistor& DataPersistorFactory::getOffline()
{
	return m_offlineDataPersistor;
}

PlayerInfoDeltaHandler& DataPersistorFactory::GetDeltaHandler()
{
	return m_playerInfoDeltaHandler;
}

OnlineDataPersistor& DataPersistorFactory::getOnline()
{
	return m_onlineDataPersistor;
}

DataPersistorFactory::DataPersistorFactory(const NetworkStatusDecider& networkStatusDecider, ServerConfigGetter& serverConfigGetter, PlayerIdentityService& playerIdentityService)
	: m_offlineDataPersistor("pp.dat", PVZDB::TABLE_PLAYER_PROFILES)
	, m_playerInfoDeltaHandler()
	, m_onlineDataPersistor(serverConfigGetter, playerIdentityService, m_offlineDataPersistor, m_playerInfoDeltaHandler)
	, m_serverConfigGetter(serverConfigGetter)
	, m_networkStatusDecider(networkStatusDecider)
{
}

IDataPersistor& DataPersistorFactory::GetPersistor()
{
	return getOffline();
}

IDataPersistor& DataPersistorFactory::GetOfflinePersistor()
{
	return getOffline();
}

OnlineDataPersistor& DataPersistorFactory::GetOnlinePersistor()
{
	return getOnline();
}
