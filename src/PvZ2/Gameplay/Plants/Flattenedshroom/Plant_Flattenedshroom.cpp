//
//  Plant_Flattenedshroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Flattenedshroom.h"

PlantFlattenedshroom::PlantFlattenedshroom()
{
}

PlantFlattenedshroom::~PlantFlattenedshroom()
{
}

PlantTypeFlattenedshroom::PlantTypeFlattenedshroom()
{
}

PlantTypeFlattenedshroom::~PlantTypeFlattenedshroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantFlattenedshroom);

void PlantFlattenedshroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantFlattenedshroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isOnPot);
	REFLECTION_CLASSBUILDER_END(PlantFlattenedshroom);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeFlattenedshroom);

#include "PlantFramework.h"
void PlantFlattenedshroom::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

#include "PlantFramework.h"
void PlantFlattenedshroom::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantFlattenedshroom::CanApplyPlantfood()
{
	return true;
}
