//
//  ZombieAnimRig_ImpPorter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityImpPorter.h"

ZombieAnimRig_ImpPorter::ZombieAnimRig_ImpPorter()
{
}

ZombieAnimRig_ImpPorter::~ZombieAnimRig_ImpPorter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ImpPorter);

void ZombieAnimRig_ImpPorter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ImpPorter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ImpPorter);
}

const bool ZombieAnimRig_ImpPorter::getDieShouldBlend()
{
	return false;
}
