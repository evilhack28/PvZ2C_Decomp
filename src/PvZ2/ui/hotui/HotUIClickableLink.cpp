//
//  HotUIClickableLink.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HotUIClickableLink.h"

HotUIClickableLinkProperties::~HotUIClickableLinkProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIClickableLink);

void HotUIClickableLink::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIClickableLink);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidget);

	REFLECTION_CLASSBUILDER_END(HotUIClickableLink);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIClickableLinkProperties);

void HotUIClickableLinkProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIClickableLinkProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIWidgetProperties);

	REFLECTION_CLASSBUILDER_END(HotUIClickableLinkProperties);
}
