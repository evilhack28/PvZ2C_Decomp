//
//  ZombieAnimRig_Gargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Gargantuar.h"

ZombieAnimRig_Gargantuar::ZombieAnimRig_Gargantuar()
{
}

ZombieAnimRig_Gargantuar::~ZombieAnimRig_Gargantuar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Gargantuar);

void ZombieAnimRig_Gargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Gargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Gargantuar);
}
