//
//  ZombieAnimRig_ZombossMech_Steam.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_Steam.h"

ZombieAnimRig_ZombossMech_Steam::~ZombieAnimRig_ZombossMech_Steam()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossMech_Steam);

void ZombieAnimRig_ZombossMech_Steam::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossMech_Steam);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ZombossMech);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossMech_Steam);
}
