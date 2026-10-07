//
//  ZombieAnimRig_IceBall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_IceBall.h"
#include "ReflectionBuilder.h"
#include "ZombieAnimRig.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_IceBall::ZombieAnimRig_IceBall()
{
}

ZombieAnimRig_IceBall::~ZombieAnimRig_IceBall()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_IceBall);

void ZombieAnimRig_IceBall::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_IceBall);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_IceBall);
}

/////////////// Logic ///////////////

void ZombieAnimRig_IceBall::PlayMove()
{
	PlayAndContinue("roll");
}

void ZombieAnimRig_IceBall::onNeedsToDie()
{
	 ZombieAnimRig::setReadyToDie();
}
