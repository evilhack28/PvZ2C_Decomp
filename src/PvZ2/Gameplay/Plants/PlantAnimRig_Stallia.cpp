//
//  PlantAnimRig_Stallia.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Stallia.h"

PlantAnimRig_Stallia::PlantAnimRig_Stallia()
{
}

PlantAnimRig_Stallia::~PlantAnimRig_Stallia()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Stallia);

void PlantAnimRig_Stallia::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Stallia);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlayedFirstIdle);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Stallia);
}
