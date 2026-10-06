//
//  Plant_IntensiveCarrot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_IntensiveCarrot.h"

PlantIntensiveCarrot::PlantIntensiveCarrot()
{
}

PlantIntensiveCarrot::~PlantIntensiveCarrot()
{
}

PlantTypeIntensiveCarrot::PlantTypeIntensiveCarrot()
{
}

PlantTypeIntensiveCarrot::~PlantTypeIntensiveCarrot()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantIntensiveCarrot);

void PlantIntensiveCarrot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantIntensiveCarrot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<IntensiveCarrotRevivalSubsystem>, m_carrotRevivalSubsystem);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_plantBeingRevived);
	REFLECTION_CLASSBUILDER_END(PlantIntensiveCarrot);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeIntensiveCarrot);

bool PlantIntensiveCarrot::CanBeShoveled()
{
	return false;
}

bool PlantIntensiveCarrot::CanBeTargeted()
{
	return false;
}

bool PlantIntensiveCarrot::CanApplyPlantfood()
{
	return false;
}
