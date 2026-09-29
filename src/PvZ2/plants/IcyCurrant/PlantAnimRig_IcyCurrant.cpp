//
//  PlantAnimRig_IcyCurrant.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_IcyCurrant.h"

PlantAnimRig_IcyCurrant::~PlantAnimRig_IcyCurrant()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_IcyCurrant);

void PlantAnimRig_IcyCurrant::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_IcyCurrant);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_bAvatar);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_IcyCurrant);
}
