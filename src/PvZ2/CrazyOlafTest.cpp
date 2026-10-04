//
//  CrazyOlafTest.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CrazyOlafTest.h"

#include "ReflectionBuilder.h"
#include "LevelModuleManager.h"
#include "GameEventMgr.h"
#include "Plant.h"
#include "Zombie.h"
#include "LawnApp.h"
#include "Board.h"
#include "PlantType.h"
#include "ProbabilitySet.h"
#include "PowerTileSubsystem.h"
#include "GridItemGoldTile.h"
#include "PlantfoodCursor.h"
#include "Plant_Peapod.h"
#include "ObjectTypeDirectory.h"
#include "EntityFinder.h"
#include "PlantGroup.h"
#include "Effect_FloatingText.h"

RT_CLASS_IMPLEMENT(CrazyOlafTest);

void CrazyOlafTest::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CrazyOlafTest);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_actionTimer);
	REFLECTION_CLASSBUILDER_END(CrazyOlafTest);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CrazyOlafTestProperties);

void CrazyOlafTestProperties::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(TestActionsCrazyOlafStyle);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(Shovel, TACOS_Shovel);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(PlantSingle, TACOS_PlantSingle);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(PlantColumn, TACOS_PlantColumn);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(PlantfoodSingle, TACOS_PlantfoodSingle);
	REFLECTION_ENUMBUILDER_END(TestActionsCrazyOlafStyle);

	REFLECTION_CLASSBUILDER_BEGIN(ActionWeights);
		REFLECTION_CLASSBUILDER_FIELD(TestActionsCrazyOlafStyle, Action);
		REFLECTION_CLASSBUILDER_FIELD(int32, Weight);
	REFLECTION_CLASSBUILDER_END(ActionWeights);

	REFLECTION_CLASSBUILDER_BEGIN(CrazyOlafTestProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ActionWeights>, Actions);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PlantWhitelist);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PlantBlacklist);
		REFLECTION_CLASSBUILDER_FIELD(float, ActionTimer);
		REFLECTION_CLASSBUILDER_FIELD(int32, MaxPlantTypes);
		REFLECTION_CLASSBUILDER_FIELD(int32, MaxPerType);
		REFLECTION_CLASSBUILDER_FIELD(int32, PlantBeforeColumn);
	REFLECTION_CLASSBUILDER_END(CrazyOlafTestProperties);
}

/////////////// CrazyOlafTest ///////////////

void CrazyOlafTest::registerForEvents()
{
	getManager()->RegisterOnUpdate(Sexy::MakeDelegate(*this, &CrazyOlafTest::onUpdate));
	gMessageRouter->Subscribe(Message::PlantDied, Sexy::MakeDelegate(*this, &CrazyOlafTest::onPlantDied));
	gMessageRouter->Subscribe(Message::ZombieAddedToBoard, Sexy::MakeDelegate(*this, &CrazyOlafTest::onZombieAddedToBoard));
	gMessageRouter->Subscribe(Message::ZombieDied, Sexy::MakeDelegate(*this, &CrazyOlafTest::onZombieDied));
}

void CrazyOlafTest::initializeModule()
{
	const CrazyOlafTestProperties* props = getProps<CrazyOlafTestProperties>();
	m_actionTimer = PVZ_T() + props->ActionTimer;

	std::vector<PlantTypePtr> available;
	if (props->PlantWhitelist.size() == 0)
	{
		for (ObjectTypeDirectoryIterator<PlantType> it; it; ++it)
		{
			PlantTypePtr type = *it;
			if (!((const PlantType*)type)->Enabled)
				continue;
			available.push_back(type);
		}
	}
	else
	{
		for (size_t i = 0; i < props->PlantWhitelist.size(); ++i)
		{
			PlantTypePtr type = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(props->PlantWhitelist[i]);
			if (type->Enabled)
				available.push_back(type);
		}
	}

	std::vector<std::string> blacklist = props->PlantBlacklist;
	blacklist.push_back("imitater");
	size_t next = 0;
	size_t i;
	while (i = next, next++, i < blacklist.size())
	{
		PlantTypePtr type = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(blacklist[i]);
		available.erase(std::remove(available.begin(), available.end(), type), available.end());
	}

	std::random_shuffle(available.begin(), available.end());
	m_freePlantTypes = available;

	for (int i = 0; i < props->MaxPlantTypes; ++i)
	{
		PlantTypePtr loaded = popFreeQueue();
		loadPlantType(loaded);
	}

	m_plantCount = 0;
	m_zombieCount = 0;
	m_deadPlantCount = 0;
	m_deadZombieCount = 0;

	SexyVector2 origin;
	origin = SexyVector2(gLawnApp->mWidth * 0.15f, gLawnApp->mHeight * 0.2f);

	m_textPlantCount = gLawnApp->m_board->AddEffect<Effect_FloatingText>()->GetPtr();
	m_textPlantCount->SetScreenSpaceOrigin(origin, 0xDBBA0);
	m_textPlantCount->SetColor(Color(Color::Green));
	m_textPlantCount->SetStyle(FTS_OlafStats);
	origin.y += gLawnApp->mHeight * 0.08f;

	m_textKilledPlants = gLawnApp->m_board->AddEffect<Effect_FloatingText>()->GetPtr();
	m_textKilledPlants->SetScreenSpaceOrigin(origin, 0xDBBA0);
	m_textKilledPlants->SetColor(Color(128, 255, 128));
	m_textKilledPlants->SetStyle(FTS_OlafStats);
	origin.y += gLawnApp->mHeight * 0.08f;

	m_textZombieCount = gLawnApp->m_board->AddEffect<Effect_FloatingText>()->GetPtr();
	m_textZombieCount->SetScreenSpaceOrigin(origin, 0xDBBA0);
	m_textZombieCount->SetColor(Color(Color::Purple));
	m_textZombieCount->SetStyle(FTS_OlafStats);
	origin.y += gLawnApp->mHeight * 0.08f;

	m_textKilledZombies = gLawnApp->m_board->AddEffect<Effect_FloatingText>()->GetPtr();
	m_textKilledZombies->SetScreenSpaceOrigin(origin, 0xDBBA0);
	m_textKilledZombies->SetColor(Color(255, 128, 255));
	m_textKilledZombies->SetStyle(FTS_OlafStats);

	refreshDisplayText();
}

void CrazyOlafTest::onUpdate()
{
	if (PVZ_T() > m_actionTimer)
	{
		pickAndPerformAction();
		m_actionTimer = PVZ_T() + getProps<CrazyOlafTestProperties>()->ActionTimer;
	}
	refreshDisplayText();
}

void CrazyOlafTest::onPlantDied(Plant* i_plant)
{
	m_deadPlantCount++;
}

void CrazyOlafTest::onZombieAddedToBoard(Zombie* i_zombie)
{
	m_zombieCount++;
}

void CrazyOlafTest::onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow)
{
	m_deadZombieCount++;
}

void CrazyOlafTest::pushFreeQueue(PlantTypePtr i_type)
{
	m_freePlantTypes.push_back(i_type);
}

PlantTypePtr CrazyOlafTest::popFreeQueue()
{
	if (m_freePlantTypes.empty())
		return PlantTypePtr();

	PlantTypePtr type = m_freePlantTypes.front();
	m_freePlantTypes.erase(m_freePlantTypes.begin());
	return type;
}

void CrazyOlafTest::loadPlantType(PlantTypePtr i_type)
{
	if (!i_type.IsValid())
		return;

	std::vector<PlantTypePtr>::iterator it = m_loadedPlantTypes.begin();
	for (; it != m_loadedPlantTypes.end(); ++it)
	{
		if (*it == i_type)
			return;
	}

	gLawnApp->m_board->LoadResourceGroupForGameplay(i_type->PlantFramework);
	m_loadedPlantTypes.push_back(i_type);
}

void CrazyOlafTest::unloadPlantType(PlantTypePtr i_type)
{
	if (!i_type.IsValid())
		return;

	std::vector<PlantTypePtr>::iterator it = m_loadedPlantTypes.begin();
	for (; it != m_loadedPlantTypes.end(); ++it)
	{
		if (*it == i_type)
			break;
	}

	if (it == m_loadedPlantTypes.end())
		return;

	gLawnApp->m_board->DeleteResourceGroupForGameplay(i_type->PlantFramework);
	m_loadedPlantTypes.erase(it);
}

void CrazyOlafTest::refreshDisplayText()
{
	m_textPlantCount->SetText(Sexy::StrFormat("%d Planted", m_plantCount));
	m_textKilledPlants->SetText(Sexy::StrFormat("%d Dead Plants", m_deadPlantCount));
	m_textZombieCount->SetText(Sexy::StrFormat("%d Zombies Spawned", m_zombieCount));
	m_textKilledZombies->SetText(Sexy::StrFormat("%d Dead Zombies", m_deadZombieCount));
}

PlantGroupPtr CrazyOlafTest::pickRandomPlantGroup()
{
	const std::vector<PlantGroupPtr>& groups = gLawnApp->m_board->GetAllActivePlantGroups();
	std::vector<PlantGroupPtr> valid;

	int maxColumn = gLawnApp->m_board->m_gridSizeX;
	if (getProps<CrazyOlafTestProperties>()->PlantBeforeColumn > 0)
		maxColumn = std::min(maxColumn, getProps<CrazyOlafTestProperties>()->PlantBeforeColumn);

	for (const PlantGroupPtr& group : groups)
	{
		if (group->GridX() < maxColumn)
			valid.push_back(group);
	}

	if (valid.empty())
		return PlantGroupPtr();
	return valid[Sexy::Rand((int)valid.size())];
}

std::vector<Point> CrazyOlafTest::destroyAllPlantsOfType(PlantTypePtr i_type)
{
	std::vector<Point> destroyed;
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntities(entities, ENTITYTYPE_PLANT);
	for (size_t i = 0; i < entities.size(); ++i)
	{
		if (entities[i]->Cast<Plant>()->GetType() == i_type)
		{
			destroyed.push_back(entities[i]->Cast<Plant>()->CalcGridPosition());
			entities[i]->Destroy();
		}
	}
	return destroyed;
}

Plant* CrazyOlafTest::pickRandomPlant(PlantTypePtr i_type)
{
	std::vector<BoardEntity*> entities;
	std::vector<Plant*> valid;
	bool filterByType = i_type.IsValid();
	EntityFinder::GetEntities(entities, ENTITYTYPE_PLANT);

	int maxColumn = gLawnApp->m_board->m_gridSizeX;
	if (getProps<CrazyOlafTestProperties>()->PlantBeforeColumn > 0)
		maxColumn = std::min(maxColumn, getProps<CrazyOlafTestProperties>()->PlantBeforeColumn);

	for (size_t i = 0; i < entities.size(); ++i)
	{
		Plant* plant = entities[i]->Cast<Plant>();
		if (!filterByType || plant->GetType() == i_type)
		{
			if (plant->CalcGridPosition().mX < maxColumn)
				valid.push_back(plant);
		}
	}

	if (valid.empty())
		return nullptr;
	return valid[Sexy::Rand((int)valid.size())];
}

Point CrazyOlafTest::pickRandomGridSquare(PlantTypePtr i_canPlantAt)
{
	std::vector<Point> valid;
	bool filterByType = i_canPlantAt.IsValid();

	int maxColumn = gLawnApp->m_board->m_gridSizeX;
	if (getProps<CrazyOlafTestProperties>()->PlantBeforeColumn > 0)
		maxColumn = std::min(maxColumn, getProps<CrazyOlafTestProperties>()->PlantBeforeColumn);

	for (int y = 0; y < gLawnApp->m_board->m_gridSizeY; ++y)
	{
		for (int x = 0; x < maxColumn; ++x)
		{
			if (!filterByType || gLawnApp->m_board->CanPlantAt(Point(x, y), i_canPlantAt))
				valid.push_back(Point(x, y));
		}
	}

	if (valid.empty())
		return Point(-1, -1);
	return valid[Sexy::Rand((int)valid.size())];
}

PlantTypePtr CrazyOlafTest::pickValidPlantType()
{
	std::vector<PlantTypePtr> candidates = m_loadedPlantTypes;

	if (getProps<CrazyOlafTestProperties>()->MaxPerType > 0)
	{
		std::map<PlantTypePtr, int> counts;
		std::vector<BoardEntity*> entities;
		EntityFinder::GetEntities(entities, ENTITYTYPE_PLANT);
		for (size_t i = 0; i < entities.size(); ++i)
		{
			PlantTypePtr type = entities[i]->Cast<Plant>()->GetType();
			if (counts.find(type) == counts.end())
				counts[type] = 1;
			else
				counts[type]++;
		}

		for (std::map<PlantTypePtr, int>::iterator it = counts.begin(); it != counts.end(); ++it)
		{
			if ((*it).second >= getProps<CrazyOlafTestProperties>()->MaxPerType)
			{
				for (size_t i = 0; i < candidates.size(); ++i)
				{
					if (candidates[i] == (*it).first)
						candidates.erase(candidates.begin() + i);
				}
			}
		}
	}

	if (candidates.empty())
		return PlantTypePtr();
	return candidates[Sexy::Rand((int)candidates.size())];
}

void CrazyOlafTest::plantAt(const std::vector<Point>& i_squares, PlantTypePtr i_type)
{
	for (size_t i = 0; i < i_squares.size(); ++i)
	{
		if (!gLawnApp->m_board->CanPlantAt(Point(i_squares[i].mX, i_squares[i].mY), i_type))
			continue;

		Plant* existing = gLawnApp->m_board->GetPlantAt(i_squares[i].mX, i_squares[i].mY);
		if (existing != nullptr && existing->GetType() == i_type)
			existing->Destroy();

		if (i_type == ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName("wallnut")
			|| i_type == ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName("tallnut"))
		{
			if (existing != nullptr && existing->GetType() == i_type)
				existing->Destroy();
		}

		PlantTypePtr peapod = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName("peapod");
		if (existing != nullptr && i_type == peapod)
		{
			existing->GetPlantFramework<PlantPeapod>()->Upgrade();
			break;
		}

		gLawnApp->m_board->AddPlant(i_squares[i].mX, i_squares[i].mY, i_type);
		m_plantCount++;
	}
}

void CrazyOlafTest::plantAt(const Point& i_square, PlantTypePtr i_type)
{
	std::vector<Point> squares;
	squares.push_back(i_square);
	plantAt(squares, i_type);
}

void CrazyOlafTest::pickAndPerformAction()
{
	ProbabilitySet<TACOS> actions;
	const CrazyOlafTestProperties* props = getProps<CrazyOlafTestProperties>();
	size_t n = 0;
	while (n++ < props->Actions.size())
		actions.AddItem(props->Actions[n - 1].Action, props->Actions[n - 1].Weight);

	if (actions.GetSize() == 0)
		return;

	switch (actions.PickItem())
	{
	case CrazyOlafTestProperties::TACOS_PlantColumn:
	{
		PlantTypePtr type = pickValidPlantType();
		if (type)
		{
			Point square = pickRandomGridSquare(type);
			if (square.mX >= 0)
			{
				for (int y = 0; y < gLawnApp->m_board->m_gridSizeY; ++y)
					plantAt(Point(square.mX, y), type);
			}
		}
		break;
	}
	case CrazyOlafTestProperties::TACOS_PlantSingle:
	{
		PlantTypePtr type = pickValidPlantType();
		if (type)
		{
			Point square = pickRandomGridSquare(type);
			plantAt(square, type);
		}
		break;
	}
	case CrazyOlafTestProperties::TACOS_Shovel:
	{
		PlantGroup* group = pickRandomPlantGroup();
		if (group)
		{
			PowerTileSubsystem* powerTiles = gLawnApp->m_board->GetGameSubSystem<PowerTileSubsystem>();
			powerTiles->DestroyPowerTileAt(group->GridLocation());
			GridItemGoldTile* tile = EntityFinder::GetGridItemAt<GridItemGoldTile>(group->GridX(), group->GridY());
			if (tile)
				tile->Destroy();
		}
		PlantPtr plant = group->FindValidPlantToShovel();
		if (plant)
		{
			plant->Shovel();
			m_deadPlantCount--;
		}
		break;
	}
	case CrazyOlafTestProperties::TACOS_PlantfoodSingle:
	{
		PlantGroupPtr group = pickRandomPlantGroup();
		if (group)
			ApplyPlantFoodToPlantGroup(group.operator->());
		break;
	}
	}
}
