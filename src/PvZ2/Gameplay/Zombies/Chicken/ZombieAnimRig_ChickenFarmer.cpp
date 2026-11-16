//
//  ZombieAnimRig_ChickenFarmer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_ChickenFarmer.h"

ZombieAnimRig_ChickenFarmer::ZombieAnimRig_ChickenFarmer()
{
	m_hasChickens = 1;
}

ZombieAnimRig_ChickenFarmer::~ZombieAnimRig_ChickenFarmer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ChickenFarmer);

void ZombieAnimRig_ChickenFarmer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ChickenFarmer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ChickenFarmer);
}
