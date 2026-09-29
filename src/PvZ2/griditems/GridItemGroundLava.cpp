//
//  GridItemGroundLava.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LavaGuava.h"

GridItemGroundLava::GridItemGroundLava()
{
}

GridItemGroundLava::~GridItemGroundLava()
{
}

GridItemGroundLavaProps::GridItemGroundLavaProps()
{
}

GridItemGroundLavaProps::~GridItemGroundLavaProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGroundLava);

void GridItemGroundLava::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGroundLava);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemLava);

	REFLECTION_CLASSBUILDER_END(GridItemGroundLava);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGroundLavaProps);

void GridItemGroundLavaProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGroundLavaProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemLavaProps);

	REFLECTION_CLASSBUILDER_END(GridItemGroundLavaProps);
}

void GridItemGroundLava::onAnimStopped(const std::string & i_arg)
{
}
