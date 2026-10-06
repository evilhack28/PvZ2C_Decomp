//
//  ZombieZombossMech_IceAge.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_IceAge.h"

ZombieZombossMechIceAgeProps::~ZombieZombossMechIceAgeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMech_IceAge);

void ZombieZombossMech_IceAge::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMech_IceAge);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMech);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_bInEliminate);
	REFLECTION_CLASSBUILDER_END(ZombieZombossMech_IceAge);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMechIceAgeProps);

void ZombieZombossMechIceAgeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMechIceAgeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMechProps);

		REFLECTION_CLASSBUILDER_FIELD(int, IceCrustHealth);
	REFLECTION_CLASSBUILDER_END(ZombieZombossMechIceAgeProps);
}

#include "ZombieZombossMech_IceAge.h"
void ZombieZombossMech_IceAge::onEndCondition(ZombieConditions i_arg)
{
	 ZombieZombossMech_IceAge::updateHelmEffects();
}
