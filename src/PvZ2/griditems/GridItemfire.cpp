//
//  GridItemfire.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Rapeflower.h"

GridItemfire::~GridItemfire()
{
}

GridItemfireProps::~GridItemfireProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemfire);

void GridItemfire::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemfire);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(float, DamagePerSecond);
	REFLECTION_CLASSBUILDER_END(GridItemfire);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemfireProps);

void GridItemfireProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemfireProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemfireProps);
}
