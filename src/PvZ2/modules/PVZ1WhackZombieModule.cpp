//
//  PVZ1WhackZombieModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PVZ1WhackZombieModule.h"

void PVZ1WhackZombieModule::onCancelEvent()
{
}

PVZ1WhackZombieModule::~PVZ1WhackZombieModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZ1WhackZombieModule);

void PVZ1WhackZombieModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ1WhackZombieModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(PVZ1WhackZombieModule);
}

void PVZ1WhackZombieModule::onZombieDestroyed(Zombie * i_arg)
{
}
