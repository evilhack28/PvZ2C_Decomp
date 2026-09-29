//
//  HotUISlider.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUISlider.h"

HotUISliderProperties::~HotUISliderProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUISlider);

void HotUISlider::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUISlider);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUISlider);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUISliderProperties);

void HotUISliderProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUISliderProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

	REFLECTION_CLASSBUILDER_END(HotUISliderProperties);
}
