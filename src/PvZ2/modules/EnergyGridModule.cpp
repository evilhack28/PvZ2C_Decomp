//
//  EnergyGridModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EnergyGridModule.h"

EnergyGridModule::~EnergyGridModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EnergyGridModule);

void EnergyGridModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EnergyGridModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_FIELD(int32, leftCount);
	REFLECTION_CLASSBUILDER_FIELD(float, nextSpawnTime);
	REFLECTION_CLASSBUILDER_FIELD(int, currentWave);

	REFLECTION_CLASSBUILDER_END(EnergyGridModule);
}
