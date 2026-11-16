//
//  HotUIScrollWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIScrollWidget.h"

HotUIScrollWidget::HotUIScrollWidget()
{
	m_scrollListener = 0;
	m_scrollWidget = 0;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIScrollWidget);

void HotUIScrollWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIScrollWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIScrollWidget);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIScrollWidgetProperties);
