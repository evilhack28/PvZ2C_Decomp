//
//  ZombieAnimRig_PirateCaptain.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_PirateCaptain.h"

ZombieAnimRig_PirateCaptain::ZombieAnimRig_PirateCaptain()
{
}

ZombieAnimRig_PirateCaptain::~ZombieAnimRig_PirateCaptain()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_PirateCaptain);

void ZombieAnimRig_PirateCaptain::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_PirateCaptain);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_PirateCaptain);
}
