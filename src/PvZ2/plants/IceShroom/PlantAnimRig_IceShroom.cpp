//
//  PlantAnimRig_IceShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_IceShroom.h"

PlantAnimRig_IceShroom::~PlantAnimRig_IceShroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_IceShroom);

void PlantAnimRig_IceShroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_IceShroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(uint8, m_currentGrowthStage);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_IceShroom);
}
