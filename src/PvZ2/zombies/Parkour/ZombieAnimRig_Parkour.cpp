//
//  ZombieAnimRig_Parkour.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieParkour.h"

ZombieAnimRig_Parkour::ZombieAnimRig_Parkour()
{
}

ZombieAnimRig_Parkour::~ZombieAnimRig_Parkour()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Parkour);

void ZombieAnimRig_Parkour::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Parkour);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Parkour);
}

#include "ZombieAnimRig_Basic.h"
void ZombieAnimRig_Parkour::onPopAnimInitialized()
{
	 ZombieAnimRig_Basic::onPopAnimInitialized();
}

bool ZombieAnimRig_Parkour::PlayTackling(std::string animation, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped)
{
	return PlayAndStop(animation, SELECT_EXACT, i_onAnimStopped) != -1;
}

