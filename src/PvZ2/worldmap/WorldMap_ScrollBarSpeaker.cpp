//
//  WorldMap_ScrollBarSpeaker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_ScrollBarSpeaker.h"

WorldMap_ScrollBarSpeaker::~WorldMap_ScrollBarSpeaker()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_ScrollBarSpeaker);

void WorldMap_ScrollBarSpeaker::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_ScrollBarSpeaker);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(SexyString, m_textToScroll);
		REFLECTION_CLASSBUILDER_FIELD(Sexy::Color, m_color);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_startScrollingText);
	REFLECTION_CLASSBUILDER_END(WorldMap_ScrollBarSpeaker);
}

void WorldMap_ScrollBarSpeaker::initLoadingResourcesGroupList()
{
}
