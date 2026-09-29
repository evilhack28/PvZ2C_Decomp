//
//  GridItemDusklobberFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Dusklobber.h"

GridItemDusklobberFlower::~GridItemDusklobberFlower()
{
}

GridItemDusklobberFlowerProps::~GridItemDusklobberFlowerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemDusklobberFlower);

void GridItemDusklobberFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemDusklobberFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(GridItemDusklobberFlower);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemDusklobberFlowerProps);

void GridItemDusklobberFlowerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemDusklobberFlowerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
	REFLECTION_CLASSBUILDER_END(GridItemDusklobberFlowerProps);
}
