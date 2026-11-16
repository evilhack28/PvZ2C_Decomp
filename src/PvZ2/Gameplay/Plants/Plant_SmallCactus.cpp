//
//  Plant_SmallCactus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SmallCactus.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSmallCactus);

void PlantSmallCactus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSmallCactus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_NextStuckTime);
	REFLECTION_CLASSBUILDER_END(PlantSmallCactus);
}

#include "PlantFramework.h"
void PlantSmallCactus::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantSmallCactus::CanApplyPlantfood()
{
	return false;
}
