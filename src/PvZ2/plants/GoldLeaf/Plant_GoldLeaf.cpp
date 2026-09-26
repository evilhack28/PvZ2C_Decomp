//
//  Plant_GoldLeaf.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_GoldLeaf.h"

PlantGoldLeaf::PlantGoldLeaf()
{
}

PlantGoldLeaf::~PlantGoldLeaf()
{
}

PlantTypeGoldLeaf::PlantTypeGoldLeaf()
{
}

PlantTypeGoldLeaf::~PlantTypeGoldLeaf()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGoldLeaf);

void PlantGoldLeaf::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGoldLeaf);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantGoldLeaf);
}

bool PlantGoldLeaf::CanBeShoveled()
{
	return false;
}
