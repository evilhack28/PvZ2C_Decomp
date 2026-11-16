//
//  ZombieAnimRig_Seagull.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Seagull.h"

ZombieAnimRig_Seagull::ZombieAnimRig_Seagull()
{
}

ZombieAnimRig_Seagull::~ZombieAnimRig_Seagull()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Seagull);

void ZombieAnimRig_Seagull::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Seagull);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Seagull);
}

#include "ZombieAnimRig.h"
void ZombieAnimRig_Seagull::onNeedsToDie()
{
	 ZombieAnimRig::setReadyToDie();
}
