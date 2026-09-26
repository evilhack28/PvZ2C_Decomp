//
//  LevelOfTheDay.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LevelOfTheDay.h"

LevelOfTheDayPropertySheet::~LevelOfTheDayPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LevelOfTheDayPropertySheet);

void LevelOfTheDayPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LevelOfTheDayPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<ZombieType> >, KilledZombieBlacklist);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<LevelOfTheDaySchedule>, Schedules);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<LevelOfTheDay_RewardItemType>, Rewards);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<HolidayEventProperties>, HolidayEvents);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, AndroidBlacklist);

	REFLECTION_CLASSBUILDER_END(LevelOfTheDayPropertySheet);
}
