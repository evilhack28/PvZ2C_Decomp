//
//  ZombieAnimRig_ZombossMech_Dino.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_Dino.h"

ZombieAnimRig_ZombossMech_Dino::~ZombieAnimRig_ZombossMech_Dino()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossMech_Dino);

void ZombieAnimRig_ZombossMech_Dino::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossMech_Dino);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ZombossMech);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_playingIdle);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossMech_Dino);
}
