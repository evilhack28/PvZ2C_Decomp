//
//  ZombieAnimRig_TreasureYeti.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_TreasureYeti.h"

ZombieAnimRig_TreasureYeti::ZombieAnimRig_TreasureYeti()
{
}

ZombieAnimRig_TreasureYeti::~ZombieAnimRig_TreasureYeti()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_TreasureYeti);

void ZombieAnimRig_TreasureYeti::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_TreasureYeti);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_TreasureYeti);
}
