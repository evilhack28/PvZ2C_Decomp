//
//  PlantAnimRig_Hammerflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Hammerflower.h"

PlantAnimRig_Hammerflower::PlantAnimRig_Hammerflower()
{
}

PlantAnimRig_Hammerflower::~PlantAnimRig_Hammerflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Hammerflower);

void PlantAnimRig_Hammerflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Hammerflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastUsedIdleAnim);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Hammerflower);
}
