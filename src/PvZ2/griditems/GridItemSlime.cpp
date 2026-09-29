//
//  GridItemSlime.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PrimalRafflesia.h"

GridItemSlime::~GridItemSlime()
{
}

GridItemSlimeProps::~GridItemSlimeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSlime);

void GridItemSlime::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSlime);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_advanced);
	REFLECTION_CLASSBUILDER_END(GridItemSlime);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSlimeProps);

void GridItemSlimeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSlimeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
	REFLECTION_CLASSBUILDER_END(GridItemSlimeProps);
}
