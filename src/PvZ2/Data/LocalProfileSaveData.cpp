//
//  LocalProfileSaveData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "PlayerInfoLocalSaveData.h"
#include "ProfileMgr.h"
#include "PVZDB.h"
#include "LawnApp.h"
#include "TimeUtil.h"
#include "ActivityManager.h"
#include "PVZ1ModeNetworkMgr.h"
#include "JoustNetworkMgr.h"
#include "RiftNetworkMgr.h"

/////////////// Storage ///////////////

static PlayerInfoLocalSaveData* CreateLocalProfileData(const PlayerInfo* i_playerInfo)
{
	PlayerInfoLocalSaveData* data = PlayerInfoLocalSaveData::StaticGetClass()->New()->CastChecked<PlayerInfoLocalSaveData>();
	data->ProfileIndex = i_playerInfo->GetProfileIndex();
	Sexy::RtId id = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PROFILELOCALSAVEDATA)->AllocId(data, Sexy::RtDbTable::ODM_Auto, true, NULL);
	return data;
}

static std::string GetLocalProfilesPath()
{
	return GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "local_profiles";
}

static void SaveLocalProfileData()
{
	PVZDB::GetInstance().SavePackageForTableToFile(PVZDB::TABLE_PROFILELOCALSAVEDATA, GetLocalProfilesPath(), false, false);
}

PlayerInfoLocalSaveData* LocalProfileSaveData::GetOrCreateLocalProfileData(const PlayerInfo* i_playerInfo)
{
	if (i_playerInfo == NULL)
	{
		static PlayerInfoLocalSaveData s_defaultData;
		return &s_defaultData;
	}

	PlayerInfoLocalSaveData* found = NULL;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PROFILELOCALSAVEDATA); it; ++it)
	{
		PlayerInfoLocalSaveDataPtr data(*it);
		if (data->ProfileIndex == i_playerInfo->GetProfileIndex())
		{
			found = data;
			break;
		}
	}
	if (found == NULL)
	{
		found = CreateLocalProfileData(i_playerInfo);
		SaveLocalProfileData();
	}
	return found;
}

/////////////// Facebook ///////////////

void LocalProfileSaveData::SetCanPostToFacebook(const PlayerInfo* i_playerInfo, const bool i_canPost)
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PROFILELOCALSAVEDATA); it; ++it)
	{
		PlayerInfoLocalSaveDataPtr data(*it);
		if (data->ProfileIndex == i_playerInfo->GetProfileIndex())
		{
			data->FacebookConnected = i_canPost;
			SaveLocalProfileData();
			return;
		}
	}

	if (i_canPost)
	{
		CreateLocalProfileData(i_playerInfo)->FacebookConnected = true;
		SaveLocalProfileData();
	}
}

bool LocalProfileSaveData::CanPostToFacebook(const PlayerInfo* i_playerInfo)
{
	if (i_playerInfo == NULL)
		return false;

	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PROFILELOCALSAVEDATA); it; ++it)
	{
		PlayerInfoLocalSaveDataPtr data(*it);
		if (data->ProfileIndex == i_playerInfo->GetProfileIndex())
			return data->FacebookConnected;
	}
	return false;
}

/////////////// Profile picture ///////////////

static std::string GetProfilePicturePath(const PlayerInfo* i_playerInfo)
{
	return GetFolder(Sexy::IFileDriver::PathType_NoBackup) + Sexy::StrFormat("profile_icon_%d", i_playerInfo->GetProfileIndex());
}

void LocalProfileSaveData::SetProfilePicture(const PlayerInfo* i_playerInfo, Sexy::MemoryImage* i_image)
{
	bool found = false;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PROFILELOCALSAVEDATA); it; ++it)
	{
		PlayerInfoLocalSaveDataPtr data(*it);
		if (data->ProfileIndex == i_playerInfo->GetProfileIndex())
		{
			delete data->ProfileIcon;
			data->ProfileIcon = i_image;
			found = true;
			break;
		}
	}
	if (!found)
	{
		CreateLocalProfileData(i_playerInfo)->ProfileIcon = i_image;
		SaveLocalProfileData();
	}

	Sexy::Buffer buffer;
	buffer.WriteInt32(i_image->mWidth);
	buffer.WriteInt32(i_image->mHeight);
	buffer.WriteBytes((const uchar*)i_image->mBits, (unsigned int)(i_image->mWidth * i_image->mHeight * 4));
	gSexyAppBase->WriteBufferToFile(GetProfilePicturePath(i_playerInfo), &buffer);
	gMessageRouter->Post(&Message::ProfileIconPictureTaken, i_playerInfo, i_image);
}

Sexy::MemoryImage* LocalProfileSaveData::GetProfilePicture(const PlayerInfo* i_playerInfo)
{
	if (i_playerInfo == NULL)
		return NULL;

	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PROFILELOCALSAVEDATA); it; ++it)
	{
		PlayerInfoLocalSaveDataPtr data(*it);
		if (data->ProfileIndex == i_playerInfo->GetProfileIndex())
		{
			if (data->ProfileIcon == NULL && gLawnApp->FileExists(GetProfilePicturePath(i_playerInfo)))
			{
				Sexy::Buffer buffer;
				gSexyAppBase->ReadBufferFromFile(GetProfilePicturePath(i_playerInfo), &buffer);
				int width = buffer.ReadInt32();
				int height = buffer.ReadInt32();
				Sexy::MemoryImage* image = new Sexy::MemoryImage();
				image->SetImageMode(true, true);
				image->AddImageFlags(Sexy::ImageFlag_UseA8R8G8B8);
				image->SetBits((uint32*)&buffer.mData[buffer.mReadBitPos / 8], width, height, true);
				data->ProfileIcon = image;
			}
			return data->ProfileIcon;
		}
	}
	return NULL;
}

/////////////// Plant wars ///////////////

PlantWarsLevelTeamData LocalProfileSaveData::GetPlantWarsLevelTeamData(int i_worldIndex, int i_levelIndex)
{
	std::vector<PlantWarsWorldTeamData>& worlds = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->PlantWarsTeamData;
	for (size_t w = 0; w != worlds.size(); w++)
	{
		if (worlds[w].WorldIndex == i_worldIndex)
		{
			std::vector<PlantWarsLevelTeamData>& levels = worlds[w].LevelTeamData;
			for (size_t l = 0; l != levels.size(); l++)
			{
				if (levels[l].LevelIndex == i_levelIndex)
					return levels[l];
			}
		}
	}

	PlantWarsLevelTeamData none;
	none.LevelIndex = -1;
	return none;
}

void LocalProfileSaveData::UpdatePlantWarsTeamData(int i_worldIndex, int i_levelIndex, const std::vector<std::string>& i_firstTeam, const std::vector<std::string>& i_secondTeam)
{
	PlayerInfoLocalSaveData* data = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile());
	std::vector<PlantWarsWorldTeamData>& worlds = data->PlantWarsTeamData;
	for (size_t w = 0; w != worlds.size(); w++)
	{
		if (worlds[w].WorldIndex == i_worldIndex)
		{
			std::vector<PlantWarsLevelTeamData>& levels = worlds[w].LevelTeamData;
			for (size_t l = 0; l != levels.size(); l++)
			{
				if (levels[l].LevelIndex == i_levelIndex)
				{
					levels[l].FirstTeam = i_firstTeam;
					worlds[w].LevelTeamData[l].SecondTeam = i_secondTeam;
					SaveLocalProfileData();
					return;
				}
			}

			PlantWarsLevelTeamData level;
			level.LevelIndex = i_levelIndex;
			level.FirstTeam = i_firstTeam;
			level.SecondTeam = i_secondTeam;
			worlds[w].LevelTeamData.push_back(level);
			SaveLocalProfileData();
			return;
		}
	}

	PlantWarsLevelTeamData level;
	level.LevelIndex = i_levelIndex;
	level.FirstTeam = i_firstTeam;
	level.SecondTeam = i_secondTeam;
	PlantWarsWorldTeamData world;
	world.WorldIndex = i_worldIndex;
	world.LevelTeamData.push_back(level);
	data->PlantWarsTeamData.push_back(world);
	SaveLocalProfileData();
}

/////////////// Arcade ///////////////

ArcadeLastPlayData* LocalProfileSaveData::GetOrCreateArcadeLastPlayData(const PlayerInfo* i_playerInfo, const std::string& i_modeID)
{
	std::vector<ArcadeLastPlayData>& list = GetOrCreateLocalProfileData(i_playerInfo)->ArcadeLastPlays;
	for (std::vector<ArcadeLastPlayData>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (it->ModeID.compare(i_modeID) == 0)
			return &*it;
	}

	ArcadeLastPlayData entry;
	entry.ModeID = i_modeID;
	list.push_back(entry);
	return &list.back();
}

/////////////// Accessors ///////////////

int32_t LocalProfileSaveData::GetDangerRoomRandomSeed(const PlayerInfo* i_playerInfo)
{
	return GetOrCreateLocalProfileData(i_playerInfo)->DangerRoomRandomSeed;
}

time_t LocalProfileSaveData::GetZombossUnlockedTime(const PlayerInfo* i_playerInfo)
{
	return GetOrCreateLocalProfileData(i_playerInfo)->ZombossUnlockedTime;
}

void LocalProfileSaveData::SetZombossUnlockedTime(const PlayerInfo* i_playerInfo, time_t i_time)
{
	GetOrCreateLocalProfileData(i_playerInfo)->ZombossUnlockedTime = i_time;
	SaveLocalProfileData();
}

void LocalProfileSaveData::AddSeedChooserFavorite(const PlayerInfo* i_playerInfo, const std::string& i_plantType)
{
	GetOrCreateLocalProfileData(i_playerInfo)->m_favoriteSeedChooserPlants.push_back(i_plantType);
	SaveLocalProfileData();
}

void LocalProfileSaveData::SaveDangerRoomSelectedList(const PlayerInfo* i_playerInfo, const std::vector<int>& i_list)
{
	GetOrCreateLocalProfileData(i_playerInfo)->m_dangerRoomSelectedList = i_list;
	SaveLocalProfileData();
}

void LocalProfileSaveData::SetHasPurchasedExtraDRCard(const PlayerInfo* i_playerInfo, bool i_purchasedCard)
{
	GetOrCreateLocalProfileData(i_playerInfo)->HasPurchasedExtraDRCard = i_purchasedCard;
	SaveLocalProfileData();
}

std::vector<std::string>& LocalProfileSaveData::GetFavoriteArtifactList()
{
	return GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->ArtifactFavoriteList;
}

std::vector<PlantWarsWorldTeamData>& LocalProfileSaveData::GetPlantWarsTeamData()
{
	return GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->PlantWarsTeamData;
}

bool LocalProfileSaveData::CheckTransGenosisTips()
{
	return TimeUtil::IsToday(GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->LastTransGenosisTipsTime);
}

int LocalProfileSaveData::GetPlantGeneAdditionVersion()
{
	return GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->PlantGeneAdditionVersion;
}

void LocalProfileSaveData::SetPlantGeneAdditionVersion(int i_newVersion)
{
	GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->PlantGeneAdditionVersion = i_newVersion;
	SaveLocalProfileData();
}

bool LocalProfileSaveData::GetHeroPlantArmorflameIntroStatus()
{
	return GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->HeroPlantArmorflameIntro;
}

void LocalProfileSaveData::SetHeroPlantArmorflameIntroStatus(bool i_status)
{
	GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->HeroPlantArmorflameIntro = i_status;
	SaveLocalProfileData();
}

const Network_ArtifactImprovedPropertySheet& LocalProfileSaveData::GetNetworkArtifactImprovedPropertySheet()
{
	return GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->ArtifactImprovedPropertySheet;
}

void LocalProfileSaveData::ObtainPlantPediaReward(int i_plantPediaId)
{
	GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->PlantPediaList.push_back(i_plantPediaId);
	SaveLocalProfileData();
}

void LocalProfileSaveData::UpdateTransGenosisTipsTime()
{
	GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->LastTransGenosisTipsTime = gLawnApp->GetRealServerTime();
	SaveLocalProfileData();
}

bool LocalProfileSaveData::GetHasPurchasedExtraDRCard(const PlayerInfo* i_playerInfo)
{
	return GetOrCreateLocalProfileData(i_playerInfo)->HasPurchasedExtraDRCard;
}

int32_t LocalProfileSaveData::GetDangerRoomRepickSeed(const PlayerInfo* i_playerInfo)
{
	return GetOrCreateLocalProfileData(i_playerInfo)->DangerRoomRepickSeed;
}

void LocalProfileSaveData::SetDangerRoomRandomSeed(const PlayerInfo* i_playerInfo, int32_t i_randomSeed)
{
	GetOrCreateLocalProfileData(i_playerInfo)->DangerRoomRandomSeed = i_randomSeed;
}

void LocalProfileSaveData::SetDangerRoomRepickSeed(const PlayerInfo* i_playerInfo, int32_t i_randomSeed)
{
	GetOrCreateLocalProfileData(i_playerInfo)->DangerRoomRepickSeed = i_randomSeed;
}

std::vector<std::string>& LocalProfileSaveData::GetSeedChooserFavorites(const PlayerInfo* i_playerInfo)
{
	return GetOrCreateLocalProfileData(i_playerInfo)->m_favoriteSeedChooserPlants;
}

const std::vector<int>& LocalProfileSaveData::GetDangerRoomSelectedList(const PlayerInfo* i_playerInfo)
{
	return GetOrCreateLocalProfileData(i_playerInfo)->m_dangerRoomSelectedList;
}

bool LocalProfileSaveData::GetHasJustClearedRiftZomboss(const PlayerInfo* i_playerInfo)
{
	return GetOrCreateLocalProfileData(i_playerInfo)->HasJustClearedRiftZomboss;
}

void LocalProfileSaveData::SetHasJustClearedRiftZomboss(const PlayerInfo* i_playerInfo, bool i_cleared)
{
	GetOrCreateLocalProfileData(i_playerInfo)->HasJustClearedRiftZomboss = i_cleared;
	SaveLocalProfileData();
}

int LocalProfileSaveData::GetCurrentNewPVPCPULevel(const PlayerInfo* i_playerInfo)
{
	return GetOrCreateLocalProfileData(i_playerInfo)->CurrentNewPVPCPULevel;
}

void LocalProfileSaveData::SetCurrentNewPVPCPULevel(const PlayerInfo* i_playerInfo, int i_level)
{
	GetOrCreateLocalProfileData(i_playerInfo)->CurrentNewPVPCPULevel = i_level;
	SaveLocalProfileData();
}

bool LocalProfileSaveData::HasPlantPediaRewarded(int i_plantPediaId)
{
	std::vector<int>& list = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->PlantPediaList;
	return std::find(list.begin(), list.end(), i_plantPediaId) != list.end();
}

bool LocalProfileSaveData::IsSeedChooserFavorite(const PlayerInfo* i_playerInfo, const std::string& i_plantType)
{
	std::vector<std::string>& list = GetOrCreateLocalProfileData(i_playerInfo)->m_favoriteSeedChooserPlants;
	return std::find(list.begin(), list.end(), i_plantType) != list.end();
}

/////////////// Favorites ///////////////

void LocalProfileSaveData::AddFavoriteArtifact(const std::string& i_artifactName)
{
	std::vector<std::string>& list = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->ArtifactFavoriteList;
	list.insert(list.begin(), i_artifactName);
	SaveLocalProfileData();
}

void LocalProfileSaveData::RemoveFavoriteArtifact(const std::string& i_artifactName)
{
	std::vector<std::string>& list = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->ArtifactFavoriteList;
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); )
	{
		if (*it == i_artifactName)
			it = list.erase(it);
		else
			++it;
	}
	SaveLocalProfileData();
}

bool LocalProfileSaveData::IsFavoriteArtifact(const std::string& i_artifactName)
{
	std::vector<std::string>& list = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->ArtifactFavoriteList;
	return std::find(list.begin(), list.end(), i_artifactName) != list.end();
}

void LocalProfileSaveData::RemoveSeedChooserFavorite(const PlayerInfo* i_playerInfo, const std::string& i_plantType)
{
	std::vector<std::string>& list = GetOrCreateLocalProfileData(i_playerInfo)->m_favoriteSeedChooserPlants;
	std::vector<std::string>::iterator it = std::find(list.begin(), list.end(), i_plantType);
	if (it != list.end())
		list.erase(it);
	SaveLocalProfileData();
}

/////////////// Lv5 skill switch ///////////////

void LocalProfileSaveData::SetPlantLv5SkillSwitch(const PlayerInfo* i_playerInfo, const std::string& i_plantType, bool i_on)
{
	std::vector<Lv5Switch>& list = GetOrCreateLocalProfileData(i_playerInfo)->Lv5SkillSwitch;
	std::vector<Lv5Switch>::iterator it = std::find_if(list.begin(), list.end(), [&](const Lv5Switch& i_switch) { return i_switch.plantName == i_plantType; });
	if (it != list.end())
		it->on = i_on;
	else
	{
		Lv5Switch entry;
		entry.plantName = i_plantType;
		entry.on = i_on;
		list.push_back(entry);
	}
	SaveLocalProfileData();
}

bool LocalProfileSaveData::GetPlantLv5SkillSwitch(const PlayerInfo* i_playerInfo, const std::string& i_plantType)
{
	std::vector<Lv5Switch>& list = GetOrCreateLocalProfileData(i_playerInfo)->Lv5SkillSwitch;
	std::vector<Lv5Switch>::iterator it = std::find_if(list.begin(), list.end(), [&](const Lv5Switch& i_switch) { return i_switch.plantName == i_plantType; });
	if (it != list.end())
		return it->on;
	SetPlantLv5SkillSwitch(i_playerInfo, i_plantType, false);
	return false;
}

/////////////// Tips ///////////////

bool LocalProfileSaveData::CheckDangerRoomTips()
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_DangerRoom);
	bool result = false;
	if (item.m_bOpen && item.GetLeftDays() >= 0)
		result = !TimeUtil::IsInThisWeek(GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->LastDangerRoomTipsTime);
	return result;
}

void LocalProfileSaveData::UpdateDangerRoomTipsTime()
{
	PlayerInfoLocalSaveData* data = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile());
	if (!TimeUtil::IsInThisWeek(data->LastDangerRoomTipsTime))
	{
		data->LastDangerRoomTipsTime = gLawnApp->GetRealServerTime();
		SaveLocalProfileData();
	}
}

bool LocalProfileSaveData::CheckPVZ1Tips()
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_PVZ1_Mode);
	bool result = item.m_bOpen;
	if (result)
	{
		PVZ1ModeMainEntryData data;
		result = item.GetDataSerialized(data);
		if (result)
		{
			time_t lastTime = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->LastPVZ1TipsTime;
			if (lastTime >= data.ThemeLeftTime - 604800 && lastTime <= data.ThemeLeftTime)
				result = false;
		}
	}
	return result;
}

bool LocalProfileSaveData::CheckBattleZTips()
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_Joust);
	bool result = item.m_bOpen;
	if (result)
	{
		NetworkDashboardInfo data;
		if (item.GetDataSerialized(data) && data.CanPlay)
		{
			time_t lastTime = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->LastBattleZTipsTime;
			result = lastTime < data.Tournament.EndTime - 604800 || lastTime > data.Tournament.EndTime;
		}
		else
			result = false;
	}
	return result;
}

void LocalProfileSaveData::UpdateBattleZTipsTime()
{
	if (CheckBattleZTips())
	{
		GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->LastBattleZTipsTime = gLawnApp->GetRealServerTime();
		SaveLocalProfileData();
	}
}

bool LocalProfileSaveData::CheckPennyTips()
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_Rift);
	bool result = item.m_bOpen;
	if (result)
	{
		NetworkMainEntryInfo data;
		result = item.GetDataSerialized(data);
		if (result)
		{
			time_t lastTime = GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->LastPennyTipsTime;
			if (lastTime >= data.ThemeLeftTime - 604800 && lastTime <= data.ThemeLeftTime)
				result = false;
		}
	}
	return result;
}

void LocalProfileSaveData::UpdatePennyTipsTime()
{
	if (CheckPennyTips())
	{
		GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->LastPennyTipsTime = gLawnApp->GetRealServerTime();
		SaveLocalProfileData();
	}
}

void LocalProfileSaveData::UpdatePVZ1TipsTime()
{
	if (CheckPVZ1Tips())
	{
		GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->LastPVZ1TipsTime = gLawnApp->GetRealServerTime();
		SaveLocalProfileData();
	}
}

/////////////// Lifecycle ///////////////

void LocalProfileSaveData::LoadLocalProfileSaveData()
{
	bool exists = gLawnApp->FileExists(GetLocalProfilesPath());
	if (exists)
		PVZDB::GetInstance().LoadPackageForTableFromFile(PVZDB::TABLE_PROFILELOCALSAVEDATA, GetLocalProfilesPath(), false, false);
}

void LocalProfileSaveData::SetNetworkArtifactImprovedPropertySheet(const Network_ArtifactImprovedPropertySheet& i_sheet)
{
	GetOrCreateLocalProfileData(ProfileMgr::GetInstance().GetCurrentProfile())->ArtifactImprovedPropertySheet = i_sheet;
	SaveLocalProfileData();
}
