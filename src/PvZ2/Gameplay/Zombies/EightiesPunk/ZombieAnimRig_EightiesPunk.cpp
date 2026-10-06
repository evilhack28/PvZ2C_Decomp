//
//  ZombieAnimRig_EightiesPunk.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesPunk.h"

ZombieAnimRig_EightiesPunk::ZombieAnimRig_EightiesPunk()
{
	m_isJamming = 0;
}

ZombieAnimRig_EightiesPunk::~ZombieAnimRig_EightiesPunk()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_EightiesPunk);

void ZombieAnimRig_EightiesPunk::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_EightiesPunk);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isJamming);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_EightiesPunk);
}
