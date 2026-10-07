//
//  ZombieAnimRig_Walrus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeWalrus.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_Walrus::ZombieAnimRig_Walrus()
{
}

ZombieAnimRig_Walrus::~ZombieAnimRig_Walrus()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_Walrus);

void ZombieAnimRig_Walrus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Walrus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Walrus);
}
