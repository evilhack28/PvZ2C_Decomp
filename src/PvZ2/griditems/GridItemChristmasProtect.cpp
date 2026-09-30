//
//  GridItemChristmasProtect.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemChristmasProtect.h"

void GridItemChristmasProtect::onPlaceOnBoard()
{
}

GridItemChristmasProtect::GridItemChristmasProtect()
{
	m_stealedNum = 0;
}

GridItemChristmasProtect::~GridItemChristmasProtect()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemChristmasProtect);

void GridItemChristmasProtect::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemChristmasProtect);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_stealedNum);
	REFLECTION_CLASSBUILDER_END(GridItemChristmasProtect);
}

#include "GridItem.h"
void GridItemChristmasProtect::registerForEvents()
{
	 GridItem::registerForEvents();
}

#include "GridItemAnimation.h"
void GridItemChristmasProtect::onUpdate()
{
	 GridItemAnimation::onUpdate();
}
