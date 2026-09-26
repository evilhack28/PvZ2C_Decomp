//
//  ZombieAnimRig_ConeMech.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Mech.h"

ZombieAnimRig_ConeMech::ZombieAnimRig_ConeMech()
{
}

ZombieAnimRig_ConeMech::~ZombieAnimRig_ConeMech()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ConeMech);

void ZombieAnimRig_ConeMech::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ConeMech);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Mech);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ConeMech);
}
