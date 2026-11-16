//
//  ZombieAnimRig_FairyTaleImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFairyTaleImp.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieAnimRig_FairyTaleImp::~ZombieAnimRig_FairyTaleImp()
{
}

ZombieAnimRig_FairyTaleImp::ZombieAnimRig_FairyTaleImp()
{
	m_running = 0;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_FairyTaleImp);

void ZombieAnimRig_FairyTaleImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_FairyTaleImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Imp);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_running);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_FairyTaleImp);
}

/////////////// Accessors ///////////////

void ZombieAnimRig_FairyTaleImp::SetRunning(bool i_running)
{
	m_running = i_running;
}

/////////////// Logic ///////////////

const std::string ZombieAnimRig_FairyTaleImp::getWalkAnimationName()
{
	const char* aName;
	if (m_running)
		aName = "run";
	else
		aName = "walk";

	return aName;
}
