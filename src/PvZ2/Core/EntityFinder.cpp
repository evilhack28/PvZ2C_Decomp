//
//  EntityFinder.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-11.
//

#include "SexyAppFramework/Common.h"

#include <algorithm>
#include <functional>

#include "Board.h"
#include "BoardConstants.h"
#include "BoardTransforms.h"
#include "Creature.h"
#include "EntityFinder.h"
#include "EntitySearch.h"
#include "GridItem.h"
#include "GridItemGoldTile.h"
#include "GridItemZombieTent.h"
#include "LawnApp.h"
#include "Plant.h"
#include "Plant_Aloes.h"
#include "Plant_HeathSeeker.h"
#include "Plant_Icelotus.h"
#include "Plant_JackOLantern.h"
#include "Plant_LilyPad.h"
#include "PlantGroup.h"
#include "PVZDB.h"
#include "ResourceHelpers.h"
#include "Zombie.h"

/////////////// Grid ///////////////

static const Sexy::Point s_aroundOffsets[8] = {
	Sexy::Point(-1, -1), Sexy::Point(0, -1), Sexy::Point(1, -1), Sexy::Point(1, 0),
	Sexy::Point(1, 1),   Sexy::Point(0, 1),  Sexy::Point(-1, 1), Sexy::Point(-1, 0)
};

bool EntityFinder::CheckGridValid(Sexy::Point grid)
{
	bool columnValid = false;
	if (grid.mX >= 0)
		columnValid = BoardConstants::NUMBER_OF_COLUMNS() > grid.mX;
	if (grid.mY >= 0)
		return columnValid & (BoardConstants::NUMBER_OF_ROWS() > grid.mY);
	return false;
}

std::vector<Sexy::Point> EntityFinder::CalcAroundGrids(Sexy::Point grid)
{
	std::vector<Sexy::Point> result;
	for (const Sexy::Point& offset : s_aroundOffsets)
	{
		Sexy::Point around(grid.mX + offset.mX, grid.mY + offset.mY);
		if (CheckGridValid(around))
			result.push_back(around);
	}
	return result;
}

/////////////// Base searches ///////////////

static bool __attribute__((noinline)) OnBoardPassThrough(bool i_onBoard) { return i_onBoard; }

void EntityFinder::GetEntities(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const EntitySearchAcceptEventType& i_acceptEvent)
{
	if (__builtin_expect(TestFlag(i_acceptedTypes, ENTITYTYPE_ZOMBIE), 0))
	{
		std::vector<Zombie*> zombies = gLawnApp->m_board->GetZombies();
		for (size_t i = 0; i < zombies.size(); i++)
		{
			Zombie* zombie = zombies[i];
			if (!zombie->IsDestroyed() && i_acceptEvent(zombie))
				o_entityList.push_back(zombie);
		}
	}
	if (TestFlag(i_acceptedTypes, ENTITYTYPE_GRIDITEM))
	{
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_GRIDITEMS); it; ++it)
		{
			GridItem* gridItem = PVZDB::GetInstance().GetTable(PVZDB::TABLE_GRIDITEMS)->GetObjectForId(*it)->Cast<GridItem>();
			if (i_acceptEvent(gridItem))
				o_entityList.push_back(gridItem);
		}
	}
	if (TestFlag(i_acceptedTypes, ENTITYTYPE_PLANT))
	{
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANTS); it; ++it)
		{
			Plant* plant = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLANTS)->GetObjectForId(*it)->Cast<Plant>();
			if (plant->m_isOnBoard && i_acceptEvent(plant))
				o_entityList.push_back(plant);
		}
	}
	if (TestFlag(i_acceptedTypes, ENTITYTYPE_PLANTGROUP))
	{
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANTGROUPS); it; ++it)
		{
			PlantGroup* plantGroup = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLANTGROUPS)->GetObjectForId(*it)->Cast<PlantGroup>();
			if (OnBoardPassThrough(plantGroup->m_isOnBoard) && i_acceptEvent(plantGroup))
				o_entityList.push_back(plantGroup);
		}
	}
	if (TestFlag(i_acceptedTypes, ENTITYTYPE_CREATURE))
	{
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_CREATURES); it; ++it)
		{
			CreaturePtr creaturePtr = *it;
			Creature* creature = creaturePtr.operator->();
			if (__builtin_expect(i_acceptEvent(creature), 0))
				o_entityList.push_back(creature);
		}
	}
	if (TestFlag(i_acceptedTypes, ENTITYTYPE_OTHERBOARDENTITIES))
	{
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_BOARDENTITIES); it; ++it)
		{
			BoardEntityPtr entityPtr = *it;
			BoardEntity* entity = entityPtr;
			if (i_acceptEvent(entity))
				o_entityList.push_back(entity);
		}
	}
}

void EntityFinder::GetEntities(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes)
{
	EntitySearchAcceptEventType acceptEvent;
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesAtGridSquare(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const int i_x, const int i_y)
{
	Sexy::Rect searchRect(i_x, i_y, 1, 1);
	GetEntitiesInGridSquares(o_entityList, i_acceptedTypes, searchRect);
}

/////////////// Region searches ///////////////

void EntityFinder::GetEntitiesInGridSquares(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const Sexy::Rect& i_searchRectGridSquares)
{
	EntitySearch_InGridSquares search(i_searchRectGridSquares);
	EntitySearchAcceptEventType acceptEvent;
	acceptEvent += MakeDelegate(search, &EntitySearch_InGridSquares::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesOnBoard(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes)
{
	Sexy::Rect boardRect(0, 0, BoardConstants::NUMBER_OF_COLUMNS(), BoardConstants::NUMBER_OF_ROWS());
	EntitySearch_InGridSquares search(boardRect);
	EntitySearchAcceptEventType acceptEvent;
	acceptEvent += MakeDelegate(search, &EntitySearch_InGridSquares::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesInRectangle(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const Sexy::Rect& i_searchRect)
{
	EntitySearch_InRectangle search(i_searchRect);
	EntitySearchAcceptEventType acceptEvent;
	acceptEvent += MakeDelegate(search, &EntitySearch_InRectangle::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesWithinCircle(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector3& i_searchLocation, const float i_radius)
{
	EntitySearch_WithinRadius search(i_searchLocation, i_radius);
	EntitySearchAcceptEventType acceptEvent;
	acceptEvent += MakeDelegate(search, &EntitySearch_WithinRadius::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesWithinCircle2D(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector2& i_searchLocation, const float i_radius)
{
	EntitySearch_WithinRadius2D search(i_searchLocation, i_radius);
	EntitySearchAcceptEventType acceptEvent;
	acceptEvent += MakeDelegate(search, &EntitySearch_WithinRadius2D::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesTouchingRectangleWithoutGrid(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const Sexy::Rect& i_searchRect)
{
	EntitySearchAcceptEventType acceptEvent;
	EntitySearch_TouchingRectangle search(i_searchRect);
	acceptEvent += MakeDelegate(search, &EntitySearch_TouchingRectangle::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

/////////////// Class matching ///////////////

void EntityFinder::GetEntitiesMatchingClass(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, RtClass* i_acceptedBaseClass)
{
	EntitySearchAcceptEventType acceptEvent;
	EntitySearch_MatchesClass search(i_acceptedBaseClass);
	acceptEvent += MakeDelegate(search, &EntitySearch_MatchesClass::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

/////////////// Row-restricted searches ///////////////

void EntityFinder::GetEntitiesTouchingRectangle(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const Sexy::Rect& i_searchRect, int i_topRow, int i_bottomRow)
{
	const int top = i_topRow == -1 ? BoardTransforms::BoardSpaceToGridYUnbounded(i_searchRect.mY) : i_topRow;
	const int bottom = i_bottomRow == -1 ? BoardTransforms::BoardSpaceToGridYUnbounded(i_searchRect.mY + i_searchRect.mHeight) : i_bottomRow;
	EntitySearchAcceptEventType acceptEvent;
	EntitySearch_InGridRows rows(top, bottom);
	acceptEvent += MakeDelegate(rows, &EntitySearch_InGridRows::Accept);
	EntitySearch_TouchingRectangle touching(i_searchRect);
	acceptEvent += MakeDelegate(touching, &EntitySearch_TouchingRectangle::Accept);	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesTouchingPoint(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector2& i_searchPoint, int i_topRow, int i_bottomRow)
{
	EntitySearch_InGridRows rows(i_topRow == -1 ? BoardTransforms::BoardSpaceToGridYUnbounded(i_searchPoint.y) : i_topRow, i_bottomRow == -1 ? BoardTransforms::BoardSpaceToGridYUnbounded(i_searchPoint.y) : i_bottomRow);
	EntitySearchAcceptEventType acceptEvent;
	acceptEvent += MakeDelegate(rows, &EntitySearch_InGridRows::Accept);
	EntitySearch_TouchingPoint touching(i_searchPoint);
	acceptEvent += MakeDelegate(touching, &EntitySearch_TouchingPoint::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesTouchingCircle2D(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector2& i_searchLocation, float i_radius, int i_topRow, int i_bottomRow)
{
	const int top = i_topRow == -1 ? BoardTransforms::BoardSpaceToGridYUnbounded(i_searchLocation.y - i_radius) : i_topRow;
	const int bottom = i_bottomRow == -1 ? BoardTransforms::BoardSpaceToGridYUnbounded(i_searchLocation.y + i_radius) : i_bottomRow;
	EntitySearchAcceptEventType acceptEvent;
	EntitySearch_InGridRows rows(top, bottom);
	acceptEvent += MakeDelegate(rows, &EntitySearch_InGridRows::Accept);
	EntitySearch_TouchingCircle touching(i_searchLocation, i_radius);
	acceptEvent += MakeDelegate(touching, &EntitySearch_TouchingCircle::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesTouchingRay(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector2& i_searchLocation, const SexyVector2& i_searchDirection, int i_topRow, int i_bottomRow)
{
	const int top = i_topRow == -1 ? BoardTransforms::BoardSpaceToGridYUnbounded(i_searchLocation.y) : i_topRow;
	const int bottom = i_bottomRow == -1 ? BoardTransforms::BoardSpaceToGridYUnbounded(i_searchLocation.y) : i_bottomRow;
	EntitySearchAcceptEventType acceptEvent;
	EntitySearch_InGridRows rows(top, bottom);
	acceptEvent += MakeDelegate(rows, &EntitySearch_InGridRows::Accept);
	EntitySearch_TouchingRay touching(i_searchLocation, i_searchDirection);
	acceptEvent += MakeDelegate(touching, &EntitySearch_TouchingRay::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

/////////////// Entity list pulling ///////////////

BoardEntity* EntityFinder::PullFirstMatchingEntity(std::vector<BoardEntity*>& io_entities, int i_preferredRow, bool i_allowMainPool)
{
	size_t i = 0;
	int index = -1;
	if (i_preferredRow >= 0 && i_preferredRow < BoardConstants::NUMBER_OF_ROWS())
	{
		for (i = 0; i < io_entities.size() && index == -1; i++)
		{
			if (io_entities[i]->CalcRowPosition() == i_preferredRow)
				index = i;
		}
	}
	if (index == -1)
	{
		if (io_entities.size() == 0 || !i_allowMainPool)
			return NULL;
		i = 0;
	}
	else
		i = index;
	BoardEntity* entity = io_entities[i];
	io_entities.erase(io_entities.begin() + i);
	return entity;
}

/////////////// Typed searches ///////////////

void EntityFinder::GetEntitiesAtGridSquareMatchingClass(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const int i_x, const int i_y, RtClass* i_matchClass)
{
	EntitySearchAcceptEventType acceptEvent;
	EntitySearch_MatchesClass matches(i_matchClass);
	EntitySearch_InGridSquares squares(Sexy::Rect(i_x, i_y, 1, 1));
	acceptEvent += MakeDelegate(matches, &EntitySearch_MatchesClass::Accept);
	acceptEvent += MakeDelegate(squares, &EntitySearch_InGridSquares::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetEntitiesInRowMatchingClass(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, int32 zombieRow, RtClass* i_matchClass)
{
	EntitySearchAcceptEventType acceptEvent;
	EntitySearch_MatchesClass matches(i_matchClass);
	EntitySearch_InGridRows rows(zombieRow, zombieRow);
	acceptEvent += MakeDelegate(matches, &EntitySearch_MatchesClass::Accept);
	acceptEvent += MakeDelegate(rows, &EntitySearch_InGridRows::Accept);
	GetEntities(o_entityList, i_acceptedTypes, acceptEvent);
}

void EntityFinder::GetZombiesAtGridSquareWithType(std::vector<BoardEntity*>& o_entityList, const int i_x, const int i_y, ZombieTypePtr zombieType)
{
	EntitySearchAcceptEventType acceptEvent;
	EntitySearch_InGridSquares squares(Sexy::Rect(i_x, i_y, 1, 1));
	EntitySearch_MatchesZombieType matches(zombieType);
	acceptEvent += MakeDelegate(squares, &EntitySearch_InGridSquares::Accept);
	acceptEvent += MakeDelegate(matches, &EntitySearch_MatchesZombieType::Accept);
	GetEntities(o_entityList, ENTITYTYPE_ZOMBIE, acceptEvent);
}

bool EntityFinder::HasZombiesAtGridSquareWithType(const int i_x, const int i_y, ZombieTypePtr zombieType)
{
	std::vector<BoardEntity*> zombies;
	GetZombiesAtGridSquareWithType(zombies, i_x, i_y, zombieType);
	return (int)zombies.size() > 0;
}

/////////////// Combined searches ///////////////

void EntityFinder::EntityFinderGridspace(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const std::vector<Sexy::Rect>& i_searchRects, BoardEntitySorter* i_sorter)
{
	std::vector<Sexy::Rect>::const_iterator it = i_searchRects.begin();
	std::vector<Sexy::Rect>::const_iterator end = i_searchRects.end();
	for (; it != end; ++it)
	{
		const Sexy::Rect& searchRect = *it;
		std::vector<BoardEntity*> found;
		GetEntitiesInGridSquares(found, i_acceptedTypes, searchRect);
		if (i_sorter)
			std::sort(found.begin(), found.end(), std::bind(&BoardEntitySorter::operator(), i_sorter, std::placeholders::_1, std::placeholders::_2));
		std::copy(found.begin(), found.end(), std::back_inserter(o_entityList));
	}
}

/////////////// Sorters ///////////////

EntityFinder::BoardEntitySorter::BoardEntitySorter(const BoardEntitySorter& i_other)
{
}

EntityFinder::BoardEntitySorter_ClosestByColumn::BoardEntitySorter_ClosestByColumn(const BoardEntitySorter_ClosestByColumn& i_other)
	: BoardEntitySorter(i_other)
	, m_gridOrigin(i_other.m_gridOrigin)
{
}

EntityFinder::BoardEntitySorter_Closest::BoardEntitySorter_Closest(const BoardEntitySorter_Closest& i_other)
	: BoardEntitySorter(i_other)
	, m_gridOrigin(i_other.m_gridOrigin)
{
}

EntityFinder::BoardEntitySorter_Closest_WeightNewRows::BoardEntitySorter_Closest_WeightNewRows(const BoardEntitySorter_Closest_WeightNewRows& i_other)
	: BoardEntitySorter(i_other)
	, m_gridOrigin(i_other.m_gridOrigin)
	, m_previousTargets(i_other.m_previousTargets)
{
}

EntityFinder::BoardEntitySorter_ClosestByColumn::BoardEntitySorter_ClosestByColumn(Point i_gridPosition)
	: m_gridOrigin(i_gridPosition)
{
}

bool EntityFinder::BoardEntitySorter_ClosestByColumn::operator()(BoardEntity* i_a, BoardEntity* i_b) const
{
	Point gridA = i_a->CalcGridPosition();
	Point gridB = i_b->CalcGridPosition();
	if (abs(gridA.mX - m_gridOrigin.mX) != abs(gridB.mX - m_gridOrigin.mX))
		return abs(gridA.mX - m_gridOrigin.mX) < abs(gridB.mX - m_gridOrigin.mX);
	return abs(gridA.mY - m_gridOrigin.mY) < abs(gridB.mY - m_gridOrigin.mY);
}

EntityFinder::BoardEntitySorter_Closest::BoardEntitySorter_Closest(Point i_gridPosition)
	: m_gridOrigin(i_gridPosition)
{
}

bool EntityFinder::BoardEntitySorter_Closest::operator()(BoardEntity* i_a, BoardEntity* i_b) const
{
	Point gridA = i_a->CalcGridPosition();
	Point gridB = i_b->CalcGridPosition();
	float distA = abs(gridA.mX - m_gridOrigin.mX) ^ 2 + abs(gridA.mY - m_gridOrigin.mY) ^ 2;
	float distB = abs(gridB.mX - m_gridOrigin.mX) ^ 2 + abs(gridB.mY - m_gridOrigin.mY) ^ 2;
	return distA < distB;
}

EntityFinder::BoardEntitySorter_Closest_WeightNewRows::BoardEntitySorter_Closest_WeightNewRows(Sexy::Point i_gridPosition, const std::vector<RtWeakPtr<BoardEntity> >& i_previousTargets)
	: m_gridOrigin(i_gridPosition)
	, m_previousTargets(i_previousTargets)
{
}

bool EntityFinder::BoardEntitySorter_Closest_WeightNewRows::findEntityInRow(const std::vector<RtWeakPtr<BoardEntity> >& i_entities, int i_row) const
{
	for (const RtWeakPtr<BoardEntity>& entity : i_entities)
	{
		if (entity && entity->CalcGridPosition().mY == i_row)
			return true;
	}
	return false;
}

bool EntityFinder::BoardEntitySorter_Closest_WeightNewRows::operator()(BoardEntity* i_a, BoardEntity* i_b) const
{
	Point gridA = i_a->CalcGridPosition();
	Point gridB = i_b->CalcGridPosition();
	bool rowA = findEntityInRow(m_previousTargets, gridA.mY);
	bool rowB = findEntityInRow(m_previousTargets, gridB.mY);
	if (rowA != rowB)
		return !rowA;
	if (abs(gridA.mY - m_gridOrigin.mY) != abs(gridB.mY - m_gridOrigin.mY))
		return abs(gridA.mY - m_gridOrigin.mY) < abs(gridB.mY - m_gridOrigin.mY);
	return abs(gridA.mX - m_gridOrigin.mX) < abs(gridB.mX - m_gridOrigin.mX);
}

EntityFinder::BoardEntitySorter_Closest_PreferNewTargets::BoardEntitySorter_Closest_PreferNewTargets(SexyVector3 i_refPos, const std::vector<RtWeakPtr<BoardEntity> >& i_previousTargets, float i_nearestTargetFactor, float i_homingdistanceFactor, bool i_prioritizeZombies, std::function<bool(const BoardEntity*)> i_shouldDeprioritizeTarget)
	: m_refPos(i_refPos)
	, m_previousTargets(i_previousTargets)
	, m_nearestTargetFactor(i_nearestTargetFactor)
	, m_homingdistanceFactor(i_homingdistanceFactor)
	, m_prioritizeZombies(i_prioritizeZombies)
	, m_shouldDeprioritizeTarget(i_shouldDeprioritizeTarget)
{
}

bool EntityFinder::BoardEntitySorter_Closest_PreferNewTargets::isPreviousTarget(BoardEntity* i_entity) const
{
	return std::find(m_previousTargets.begin(), m_previousTargets.end(), i_entity->GetPtr()) != m_previousTargets.end();
}

bool EntityFinder::BoardEntitySorter_Closest_PreferNewTargets::operator()(BoardEntity* i_a, BoardEntity* i_b) const
{
	if (m_shouldDeprioritizeTarget(i_a))
		return false;
	if (m_shouldDeprioritizeTarget(i_b))
		return true;

	bool zombieA = i_a && i_a->IsA<Zombie>();
	bool zombieB = i_b && i_b->IsA<Zombie>();
	if (m_prioritizeZombies && zombieA != zombieB)
		return zombieA;

	bool previousA = isPreviousTarget(i_a);
	bool previousB = isPreviousTarget(i_b);
	if (previousA != previousB)
		return !previousA;
	if (zombieA != zombieB)
		return zombieA;

	const SexyVector3& positionA = i_a->GetPosition();
	float distanceA = (positionA - m_refPos).MagnitudeSquared();
	const SexyVector3& positionB = i_b->GetPosition();
	float distanceB = (positionB - m_refPos).MagnitudeSquared();
	float nearest = m_nearestTargetFactor;
	float homing = m_homingdistanceFactor;
	float scoreA = distanceA * nearest + (positionA.x - 200.0f) * (positionA.x - 200.0f) * homing;
	float scoreB = distanceB * nearest + (positionB.x - 200.0f) * (positionB.x - 200.0f) * homing;
	return scoreA < scoreB;
}

/////////////// Grid item lookups ///////////////

template GridItemWisp* EntityFinder::GetGridItemAt<GridItemWisp>(int, int);
template GridItemLilyPad* EntityFinder::GetGridItemAt<GridItemLilyPad>(int, int);
template GridItemGoldTile* EntityFinder::GetGridItemAt<GridItemGoldTile>(int, int);
template GridItemWaterMist* EntityFinder::GetGridItemAt<GridItemWaterMist>(int, int);
template GridItemZombieTent* EntityFinder::GetGridItemAt<GridItemZombieTent>(int, int);
template GridIcelotusDropwater* EntityFinder::GetGridItemAt<GridIcelotusDropwater>(int, int);
