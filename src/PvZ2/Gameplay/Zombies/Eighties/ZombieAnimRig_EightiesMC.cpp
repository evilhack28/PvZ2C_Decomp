//
//  ZombieAnimRig_EightiesMC.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesMC.h"

ZombieAnimRig_EightiesMC::~ZombieAnimRig_EightiesMC()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_EightiesMC);

void ZombieAnimRig_EightiesMC::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_EightiesMC);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_jamActive);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_EightiesMC);
}
