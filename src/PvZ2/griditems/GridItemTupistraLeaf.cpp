//
//  GridItemTupistraLeaf.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_TupistraStalker.h"

GridItemTupistraLeaf::~GridItemTupistraLeaf()
{
}

GridItemTupistraLeafProps::~GridItemTupistraLeafProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTupistraLeaf);

void GridItemTupistraLeaf::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTupistraLeaf);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(float, m_attackRate);
	REFLECTION_CLASSBUILDER_END(GridItemTupistraLeaf);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTupistraLeafProps);

void GridItemTupistraLeafProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTupistraLeafProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
	REFLECTION_CLASSBUILDER_END(GridItemTupistraLeafProps);
}
