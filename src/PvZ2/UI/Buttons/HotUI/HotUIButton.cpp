//
//  HotUIButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIButton.h"

HotUIButtonProperties::~HotUIButtonProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIButton);

void HotUIButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIButton);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIButtonProperties);

void HotUIButtonProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIButtonProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

		REFLECTION_CLASSBUILDER_FIELD(DynamicPadding, LabelInset);
		REFLECTION_CLASSBUILDER_FIELD(bool, HideButtonImages);
		REFLECTION_CLASSBUILDER_FIELD(UIImageType, ButtonImageType);
		REFLECTION_CLASSBUILDER_FIELD(UIImageDrawStyle, ButtonImageDrawStyle);
	REFLECTION_CLASSBUILDER_END(HotUIButtonProperties);
}

#include "HotUIButton.h"
void HotUIButton::onLayoutFinalized()
{
	 HotUIButton::setButtonSize();
}
