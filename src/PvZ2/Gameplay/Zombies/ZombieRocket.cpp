//
//  ZombieRocket.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombieRocket.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRocket);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRocketProps);

void ZombieRocketProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieRocketProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieRocketProps);
}

void ZombieRocket::onLostArm()
{
}
