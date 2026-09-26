//
//  PlantAnimRig_PinkStarFruit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PinkStarFruit.h"

PlantAnimRig_PinkStarFruit::PlantAnimRig_PinkStarFruit()
{
}

PlantAnimRig_PinkStarFruit::~PlantAnimRig_PinkStarFruit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_PinkStarFruit);

void PlantAnimRig_PinkStarFruit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_PinkStarFruit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int32, m_animState);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_PinkStarFruit);
}
