//
//  ZombieAnimRig_PumpkinKnight.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePumpkinKnight.h"

ZombieAnimRig_PumpkinKnight::ZombieAnimRig_PumpkinKnight()
{
}

ZombieAnimRig_PumpkinKnight::~ZombieAnimRig_PumpkinKnight()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_PumpkinKnight);

void ZombieAnimRig_PumpkinKnight::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_PumpkinKnight);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int, m_currentAnimPhase);
	REFLECTION_CLASSBUILDER_FIELD(bool, m_isRunning);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_PumpkinKnight);
}
