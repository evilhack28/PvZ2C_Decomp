//
//  ShovelUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ShovelUI.h"

void ShovelUI::initLoadingResourcesGroupList()
{
}

void ShovelUI::onUpdate()
{
}

ShovelUI::~ShovelUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ShovelUI);

void ShovelUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ShovelUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(ShovelUI);
}
