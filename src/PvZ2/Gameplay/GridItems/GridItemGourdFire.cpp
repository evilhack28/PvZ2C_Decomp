//
//  GridItemGourdFire.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGourdFire.h"

void GridItemGourdFire::UpdateActions()
{
}

void GridItemGourdFire::onUpdate()
{
}

void GridItemGourdFire::spawnDirt()
{
}

GridItemGourdFire::GridItemGourdFire()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGourdFire);

void GridItemGourdFire::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGourdFire);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_dirtEffectSpawned);
	REFLECTION_CLASSBUILDER_END(GridItemGourdFire);
}

void GridItemGourdFire::onDraw(Sexy::Graphics* i_g)
{
}

#include "GameObject.h"
void GridItemGourdFire::Destroy()
{
	 GameObject::Destroy();
}

bool GridItemGourdFire::CanBeTargetedBy(const BoardEntity* i_entity) const
{
	return false;
}

bool GridItemGourdFire::CollidesWithType(CollisionTypeFlags i_collisionTypes) const
{
	return false;
}
