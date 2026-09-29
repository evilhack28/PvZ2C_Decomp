//
//  ZombieCamelTouch.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCamelTouch.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCamelTouch);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCamelTouchProps);

void ZombieCamelTouchProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieCamelTouchProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieCamelProps);

	REFLECTION_CLASSBUILDER_END(ZombieCamelTouchProps);
}

#include "ZombieCamelTouch.h"
void ZombieCamelTouch::TriggerMatched()
{
	 ZombieCamelTouch::onCardMatched();
}

void ZombieCamelTouch::BecomeHeadZombie(ZombieTypePtr i_arg)
{
}
