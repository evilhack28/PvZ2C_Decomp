//
//  ZombieAnimRig_Gum.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieGum.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_Gum::ZombieAnimRig_Gum()
{
}

ZombieAnimRig_Gum::~ZombieAnimRig_Gum()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_Gum);

void ZombieAnimRig_Gum::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Gum);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Gum);
}
