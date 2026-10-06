//
//  ZombieAnimRig_BeachSurfer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBeachSurfer.h"

ZombieAnimRig_BeachSurfer::ZombieAnimRig_BeachSurfer()
{
	m_hasSurfboard = 1;
}

ZombieAnimRig_BeachSurfer::~ZombieAnimRig_BeachSurfer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_BeachSurfer);

void ZombieAnimRig_BeachSurfer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_BeachSurfer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasSurfboard);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_BeachSurfer);
}

const bool ZombieAnimRig_BeachSurfer::getDieShouldBlend()
{
	return false;
}
