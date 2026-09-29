//
//  GridItemHouse.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemHouse.h"

GridItemHouse::~GridItemHouse()
{
}

GridItemHouseProps::GridItemHouseProps()
{
}

GridItemHouseProps::~GridItemHouseProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHouse);

void GridItemHouse::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHouse);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_row);
	REFLECTION_CLASSBUILDER_END(GridItemHouse);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHouseProps);

void GridItemHouseProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHouseProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPropertySheet);

	REFLECTION_CLASSBUILDER_END(GridItemHouseProps);
}

#include "GridItem.h"
void GridItemHouse::onGridItemInitialize()
{
	 GridItem::onGridItemInitialize();
}
