//
//  GridItemCrater.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCrater.h"

GridItemCrater::GridItemCrater()
{
}

GridItemCrater::~GridItemCrater()
{
}

GridItemCraterProps::~GridItemCraterProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCrater);

void GridItemCrater::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCrater);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemCrater);
}

#include "GridItemAnimation.h"
void GridItemCrater::onGridItemInitialize()
{
	 GridItemAnimation::setDefaultAnimRig();
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCraterProps);
