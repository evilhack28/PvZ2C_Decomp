//
//  ZombossRiftBattleModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombossRiftBattleModule.h"

ZombossRiftBattleModule::ZombossRiftBattleModule()
{
	m_zombossPhaseReached = 0;
}

ZombossRiftBattleModule::~ZombossRiftBattleModule()
{
}

ZombossRiftBattleModuleProperties::~ZombossRiftBattleModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossRiftBattleModule);

void ZombossRiftBattleModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossRiftBattleModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombossBattleModule);

		REFLECTION_CLASSBUILDER_FIELD(int, m_zombossPhaseReached);
	REFLECTION_CLASSBUILDER_END(ZombossRiftBattleModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossRiftBattleModuleProperties);

void ZombossRiftBattleModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossRiftBattleModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombossBattleModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, ZombossPhases);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, TimeLimit);
	REFLECTION_CLASSBUILDER_END(ZombossRiftBattleModuleProperties);
}

bool ZombossRiftBattleModule::getPreventSave()
{
	return true;
}

void ZombossRiftBattleModule::onGameplayEnded()
{
}

void ZombossRiftBattleModule::onGameplayUpdate()
{
}
