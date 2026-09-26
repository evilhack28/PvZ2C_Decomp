//
//  WorldMap_PVZ1EnergyBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_PVZ1EnergyBank.h"

WorldMap_PVZ1EnergyBank::WorldMap_PVZ1EnergyBank()
{
}

WorldMap_PVZ1EnergyBank::~WorldMap_PVZ1EnergyBank()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_PVZ1EnergyBank);

void WorldMap_PVZ1EnergyBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_PVZ1EnergyBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(FuelBank);

	REFLECTION_CLASSBUILDER_END(WorldMap_PVZ1EnergyBank);
}
