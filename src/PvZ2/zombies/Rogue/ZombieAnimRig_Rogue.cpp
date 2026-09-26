//
//  ZombieAnimRig_Rogue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Rogue.h"

ZombieAnimRig_Rogue::ZombieAnimRig_Rogue()
{
}

ZombieAnimRig_Rogue::~ZombieAnimRig_Rogue()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Rogue);

void ZombieAnimRig_Rogue::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Rogue);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_isInvisible);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Rogue);
}
