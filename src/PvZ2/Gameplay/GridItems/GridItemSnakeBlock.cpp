//
//  GridItemSnakeBlock.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSnakeBlock.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSnakeBlock);

void GridItemSnakeBlock::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSnakeBlock);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_bAppear);

	REFLECTION_CLASSBUILDER_END(GridItemSnakeBlock);
}
