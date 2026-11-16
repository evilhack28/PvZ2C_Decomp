//
//  WorldMap_FuelBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_FuelBank.h"

WorldMap_FuelBank::WorldMap_FuelBank()
{
}

WorldMap_FuelBank::~WorldMap_FuelBank()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_FuelBank);

void WorldMap_FuelBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_FuelBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(FuelBank);

	REFLECTION_CLASSBUILDER_END(WorldMap_FuelBank);
}
