//
//  ZombieAnimRig_TurkeypultBase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieTurkeypultBasic.h"

ZombieAnimRig_TurkeypultBase::ZombieAnimRig_TurkeypultBase()
{
}

ZombieAnimRig_TurkeypultBase::~ZombieAnimRig_TurkeypultBase()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_TurkeypultBase);

void ZombieAnimRig_TurkeypultBase::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_TurkeypultBase);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_TurkeypultBase);
}
