//
//  GridItemZombieMirrorQueenPoisonApplePuree.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMirrorQueen.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieMirrorQueenPoisonApplePuree);

void GridItemZombieMirrorQueenPoisonApplePuree::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieMirrorQueenPoisonApplePuree);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(PlantPtr, m_plantPtr);
		REFLECTION_CLASSBUILDER_FIELD(ZombiePtr, m_zombiePtr);
		REFLECTION_CLASSBUILDER_FIELD(GridItemPtr, m_gridItemPtr);
	REFLECTION_CLASSBUILDER_END(GridItemZombieMirrorQueenPoisonApplePuree);
}
