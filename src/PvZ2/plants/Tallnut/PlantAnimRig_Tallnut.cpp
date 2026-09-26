//
//  PlantAnimRig_Tallnut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Tallnut.h"

int PlantAnimRig_Tallnut::GetArmorStateCount()
{
	return 3;
}

PlantAnimRig_Tallnut::PlantAnimRig_Tallnut()
{
}

PlantAnimRig_Tallnut::~PlantAnimRig_Tallnut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Tallnut);

void PlantAnimRig_Tallnut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Tallnut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_willDie);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Tallnut);
}
