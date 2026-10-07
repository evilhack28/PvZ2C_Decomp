//
//  TimeEnergyModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "TimeEnergyModule.h"

TimeEnergyModule::~TimeEnergyModule()
{
}

TimeEnergyModuleProperties::~TimeEnergyModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TimeEnergyModule);

void TimeEnergyModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TimeEnergyModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_triggerCooldownEndTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TimeEnergyTriggerData>, m_triggerDataList);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BlackHole>, m_blackHole);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_triggerLose);
		REFLECTION_CLASSBUILDER_FIELD(std::map<TimeEnergyTriggerType RT_COMMA bool>, m_TriggerMap);
	REFLECTION_CLASSBUILDER_END(TimeEnergyModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TimeEnergyModuleProperties);

void TimeEnergyModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TimeEnergyModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<TimeEnergyTriggerData>, TimeEnergyTriggers);
		REFLECTION_CLASSBUILDER_FIELD(float, TimeEnergyValueMax);
	REFLECTION_CLASSBUILDER_END(TimeEnergyModuleProperties);
}

void TimeEnergyModule::onLoadComplete()
{
}

#include "TimeEnergyModule.h"
void TimeEnergyModule::achievementOnLilyPadDied(class GridItemLilyPad* i_lilyPad)
{
	 TimeEnergyModule::achievementHandlePlantDied();
}

void TimeEnergyModule::achievementOnFlowerPotDied(class GridItemFlowerPot* i_flowerPot)
{
}
