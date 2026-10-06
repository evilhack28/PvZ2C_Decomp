//
//  GridItemBesiegeGuide.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BesiegeModule.h"

GridItemBesiegeGuide::GridItemBesiegeGuide()
{
}

GridItemBesiegeGuide::~GridItemBesiegeGuide()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBesiegeGuide);

void GridItemBesiegeGuide::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBesiegeGuide);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemBesiegeGuide);
}

#include "GridItem.h"
void GridItemBesiegeGuide::registerForEvents()
{
	 GridItem::registerForEvents();
}

void GridItemBesiegeGuide::onGridItemInitialize()
{
}
