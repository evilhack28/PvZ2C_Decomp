//
//  ZombieAnimRig_ChildrensdayCone.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Tutorial.h"

ZombieAnimRig_ChildrensdayCone::ZombieAnimRig_ChildrensdayCone()
{
}

ZombieAnimRig_ChildrensdayCone::~ZombieAnimRig_ChildrensdayCone()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ChildrensdayCone);

void ZombieAnimRig_ChildrensdayCone::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ChildrensdayCone);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ChildrensdayBasic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ChildrensdayCone);
}
