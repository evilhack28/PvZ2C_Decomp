//
//  CustomLevelAppraiseUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CustomLevelAppraiseUI.h"

void CustomLevelAppraiseUI::unregisterForEvents()
{
}

void CustomLevelAppraiseUI::initLoadingResourcesGroupList()
{
}

CustomLevelAppraiseUI::~CustomLevelAppraiseUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CustomLevelAppraiseUI);

void CustomLevelAppraiseUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CustomLevelAppraiseUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(int, m_currentPress);
		REFLECTION_CLASSBUILDER_FIELD(float, m_countTimer);
	REFLECTION_CLASSBUILDER_END(CustomLevelAppraiseUI);
}
