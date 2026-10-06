//
//  Plant_Bloomerang.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Bloomerang.h"

PlantBloomerang::PlantBloomerang()
{
}

PlantBloomerang::~PlantBloomerang()
{
}

PlantTypeBloomerang::PlantTypeBloomerang()
{
}

PlantTypeBloomerang::~PlantTypeBloomerang()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBloomerang);

void PlantBloomerang::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBloomerang);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextPlantfoodRoundTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_plantfoodRounds);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_preventReturnAnimation);
	REFLECTION_CLASSBUILDER_END(PlantBloomerang);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeBloomerang);

void PlantTypeBloomerang::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTypeBloomerang);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantType);

	REFLECTION_CLASSBUILDER_END(PlantTypeBloomerang);
}

bool PlantBloomerang::CanApplyPlantfood()
{
	return true;
}
