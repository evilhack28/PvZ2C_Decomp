//
//  ZombieAnimRig_Parrot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Parrot.h"

ZombieAnimRig_Parrot::ZombieAnimRig_Parrot()
{
}

ZombieAnimRig_Parrot::~ZombieAnimRig_Parrot()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Parrot);

void ZombieAnimRig_Parrot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Parrot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Parrot);
}

#include "ZombieAnimRig.h"
void ZombieAnimRig_Parrot::onNeedsToDie()
{
	 ZombieAnimRig::setReadyToDie();
}
