//
//  ZombieFairyTaleImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFairyTaleImp.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieFairyTaleImp);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieFairyTaleImpProps);

void ZombieFairyTaleImpProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieFairyTaleImpProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, CallKnightType);
	REFLECTION_CLASSBUILDER_END(ZombieFairyTaleImpProps);
}

#include "Zombie.h"
void ZombieFairyTaleImp::onZombieInitialize()
{
	 Zombie::onZombieInitialize();
}

void ZombieFairyTaleImp::onWalkAnimContinued(const std::string& i_animLabel, const std::string& i_nextAnimLabel, int i_cycleCount)
{
}

bool ZombieFairyTaleImp::CheckEdge()
{
	return true;
}

bool ZombieFairyTaleImp::canAttack()
{
	return false;
}
