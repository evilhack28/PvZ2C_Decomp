//
//  GridItemSushi.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieHeianSushi.h"

GridItemSushi::GridItemSushi()
{
}

GridItemSushi::~GridItemSushi()
{
}

GridItemSushiProps::~GridItemSushiProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSushi);

void GridItemSushi::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSushi);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTarget);

	REFLECTION_CLASSBUILDER_END(GridItemSushi);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSushiProps);

void GridItemSushiProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSushiProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(float, SpeedUpTimer);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, BlackList);
	REFLECTION_CLASSBUILDER_END(GridItemSushiProps);
}
