//
//  ZombieAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig.h"

bool ZombieAnimRig::IsReadyToDie()
{
	return true;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig);

void ZombieAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_state);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_needsToDieRequestedTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_readyToDie);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig);
}

void ZombieAnimRig::CursorAnimChange(class Zombie* i_zombie)
{
}

const std::string ZombieAnimRig::getWalkAnimationName()
{
	return "walk";
}

