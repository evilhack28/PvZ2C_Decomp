//
//  ZombieAnimRig_FutureImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFutureImp.h"

ZombieAnimRig_FutureImp::~ZombieAnimRig_FutureImp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_FutureImp);

void ZombieAnimRig_FutureImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_FutureImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Imp);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isFallingFromSky);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_FutureImp);
}
