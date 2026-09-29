//
//  GridItemCardGameZombieMirrorQueen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombieMirrorQueen.h"

GridItemCardGameZombieMirrorQueen::GridItemCardGameZombieMirrorQueen()
{
	m_throwAppleCount = 1;
}

GridItemCardGameZombieMirrorQueen::~GridItemCardGameZombieMirrorQueen()
{
}

GridItemCardGameZombieMirrorQueenProps::~GridItemCardGameZombieMirrorQueenProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieMirrorQueen);

void GridItemCardGameZombieMirrorQueen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieMirrorQueen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombie);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieMirrorQueen);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieMirrorQueenProps);

void GridItemCardGameZombieMirrorQueenProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieMirrorQueenProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombieProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<Point>, MirrorPos);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieMirrorQueenProps);
}
