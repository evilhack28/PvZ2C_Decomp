//
//  ZombieAnimRig_ZombossQigong.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_ZombossQigong.h"

ZombieAnimRig_ZombossQigong::ZombieAnimRig_ZombossQigong()
{
}

ZombieAnimRig_ZombossQigong::~ZombieAnimRig_ZombossQigong()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossQigong);

void ZombieAnimRig_ZombossQigong::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossQigong);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Zomboss);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossQigong);
}
