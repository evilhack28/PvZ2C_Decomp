//
//  PlantAnimRig_Electricitea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Electricitea.h"

PlantAnimRig_Electricitea::PlantAnimRig_Electricitea()
{
}

PlantAnimRig_Electricitea::~PlantAnimRig_Electricitea()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Electricitea);

void PlantAnimRig_Electricitea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Electricitea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_isSuperAttack);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Electricitea);
}
