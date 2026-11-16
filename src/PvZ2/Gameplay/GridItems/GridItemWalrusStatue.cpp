//
//  GridItemWalrusStatue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemWalrusStatue.h"

GridItemWalrusStatue::GridItemWalrusStatue()
{
}

GridItemWalrusStatue::~GridItemWalrusStatue()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemWalrusStatue);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemWalrusStatuePropertySheet);

void GridItemWalrusStatuePropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemWalrusStatuePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemWalrusStatuePropertySheet);
}

#include "GridItem.h"
void GridItemWalrusStatue::registerForEvents()
{
	 GridItem::registerForEvents();
}
