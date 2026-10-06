//
//  ZombieAnimRig_Ballet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBallet.h"

ZombieAnimRig_Ballet::ZombieAnimRig_Ballet()
{
}

ZombieAnimRig_Ballet::~ZombieAnimRig_Ballet()
{
}

void ZombieAnimRig_Ballet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Ballet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ZombieBallet>, m_zombie);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Ballet);
}
