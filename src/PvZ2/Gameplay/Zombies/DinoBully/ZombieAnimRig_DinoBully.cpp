//
//  ZombieAnimRig_DinoBully.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieDinoBully.h"

ZombieAnimRig_DinoBully::ZombieAnimRig_DinoBully()
{
}

ZombieAnimRig_DinoBully::~ZombieAnimRig_DinoBully()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_DinoBully);

void ZombieAnimRig_DinoBully::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_DinoBully);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_DinoBasic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_DinoBully);
}
