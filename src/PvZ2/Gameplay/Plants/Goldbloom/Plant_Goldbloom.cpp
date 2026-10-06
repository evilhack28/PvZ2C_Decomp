//
//  Plant_Goldbloom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Goldbloom.h"

PlantGoldbloom::PlantGoldbloom()
{
}

PlantGoldbloom::~PlantGoldbloom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGoldbloom);

void PlantGoldbloom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGoldbloom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_FIELD(int, m_state);

	REFLECTION_CLASSBUILDER_END(PlantGoldbloom);
}

bool PlantGoldbloom::CanApplyPlantfood()
{
	return false;
}

bool PlantGoldbloom::HasShadow()
{
	return true;
}
