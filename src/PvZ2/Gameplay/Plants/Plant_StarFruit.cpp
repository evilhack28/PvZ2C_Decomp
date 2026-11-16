//
//  Plant_StarFruit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_StarFruit.h"

PlantStarFruit::PlantStarFruit()
{
}

PlantStarFruit::~PlantStarFruit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantStarFruit);

void PlantStarFruit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantStarFruit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_rotation);
	REFLECTION_CLASSBUILDER_END(PlantStarFruit);
}

#include "PlantFramework.h"
void PlantStarFruit::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantStarFruit::CanApplyPlantfood()
{
	return true;
}
