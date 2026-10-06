//
//  PlantAnimRig_Buttercup.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Buttercup.h"

PlantAnimRig_Buttercup::PlantAnimRig_Buttercup()
{
	m_nextFortifyAttack = 0;
}

PlantAnimRig_Buttercup::~PlantAnimRig_Buttercup()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Buttercup);

void PlantAnimRig_Buttercup::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Buttercup);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Buttercup);
}
