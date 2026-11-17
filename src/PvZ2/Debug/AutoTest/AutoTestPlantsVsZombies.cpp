//
//  AutoTestPlantsVsZombies.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-16.
//

#include "SexyAppFramework/Common.h"

#include "AutoTest.h"
#include "LawnApp.h"
#include "Board.h"
#include "BoardTransforms.h"
#include "Zombie.h"
#include "Plant.h"
#include "PVZDB.h"
#include "Cheats.h"
#include "LevelModuleManager.h"
#include "CrazyNPCManager.h"
#include "WorldData.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

AutoTestPlantsVsZombies::AutoTestPlantsVsZombies() :
	m_plantIndex(-1),
	m_zombieIndex(0),
	m_worldIndex(1),
	m_delayCheck(false),
	m_changeTime(PVZ_EOT())
{
	gMessageRouter->Subscribe(&Message::changePlantsVsZombiesStartWorld, Sexy::MakeDelegate(*this, &AutoTestPlantsVsZombies::changeStartWorld));
}

AutoTestPlantsVsZombies::~AutoTestPlantsVsZombies()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Logic ///////////////

void AutoTestPlantsVsZombies::AutoStartNextLevel()
{
	AutoTestPlantsVsZombies::AutoEnterLevel();
}

void AutoTestPlantsVsZombies::AutoConfirmOver()
{
	gLawnApp->KillPVZ2Dialog();
}

void AutoTestPlantsVsZombies::AutoFinishWinLevel()
{
	gMessageRouter->Post(&Message::AutoTestLevelWinFinishNotify);
}

void AutoTestPlantsVsZombies::AutoTestSkyCityDamage(float i_Percent)
{
	if (i_Percent < 90.0f)
	{
		if (gLawnApp->m_board)
		{
			gLawnApp->m_board->DestroyAllZombies();
			gMessageRouter->Post(&Message::ReviveSucceed);
		}
	}
}

void AutoTestPlantsVsZombies::killZombie(Zombie* i_zombie)
{
	if (i_zombie)
		i_zombie->setZombieState(ZS_Die);
}

void AutoTestPlantsVsZombies::onPlantDied(Plant* i_plant)
{
	Sexy::OutputDebugStrF("onPlantDied\n");
	m_changeTime = PVZ_T();
}

void AutoTestPlantsVsZombies::OnZombieCloseToHouse(Zombie* i_zmobie)
{
	Sexy::OutputDebugStrF("OnZombieCloseToHouse\n");
	int y = BoardTransforms::BoardSpaceToGridY(i_zmobie->GetPosition().y);
	killZombie(i_zmobie);
	checkAndAddPlant(y);
	checkAndAddZombie(y);
	m_delayCheck = true;
	m_changeTime = PVZ_T();
}

void AutoTestPlantsVsZombies::onZombieDied(Zombie* i_zmobie, const DamageInfo* i_deathBlow)
{
	Sexy::OutputDebugStrF("onZombieDied\n");
	int y = BoardTransforms::BoardSpaceToGridY(i_zmobie->GetPosition().y);
	checkAndAddPlant(y);
	checkAndAddZombie(y);
	m_delayCheck = true;
	m_changeTime = PVZ_T();
}

void AutoTestPlantsVsZombies::QuitLevel()
{
	Sexy::OutputDebugStrF("QuitLevel!\n");
	gLawnApp->m_board->DestroyAllZombies();
	Board* board = gLawnApp->m_board;
	if (board->GetState() != BOARDSTATE_TUTORIAL && board->GetState() != BOARDSTATE_PLAYING_LEVEL)
	{
		Sexy::OutputDebugStrF("*** Can't complete level until actual gameplay state!\n");
		return;
	}
	board->m_boardState = BOARDSTATE_ENDLEVEL;
	gLawnApp->GetNarrationSystem()->ForceEndNarrative();
	gLawnApp->m_board->PlayerWon();
}

bool AutoTestPlantsVsZombies::getWorld()
{
	const WorldMapList* mapList = gLawnApp->GetWorldMapList();
	if (m_worldIndex < mapList->MapList.size())
		return !mapList->MapList[m_worldIndex].EntryPoint.empty();
	return false;
}

void AutoTestPlantsVsZombies::addPlant(int y)
{
	if (m_plantIndex < m_plants.size() && m_zombieIndex < m_zombies.size())
	{
		PlantTypePtr type = m_plants[m_plantIndex];
		gLawnApp->m_board->TestSpawnPlant(type->TypeName, 0, y);
		Sexy::OutputDebugStrF("add plant:%d,[%s]\n", m_plantIndex, type->TypeName.c_str());
	}
}

void AutoTestPlantsVsZombies::addZombie(int y)
{
	if (m_zombieIndex < m_zombies.size() && m_plantIndex < m_plants.size())
	{
		ZombieTypePtr type = m_zombies[m_zombieIndex];
		gLawnApp->m_board->CheatAddZombie(type, y, true);
		Sexy::OutputDebugStrF("add zombie:%d,[%s]\n", m_zombieIndex, type->TypeName.c_str());
		m_zombieIndex++;
	}
}

void AutoTestPlantsVsZombies::GetPlants(std::vector<Plant*>& o_plantList, const std::function<bool(const BoardEntity*)>& accept)
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANTS); it; ++it)
	{
		Plant* plant = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLANTS)->GetObjectForId(*it)->CastChecked<Plant>();
		if (plant->m_isOnBoard)
		{
			if (accept(plant))
				o_plantList.push_back(plant);
		}
	}
}

void AutoTestPlantsVsZombies::PlantsVsZombiesStart()
{
	if (gLawnApp->m_board && gLawnApp->m_board->IsPlaying())
	{
		gLawnApp->m_board->GetLevelModuleManager()->RegisterOnGameplayUpdate(Sexy::MakeDelegate(*this, &AutoTestPlantsVsZombies::PlantsVsZombiesUpdate));
		initByWorld();
		checkAndTestNextPlant(true);
	}
}

void AutoTestPlantsVsZombies::PlantsVsZombiesUpdate()
{
	if (m_delayCheck)
	{
		m_delayCheck = false;
		checkAndTestNextPlant(false);
	}
	else if (!gLawnApp->m_board->IsLevelEnded())
	{
		if (PVZ_T() - m_changeTime > 180.0f)
		{
			m_changeTime = PVZ_T();
			gLawnApp->m_board->DestroyAllPlants();
			gLawnApp->m_board->DestroyAllZombies();
			for (int y = 0; y < gLawnApp->m_board->m_gridSizeY; y++)
			{
				addPlant(y);
				addZombie(y);
			}
			checkAndTestNextPlant(false);
		}
	}
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(AutoTestPlantsVsZombies);
