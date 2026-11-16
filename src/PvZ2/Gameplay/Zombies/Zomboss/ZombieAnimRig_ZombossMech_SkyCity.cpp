//
//  ZombieAnimRig_ZombossMech_SkyCity.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_SkyCity.h"

ZombieAnimRig_ZombossMech_SkyCity::~ZombieAnimRig_ZombossMech_SkyCity()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossMech_SkyCity);

void ZombieAnimRig_ZombossMech_SkyCity::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossMech_SkyCity);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ZombossMech);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_playingIdle);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossMech_SkyCity);
}
