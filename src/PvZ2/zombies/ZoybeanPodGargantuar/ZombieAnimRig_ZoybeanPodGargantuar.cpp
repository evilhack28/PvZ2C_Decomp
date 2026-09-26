//
//  ZombieAnimRig_ZoybeanPodGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZoybeanPodGargantuar.h"

ZombieAnimRig_ZoybeanPodGargantuar::ZombieAnimRig_ZoybeanPodGargantuar()
{
}

ZombieAnimRig_ZoybeanPodGargantuar::~ZombieAnimRig_ZoybeanPodGargantuar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZoybeanPodGargantuar);

void ZombieAnimRig_ZoybeanPodGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZoybeanPodGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Gargantuar);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZoybeanPodGargantuar);
}
