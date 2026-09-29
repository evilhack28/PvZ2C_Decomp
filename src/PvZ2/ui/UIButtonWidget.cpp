//
//  UIButtonWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "UIButtonWidget.h"

UIButtonWidget::~UIButtonWidget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(UIButtonWidget);

void UIButtonWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(UIButtonWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(UIButtonWidget);
}

void UIButtonWidget::performButtonAction()
{
}
