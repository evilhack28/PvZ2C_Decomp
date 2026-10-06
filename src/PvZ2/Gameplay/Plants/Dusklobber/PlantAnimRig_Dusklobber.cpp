//
//  PlantAnimRig_Dusklobber.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Dusklobber.h"

PlantAnimRig_Dusklobber::PlantAnimRig_Dusklobber()
{
}

PlantAnimRig_Dusklobber::~PlantAnimRig_Dusklobber()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Dusklobber);

void PlantAnimRig_Dusklobber::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Dusklobber);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastPlayedIdleAnim);
		REFLECTION_CLASSBUILDER_FIELD(AnimRigLayerSet, m_boostedLayerSet);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Dusklobber);
}

#include "Plant_Dusklobber.h"
bool PlantAnimRig_Dusklobber::PlayIdleLooped()
{
	return PlantAnimRig_Dusklobber::playIdleAnimation();
}
