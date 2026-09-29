//
//  GridItemCardGameZombie.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombie.h"

GridItemCardGameZombie::GridItemCardGameZombie()
{
}

GridItemCardGameZombieProps::~GridItemCardGameZombieProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombie);

void GridItemCardGameZombie::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombie);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTarget);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_drawHealthBar);
		REFLECTION_CLASSBUILDER_FIELD(int, m_intentionCountDown);
	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombie);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieProps);

void GridItemCardGameZombie::TouchMoved(const Sexy::Touch& i_arg)
{
}

#include "GridItemBreakableTarget.h"
void GridItemCardGameZombie::PlayDeathAnim()
{
	 GridItemBreakableTarget::startDeathAnim();
}

void GridItemCardGameZombie::RoundFinishStart()
{
}

void GridItemCardGameZombie::onIntentionAnimDone(const std::string& i_arg)
{
}

#include "GridItemBreakableTarget.h"
void GridItemCardGameZombie::onUpdate()
{
	 GridItemBreakableTarget::onUpdate();
}
