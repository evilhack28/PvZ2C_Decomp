//
//  GridItemIcyFence.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemIcyFence.h"

GridItemIcyFenceProps::~GridItemIcyFenceProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemIcyFence);

void GridItemIcyFence::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemIcyFence);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_counter);
		REFLECTION_CLASSBUILDER_FIELD(float, m_nextAttackTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, m_windEffect);
	REFLECTION_CLASSBUILDER_END(GridItemIcyFence);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemIcyFenceProps);

void GridItemIcyFenceProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemIcyFenceProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemIcyFenceProps);
}

bool GridItemIcyFence::IsDamageable() const
{
	return false;
}
