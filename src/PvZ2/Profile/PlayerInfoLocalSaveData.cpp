//
//  PlayerInfoLocalSaveData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-08.
//

#include "SexyAppFramework/Common.h"

#include "PlayerInfoLocalSaveData.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

PlayerInfoLocalSaveData::PlayerInfoLocalSaveData()
{
	ProfileIndex = 0;
	FacebookConnected = false;
	ProfileIcon = NULL;
	DangerRoomRandomSeed = 0;
	HasPurchasedExtraDRCard = false;
	DangerRoomRepickSeed = 0;
	ZombossUnlockedTime = 0;
	HasJustClearedRiftZomboss = false;
	LastDangerRoomTipsTime = 0;
	LastBattleZTipsTime = 0;
	LastPennyTipsTime = 0;
	LastPVZ1TipsTime = 0;
	PlantGeneAdditionVersion = 0;
	CurrentNewPVPCPULevel = 0;
	HeroPlantArmorflameIntro = false;
}

PlayerInfoLocalSaveData::~PlayerInfoLocalSaveData()
{
	delete ProfileIcon;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PlayerInfoLocalSaveData);

void PlayerInfoLocalSaveData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Lv5Switch);
		REFLECTION_CLASSBUILDER_FIELD(std::string, plantName);
		REFLECTION_CLASSBUILDER_FIELD(bool, on);
	REFLECTION_CLASSBUILDER_END(Lv5Switch);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsLevelTeamData);
		REFLECTION_CLASSBUILDER_FIELD(int, LevelIndex);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, FirstTeam);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, SecondTeam);
	REFLECTION_CLASSBUILDER_END(PlantWarsLevelTeamData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantWarsWorldTeamData);
		REFLECTION_CLASSBUILDER_FIELD(int, WorldIndex);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantWarsLevelTeamData>, LevelTeamData);
	REFLECTION_CLASSBUILDER_END(PlantWarsWorldTeamData);

	REFLECTION_CLASSBUILDER_BEGIN(PlayerInfoLocalSaveData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

		REFLECTION_CLASSBUILDER_FIELD(int32, ProfileIndex);
		REFLECTION_CLASSBUILDER_FIELD(bool, FacebookConnected);
		REFLECTION_CLASSBUILDER_FIELD(bool, HasPurchasedExtraDRCard);
		REFLECTION_CLASSBUILDER_FIELD(int32_t, DangerRoomRandomSeed);
		REFLECTION_CLASSBUILDER_FIELD(int32_t, DangerRoomRepickSeed);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ArcadeLastPlayData>, ArcadeLastPlays);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, m_favoriteSeedChooserPlants);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, m_dangerRoomSelectedList);
		REFLECTION_CLASSBUILDER_FIELD(serializable_time_t, ZombossUnlockedTime);
		REFLECTION_CLASSBUILDER_FIELD(serializable_time_t, LastDangerRoomTipsTime);
		REFLECTION_CLASSBUILDER_FIELD(serializable_time_t, LastBattleZTipsTime);
		REFLECTION_CLASSBUILDER_FIELD(serializable_time_t, LastPennyTipsTime);
		REFLECTION_CLASSBUILDER_FIELD(serializable_time_t, LastPVZ1TipsTime);
		REFLECTION_CLASSBUILDER_FIELD(int, PlantGeneAdditionVersion);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<Lv5Switch>, Lv5SkillSwitch);
		REFLECTION_CLASSBUILDER_FIELD(Network_ArtifactImprovedPropertySheet, ArtifactImprovedPropertySheet);
		REFLECTION_CLASSBUILDER_FIELD(bool, HeroPlantArmorflameIntro);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantWarsWorldTeamData>, PlantWarsTeamData);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ArtifactFavoriteList);
		REFLECTION_CLASSBUILDER_FIELD(serializable_time_t, LastTransGenosisTipsTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, PlantPediaList);

	REFLECTION_CLASSBUILDER_END(PlayerInfoLocalSaveData);
}
