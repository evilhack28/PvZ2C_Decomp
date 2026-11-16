//
//  LevelEscalationModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "LevelEscalationModule.h"

LevelEscalationModule::LevelEscalationModule()
{
}

LevelEscalationModule::~LevelEscalationModule()
{
}

LevelEscalationModuleProperties::~LevelEscalationModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LevelEscalationModule);

void LevelEscalationModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LevelEscalationModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(LevelEscalationModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LevelEscalationModuleProperties);

void LevelEscalationModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LevelEscalationModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<WaveManagerProperties>, WaveManagerProps);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<ZombieType> >, ZombiePool);
	REFLECTION_CLASSBUILDER_END(LevelEscalationModuleProperties);
}

void LevelEscalationModule::generateRandomEvents(int i_level, MTRand & i_random, class WaveManagerProperties * o_props)
{
}
