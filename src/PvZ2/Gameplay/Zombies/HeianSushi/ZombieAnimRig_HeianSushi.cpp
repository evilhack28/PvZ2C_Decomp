//
//  ZombieAnimRig_HeianSushi.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieHeianSushi.h"

ZombieAnimRig_HeianSushi::ZombieAnimRig_HeianSushi()
{
}

ZombieAnimRig_HeianSushi::~ZombieAnimRig_HeianSushi()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_HeianSushi);

void ZombieAnimRig_HeianSushi::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_HeianSushi);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_HeianSushi);
}
