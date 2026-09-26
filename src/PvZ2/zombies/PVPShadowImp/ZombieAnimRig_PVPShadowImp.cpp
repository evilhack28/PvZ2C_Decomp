//
//  ZombieAnimRig_PVPShadowImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPImp.h"

ZombieAnimRig_PVPShadowImp::~ZombieAnimRig_PVPShadowImp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_PVPShadowImp);

void ZombieAnimRig_PVPShadowImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_PVPShadowImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_PVPImp);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_PVPShadowImp);
}
