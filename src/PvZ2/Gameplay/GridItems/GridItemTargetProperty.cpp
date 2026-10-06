//
//  GridItemTargetProperty.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CardTarget.h"

GridItemTargetProperty::~GridItemTargetProperty()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTargetProperty);

void GridItemTargetProperty::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTargetProperty);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridTargetProperty);

	REFLECTION_CLASSBUILDER_END(GridItemTargetProperty);
}
