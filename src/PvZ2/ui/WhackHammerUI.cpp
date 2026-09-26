//
//  WhackHammerUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WhackHammerUI.h"

void WhackHammerUI::initLoadingResourcesGroupList()
{
}

void WhackHammerUI::onUpdate()
{
}

WhackHammerUI::~WhackHammerUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WhackHammerUI);

void WhackHammerUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WhackHammerUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_levelEnded);

	REFLECTION_CLASSBUILDER_END(WhackHammerUI);
}
