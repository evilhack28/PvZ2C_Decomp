//
//  HotUIVerticalList.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIVerticalList.h"

HotUIVerticalListProperties::~HotUIVerticalListProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIVerticalList);

void HotUIVerticalList::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIVerticalList);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIVerticalList);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIVerticalListProperties);

void HotUIVerticalListProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIVerticalListProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

		REFLECTION_CLASSBUILDER_FIELD(DynamicSizeData, SpaceBetweenWidgets);
		REFLECTION_CLASSBUILDER_FIELD(int, NumColumns);
	REFLECTION_CLASSBUILDER_END(HotUIVerticalListProperties);
}

#include "HotUIVerticalList.h"
void HotUIVerticalList::onLayoutFinalized()
{
	 HotUIVerticalList::RepositionChildrenAndResize();
}
