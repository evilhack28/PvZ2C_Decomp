//
//  HotUIButtonList.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HotUIButtonList.h"

HotUIButtonListProperties::~HotUIButtonListProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIButtonList);

void HotUIButtonList::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIButtonList);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUILayoutList);

	REFLECTION_CLASSBUILDER_END(HotUIButtonList);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIButtonListProperties);

void HotUIButtonListProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIButtonListProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUILayoutListProperties);

	REFLECTION_CLASSBUILDER_END(HotUIButtonListProperties);
}
