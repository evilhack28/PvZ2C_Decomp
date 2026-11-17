//
//  AutoTestAllLevel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-16.
//

#include "SexyAppFramework/Common.h"

#include "AutoTest.h"
#include "LawnApp.h"
#include "Board.h"
#include "SeedChooser.h"
#include "CrazyNPCManager.h"
#include "WorldMap.h"
#include "UniverseMap.h"
#include "WorldMapUtils.h"
#include "WorldData.h"
#include "DebugLog.h"
#include "Cheats.h"
#include "PVZ2UIDialog.h"
#include "PrimeText_Game.h"
#include "GameStateMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

AutoTestAllLevel::AutoTestAllLevel() :
	m_currentLevel(NULL),
	m_needChangeLevel(NULL),
	m_curWorldIndex(1),
	m_curLevelIndex(0)
{
	m_vecWorldMap.clear();
	gMessageRouter->Subscribe(&Message::changeAutoTestStartLevel, Sexy::MakeDelegate(*this, &AutoTestAllLevel::ChangeStartLevel));
}

AutoTestAllLevel::~AutoTestAllLevel()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Logic ///////////////

void AutoTestAllLevel::SkipSeedChooser()
{
	gLawnApp->m_board->GetSeedChooser()->AutoSelectSeedsAndFinalize();
}

void AutoTestAllLevel::AutoTestZombieCloseToHouse(Zombie* i_zmobie)
{
	if (gLawnApp->m_board)
		gLawnApp->m_board->DestroyAllZombies();
}

void AutoTestAllLevel::ConfirmStartMiniGame()
{
	gMessageRouter->Post(&Message::StartGameButtonPressed);
}

void AutoTestAllLevel::AutoFinishWinLevel()
{
	gMessageRouter->Post(&Message::AutoTestLevelWinFinishNotify);
}

void AutoTestAllLevel::AutoFinishLoseLevel()
{
	gMessageRouter->Post(&Message::AutoTestLevelLoseFinishNotify);
}

void AutoTestAllLevel::AutoConfirmOver()
{
	gLawnApp->KillPVZ2Dialog();
}

void AutoTestAllLevel::AutoTestSkyCityDamage(float i_Percent)
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

void AutoTestAllLevel::ForceFinishLevel()
{
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

void AutoTestAllLevel::AutoStartLevelFight()
{
	AutoTestInitPlantPlace("test");
}

void AutoTestAllLevel::AutoEnterWorld()
{
	WorldMap* worldMap = gLawnApp->GetWorldMap();
	if (worldMap)
	{
		UniverseMap* universeMap = worldMap->GetUniverseMap();
		if (universeMap && m_currentLevel)
			universeMap->enterWorldAction(m_currentLevel->GetWorldDataPtr()->m_worldId - 1);
	}
	AutoStartFirstLevel();
}

void AutoTestAllLevel::AutoEnterLevel()
{
	if (m_vecLevel.size() == 0)
	{
		m_curLevelIndex = 0;
		m_curWorldIndex = 1;
		RefreshNewLevelList(m_vecLevel);
	}
	m_currentLevel = WorldMapUtils::GetWorldDataForEdit()->FindEventByLevelName(m_vecLevel[m_curLevelIndex]);
	if (m_currentLevel)
		gLawnApp->GetWorldMap()->GetUniverseMap()->TransitionToUniverse(false);
}

void AutoTestAllLevel::AutoStartFirstLevel()
{
	if (m_needChangeLevel)
	{
		RefreshNewLevelList(m_vecLevel);
		StartCurrentLevel(m_vecLevel[m_curLevelIndex]);
		m_needChangeLevel = NULL;
	}
	else
	{
		m_curLevelIndex = 0;
		m_curWorldIndex = 1;
		RefreshNewLevelList(m_vecLevel);
		StartCurrentLevel(m_vecLevel[m_curLevelIndex]);
	}
}

void AutoTestAllLevel::RefreshNewLevelList(std::vector<std::string>& vecLevel)
{
	vecLevel.clear();
	int worldIndex = m_curWorldIndex;
	if (worldIndex < m_vecWorldMap.size())
	{
		std::string world = m_vecWorldMap[worldIndex];
		std::vector<const MapEventItem*> events;
		WorldMapUtils::GetOrderedMainSpinePath(world, events);
		for (const MapEventItem* event : events)
		{
			if (event->GetEventType() == MAPEVENT_LEVEL_ENTRANCE)
				vecLevel.push_back(event->GetDataString());
		}
	}
}

void AutoTestAllLevel::AutoTestPLantDie(Plant* i_plant)
{
	if (!gLawnApp->m_board)
		return;
	if (m_strAimUsePlant.empty())
		return;
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (!gLawnApp->m_board->GetPlantAt(x, y, ""))
				gLawnApp->m_board->TestSpawnPlant(m_strAimUsePlant, x, y);
		}
	}
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(AutoTestAllLevel);
