//
//  ZombieAnimRig_Hammer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Hammer.h"

ZombieAnimRig_Hammer::ZombieAnimRig_Hammer()
{
}

ZombieAnimRig_Hammer::~ZombieAnimRig_Hammer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Hammer);

void ZombieAnimRig_Hammer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Hammer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Hammer);
}

#include "ZombieAnimRig.h"
void ZombieAnimRig_Hammer::onPopAnimInitialized()
{
	 ZombieAnimRig::onPopAnimInitialized();
}
