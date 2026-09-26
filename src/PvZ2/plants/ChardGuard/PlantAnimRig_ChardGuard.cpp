//
//  PlantAnimRig_ChardGuard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ChardGuard.h"

PlantAnimRig_ChardGuard::~PlantAnimRig_ChardGuard()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_ChardGuard);

void PlantAnimRig_ChardGuard::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_ChardGuard);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastPlayedIdleAnim);
	REFLECTION_CLASSBUILDER_FIELD(int, m_leafCount);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_ChardGuard);
}

bool PlantAnimRig_ChardGuard::playPlantFoodOn()
{
	return true;
}

bool PlantAnimRig_ChardGuard::playPlantFoodMain()
{
	return true;
}
