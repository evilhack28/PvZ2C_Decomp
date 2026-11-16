//
//  ZombieAnimRig_ChildrensdayGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Gargantuar.h"

ZombieAnimRig_ChildrensdayGargantuar::ZombieAnimRig_ChildrensdayGargantuar()
{
}

ZombieAnimRig_ChildrensdayGargantuar::~ZombieAnimRig_ChildrensdayGargantuar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ChildrensdayGargantuar);

void ZombieAnimRig_ChildrensdayGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ChildrensdayGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Gargantuar);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ChildrensdayGargantuar);
}
