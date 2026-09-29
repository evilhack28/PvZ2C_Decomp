//
//  ZombieAnimRig_Bull.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Bull.h"

ZombieAnimRig_Bull::ZombieAnimRig_Bull()
{
	m_running = 0;
}

ZombieAnimRig_Bull::~ZombieAnimRig_Bull()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Bull);

void ZombieAnimRig_Bull::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Bull);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_running);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Bull);
}

const bool ZombieAnimRig_Bull::getDieShouldBlend()
{
	return false;
}

void ZombieAnimRig_Bull::SetRunning(bool i_arg)
{
	m_running = i_arg;
}

