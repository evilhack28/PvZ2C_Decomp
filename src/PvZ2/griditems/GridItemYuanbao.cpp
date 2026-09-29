//
//  GridItemYuanbao.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMoneyTree.h"

GridItemYuanbao::GridItemYuanbao()
{
}

GridItemYuanbao::~GridItemYuanbao()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemYuanbao);

void GridItemYuanbao::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemYuanbao);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemYuanbao);
}
