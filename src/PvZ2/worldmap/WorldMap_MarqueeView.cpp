//
//  WorldMap_MarqueeView.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_MarqueeView.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_MarqueeView);

void WorldMap_MarqueeView::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_MarqueeView);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::Widget);

	REFLECTION_CLASSBUILDER_END(WorldMap_MarqueeView);
}

void WorldMap_MarqueeView::ScrollTargetReached(ScrollWidget* i_arg)
{
}

void WorldMap_MarqueeView::OnOrientationChanged()
{
}

void WorldMap_MarqueeView::ScrollTargetInterrupted(ScrollWidget* i_arg)
{
}
