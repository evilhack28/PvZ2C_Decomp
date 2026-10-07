//
//  GridItemZombieBoundTile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombiePotion.h"

GridItemZombieBoundTile::GridItemZombieBoundTile()
{
}

GridItemZombieBoundTile::~GridItemZombieBoundTile()
{
}

GridItemZombieBoundTileProps::~GridItemZombieBoundTileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieBoundTile);

void GridItemZombieBoundTile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieBoundTile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_endCooldownTime);
	REFLECTION_CLASSBUILDER_END(GridItemZombieBoundTile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieBoundTileProps);

void GridItemZombieBoundTileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieBoundTileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemZombieBoundTileProps);
}

void GridItemZombieBoundTile::OnStartAnimStopped(const std::string & i_animName)
{
}

bool GridItemZombieBoundTile::CanBeTargetedBy(const BoardEntity* i_entity) const
{
	return false;
}
