//
//  PlantAnimRig_CrownFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CrownFlower.h"

PlantAnimRig_CrownFlower::PlantAnimRig_CrownFlower()
{
}

PlantAnimRig_CrownFlower::~PlantAnimRig_CrownFlower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_CrownFlower);

void PlantAnimRig_CrownFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_CrownFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_isInHeState);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_CrownFlower);
}
