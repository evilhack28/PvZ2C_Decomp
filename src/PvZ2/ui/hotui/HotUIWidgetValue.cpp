//
//  HotUIWidgetValue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HotUIWidgetValue.h"

HotUIWidgetValue::~HotUIWidgetValue()
{
}

HotUIWidgetValueProperties::~HotUIWidgetValueProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIWidgetValue);

void HotUIWidgetValue::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIWidgetValue);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIWidgetValue);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIWidgetValueProperties);

void HotUIWidgetValueProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIWidgetValueProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

	REFLECTION_CLASSBUILDER_END(HotUIWidgetValueProperties);
}
