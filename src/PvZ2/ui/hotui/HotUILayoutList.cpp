//
//  HotUILayoutList.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUILayoutList.h"

HotUILayoutListProperties::~HotUILayoutListProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUILayoutList);

void HotUILayoutList::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUILayoutList);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUILayoutList);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUILayoutListProperties);

void HotUILayoutListProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUILayoutListProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

	REFLECTION_CLASSBUILDER_END(HotUILayoutListProperties);
}

#include "HotUILayoutList.h"
void HotUILayoutList::onLayoutFinalized()
{
	 HotUILayoutList::performLayout();
}
