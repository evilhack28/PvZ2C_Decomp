//
//  GridItemspearrain.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BambooSpartan.h"

GridItemspearrainProps::~GridItemspearrainProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemspearrainProps);

void GridItemspearrainProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemspearrainProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemspearrainProps);
}
