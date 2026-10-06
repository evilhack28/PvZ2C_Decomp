//
//  ZombieAnimRig_DarkKing.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieDarkKing.h"

ZombieAnimRig_DarkKing::ZombieAnimRig_DarkKing()
{
}

ZombieAnimRig_DarkKing::~ZombieAnimRig_DarkKing()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_DarkKing);

void ZombieAnimRig_DarkKing::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_DarkKing);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_DarkKing);
}
