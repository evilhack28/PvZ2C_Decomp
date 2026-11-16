//
//  ZombiePumpkinKnight.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePumpkinKnight.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePumpkinKnight);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePumpkinKnightProps);

void ZombiePumpkinKnightProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePumpkinKnightProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(Rect, AttackRectInPhase2);
	REFLECTION_CLASSBUILDER_END(ZombiePumpkinKnightProps);
}

void ZombiePumpkinKnight::onZombieInitialize()
{
}

void ZombiePumpkinKnight::switchPopAnimRigToPhase2()
{
}

#include "ZombiePumpkinKnight.h"
void ZombiePumpkinKnight::onRetreatStartAnimationDone()
{
	 ZombiePumpkinKnight::playRetreatLoopAnimation();
}
