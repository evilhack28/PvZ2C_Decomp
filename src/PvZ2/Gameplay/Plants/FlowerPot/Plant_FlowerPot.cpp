//
//  Plant_FlowerPot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_FlowerPot.h"

PlantFlowerPot::PlantFlowerPot()
{
}

PlantFlowerPot::~PlantFlowerPot()
{
}

PlantTypeFlowerPot::PlantTypeFlowerPot()
{
}

PlantTypeFlowerPot::~PlantTypeFlowerPot()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantFlowerPot);

void PlantFlowerPot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantFlowerPot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantFlowerPot);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeFlowerPot);

void PlantTypeFlowerPot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTypeFlowerPot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantType);

	REFLECTION_CLASSBUILDER_END(PlantTypeFlowerPot);
}
