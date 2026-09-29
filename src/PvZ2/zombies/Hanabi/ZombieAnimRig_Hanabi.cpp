//
//  ZombieAnimRig_Hanabi.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieHanabi.h"

ZombieAnimRig_Hanabi::ZombieAnimRig_Hanabi()
{
}

ZombieAnimRig_Hanabi::~ZombieAnimRig_Hanabi()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Hanabi);

void ZombieAnimRig_Hanabi::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Hanabi);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Hanabi);
}
