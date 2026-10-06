//
//  JoustGameModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "JoustGameModule.h"

JoustGameModuleProperties::~JoustGameModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustGameModule);

void JoustGameModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPowerData);
		REFLECTION_CLASSBUILDER_FIELD(bool, HasAvatar);
	REFLECTION_CLASSBUILDER_END(PlantPowerData);

	REFLECTION_CLASSBUILDER_BEGIN(JoustGameModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_levelTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantPowerData>, m_powerDatas);
	REFLECTION_CLASSBUILDER_END(JoustGameModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustGameModuleProperties);

void JoustGameModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustGameModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, TimeLimit);
	REFLECTION_CLASSBUILDER_END(JoustGameModuleProperties);
}

bool JoustGameModule::preventSave()
{
	return true;
}

void JoustGameModule::reportToSlack()
{
}

void JoustGameModule::postInitialize()
{
}

void JoustGameModule::onGameplayEnded()
{
}

#include "JoustGameModule.h"
void JoustGameModule::onSeedChooserFinalized()
{
	 JoustGameModule::hideCoinBank();
}
