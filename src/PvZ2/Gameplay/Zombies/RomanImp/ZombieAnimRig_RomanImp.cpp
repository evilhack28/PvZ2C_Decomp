//
//  ZombieAnimRig_RomanImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieRomanImp.h"

ZombieAnimRig_RomanImp::ZombieAnimRig_RomanImp()
{
}

ZombieAnimRig_RomanImp::~ZombieAnimRig_RomanImp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_RomanImp);

void ZombieAnimRig_RomanImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_RomanImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Imp);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_RomanImp);
}
