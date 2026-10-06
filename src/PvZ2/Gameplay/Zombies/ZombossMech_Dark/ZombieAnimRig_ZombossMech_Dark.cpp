//
//  ZombieAnimRig_ZombossMech_Dark.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_Dark.h"

ZombieAnimRig_ZombossMech_Dark::~ZombieAnimRig_ZombossMech_Dark()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossMech_Dark);

void ZombieAnimRig_ZombossMech_Dark::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossMech_Dark);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ZombossMech);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_playingIdle);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossMech_Dark);
}
