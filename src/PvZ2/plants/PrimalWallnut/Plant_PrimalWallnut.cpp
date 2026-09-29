//
//  Plant_PrimalWallnut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PrimalWallnut.h"

PlantPrimalWallnut::PlantPrimalWallnut()
{
}

PlantPrimalWallnut::~PlantPrimalWallnut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPrimalWallnut);

void PlantPrimalWallnut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPrimalWallnut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantWallnut);

		REFLECTION_CLASSBUILDER_FIELD(bool, isCuring);
	REFLECTION_CLASSBUILDER_END(PlantPrimalWallnut);
}
