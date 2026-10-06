//
//  TimerBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "TimerBank.h"

void TimerBank::registerForEvents()
{
}

void TimerBank::unregisterForEvents()
{
}

void TimerBank::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TimerBank);

void TimerBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TimerBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(TimerBank);
}
