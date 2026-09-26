//
//  ZombieAnimRig_FairyTaleImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFairyTaleImp.h"

ZombieAnimRig_FairyTaleImp::~ZombieAnimRig_FairyTaleImp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_FairyTaleImp);

void ZombieAnimRig_FairyTaleImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_FairyTaleImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Imp);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_running);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_FairyTaleImp);
}

ZombieAnimRig_FairyTaleImp::ZombieAnimRig_FairyTaleImp()
{
	m_running = 0;
}

void ZombieAnimRig_FairyTaleImp::SetRunning(bool i_arg)
{
	m_running = i_arg;
}
