//
//  Plant_HappyLeek.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HappyLeek.h"

PlantHappyLeek::PlantHappyLeek()
{
}

PlantHappyLeek::~PlantHappyLeek()
{
}

PlantHappyLeekProps::~PlantHappyLeekProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHappyLeek);

void PlantHappyLeek::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHappyLeek);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextAttackTime);
	REFLECTION_CLASSBUILDER_END(PlantHappyLeek);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHappyLeekProps);

void PlantHappyLeekProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHappyLeekProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

	REFLECTION_CLASSBUILDER_END(PlantHappyLeekProps);
}

bool PlantHappyLeek::CanApplyPlantfood()
{
	return true;
}
