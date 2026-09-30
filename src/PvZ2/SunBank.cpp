//
//  SunBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SunBank.h"

void SunBank::onLevelStart()
{
}

void SunBank::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SunBank);

void SunBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SunBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(SunBank);
}
