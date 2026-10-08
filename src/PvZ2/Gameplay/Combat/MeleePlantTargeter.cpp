//
//  MeleePlantTargeter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//
/////////////// MeleePlantTargeter ///////////////

#include "PvZ/MeleePlantTargeter.h"
#include "PvZ/PlantFramework.h"
#include "PvZ/EntityFinder.h"
#include "PvZ/PlantUtils.h"
#include "PvZ/Zombie.h"
#include "PvZ/EntitySearch.h"
#include "PvZ/GridItem.h"

PlantFramework* MeleePlantTargeter::getPlantsFramework(Plant* i_plant)
{
	return i_plant->GetPlantFramework<PlantFramework>();
}

Rect MeleePlantTargeter::getPlantAttackRect(Plant* i_plant, TargetDirection i_direction, PlantWeapon i_plantWeapon)
{
	Rect rect = getPlantsFramework(i_plant)->GetPlantAttackRect(i_plantWeapon);
	if (i_plantWeapon == WEAPON_PRIMARY)
	{
		int width = rect.mWidth;
		rect.mWidth = (int)((float)width * 0.5f);
		if (i_direction == RIGHT)
			rect.mX += (int)((float)width * 0.5f);
	}
	return rect;
}

bool MeleePlantTargeter::hasZombieLeft(Plant* i_plant, PlantWeapon i_plantWeapon)
{
	return getZombieTarget(i_plant, LEFT, i_plantWeapon) != 0;
}

bool MeleePlantTargeter::hasZombieRight(Plant* i_plant, PlantWeapon i_plantWeapon)
{
	return getZombieTarget(i_plant, RIGHT, i_plantWeapon) != 0;
}

bool MeleePlantTargeter::hasGridItemLeft(Plant* i_plant, PlantWeapon i_plantWeapon)
{
	return getGridItemTarget(i_plant, LEFT, i_plantWeapon) != 0;
}

bool MeleePlantTargeter::hasGridItemRight(Plant* i_plant, PlantWeapon i_plantWeapon)
{
	return getGridItemTarget(i_plant, RIGHT, i_plantWeapon) != 0;
}

Zombie* MeleePlantTargeter::getZombieTarget(Plant* i_plant, TargetDirection i_direction, PlantWeapon i_plantWeapon)
{
	PlantTargetParams params(TARGET_PARAMS_DISTANCE_CLOSEST, TargetParamsFlags(0));
	Rect attackRect = getPlantAttackRect(i_plant, i_direction, i_plantWeapon);
	return getPlantsFramework(i_plant)->FindTargetZombieInRow(i_plant->m_row, i_plantWeapon, NULL, params, attackRect).operator->();
}

GridItem* MeleePlantTargeter::getGridItemTarget(Plant* i_plant, TargetDirection i_direction, PlantWeapon i_plantWeapon)
{
	Rect attackRect = getPlantAttackRect(i_plant, i_direction, i_plantWeapon);
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesTouchingRectangle(entities, BoardEntityTypeFlag(4), attackRect);
	return PlantUtils::GetBestDamageableGridItemFromEntities(entities).operator->();
}

BoardEntity* MeleePlantTargeter::GetBestTarget(Plant* i_plant, PlantWeapon i_plantWeapon, TargetDirection i_direction)
{
	if (!i_plant->GetPtr().IsValid())
		return NULL;
	BoardEntity* target = getZombieTarget(i_plant, i_direction, i_plantWeapon);
	if (target == NULL)
		target = getGridItemTarget(i_plant, i_direction, i_plantWeapon);
	return target;
}

MeleePlantTargeter::TargetDirection MeleePlantTargeter::GetBestTargetDirection(Plant* i_plant, PlantWeapon i_plantWeapon, TargetDirection i_forbiddenDirection)
{
	TargetDirection result = D_NONE;
	if (i_plant->GetPtr().IsValid())
	{
		if (i_forbiddenDirection != LEFT && hasZombieLeft(i_plant, i_plantWeapon))
			result = LEFT;
		else if (i_forbiddenDirection != RIGHT && (hasZombieRight(i_plant, i_plantWeapon) || hasGridItemRight(i_plant, i_plantWeapon)))
			result = RIGHT;
		else if (i_forbiddenDirection != LEFT && hasGridItemLeft(i_plant, i_plantWeapon))
			result = LEFT;
	}
	return result;
}

std::vector<BoardEntity*> MeleePlantTargeter::GetAdjacentTargets(Plant* i_plant, PlantWeapon i_plantWeapon)
{
	std::vector<BoardEntity*> targets;
	if (i_plant != NULL && i_plant->GetPtr().IsValid())
	{
		Rect attackRect = getPlantsFramework(i_plant)->GetPlantAttackRect(i_plantWeapon);
		EntityFinder::EntitySearchAcceptEventType acceptEvent;
		EntitySearch_InGridRows rows(i_plant->m_row - 1, i_plant->m_row + 1);
		EntitySearch_TouchingRectangle touching(attackRect);
		EntitySearch_Lambda lambda([i_plant](BoardEntity* i_entity) -> bool
		{
			if (Zombie* zombie = i_entity->Cast<Zombie>())
				return !zombie->MatchesAny(ZT_DYING | ZT_DOES_NOT_COLLIDE_WITH_PLANT | ZT_SAME_TEAM, i_plant);
			if (GridItem* gridItem = i_entity->Cast<GridItem>())
				return gridItem->IsDamageableByPlants();
			return false;
		});
		acceptEvent += MakeDelegate(rows, &EntitySearch_InGridRows::Accept);
		acceptEvent += MakeDelegate(touching, &EntitySearch_TouchingRectangle::Accept);
		acceptEvent += MakeDelegate(lambda, &EntitySearch_Lambda::Accept);
		EntityFinder::GetEntities(targets, BoardEntityTypeFlag(2) | BoardEntityTypeFlag(4), acceptEvent);
	}
	return targets;
}
