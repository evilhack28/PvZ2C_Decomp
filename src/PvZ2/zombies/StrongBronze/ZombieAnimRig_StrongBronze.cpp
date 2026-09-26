//
//  ZombieAnimRig_StrongBronze.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_StrongBronze.h"

ZombieAnimRig_StrongBronze::~ZombieAnimRig_StrongBronze()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_StrongBronze);

void ZombieAnimRig_StrongBronze::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_StrongBronze);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_bCrazy);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_StrongBronze);
}
