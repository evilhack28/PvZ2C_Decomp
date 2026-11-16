//
//  Plant_Splitpea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Splitpea.h"

PlantSplitpea::PlantSplitpea()
{
}

PlantSplitpea::~PlantSplitpea()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSplitpea);

void PlantSplitpea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSplitpea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantSplitpea);
}

#include "PlantFramework.h"
void PlantSplitpea::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantSplitpea::CanApplyPlantfood()
{
	return true;
}
