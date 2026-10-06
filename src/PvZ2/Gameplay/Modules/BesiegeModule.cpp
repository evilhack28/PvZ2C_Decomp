//
//  BesiegeModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BesiegeModule.h"

void BesiegeModule::cancelTouch()
{
}

bool BesiegeModule::preventSave()
{
	return true;
}

void BesiegeModule::levelStarted()
{
}

void BesiegeModule::postInitialize()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BesiegeModule);

void BesiegeModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BesiegeModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(int, m_homeHP);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_targetPoint);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_TimeFailure);
	REFLECTION_CLASSBUILDER_END(BesiegeModule);
}

void BesiegeModule::onZombieKilled(Zombie* i_arg0, const DamageInfo* i_arg1)
{
}

void BesiegeModule::initializeModule()
{
}
