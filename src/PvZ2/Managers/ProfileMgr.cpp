//
//  ProfileMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include <sstream>
#include "SexyAppFramework/Common.h"

#include "ProfileMgr.h"
#include "DataPersistorFactory.h"
#include "PlayerIdentityService.h"
#include "PVZDB.h"
#include "LawnApp.h"
#include "WorldMap.h"
#include "DataPersistorObjectsFactory.h"
#include "Throttles.h"
#include "TimeMgr.h"
#include "IdentityMessages.h"
#include "AuthMgr.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "gameNetWork/androidNetworkMsgProcess.h"
#include "SexyAppFramework/ResourceManager.h"
#include "logServer/LogServer.h"
#include "DraperSaveData.h"
#include "PvZ/TodLib/TodStringFile.h"
#include "IdentifierMgr.h"
#include "DefineIDMgr.h"

int CalReturnGoldBetweenVersionJune25AndAug05(PlayerInfo* i_profile);
void ChangeMapDataForAug05(PlayerInfo* i_profile);

/////////////// Lifecycle ///////////////

ProfileMgr::ProfileMgr()
	: m_dataPersistorFactory(DataPersistorObjectsFactory::GetInstance().GetDataPersistorFactory())
	, m_playerIdentityService(DataPersistorObjectsFactory::GetInstance().GetPlayerIdentityService())
	, m_currentProfileIndex(0)
	, m_lastSaveTime(gTimeMgr->RealT())
	, m_lastCloudSaveTime(gTimeMgr->RealT())
	, m_saveRequested(false)
	, m_readOnlyMode(false)
	, m_previousReadOnlyValue(false)
	, m_profileNameForLoad(L"")
	, m_profileIdForLoad(-1)
	, m_throttles(Throttles::GetInstance())
	, m_onLockdownDuringProfileConversion(false)
	, m_canUpload(false)
	, m_bHasPopulateProfiles(false)
	, m_isSaving(false)
	, m_checkErrorSave(false)
	, m_profileListDirty(true)
	, m_needUpdateUI(false)
	, m_needUpLoad(false)
	, m_wait(false)
	, m_save_interval(120.0f)
{
	m_originalProfile = nullptr;
	gMessageRouter->Subscribe(&Message::ForceReloadData, Sexy::MakeDelegate(*this, &ProfileMgr::forceReload));
}

ProfileMgr::~ProfileMgr()
{
	gMessageRouter->Unsubscribe(this);
	delete m_originalProfile;
}

/////////////// Accessors ///////////////

void ProfileMgr::SetLockdownForProfileConversion()
{
	m_onLockdownDuringProfileConversion = true;
}

bool ProfileMgr::HasValidProfile() const
{
	return m_currentProfileIndex != 0;
}

int ProfileMgr::GetNumProfiles() const
{
	return PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLAYER_PROFILES)->GetRtIdCount();
}

bool ProfileMgr::IsSaveDataExist()
{
	return m_dataPersistorFactory.GetPersistor().IsFileExist();
}

std::string ProfileMgr::GetAccountName()
{
	return m_playerIdentityService.GetAccount();
}

bool ProfileMgr::GetReadOnlyMode()
{
	return m_readOnlyMode;
}

PurchaseBroker* ProfileMgr::GetPurchaseBroker()
{
	return &m_purchaseBroker;
}

/////////////// Logic ///////////////

void ProfileMgr::ReloginiCloudServer()
{
}

void ProfileMgr::Init()
{
	m_playerIdentityService.Init();
}

void ProfileMgr::LoadAndSetProfile(const int i_profileId)
{
	m_profileIdForLoad = i_profileId;
	forceReload();
}

void ProfileMgr::LoadAndSetProfile(const std::wstring& i_profileName)
{
	m_profileNameForLoad = i_profileName;
	forceReload();
}

void ProfileMgr::RemoveLockdownForProfileConversion()
{
	m_onLockdownDuringProfileConversion = false;
	RequestSave();
}

void ProfileMgr::onDialogButtonPressed()
{
	gLawnApp->KillPVZ2Dialog();
}

bool ProfileMgr::hasPopulateProfiles()
{
	return m_bHasPopulateProfiles;
}

void ProfileMgr::SaveResult(bool i_success)
{
	OutputDebugStrF("ProfileMgr::SaveResult i_success= [%d]", i_success);
	if (i_success)
	{
		PlayerInfo* profile = GetCurrentProfile();
		if (profile != nullptr)
			profile->FinishUpdateDeltaDataForServer();
	}
	m_isSaving = false;
}

void ProfileMgr::forceReload()
{
	m_previousReadOnlyValue = GetReadOnlyMode();
	SetReadOnlyMode(false);
	m_dataPersistorFactory.GetOfflinePersistor().LoadWithNotify();
}

void ProfileMgr::RequestSave()
{
	if (!AuthMgr::GetInstance().HasNoAuth())
	{
		if (!m_onLockdownDuringProfileConversion)
		{
			m_saveRequested = true;
			if (!m_readOnlyMode)
			{
				if (!Test::gTestFrameworkIsRunning)
					m_dataPersistorFactory.GetOfflinePersistor().Save();
			}
		}
	}
}

bool ProfileMgr::SyncProfileFromServer()
{
	if (gLawnApp->CheckProfileOpen())
		return static_cast<androidNetworkMsgProcess*>(NetworkMgr::Instance()->GetNewNetWorkProcess())->RequestDownloadPlayerData();
	return NetworkMgr::Instance()->GetNewNetWorkProcess()->ICloudRequestGetProfile();
}

void ProfileMgr::SetReadOnlyMode(bool i_status)
{
	if (i_status)
	{
		if (!m_readOnlyMode)
			m_originalProfile = new PlayerInfo(*GetCurrentProfile());
	}
	else if (m_readOnlyMode)
	{
		delete m_originalProfile;
		m_originalProfile = nullptr;
	}
	m_readOnlyMode = i_status;
}

ProfileMgr::PROFILE_ERR ProfileMgr::RenameProfile(const std::wstring& i_oldName, const std::wstring& i_newName)
{
	PROFILE_ERR result = PROFILE_NOT_FOUND;
	PlayerInfoPtr profile = FindProfile(i_oldName);
	if (profile)
	{
		profile->SetName(i_newName);
		Save(false, false);
		result = PROFILE_OK;
	}
	return result;
}

PlayerInfoPtr ProfileMgr::FindProfile(const std::wstring& i_name)
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo->GetName() == i_name)
			return playerInfo;
	}
	return PlayerInfoPtr();
}

PlayerInfoPtr ProfileMgr::FindProfile(const int profileId)
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo->GetProfileId() == profileId)
			return playerInfo;
	}
	return PlayerInfoPtr();
}

PlayerInfoPtr ProfileMgr::FindProfileByIndex(long i_index)
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo->GetProfileIndex() == i_index)
			return playerInfo;
	}
	return PlayerInfoPtr();
}

PlayerInfoPtr ProfileMgr::FindProfileByIndex(int32_t i_index)
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo->GetProfileIndex() == i_index)
			return playerInfo;
	}
	return PlayerInfoPtr();
}

PlayerInfoPtr ProfileMgr::CreateProfile(const std::wstring& i_name)
{
	Sexy::RtId id = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLAYER_PROFILES)->AllocId(PlayerInfo::StaticGetClass()->New()->CastChecked<PlayerInfo>(), Sexy::RtDbTable::ODM_Auto, true, NULL);
	PlayerInfoPtr profile(id);
	profile->SetName(i_name);
	profile->SetProfileIndex(time(NULL));
	InitializeProfile(profile.Get());
	m_currentProfileIndex = profile->GetProfileIndex();
	m_profileListDirty = true;
	if (gLawnApp->CheckProfileOpen())
		Save(false, true);
	gMessageRouter->Post(&Message::ProfileCreated, profile);
	return profile;
}

PlayerInfoPtr ProfileMgr::DuplicateProfile(const PlayerInfo* i_existingProfile, const std::wstring& i_newName)
{
	PlayerInfoPtr existing = FindProfile(i_newName);
	if (existing)
		DeleteProfile(i_newName);
	PlayerInfoPtr profile = CreateProfile(i_newName);
	PlayerInfo* info = profile.operator->();
	*info = *i_existingProfile;
	info->SetName(i_newName);
	info->SetProfileIndex(time(NULL));
	m_currentProfileIndex = info->GetProfileIndex();
	return profile;
}

ProfileMgr::PROFILE_ERR ProfileMgr::DeleteProfile(const std::wstring& i_name)
{
	PROFILE_ERR result = PROFILE_NOT_FOUND;
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLAYER_PROFILES);
	PlayerInfoPtr profile = FindProfile(i_name);
	if (profile)
	{
		gMessageRouter->Post(&Message::ProfileAboutToBeDeleted, profile);
		table->ReleaseId(profile);
		if (table->GetRtIdCount() == 0)
		{
			m_currentProfileIndex = 0;
			result = PROFILE_NO_PROFILE;
		}
		else
		{
			setAnyProfileAsCurrent();
			result = PROFILE_OK;
			Save(false, false);
		}
	}
	return result;
}

ProfileMgr::PROFILE_ERR ProfileMgr::DeleteProfile(const int profileId)
{
	PROFILE_ERR result = PROFILE_NOT_FOUND;
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLAYER_PROFILES);
	PlayerInfoPtr profile = FindProfile(profileId);
	if (profile)
	{
		gMessageRouter->Post(&Message::ProfileAboutToBeDeleted, profile);
		table->ReleaseId(profile);
		if (table->GetRtIdCount() == 0)
		{
			m_currentProfileIndex = 0;
			result = PROFILE_NO_PROFILE;
			m_profileListDirty = true;
		}
		else
		{
			setAnyProfileAsCurrent();
			result = PROFILE_OK;
			Save(false, false);
		}
	}
	return result;
}

void ProfileMgr::ClearAllProfile()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		DeleteProfile(playerInfo->GetProfileId());
	}
	m_currentProfileIndex = 0;
	m_profileListDirty = true;
}

ProfileMgr::PROFILE_ERR ProfileMgr::SetCurrentProfile(const std::wstring& i_name)
{
	PROFILE_ERR result = PROFILE_NOT_FOUND;
	PlayerInfoPtr profile = FindProfile(i_name);
	if (profile)
	{
		m_currentProfileIndex = profile->GetProfileIndex();
		profile->SetCrashContext();
		result = PROFILE_OK;
	}
	return result;
}

ProfileMgr::PROFILE_ERR ProfileMgr::SetCurrentProfile(const int profileId)
{
	PROFILE_ERR result = PROFILE_NOT_FOUND;
	PlayerInfoPtr profile = FindProfile(profileId);
	if (profile)
	{
		m_currentProfileIndex = profile->GetProfileIndex();
		m_profileListDirty = true;
		profile->SetCrashContext();
		result = PROFILE_OK;
	}
	else
		m_profileListDirty = true;
	return result;
}

bool ProfileMgr::UpdateCurrentProfile()
{
	bool result = m_profileListDirty;
	if (result)
	{
		result = false;
		if (m_currentProfileIndex == 0)
		{
			m_profileListDirty = result;
			m_needUpdateUI = true;
			Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES);
			result = it;
			if (result)
			{
				PlayerInfoPtr playerInfo(*it);
				m_currentProfileIndex = playerInfo->GetProfileIndex();
				return result;
			}
		}
	}
	return result;
}

ProfileMgr::PROFILE_ERR ProfileMgr::setAnyProfileAsCurrent()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		SetCurrentProfile(playerInfo->GetName());
		return PROFILE_OK;
	}
	return PROFILE_NOT_FOUND;
}

PlayerInfo* ProfileMgr::GetCurrentProfile()
{
	if (m_currentProfileIndex == 0)
	{
		static PlayerInfo s_defaultProfile;
		m_currentProfileIndex = s_defaultProfile.GetProfileIndex();
		return &s_defaultProfile;
	}

	PlayerInfoPtr firstProfile;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (!firstProfile.IsValid())
			firstProfile = playerInfo;
		if (playerInfo->GetProfileIndex() == m_currentProfileIndex)
			return playerInfo;
	}
	return firstProfile;
}

void ProfileMgr::InitializeProfile(PlayerInfo* i_profile)
{
	i_profile->InitializeSavedValues();
	i_profile->GenerateRandomSeed();
	Sexy::RtId id = PVZDB::GetInstance().GetIdByAlias(PVZDB::TABLE_PROPERTYSHEETS, Sexy::RtName(_S("DefaultPlayerProfileProps")));
	Sexy::RtWeakPtr<PlayerProfileProperties> propsPtr(id);
	PlayerProfileProperties* props = propsPtr;
	if (props)
	{
		size_t i = 0;
		if (props->InitialPlantList.size() != 0)
		{
			while (i++ < props->InitialPlantList.size())
			{
				i_profile->UnlockPlant(props->InitialPlantList[i - 1], true);
				i_profile->AddPlantStartLevel(props->InitialPlantList[i - 1], 0);
			}
		}
	}
	i_profile->SetMapConversionState(MAPCONVERSION_NotNeeded);
}

void ProfileMgr::Save(bool i_bwait, bool i_forceSave)
{
	if (AuthMgr::GetInstance().HasNoAuth())
		return;

	if (gLawnApp->CheckProfileOpen())
	{
		if (!NetworkMgr::Instance()->GetNewNetWorkProcess()->IsLogined())
		{
			LoginiCloudServer();
			return;
		}
		if (m_readOnlyMode)
			return;
		if (m_onLockdownDuringProfileConversion)
			return;
		m_needUpLoad = i_forceSave;
		if (i_bwait && !m_wait)
			m_wait = true;
		return;
	}
	else
	{
		m_saveRequested = false;
		if (m_readOnlyMode || m_onLockdownDuringProfileConversion)
		{
			OutputDebugStrF("Cheat Check - ProfileMgr::Save -1");
			return;
		}
		OutputDebugStrF("Cheat Check - ProfileMgr::Save 0");
		PlayerInfo* profile = GetCurrentProfile();
		if (profile == nullptr || gLawnApp->isSyncProfileSuccess())
		{
			m_needUpLoad = true;
		}
		else
		{
			OutputDebugStrF("Cheat Check - ProfileMgr::Save 1");
			if (gLawnApp->IsNetworkModuleOK())
			{
				OutputDebugStrF("Cheat Check - ProfileMgr::Save 2");
				if (!gLawnApp->getProfileConnected())
				{
					OutputDebugStrF("Cheat Check - ProfileMgr::Save 3");
					if (gLawnApp->canDealProfile() && !gLawnApp->isProfileSyncing())
					{
						OutputDebugStrF("Cheat Check - ProfileMgr::Save 4");
						gLawnApp->setProfileSyncing(true);
						gLawnApp->syncProfileSummaryWithServer();
					}
				}
				else
				{
					OutputDebugStrF("Cheat Check - ProfileMgr::Save 6");
					if (profile->IsOlderThanServerData())
					{
						OutputDebugStrF("Cheat Check - ProfileMgr::Save 7");
						if (!gLawnApp->isProfileOpened() && gLawnApp->canDealProfile())
						{
							if (gLawnApp->GetWorldMap()->IsUserInputEnabled())
							{
								OutputDebugStrF("Cheat Check - ProfileMgr::Save 8");
								gLawnApp->showDiffProfileSummary();
								gLawnApp->setProfileOpened(true);
							}
						}
					}
				}
			}
			if (!i_forceSave)
				return;
			m_needUpLoad = true;
		}
	}
	if (i_bwait && !m_wait)
		m_wait = true;
}

void ProfileMgr::RealSave()
{
	if (AuthMgr::GetInstance().HasNoAuth())
		return;

	PlayerInfo* profile = GetCurrentProfile();
	if (profile != nullptr)
	{
		profile->UpdateDeltaDataForServer();
		if (profile->IsDiffDeltaDataBetweenServer())
		{
			std::string json;
			std::string md5;
			std::string summary;
			profile->GetDeltaDataForServer(json, md5, summary);
			bool requested;
			if (gLawnApp->CheckProfileOpen())
				requested = static_cast<androidNetworkMsgProcess*>(NetworkMgr::Instance()->GetNewNetWorkProcess())->RequestSyncPlayerData() == E_SYNC_PROFILE_SUCCESS;
			else
				requested = NetworkMgr::Instance()->GetNewNetWorkProcess()->ICloudRequestUpLoadProfile(json, md5, summary, m_wait);
			if (requested)
			{
				if (!m_isSaving)
					m_lastCloudSaveTime = gTimeMgr->RealT();
				m_isSaving = true;
			}
		}
	}
	pvztime_t now = gTimeMgr->RealT();
	m_needUpLoad = false;
	m_wait = false;
	m_lastSaveTime = now;
}

void ProfileMgr::SaveAs(PlayerInfo* i_sourcePlayerInfo, const std::wstring& i_newname)
{
	if (i_sourcePlayerInfo->GetName() == i_newname)
	{
		bool readOnlyMode = m_readOnlyMode;
		m_readOnlyMode = false;
		Save(false, false);
		m_readOnlyMode = readOnlyMode;
		return;
	}

	PlayerInfo* existing = FindProfile(i_newname);
	int profileIndex = -1;
	if (existing != nullptr)
	{
		profileIndex = existing->GetProfileIndex();
		DeleteProfile(Sexy::SexyStringToWString(i_newname));
	}

	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLAYER_PROFILES);
	Sexy::RtId id = table->AllocId(new PlayerInfo(*i_sourcePlayerInfo), Sexy::RtDbTable::ODM_Auto, true, NULL);
	PlayerInfoPtr newProfile(id);
	static_cast<PlayerInfo*>(newProfile.GetObject())->SetName(i_newname);
	if (profileIndex >= 0)
		static_cast<PlayerInfo*>(newProfile.GetObject())->SetProfileIndex(profileIndex);

	if (m_readOnlyMode)
	{
		PlayerInfoPtr current = FindProfile(GetCurrentProfile()->AM_GetName());
		Sexy::RtId currentId = current;
		PlayerInfo* currentObject = current;
		Sexy::RtDbTable::EObjectDeletionMode deletionMode = table->GetObjectDeletionMode(current);
		table->SetObjectDeletionMode(current, Sexy::RtDbTable::ODM_Never);
		table->ReplaceObjectForId(currentId, m_originalProfile);
		m_readOnlyMode = false;
		Save(false, false);
		m_readOnlyMode = true;
		table->ReplaceObjectForId(currentId, currentObject);
		table->SetObjectDeletionMode(current, deletionMode);
	}
	else
	{
		Save(false, false);
	}
}

bool ProfileMgr::replaceUUID()
{
	std::string accountName = GetAccountName();
	std::string newUUID = m_playerIdentityService.CreateNewId();
	LogServer::Instance()->SendFakderNewUUI(accountName, newUUID);
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo.IsValid())
			playerInfo->ResetALLSign();
	}
	return true;
}

void ProfileMgr::removeInvalidProfile()
{
	bool readOnlyMode = m_readOnlyMode;
	m_readOnlyMode = true;
	std::vector<PlayerInfoPtr> invalidProfiles;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (!playerInfo->IsValid())
			invalidProfiles.push_back(playerInfo);
	}
	size_t i = 0;
	if (invalidProfiles.size() != 0)
	{
		while (i++ < invalidProfiles.size())
			DeleteProfile(invalidProfiles[i - 1]->GetProfileId());
	}
	m_readOnlyMode = readOnlyMode;
}

void ProfileMgr::removeProfileOwnerError(const std::vector<int>& _vaildProfileIdVec)
{
	bool readOnlyMode = m_readOnlyMode;
	m_readOnlyMode = true;
	std::vector<PlayerInfoPtr> errorProfiles;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo->GetProfileId() != 0)
		{
			bool found = false;
			for (std::vector<int>::const_iterator iter = _vaildProfileIdVec.begin(); iter != _vaildProfileIdVec.end(); ++iter)
			{
				if (playerInfo->GetProfileId() == *iter)
				{
					found = true;
					break;
				}
			}
			if (!found)
				errorProfiles.push_back(playerInfo);
		}
	}
	size_t i = 0;
	if (errorProfiles.size() != 0)
	{
		while (i++ < errorProfiles.size())
			DeleteProfile(errorProfiles[i - 1]->GetProfileId());
	}
	m_readOnlyMode = readOnlyMode;
}

bool ProfileMgr::needCheckFakeFromServer()
{
	bool valid;
	Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES);
	while (true)
	{
		valid = it;
		if (!valid)
			break;
		{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo->GetVersion() < PLAYERPROFILEVER_HotFixForChineseVersion_Aug05_2013)
		{
			playerInfo->UpdateLawnKeyField();
			playerInfo->ResetALLSign();
			int maxGems = playerInfo->GetUnlockBonusGemCount();
			DraperSaveData* draper = DraperHelpers::GetDraperSaveData(playerInfo->GetProfileIndex());
			if (draper != nullptr)
			{
				int surplus = (int)(draper->GetPurchaseTotal() - (float)playerInfo->GetUnlockPlantGemAndCoinCount());
				if (surplus < 0)
				{
					maxGems = -1;
				}
				else
				{
					maxGems += surplus * 12;
					playerInfo->SetRecharge(surplus > 0);
				}
				playerInfo->SetGiveGems(0);
			}			else
			{
				playerInfo->SetGiveGems(std::min(maxGems, playerInfo->GetNumGems()));
			}
			int gems = playerInfo->GetNumGems();
			int coins = playerInfo->GetNumCoins();
			if ((gems > maxGems && gems < 5000000) || (coins >= 500001 && coins < 10000000))
				return true;
		}
		}
		++it;
	}
	return valid;
}

bool ProfileMgr::populateProfiles()
{
	bool foundCurrent = false;
	bool needCheckFake = gLawnApp->m_bNeedCheckFakeFromServer;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo.IsValid())
		{
			if (playerInfo->GetVersion() < PLAYERPROFILEVER_PrimaryAndChildProfile_Mar27_2013)
			{
				DeleteProfile(playerInfo->GetName());
			}
			else
			{
				if (playerInfo->GetVersion() < PLAYERPROFILEVER_NMTWorld_Sep15_2016)
				{
					if (needCheckFake && gLawnApp->GetRechargeCheckServer().GetPlayerRechargeAmount() < 0)
						return false;
					UpdateProfileToLatestVersion(playerInfo);
					RequestSave();
				}
				if (!foundCurrent)
					foundCurrent = playerInfo->GetProfileIndex() == m_currentProfileIndex;
			}
		}
	}
	if (gLawnApp->m_hasChangeFakeData)
	{
		replaceUUID();
		gLawnApp->GetRechargeCheckServer().ResetGemAmount();
	}
	if ((!m_profileNameForLoad.empty() && SetCurrentProfile(m_profileNameForLoad) != PROFILE_OK) || !foundCurrent)
		setAnyProfileAsCurrent();
	SetReadOnlyMode(m_previousReadOnlyValue);
	m_previousReadOnlyValue = false;
	gMessageRouter->Post(&Message::ProfileListChanged);
	m_bHasPopulateProfiles = true;
	return true;
}

void ProfileMgr::SaveAsAutoName()
{
	PlayerInfo* currentProfile = GetCurrentProfile();
	std::wstring baseName = currentProfile->AM_GetName();
	std::ostringstream stream;
	int index = 1;
	stream << index;
	std::wstring newName = baseName + Sexy::StringToWString("_" + stream.str());
	while (FindProfile(newName).IsValid())
	{
		++index;
		stream.str("");
		stream.clear();
		stream << index;
		newName = baseName + Sexy::StringToWString("_" + stream.str());
	}
	SaveAs(currentProfile, newName);
}

void ProfileMgr::LoginiCloudServer()
{
	if (!gLawnApp->IsAndroidSDKInitEnd())
		return;
	if (gLawnApp->GetAndroidSDKInitStatus() == 0)
	{
		if (!(m_purchaseBroker.GetUniqueID() != ""))
			return;
	}

	std::string defineId = DefineIDMgr::GetInstance().GetUserDefineID();
	bool useUUIDLogin = false;
	if (IdentifierMgr::GetInstance().EnableBind())
	{
		std::string uuid = IdentifierMgr::GetInstance().GetUUID();
		if (uuid.size() != 0)
		{
			std::string accessToken = IdentifierMgr::GetInstance().GetAccessToken();
			if (accessToken.size() != 0 && IdentifierMgr::GetInstance().IsBind())
				useUUIDLogin = IdentifierMgr::GetInstance().NeedUUIDLogin();
		}
	}
	if (useUUIDLogin && (IdentifierMgr::GetInstance().IsRequestFinished() || IdentifierMgr::GetInstance().IsRequestTimeOut()))
		NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestUUIDLogin();
	else
		NetworkMgr::Instance()->GetNewNetWorkProcess()->ICloudRequstLogin(defineId);
}

PlayerInfoPtr ProfileMgr::CreateProfileFromServer(const std::string i_profileStr)
{
	Sexy::RtId id = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLAYER_PROFILES)->AllocId(PlayerInfo::StaticGetClass()->New()->CastChecked<PlayerInfo>(), Sexy::RtDbTable::ODM_Auto, true, NULL);
	PlayerInfoPtr profile(id);
	if (!profile->SerializeJsonToObj(i_profileStr, "sd"))
	{
		profile->SetName(L"-invalid-");
		profile->SetProfileIndex(time(NULL));
		InitializeProfile(profile.Get());
	}
	else
	{
		profile->ResetStarTotal();
	}
	m_currentProfileIndex = profile->GetProfileIndex();
	m_profileListDirty = true;
	return profile;
}

PlayerInfo* ProfileMgr::GetPurchaseProfile(std::string i_productId)
{
	if (i_productId == "")
	{
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
		{
			PlayerInfoPtr playerInfo(*it);
			if (playerInfo.IsValid())
			{
				PurchaseInfo info = playerInfo->GetRestorePurchaseInfo();
				if (info.receipt != "")
					return playerInfo;
			}
		}
		return nullptr;
	}

	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo.IsValid())
		{
			PurchaseInfo info = playerInfo->GetRestorePurchaseInfo();
			if (i_productId == info.productId && info.receipt == "")
				return playerInfo;
		}
	}
	if (HasValidProfile())
		return GetCurrentProfile();
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo.IsValid())
			return playerInfo;
	}
	return nullptr;
}

bool ProfileMgr::ChangeHackDataForAug05(PlayerInfo* i_profile)
{
	int rechargeAmount = gLawnApp->GetRechargeCheckServer().GetPlayerRechargeAmount();
	bool isHacker = gLawnApp->GetRechargeCheckServer().IsHacker();
	bool changed;
	if (rechargeAmount >= 0 && isHacker)
	{
		{
			LogServer* logServer = LogServer::Instance();
			std::string accountName = GetAccountName();
			int rechargeGems = i_profile->GetRechargeGems();
			int giveGems = i_profile->GetGiveGems();
			int coins = i_profile->GetNumCoins();
			changed = true;
			logServer->SendFakeInfo(accountName, 102, rechargeGems, giveGems, coins);
		}
		i_profile->SetRechargeGems(0);
		i_profile->SetRecharge(false);
		if (i_profile->GetNumCoins() > 140000)
		{
			{
				LogServer* logServer = LogServer::Instance();
				std::string accountName = GetAccountName();
				int rechargeGems = i_profile->GetRechargeGems();
				int giveGems = i_profile->GetGiveGems();
				int coins = i_profile->GetNumCoins();
				logServer->SendFakeInfo(accountName, 103, rechargeGems, giveGems, coins);
			}
			i_profile->SetCoins(140000);
		}
	}
	else if (rechargeAmount == -1 && i_profile->GetNumGems() > 4999999)
	{
		{
			LogServer* logServer = LogServer::Instance();
			std::string accountName = GetAccountName();
			int rechargeGems = i_profile->GetRechargeGems();
			int giveGems = i_profile->GetGiveGems();
			int coins = i_profile->GetNumCoins();
			changed = true;
			logServer->SendFakeInfo(accountName, 108, rechargeGems, giveGems, coins);
		}
		i_profile->SetRechargeGems(0);
		i_profile->SetRecharge(false);
		if (i_profile->GetNumCoins() > 140000)
		{
			{
				LogServer* logServer = LogServer::Instance();
				std::string accountName = GetAccountName();
				int rechargeGems = i_profile->GetRechargeGems();
				int giveGems = i_profile->GetGiveGems();
				int coins = i_profile->GetNumCoins();
				logServer->SendFakeInfo(accountName, 103, rechargeGems, giveGems, coins);
			}
			i_profile->SetCoins(140000);
		}
	}
	else
	{
		changed = false;
	}
	if (i_profile->GetNumCoins() > 9999999)
	{
		{
			LogServer* logServer = LogServer::Instance();
			changed = true;
			std::string accountName = GetAccountName();
			int rechargeGems = i_profile->GetRechargeGems();
			int giveGems = i_profile->GetGiveGems();
			int coins = i_profile->GetNumCoins();
			logServer->SendFakeInfo(accountName, 104, rechargeGems, giveGems, coins);
		}
		i_profile->SetCoins(140000);
	}
	return changed;
}

void ProfileMgr::Update()
{
	if (gLawnApp->CheckProfileOpen())
	{
		if (m_isSaving)
		{
			if (!m_checkErrorSave)
			{
				if (gTimeMgr->RealT() > m_lastCloudSaveTime + 60.0f)
				{
					LawnApp* app = gLawnApp;
					if (app->canDealProfile())
					{
						PVZ2UIDialog* dialog = app->ShowPVZ2Dialog(L"[ICLOUD_PROFILE_ERROR]", TodReplaceNumberString(TodStringTranslate(L"[ICLOUD_PROFILE_ERROR_FOR_UPLOAD]"), L"{NUMBER}", 215));
						dialog->AddButton(L"[CONTINUE_BUTTON]", Sexy::Delegate0(Sexy::MakeDelegate(*this, &ProfileMgr::onDialogButtonPressed)));
						m_checkErrorSave = true;
					}
				}
			}
		}
		else if (!m_needUpLoad || gLawnApp->isSyncProfileSuccess())
		{
			if (m_canUpload && gTimeMgr->RealT() > m_save_interval + m_lastSaveTime && gGameStateMgr->GetState() != GAME_Game)
				RealSave();
		}
		else
		{
			RealSave();
		}
	}
	else
	{
		LawnApp* app;
		if (m_isSaving && !m_checkErrorSave)
		{
			pvztime_t now = gTimeMgr->RealT();
			app = gLawnApp;
			if (now > m_lastCloudSaveTime + 60.0f && app->canDealProfile())
			{
				PVZ2UIDialog* dialog = app->ShowPVZ2Dialog(L"[ICLOUD_PROFILE_ERROR]", TodReplaceNumberString(TodStringTranslate(L"[ICLOUD_PROFILE_ERROR_FOR_UPLOAD]"), L"{NUMBER}", 215));
				dialog->AddButton(L"[CONTINUE_BUTTON]", Sexy::Delegate0(Sexy::MakeDelegate(*this, &ProfileMgr::onDialogButtonPressed)));
				app = gLawnApp;
				m_checkErrorSave = true;
			}
		}
		else
		{
			app = gLawnApp;
		}
		if (!app->isSyncProfileSuccess())
			m_saveRequested = true;
		PlayerInfo* currentProfile = GetCurrentProfile();
		if (currentProfile != nullptr && currentProfile->IsNeedDelaySave())
			currentProfile->SAVE_PROFILE();
		if (m_needUpLoad)
		{
			RealSave();
		}
		else if (m_saveRequested && !m_isSaving && m_canUpload)
		{
			pvztime_t now = gTimeMgr->RealT();
			pvztime_t lastSaveTime = m_lastSaveTime;
			if (now > m_throttles.GetDeltaIntervalInS() + lastSaveTime)
				RealSave();
		}
	}
	m_purchaseBroker.Update();
}

void ProfileMgr::UpdateProfileToLatestVersion(PlayerInfo* i_profile)
{
	if (i_profile->GetVersion() < PLAYERPROFILEVER_NewWorldMapDec21_2012)
		InitializeProfile(i_profile);
	if (i_profile->GetVersion() < PLAYERPROFILEVER_WorldMapZoomPersistance_Jan16_2013)
		i_profile->SetWorldMapZoomData(1.0f, false);
	if (i_profile->GetVersion() < PLAYERPROFILEVER_NewDangerRoomDataHandling_May21_2013)
	{
		std::vector<uint8> mowerStatusInRows;
		for (int i = 0; i < 5; i++)
			mowerStatusInRows.push_back(1);
		DangerRoomInfo dangerRoomInfo;
		std::string worldNames[3] = { "egypt", "pirate", "cowboy" };
		for (int i = 0; i < 3; i++)
		{
			if (i_profile->HasDangerRoomInfo(worldNames[i]))
			{
				dangerRoomInfo = i_profile->GetDangerRoomInfo(worldNames[i]);
				if (dangerRoomInfo.Lives != 0)
				{
					dangerRoomInfo.SetHasLostDangerRoom(false);
					dangerRoomInfo.SetLawnMowerStatusInRows(mowerStatusInRows);
					i_profile->SetDangerRoomInfo(worldNames[i], dangerRoomInfo);
				}
			}
		}
	}
	if (i_profile->GetVersion() < PLAYERPROFILEVER_HotFixForChineseVersion_Aug05_2013)
	{
		i_profile->UpdateLawnKeyField();
		i_profile->UpdateUUIDAndOSVerson();
		i_profile->ResetALLSign();
		i_profile->SetReturnGoldValue(CalReturnGoldBetweenVersionJune25AndAug05(i_profile));
		ChangeMapDataForAug05(i_profile);
		if (ChangeHackDataForAug05(i_profile))
			gLawnApp->m_hasChangeFakeData = true;
	}
	if (i_profile->GetVersion() < PLAYERPROFILEVER_HotFixForChineseVersion_Nov18_2013)
		i_profile->UpdateTotalRecharge();
	if (i_profile->GetVersion() < PLAYERPROFILEVER_KongFu_Dec18_2013)
	{
		i_profile->CheckWorldKeyValueWhenUpdate();
		i_profile->AddFestivalGameLeftCount(FestivalGameMode_CrazyYeti, 3);
		i_profile->AddFestivalGameLeftCount(FestivalGameMode_GargantuarCrisis, 3);
		i_profile->AddFestivalGameLeftCount(FestivalGameMode_DevilInvade, 1);
	}
	if (i_profile->GetVersion() < PLAYERPROFILEVER_YetiRemove_Mar24_2014)
	{
		i_profile->SetTreasureYetiLocation("none");
		WorldMapEventStatus egypt4Status = i_profile->GetWorldMapEventStatus("egypt4");
		if (!i_profile->GetIsPlantUnlocked("gravebuster") && i_profile->GetPlantPieceCount("gravebuster") < 1 && egypt4Status == EVENTSTATUS_CLEARED)
		{
			i_profile->ResetTutorialProgress(TUTORIAL_AFTER_CHALLENGE_1);
			i_profile->SetWorldMapEventStatusForEgypt5(EVENTSTATUS_UNLOCKED);
		}
	}
	if (i_profile->GetVersion() < PLAYERPROFILEVER_ACTIVITYUPDATE_JUN11_2014)
		i_profile->DoOnlineRefreshEventTime();
	if (i_profile->GetVersion() < PLAYERPROFILEVER_HotFixForStarPlant_July08_2014)
		i_profile->DoUpdatePlantStarRewards();
	if (i_profile->GetVersion() < PLAYERPROFILEVER_MoreAvatarCompen_Aug07_2014)
	{
	}
	if (i_profile->GetVersion() < PLAYERPROFILEVER_DailyRewardCompen_Sep03_2014)
	{
	}
	if (i_profile->GetVersion() > PLAYERPROFILEVER_NMTWorld_Sep15_2016)
	{
		i_profile->setGachaCompen(true);
		i_profile->setAvatarAdvanceCompen(true);
		i_profile->setAvatarCompen(true);
		i_profile->setDailyRewardCompen(true);
	}
	if (i_profile->GetVersion() < PLAYERPROFILEVER_HotFixRepeatData_Aug15_2016)
		i_profile->FixRepeatData();
	if (i_profile->GetVersion() < PLAYERPROFILEVER_NMTWorld_Sep15_2016)
	{
		i_profile->SetNumRechargeCurrency(0);
		i_profile->SetFirstRechargeRewardStatus(false);
		int tacticalCukeUses = i_profile->GetPowerupUsesLeft("poweruptacticalcuke");
		i_profile->SetupPowerupUses("poweruptacticalcuke", 0);
		i_profile->SetPowerupUnlockState("monthlycard_tacticalcuke", true);
		i_profile->SetupPowerupUses("monthlycard_tacticalcuke", tacticalCukeUses);
		i_profile->RemoveAllAdventure(true, true, true);
	}
	std::string markerFile = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "pvz2_m.txt";
	gSexyAppBase->EraseFile(markerFile);
	std::string activityFile = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "pvz2_ac.txt";
	gSexyAppBase->EraseFile(activityFile);
	i_profile->UpdateVersion();
}
