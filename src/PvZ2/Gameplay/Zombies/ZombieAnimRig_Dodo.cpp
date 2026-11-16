//
//  ZombieAnimRig_Dodo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeDodo.h"

ZombieAnimRig_Dodo::ZombieAnimRig_Dodo()
{
}

ZombieAnimRig_Dodo::~ZombieAnimRig_Dodo()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Dodo);

void ZombieAnimRig_Dodo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Dodo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Dodo);
}
