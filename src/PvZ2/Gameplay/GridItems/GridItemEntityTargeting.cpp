//
//  GridItemEntityTargeting.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemEntityTargeting.h"

GridItemEntityTargeting::GridItemEntityTargeting()
{
	m_actionInProgress = 0;
	m_lastUsedAction = 0;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemEntityTargeting);

void GridItemEntityTargeting::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemEntityTargeting);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTarget);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_actionInProgress);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<pvztime_t>, m_actionTimers);
		REFLECTION_CLASSBUILDER_FIELD(int, m_lastUsedAction);
	REFLECTION_CLASSBUILDER_END(GridItemEntityTargeting);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemEntityTargetingProps);

void GridItemEntityTargeting::onLevelStart()
{
}

#include "GridItem.h"
void GridItemEntityTargeting::registerForEvents()
{
	 GridItem::registerForEvents();
}
