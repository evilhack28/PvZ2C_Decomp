//
//  GridItemZombieMirrorQueenMirrorSubSystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMirrorQueen.h"

GridItemZombieMirrorQueenMirrorSubSystem::GridItemZombieMirrorQueenMirrorSubSystem()
{
}

GridItemZombieMirrorQueenMirrorSubSystem::~GridItemZombieMirrorQueenMirrorSubSystem()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieMirrorQueenMirrorSubSystem);

void GridItemZombieMirrorQueenMirrorSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieMirrorQueenMirrorUnit);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_zombiePtr);
		REFLECTION_CLASSBUILDER_FIELD(std::function<void(RtWeakPtr<Zombie>)>, m_completeCallback);
	REFLECTION_CLASSBUILDER_END(GridItemZombieMirrorQueenMirrorUnit);

	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieMirrorQueenMirrorSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

	REFLECTION_CLASSBUILDER_END(GridItemZombieMirrorQueenMirrorSubSystem);
}
