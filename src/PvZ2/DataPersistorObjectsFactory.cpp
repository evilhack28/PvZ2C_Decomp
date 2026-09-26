//
//  DataPersistorObjectsFactory.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DataPersistorObjectsFactory.h"
#include "GameEventMgr.h"
#include "ICloudWrapperFactory.h"
#include "UserPrefsWrapper.h"

DataPersistorObjectsFactory::~DataPersistorObjectsFactory()
{
}

DataPersistorFactory& DataPersistorObjectsFactory::GetDataPersistorFactory()
{
	return m_dataPersistorFactory;
}

PlayerIdentityService& DataPersistorObjectsFactory::GetPlayerIdentityService()
{
	return m_playerIdentityService;
}

DataPersistorObjectsFactory::DataPersistorObjectsFactory()
	: m_iCloudWrapper(ICloudWrapperFactory::CreateInstance())
	, m_uuidCreator()
	, m_networkStatusDecider()
	, m_serverConfigGetter()
	, m_playerIdentityService(m_iCloudWrapper, m_uuidCreator, UserPrefsWrapper::GetInstance(), *gMessageRouter)
	, m_dataPersistorFactory(m_networkStatusDecider, m_serverConfigGetter, m_playerIdentityService)
{
}
