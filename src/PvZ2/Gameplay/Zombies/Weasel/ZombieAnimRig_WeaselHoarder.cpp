//
//  ZombieAnimRig_WeaselHoarder.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_ChickenFarmer.h"

ZombieAnimRig_WeaselHoarder::ZombieAnimRig_WeaselHoarder()
{
}

ZombieAnimRig_WeaselHoarder::~ZombieAnimRig_WeaselHoarder()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_WeaselHoarder);

void ZombieAnimRig_WeaselHoarder::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_WeaselHoarder);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ChickenFarmer);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ZombieChickenFarmer>, m_zombiePtr);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_WeaselHoarder);
}
