//
//  GridItemTinyLava.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LavaGuava.h"

GridItemTinyLava::GridItemTinyLava()
{
}

GridItemTinyLava::~GridItemTinyLava()
{
}

GridItemTinyLavaProps::GridItemTinyLavaProps()
{
}

GridItemTinyLavaProps::~GridItemTinyLavaProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTinyLava);

void GridItemTinyLava::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTinyLava);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemLava);

	REFLECTION_CLASSBUILDER_END(GridItemTinyLava);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTinyLavaProps);

void GridItemTinyLavaProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTinyLavaProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemLavaProps);

	REFLECTION_CLASSBUILDER_END(GridItemTinyLavaProps);
}

void GridItemTinyLava::onAnimStopped(const std::string & i_arg)
{
}
