//
//  SkyCannonUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SkyCannonUI.h"

void SkyCannonUI::initLoadingResourcesGroupList()
{
}

SkyCannonUI::~SkyCannonUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SkyCannonUI);

void SkyCannonUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SkyCannonUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(SkyCannonUI);
}

void SkyCannonUI::onCursorDestroyed(class BaseCursor* i_arg)
{
}
