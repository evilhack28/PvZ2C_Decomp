//
//  NewPVPPropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "NewPVPDataPackets.h"
#include "NewPVPGame.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(NewPVPPropertySheet);

void NewPVPPropertySheet::Copy(const NewPVPPropertySheet& src)
{
	CommonZombieCreatedCD = src.CommonZombieCreatedCD;
	CommonPlantLevelUpValue = src.CommonPlantLevelUpValue;
	CommonMaxZombieCacheSize = src.CommonMaxZombieCacheSize;
	StartingSun = src.StartingSun;
	SunLimit = src.SunLimit;
	SunAddBase = src.SunAddBase;
	SunAddEachTurn = src.SunAddEachTurn;
	ZombieLevelStats = src.ZombieLevelStats;
	ZombiePacketInfos = src.ZombiePacketInfos;
	PlantPacketInfos = src.PlantPacketInfos;
	MaxHealthAmount = src.MaxHealthAmount;
	DealtDamage = src.DealtDamage;
	SunCostMultiplier = src.SunCostMultiplier;
	ZombieSkillInfos = src.ZombieSkillInfos;
	ZombieUpgradeInfos = src.ZombieUpgradeInfos;
	SunUpgradeInfos = src.SunUpgradeInfos;
	AreaHowToPlayData = src.AreaHowToPlayData;
	ChooserPlantBlacklist = src.ChooserPlantBlacklist;
	NewPVPZombieLevelUpSheet = src.NewPVPZombieLevelUpSheet;
	UnsyncPlantBlacklist = src.UnsyncPlantBlacklist;
	CPULevelInfos = src.CPULevelInfos;
	TutorialPlantList = src.TutorialPlantList;
	TutorialInfo = src.TutorialInfo;
}
