//
//  UIEasyButtonWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "UIEasyButtonWidget.h"

UIEasyButtonWidget::~UIEasyButtonWidget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(UIEasyButtonWidget);

void UIEasyButtonWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(UIEasyButtonWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(Color, m_buttonColor);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_onPressed);
	REFLECTION_CLASSBUILDER_END(UIEasyButtonWidget);
}
