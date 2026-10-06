//
//  ZombieAnimRig_MagicBronze.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_MagicBronze.h"

ZombieAnimRig_MagicBronze::ZombieAnimRig_MagicBronze()
{
}

ZombieAnimRig_MagicBronze::~ZombieAnimRig_MagicBronze()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_MagicBronze);

void ZombieAnimRig_MagicBronze::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_MagicBronze);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_MagicBronze);
}
