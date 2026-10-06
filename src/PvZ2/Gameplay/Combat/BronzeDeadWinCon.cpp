//
//  BronzeDeadWinCon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BronzeDeadWinCon.h"
#include "LevelModuleManager.h"
#include "BoardEntity.h"
#include "Zombie.h"
#include "LawnApp.h"
#include "Board.h"
#include "BronzeModule.h"
#include "EntityFinder.h"
#include "GridItemArmrack.h"
#include "GridItemFlame.h"

BronzeDeadWinCon::BronzeDeadWinCon()
{
}

BronzeDeadWinCon::~BronzeDeadWinCon()
{
}

BronzeDeadWinConProperties::~BronzeDeadWinConProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BronzeDeadWinConProperties);

void BronzeDeadWinConProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BronzeDeadWinConProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(BronzeDeadWinConProperties);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BronzeDeadWinCon);

/////////////// BronzeDeadWinCon ///////////////

void BronzeDeadWinCon::registerForEvents()
{
	getManager()->RegisterWinCondition(Sexy::MakeDelegate(*this, &BronzeDeadWinCon::checkWin));
}

bool BronzeDeadWinCon::canDamage(const BoardEntity* i_entity) const
{
	if (!i_entity)
		return false;
	return i_entity->IsA<Zombie>() || i_entity->IsA<GridItemArmrack>() || i_entity->IsA<GridItemFlame>();
}

bool BronzeDeadWinCon::checkWin()
{
	BronzeModule* bronze = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<BronzeModule>();
	if (!bronze)
		return false;
	int stumps = bronze->getBronzeStumpCount();
	if (stumps != 0)
		return false;
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntities(entities, ENTITYTYPE_ZOMBIE | ENTITYTYPE_GRIDITEM);
	DamageInfo damage(99999.0f, (DamageTypeFlags)0x800, nullptr, Sexy::Point(-1, -1), stumps, ResilienceDamageInfo(1.0f, 0.0f));
	for (size_t i = 0; i < entities.size(); ++i)
	{
		if (canDamage(entities[i]))
			entities[i]->TakeDamage(damage);
	}
	return true;
}
