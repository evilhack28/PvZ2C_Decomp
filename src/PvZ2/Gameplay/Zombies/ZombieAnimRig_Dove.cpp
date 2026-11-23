//
//  ZombieAnimRig_Dove.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCarnieMagician.h"

ZombieAnimRig_Dove::ZombieAnimRig_Dove()
{
}

ZombieAnimRig_Dove::~ZombieAnimRig_Dove()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Dove);

void ZombieAnimRig_Dove::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Dove);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Parrot);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Dove);
}

bool ZombieAnimRig_Dove::PlayCarry()
{
	return PlayAndContinue("fly") != -1;
}

bool ZombieAnimRig_Dove::PlayFly()
{
	return PlayAndContinue("fly") != -1;
}

bool ZombieAnimRig_Dove::PlayFlyBack()
{
	return PlayAndContinue("fly_back") != -1;
}
