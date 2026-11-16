//
//  Plant_Cactus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cactus.h"

PlantCactus::PlantCactus()
{
}

PlantCactus::~PlantCactus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCactus);

void PlantCactus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCactus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasBeenPlantfooded);
		REFLECTION_CLASSBUILDER_FIELD(float, m_reShootRate);
	REFLECTION_CLASSBUILDER_END(PlantCactus);
}
