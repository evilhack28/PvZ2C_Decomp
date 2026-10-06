//
//  ZombieAnimRig_Electric.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSkyCityElectric.h"

ZombieAnimRig_Electric::ZombieAnimRig_Electric()
{
}

ZombieAnimRig_Electric::~ZombieAnimRig_Electric()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Electric);

void ZombieAnimRig_Electric::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Electric);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_SkyCity);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Electric);
}
