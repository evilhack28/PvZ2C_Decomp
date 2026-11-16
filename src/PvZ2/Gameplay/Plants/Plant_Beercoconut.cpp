//
//  Plant_Beercoconut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Beercoconut.h"

PlantBeercoconut::PlantBeercoconut()
{
}

PlantBeercoconut::~PlantBeercoconut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBeercoconut);

void PlantBeercoconut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBeercoconut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isLevel5);
	REFLECTION_CLASSBUILDER_END(PlantBeercoconut);
}
