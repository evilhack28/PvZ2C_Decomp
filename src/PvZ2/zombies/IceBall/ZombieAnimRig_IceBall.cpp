//
//  ZombieAnimRig_IceBall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_IceBall.h"

ZombieAnimRig_IceBall::ZombieAnimRig_IceBall()
{
}

ZombieAnimRig_IceBall::~ZombieAnimRig_IceBall()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_IceBall);

void ZombieAnimRig_IceBall::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_IceBall);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_IceBall);
}

#include "ZombieAnimRig.h"
void ZombieAnimRig_IceBall::onNeedsToDie()
{
	 ZombieAnimRig::setReadyToDie();
}
