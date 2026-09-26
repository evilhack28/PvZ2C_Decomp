//
//  ZombieAnimRig_ShooterBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieShooter.h"

ZombieAnimRig_ShooterBasic::ZombieAnimRig_ShooterBasic()
{
}

ZombieAnimRig_ShooterBasic::~ZombieAnimRig_ShooterBasic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ShooterBasic);

void ZombieAnimRig_ShooterBasic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ShooterBasic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ShooterBasic);
}
