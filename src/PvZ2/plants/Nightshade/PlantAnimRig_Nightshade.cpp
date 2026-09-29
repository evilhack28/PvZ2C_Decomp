//
//  PlantAnimRig_Nightshade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Nightshade.h"

PlantAnimRig_Nightshade::PlantAnimRig_Nightshade()
{
}

PlantAnimRig_Nightshade::~PlantAnimRig_Nightshade()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Nightshade);

void PlantAnimRig_Nightshade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Nightshade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastPlayedIdleAnim);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Nightshade);
}
