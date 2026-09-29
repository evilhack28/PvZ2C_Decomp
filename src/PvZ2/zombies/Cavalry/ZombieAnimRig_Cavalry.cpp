//
//  ZombieAnimRig_Cavalry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCavalry.h"

ZombieAnimRig_Cavalry::ZombieAnimRig_Cavalry()
{
	m_running = 0;
}

ZombieAnimRig_Cavalry::~ZombieAnimRig_Cavalry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Cavalry);

void ZombieAnimRig_Cavalry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Cavalry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_running);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Cavalry);
}

void ZombieAnimRig_Cavalry::SetRunning(bool i_arg)
{
	m_running = i_arg;
}

