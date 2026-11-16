//
//  ZombieAnimRig_Neuropathy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Neuropathy.h"

ZombieAnimRig_Neuropathy::ZombieAnimRig_Neuropathy()
{
}

ZombieAnimRig_Neuropathy::~ZombieAnimRig_Neuropathy()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Neuropathy);

void ZombieAnimRig_Neuropathy::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Neuropathy);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_Havebox);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Neuropathy);
}
