//
//  GridItemCardGameZombieCannon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombieCannon.h"

GridItemCardGameZombieCannon::GridItemCardGameZombieCannon()
{
	m_spawnImpCount = 1;
	m_spawnImpCountMax = (decltype(m_spawnImpCountMax))3;
}

GridItemCardGameZombieCannon::~GridItemCardGameZombieCannon()
{
}

GridItemCardGameZombieCannonProps::~GridItemCardGameZombieCannonProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieCannon);

void GridItemCardGameZombieCannon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieCannon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombie);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieCannon);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieCannonProps);

void GridItemCardGameZombieCannonProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieCannonProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombieProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnimFireProjectileName);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieCannonProps);
}
