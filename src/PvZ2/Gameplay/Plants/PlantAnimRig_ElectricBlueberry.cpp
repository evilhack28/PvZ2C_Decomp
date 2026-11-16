//
//  PlantAnimRig_ElectricBlueberry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ElectricBlueberry.h"

PlantAnimRig_ElectricBlueberry::PlantAnimRig_ElectricBlueberry()
{
}

PlantAnimRig_ElectricBlueberry::~PlantAnimRig_ElectricBlueberry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_ElectricBlueberry);

void PlantAnimRig_ElectricBlueberry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_ElectricBlueberry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_ElectricBlueberry);
}
