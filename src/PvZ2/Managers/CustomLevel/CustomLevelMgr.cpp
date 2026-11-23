//
//  CustomLevelMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CustomLevelMgr.h"

#include "CustomLevelMgr.h"
#include "CustomLevelMgr.h"
#include "ProfileMgr.h"

/////////////// Accessors ///////////////

int CustomLevelMgr::GetEvilDaveStartingSun()
{
	return CustomLevelMgr::GetStartingSun();
}

void CustomLevelMgr::SetTowerDefendPlantfood(int i_count)
{
}

const CustomLevelConfig* CustomLevelMgr::GetConfig() const
{
	return CustomLevelMgr::getConfig();
}

void CustomLevelMgr::SetEvilDaveStartingSun(int i_count)
{
	SetStartingSun(i_count);
}

bool CustomLevelMgr::IsLevelDownloaded(const std::string& i_localLevelID)
{
	return m_dataCreator.IsLevelDownload(i_localLevelID);
}

const CustomNetworkExtraData& CustomLevelMgr::GetExtraData()
{
	return m_activityExtraData;
}

CustomLevelNetworkWorldType CustomLevelMgr::GetWorldType()
{
	return m_currentLevelData.NetworkWorldType;
}

void CustomLevelMgr::SetLevelName(const std::string& i_levelName)
{
	m_currentLevelData.NetworkLevelName = i_levelName;
}

const std::string& CustomLevelMgr::GetLevelName()
{
	return m_currentLevelData.NetworkLevelName;
}

void CustomLevelMgr::SetTowerDefendStartingSun(int i_count)
{
	SetStartingSun(i_count);
}

int CustomLevelMgr::GetTowerDefendStartingSun()
{
	return m_currentLevelData.LevelParams.StartingSun;
}

void CustomLevelMgr::SetCanBuySunmoney(bool i_flag)
{
	m_currentLevelData.LevelParams.Encourage.BuySunmoney = i_flag;
}

bool CustomLevelMgr::GetCanBuySunmoney()
{
	return m_currentLevelData.LevelParams.Encourage.BuySunmoney;
}

void CustomLevelMgr::SetCanBuyPlantfood(bool i_flag)
{
	m_currentLevelData.LevelParams.Encourage.BuyPlantfood = i_flag;
}

bool CustomLevelMgr::GetCanBuyPlantfood()
{
	return m_currentLevelData.LevelParams.Encourage.BuyPlantfood;
}

void CustomLevelMgr::SetCanBuyMower(bool i_flag)
{
	m_currentLevelData.LevelParams.Encourage.BuyMower = i_flag;
}

bool CustomLevelMgr::GetCanBuyMower()
{
	return m_currentLevelData.LevelParams.Encourage.BuyMower;
}

int CustomLevelMgr::GetStartingSun()
{
	return m_currentLevelData.LevelParams.StartingSun;
}

void CustomLevelMgr::SetStartingSun(int i_count)
{
	m_currentLevelData.LevelParams.StartingSun = i_count;
}

CustomSeedBankType CustomLevelMgr::GetSeedBankType()
{
	return m_currentLevelData.LevelParams.SeedBankData.Type;
}

void CustomLevelMgr::SetSeedBankType(CustomSeedBankType i_type)
{
	m_currentLevelData.LevelParams.SeedBankData.Type = i_type;
}

void CustomLevelMgr::SetSeedBankGlobalLevel(int i_level)
{
	m_currentLevelData.LevelParams.SeedBankData.GlobalLevel = i_level;
}

int CustomLevelMgr::GetSeedBankGlobalLevel()
{
	return m_currentLevelData.LevelParams.SeedBankData.GlobalLevel;
}

const std::vector<std::string>& CustomLevelMgr::GetSeedBankPlantBlackList()
{
	return m_currentLevelData.LevelParams.SeedBankData.BlackList;
}

const std::vector<std::string>& CustomLevelMgr::GetPresetSeedBankPlants()
{
	return m_currentLevelData.LevelParams.SeedBankData.PresetList;
}

const std::vector<CustomConveyorData>& CustomLevelMgr::GetConveyorSeedBankPlants()
{
	return m_currentLevelData.LevelParams.SeedBankData.ConveyorList;
}

bool CustomLevelMgr::IsLastStandValid()
{
	return m_currentLevelData.LevelParams.Challenge.HasLastStand();
}

void CustomLevelMgr::SetLastStandStartingSun(int i_count)
{
	m_currentLevelData.LevelParams.Challenge.ChallengeData.LastStand.StartingSun = i_count;
}

void CustomLevelMgr::SetLastStandPlantfood(int i_count)
{
	m_currentLevelData.LevelParams.Challenge.ChallengeData.LastStand.StartingPlantfood = i_count;
}

int CustomLevelMgr::GetLastStandPlantfood()
{
	return m_currentLevelData.LevelParams.Challenge.ChallengeData.LastStand.StartingPlantfood;
}

void CustomLevelMgr::SetEvilDavePlantDistance(float i_distance)
{
	m_currentLevelData.LevelParams.Challenge.ChallengeData.EvilDave.PlantDistance = i_distance;
}

float CustomLevelMgr::GetEvilDavePlantDistance()
{
	return m_currentLevelData.LevelParams.Challenge.ChallengeData.EvilDave.PlantDistance;
}

const std::string& CustomLevelMgr::GetStartingPlant()
{
	return m_currentLevelData.LevelParams.Challenge.ChallengeData.SingleHanded.StartingPlantType;
}

void CustomLevelMgr::SetExtraData(CustomNetworkExtraData& i_data)
{
	m_activityExtraData = i_data;
}

bool CustomLevelMgr::IsCustomLevel(const std::string& i_levelID)
{
	return i_levelID.find(m_creator.GetCustomLevelPrefix(), 0) != std::string::npos;
}

bool CustomLevelMgr::GetMoldGrid(int i_x, int i_y)
{
	return m_currentLevelData.LevelParams.Challenge.ChallengeData.Molds.MoldGrids[i_y][i_x] == 1;
}

std::string CustomLevelMgr::GetPresetSeedBankPlant(int i_index)
{
	return m_currentLevelData.LevelParams.SeedBankData.PresetList[i_index];
}

CustomConveyorData CustomLevelMgr::GetConveyorSeedBankPlantData(int i_index)
{
	return m_currentLevelData.LevelParams.SeedBankData.ConveyorList[i_index];
}

int CustomLevelMgr::GetSetSize()
{
	return m_currentLevelData.LevelParams.Challenge.ChallengeData.StatueMaze.SetInfos.size();
}

/////////////// Logic ///////////////

void CustomLevelMgr::InitModules(const CustomLevelWorldParams& i_g)
{
	initializeDefaultModules();
	CustomLevelMgr::initOtherModules(i_g);
}

void CustomLevelMgr::ClearSeedBankPlantBlackList()
{
	m_currentLevelData.LevelParams.SeedBankData.BlackList.clear();
}

void CustomLevelMgr::AddStartingPlant(const std::string& i_typeName)
{
	m_currentLevelData.LevelParams.Challenge.ChallengeData.SingleHanded.StartingPlantType = i_typeName;
}

void CustomLevelMgr::UploadCurrentLevelData()
{
	RequestUploadLevelData(m_currentLevelData);
}

void CustomLevelMgr::UpdateMoldGrid(int i_x, int i_y, bool i_add)
{
	m_currentLevelData.LevelParams.Challenge.ChallengeData.Molds.MoldGrids[i_y][i_x] = i_add;
}

bool CustomLevelMgr::CheckInTutorial()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (!profile)
		return false;
	int tutorial = profile->GetActiveTutorial();
	return tutorial == TUTORIAL_CUSTOM_LEVEL_CREATOR || tutorial == TUTORIAL_CUSTOM_LEVEL_PLAY;
}

void CustomLevelMgr::Update(float dt)
{
	if (!CheckInTutorial())
		return;
	if (!(m_skipTutorialTimer <= 0))
	{
		m_skipTutorialTimer -= dt;
		if (m_skipTutorialTimer <= 0)
			CreateTutorialSkipMenu();
	}
}
