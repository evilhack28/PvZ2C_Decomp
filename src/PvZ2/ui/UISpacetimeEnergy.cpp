//
//  UISpacetimeEnergy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "UISpacetimeEnergy.h"

void UISpacetimeEnergy::unregisterForEvents()
{
}

void UISpacetimeEnergy::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(UISpacetimeEnergy);

void UISpacetimeEnergy::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(UISpacetimeEnergy);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(UISpacetimeEnergy);
}
