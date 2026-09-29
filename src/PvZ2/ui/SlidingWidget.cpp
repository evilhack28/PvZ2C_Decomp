//
//  SlidingWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SlidingWidget.h"

SlidingWidget::~SlidingWidget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SlidingWidget);

void SlidingWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SlidingWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(int, m_slidingState);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_slideEnabled);
	REFLECTION_CLASSBUILDER_END(SlidingWidget);
}

void SlidingWidget::onSlideInFinished()
{
}

void SlidingWidget::onSlideOutFinished()
{
}
