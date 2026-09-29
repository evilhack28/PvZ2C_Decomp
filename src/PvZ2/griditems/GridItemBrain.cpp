//
//  GridItemBrain.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemBrain.h"

GridItemBrain::GridItemBrain()
{
	m_hasPlayDieAnim = 0;
	m_row = 0;
}

GridItemBrain::~GridItemBrain()
{
}

GridItemBrainProps::GridItemBrainProps()
{
}

GridItemBrainProps::~GridItemBrainProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBrain);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBrainProps);

void GridItemBrainProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBrainProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPropertySheet);

	REFLECTION_CLASSBUILDER_END(GridItemBrainProps);
}

#include "GridItem.h"
void GridItemBrain::onGridItemInitialize()
{
	 GridItem::onGridItemInitialize();
}
