//
//  Plant_Repeater.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Repeater.h"

PlantRepeater::PlantRepeater()
{
}

PlantRepeater::~PlantRepeater()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantRepeater);

void PlantRepeater::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantRepeater);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(PeashooterPlantfood, m_plantfood);
	REFLECTION_CLASSBUILDER_END(PlantRepeater);
}

#include "PlantFramework.h"
void PlantRepeater::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantRepeater::CanApplyPlantfood()
{
	return true;
}
