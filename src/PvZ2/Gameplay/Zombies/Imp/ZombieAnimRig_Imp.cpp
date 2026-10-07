//
//  ZombieAnimRig_Imp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Imp.h"

bool ZombieAnimRig_Imp::PlayFalling()
{
	return false;
}

ZombieAnimRig_Imp::ZombieAnimRig_Imp()
{
}

ZombieAnimRig_Imp::~ZombieAnimRig_Imp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Imp);

void ZombieAnimRig_Imp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Imp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Imp);
}

bool ZombieAnimRig_Imp::PlayBonk(AnimStoppedReflectionDelegate i_onAnimStopped)
{
	return false;
}

bool ZombieAnimRig_Imp::PlayGetUp(AnimStoppedReflectionDelegate i_onAnimStopped)
{
	return false;
}
