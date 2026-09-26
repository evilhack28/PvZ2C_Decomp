//
//  ComponentZombieWhackTouch.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ComponentZombieWhackTouch.h"

void ComponentZombieWhackTouch::onEnd()
{
}

void ComponentZombieWhackTouch::onUpdate()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentZombieWhackTouch);

void ComponentZombieWhackTouch::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ComponentZombieWhackTouch);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ComponentBase);

	REFLECTION_CLASSBUILDER_FIELD(float, m_currentHitFraction);

	REFLECTION_CLASSBUILDER_END(ComponentZombieWhackTouch);
}

void ComponentZombieWhackTouch::onBegin()
{
}
