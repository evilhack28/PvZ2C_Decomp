//
//  GridItemZombieMirrorQueenMirror.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMirrorQueen.h"

GridItemZombieMirrorQueenMirror::GridItemZombieMirrorQueenMirror()
{
	m_currDamageState = 0;
	m_hasBroken = 0;
}

GridItemZombieMirrorQueenMirror::~GridItemZombieMirrorQueenMirror()
{
}

GridItemZombieMirrorQueenMirrorProps::GridItemZombieMirrorQueenMirrorProps()
{
	DamageStateCount = 0;
}

GridItemZombieMirrorQueenMirrorProps::~GridItemZombieMirrorQueenMirrorProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieMirrorQueenMirror);

void GridItemZombieMirrorQueenMirror::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CopyZombieParams);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_zombieTypeName);
		REFLECTION_CLASSBUILDER_FIELD(int, m_zombieLevel);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_walkOutTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_clonedZombiePtr);
	REFLECTION_CLASSBUILDER_END(CopyZombieParams);

	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieMirrorQueenMirror);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<CopyZombieParams>, m_copyZombies);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie>>, m_copiedZombies);
		REFLECTION_CLASSBUILDER_FIELD(int, m_currDamageState);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasBroken);
	REFLECTION_CLASSBUILDER_END(GridItemZombieMirrorQueenMirror);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieMirrorQueenMirrorProps);

void GridItemZombieMirrorQueenMirrorProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieMirrorQueenMirrorProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(int, DamageStateCount);
		REFLECTION_CLASSBUILDER_FIELD(float, ZombieOutDelay);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, CannotCopyZombieTypeName);
	REFLECTION_CLASSBUILDER_END(GridItemZombieMirrorQueenMirrorProps);
}

#include "GridItem.h"
void GridItemZombieMirrorQueenMirror::registerForEvents()
{
	 GridItem::registerForEvents();
}
