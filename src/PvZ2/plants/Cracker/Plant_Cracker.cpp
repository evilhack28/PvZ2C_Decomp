//
//  Plant_Cracker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cracker.h"

PlantCracker::PlantCracker()
{
	m_bCancelPlantFood = 0;
	m_iDropCracker = 0;
}

PlantCracker::~PlantCracker()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCracker);

void PlantCracker::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCracker);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_iDropCracker);
	REFLECTION_CLASSBUILDER_END(PlantCracker);
}

#include "PlantFramework.h"
void PlantCracker::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantCracker::CanApplyPlantfood()
{
	return true;
}
