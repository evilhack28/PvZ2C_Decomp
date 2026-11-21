//
//  DangerRoomPropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "DangerRoomModule.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DangerRoomPropertySheet);

void DangerRoomPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantFoodSetupData);
	REFLECTION_CLASSBUILDER_END(PlantFoodSetupData);

	REFLECTION_CLASSBUILDER_BEGIN(FlagWaveSetupData);
	REFLECTION_CLASSBUILDER_END(FlagWaveSetupData);

	REFLECTION_CLASSBUILDER_BEGIN(DangerRoomLevelData);
		REFLECTION_CLASSBUILDER_FIELD(int32, MaxStagesPerLevel);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int32>, StonePerLevel);
		REFLECTION_CLASSBUILDER_FIELD(float, BonusRate);
		REFLECTION_CLASSBUILDER_FIELD(std::string, LevelName);
	REFLECTION_CLASSBUILDER_END(DangerRoomLevelData);

	REFLECTION_CLASSBUILDER_BEGIN(DangerRoomRankData);
		REFLECTION_CLASSBUILDER_FIELD(std::string, RewardType);
	REFLECTION_CLASSBUILDER_END(DangerRoomRankData);

	REFLECTION_CLASSBUILDER_BEGIN(DangerRoomTitleData);
	REFLECTION_CLASSBUILDER_END(DangerRoomTitleData);

	REFLECTION_CLASSBUILDER_BEGIN(DangerRoomPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<FlagWaveSetupData>, FlagWaveSetupList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantFoodSetupData>, PlantfoodSetupList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<uint16>, CashOutRanks);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<DangerRoomLevelData>, LevelDatas);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<DangerRoomRankData>, RankDatas);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<DangerRoomTitleData>, TitleDatas);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombieLevelStat>, ZombieLevelStats);
		REFLECTION_CLASSBUILDER_FIELD(std::string, DangerRoomName);
		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, PlantStoredType);
	REFLECTION_CLASSBUILDER_END(DangerRoomPropertySheet);
}

void DangerRoomPropertySheet::Copy(const DangerRoomPropertySheet& src)
{
	LevelDatas = src.LevelDatas;
	FlagWaveSetupList = src.FlagWaveSetupList;
	PlantfoodSetupList = src.PlantfoodSetupList;
	MinWaveCount = src.MinWaveCount;
	MaxWaveCount = src.MaxWaveCount;
	WaveAddEach = src.WaveAddEach;
	WaveAddInterval = src.WaveAddInterval;
	MinFlagWaveCount = src.MinFlagWaveCount;
	MaxFlagWaveCount = src.MaxFlagWaveCount;
	MinLevelFlagWaveAdd = src.MinLevelFlagWaveAdd;
	ZombieLevelBase = src.ZombieLevelBase;
	ZombieLevelAdd = src.ZombieLevelAdd;
	ZombieTypeCount = src.ZombieTypeCount;
	BigZombieSureExistLevel = src.BigZombieSureExistLevel;
	LeaderMinWaveCost = src.LeaderMinWaveCost;
	LeaderProbability = src.LeaderProbability;
	LeaderStrengthenRate = src.LeaderStrengthenRate;
	WealthGodProbability = src.WealthGodProbability;
	SunLimit = src.SunLimit;
	SunAddBase = src.SunAddBase;
	SunAddEachLevel = src.SunAddEachLevel;
	SunAddBossBase = src.SunAddBossBase;
	SunAddBossEach = src.SunAddBossEach;
	BossInterval = src.BossInterval;
	BossHpBaseFactor = src.BossHpBaseFactor;
	BossHpAddFactor = src.BossHpAddFactor;
	PlantPacketLimit = src.PlantPacketLimit;
	PlantPacketStart = src.PlantPacketStart;
	PlantPacketAddEachLevel = src.PlantPacketAddEachLevel;
	ZombieLevelStats = src.ZombieLevelStats;
	StartingPoints = src.StartingPoints;
	BasePointIncrementPerWave = src.BasePointIncrementPerWave;
	BasePointIncrementPerLevel = src.BasePointIncrementPerLevel;
	PlantStoredType = src.PlantStoredType;
	MaxSelectedPlant = src.MaxSelectedPlant;
}
