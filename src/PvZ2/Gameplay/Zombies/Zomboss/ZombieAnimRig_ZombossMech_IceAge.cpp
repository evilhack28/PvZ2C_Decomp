//
//  ZombieAnimRig_ZombossMech_IceAge.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_IceAge.h"

ZombieAnimRig_ZombossMech_IceAge::ZombieAnimRig_ZombossMech_IceAge()
{
	m_isCovered = 0;
}

ZombieAnimRig_ZombossMech_IceAge::~ZombieAnimRig_ZombossMech_IceAge()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossMech_IceAge);

void ZombieAnimRig_ZombossMech_IceAge::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossMech_IceAge);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ZombossMech);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isCovered);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossMech_IceAge);
}
