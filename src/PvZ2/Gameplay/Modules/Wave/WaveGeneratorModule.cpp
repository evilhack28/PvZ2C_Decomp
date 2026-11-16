//
//  WaveGeneratorModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WaveGeneratorModule.h"

WaveGeneratorModule::~WaveGeneratorModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveGeneratorModule);

void WaveGeneratorModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WaveGeneratorModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(WaveGeneratorModule);
}

void WaveGeneratorModule::onZombieSpawned(class Zombie* i_zombie)
{
}
