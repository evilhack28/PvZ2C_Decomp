//
//  GridItemCrater.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCrater.h"
#include "ReflectionBuilder.h"
#include "GridItemAnimation.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

GridItemCrater::GridItemCrater()
{
}

GridItemCrater::~GridItemCrater()
{
}

GridItemCraterProps::~GridItemCraterProps()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(GridItemCrater);

void GridItemCrater::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCrater);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemCrater);
}

RT_CLASS_IMPLEMENT(GridItemCraterProps);

void GridItemCraterProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCraterProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
	REFLECTION_CLASSBUILDER_END(GridItemCraterProps);
}

/////////////// Logic ///////////////

void GridItemCrater::onGridItemInitialize()
{
	 GridItemAnimation::setDefaultAnimRig();
}
