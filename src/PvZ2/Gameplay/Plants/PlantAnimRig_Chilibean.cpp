//
//  PlantAnimRig_Chilibean.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Chilibean.h"

PlantAnimRig_Chilibean::PlantAnimRig_Chilibean()
{
}

PlantAnimRig_Chilibean::~PlantAnimRig_Chilibean()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Chilibean);

void PlantAnimRig_Chilibean::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Chilibean);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastPlayedIdleAnim);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Chilibean);
}
