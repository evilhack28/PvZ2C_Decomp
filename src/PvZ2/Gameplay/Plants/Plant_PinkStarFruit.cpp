//
//  Plant_PinkStarFruit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PinkStarFruit.h"

PlantPinkStarFruit::PlantPinkStarFruit()
{
}

PlantPinkStarFruit::~PlantPinkStarFruit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPinkStarFruit);

void PlantPinkStarFruit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPinkStarFruit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_currentState);
	REFLECTION_CLASSBUILDER_END(PlantPinkStarFruit);
}

bool PlantPinkStarFruit::CanApplyPlantfood()
{
	return true;
}
