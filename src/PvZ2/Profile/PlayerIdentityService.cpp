//
//  PlayerIdentityService.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlayerIdentityService.h"
#include "UUIDCreator.h"
#include "UserPrefsWrapper.h"
#include "FakeHttpDriver.h"
#include "ICloudWrapper.h"
#include "GameEventMgr.h"
#include "StringHelper.h"
#include "IdentityMessages.h"

extern pthread_mutex_t mutex;

/////////////// Lifecycle ///////////////

PlayerIdentityService::PlayerIdentityService(ICloudWrapper& iCloudWrapper, UUIDCreator& i_uuidCreator, UserPrefsWrapper& i_userPrefsWrapper, MessageRouter& i_messageRouter)
	: m_HttpDriverForTest(FakeHttpDriver::GetInstance())
	, m_iCloudWrapper(iCloudWrapper)
	, m_UUIDCreator(i_uuidCreator)
	, m_userPrefsWrapper(i_userPrefsWrapper)
	, m_messageRouter(i_messageRouter)
{
	i_messageRouter.Subscribe(&Message::UpdateAccountId, Sexy::MakeDelegate(*this, &PlayerIdentityService::onUpdateAccountID));
	m_iCloudWrapper.SetListener(this);
}

PlayerIdentityService::~PlayerIdentityService()
{
	for (std::vector<Sexy::StructuredData*>::iterator it = m_createdRequests.begin(); it != m_createdRequests.end(); ++it)
	{
		delete *it;
	}
	m_createdRequests.clear();
}

void PlayerIdentityService::Init()
{
	pthread_mutex_init(&mutex, NULL);
	m_iCloudWrapper.start();
}

/////////////// Account ///////////////

std::string PlayerIdentityService::accountStoredLocally()
{
	pthread_mutex_lock(&mutex);
	std::string account = m_userPrefsWrapper.GetString(PCPID_KEY, "");
	if (account.empty())
	{
		account = m_userPrefsWrapper.GetStringEx(PCPID_KEY, "");
		if (account.empty())
		{
			account = m_UUIDCreator.Create();
			m_userPrefsWrapper.SetString(PCPID_KEY, account);
		}
	}
	pthread_mutex_unlock(&mutex);
	return account;
}

void PlayerIdentityService::accountStoredInKvStore()
{
	pthread_mutex_lock(&mutex);
	std::string key = PCPID_KEY;
	std::string iCloudAccountId = m_iCloudWrapper.GetStringValue(key);
	std::string userPrefsAccountId = m_userPrefsWrapper.GetString(PCPID_KEY, "");
	if (iCloudAccountId.empty())
	{
		if (userPrefsAccountId.empty())
		{
			userPrefsAccountId = m_UUIDCreator.Create();
		}
		m_userPrefsWrapper.SetString(PCPID_KEY, userPrefsAccountId);
		m_iCloudWrapper.StoreStringValue(key, userPrefsAccountId);
	}
	else
	{
		m_userPrefsWrapper.SetString(PCPID_KEY, iCloudAccountId);
		if (!userPrefsAccountId.empty() && iCloudAccountId.compare(userPrefsAccountId) != 0)
		{
			postMergeRequest(iCloudAccountId, userPrefsAccountId);
		}
	}
	pthread_mutex_unlock(&mutex);
}

void PlayerIdentityService::onUpdateAccountID(const Sexy::StructuredData* i_response)
{
	std::string account = i_response->StringForPath("$.pcpid", "NOPCPID");
	if (account.compare("NOPCPID") != 0)
	{
		m_userPrefsWrapper.SetString(PCPID_KEY, i_response->StringForPath("$.pcpid", GetAccount().c_str()));
		m_messageRouter.Post(&Message::AccountIdChanged);
	}
}

void PlayerIdentityService::postMergeRequest(const std::string& i_iCloudAccountId, const std::string& i_userPrefsAccountId)
{
	Sexy::StructuredData* request = new Sexy::StructuredData();
	std::string json = "{\"boundpcpid\":\"" + i_iCloudAccountId + "\",\"requestedpcpid\":\"" + i_userPrefsAccountId + "\"}";
	StringHelper::ReadJson(json, request);
	m_createdRequests.push_back(request);
	m_messageRouter.Post(&Message::BindAskForMerge, request);
}

std::string PlayerIdentityService::GetAccount()
{
	return accountStoredLocally();
}

std::string PlayerIdentityService::CreateNewId()
{
	std::string id = m_UUIDCreator.Create();
	m_userPrefsWrapper.SetString(PCPID_KEY, id);
	return id;
}

/////////////// ICloudListener ///////////////

void PlayerIdentityService::iCloudDataInitialSyncChange()
{
	accountStoredInKvStore();
}

void PlayerIdentityService::iCloudDidFinishInitialization()
{
	accountStoredInKvStore();
}

void PlayerIdentityService::iCloudAccountDidSignInFirstTime()
{
	accountStoredInKvStore();
}

void PlayerIdentityService::iCloudDataServerChangeWithChangedKeys(const char** keys)
{
	accountStoredInKvStore();
}
