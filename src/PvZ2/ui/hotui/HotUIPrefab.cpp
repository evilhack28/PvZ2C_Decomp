//
//  HotUIPrefab.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HotUIPrefab.h"

HotUIPrefab::~HotUIPrefab()
{
}

HotUIPrefabProperties::~HotUIPrefabProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIPrefab);

void HotUIPrefab::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIPrefab);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIPrefab);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIPrefabProperties);

void HotUIPrefabProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIPrefabProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

	REFLECTION_CLASSBUILDER_END(HotUIPrefabProperties);
}
