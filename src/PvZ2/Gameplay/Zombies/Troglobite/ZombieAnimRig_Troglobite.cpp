//
//  ZombieAnimRig_Troglobite.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeTroglobite.h"

ZombieAnimRig_Troglobite::ZombieAnimRig_Troglobite()
{
}

ZombieAnimRig_Troglobite::~ZombieAnimRig_Troglobite()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Troglobite);

void ZombieAnimRig_Troglobite::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Troglobite);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithPushingActionAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Troglobite);
}
