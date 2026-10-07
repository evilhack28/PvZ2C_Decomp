//
//  MinigameWhackAZombieModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "MinigameWhackAZombieModule.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MinigameWhackAZombieModule);

void MinigameWhackAZombieModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MinigameWhackAZombieModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(MinigameWhackAZombieModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MinigameWhackAZombieModuleProperties);

void MinigameWhackAZombieModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MinigameWhackAZombieModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, HammerTapsToDecay);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, HammerHitValue);
	REFLECTION_CLASSBUILDER_END(MinigameWhackAZombieModuleProperties);
}

void MinigameWhackAZombieModule::openPuddles(int numToOpen)
{
}

void MinigameWhackAZombieModule::onLevelLoaded()
{
}

void MinigameWhackAZombieModule::initializeModule()
{
}

void MinigameWhackAZombieModule::ensureMinimumPuddles()
{
}

#include "MinigameWhackAZombieModule.h"
void MinigameWhackAZombieModule::ReserveNewZombiePuddles()
{
	 MinigameWhackAZombieModule::reserveNewPuddle();
}

void MinigameWhackAZombieModule::onUpdate()
{
}
