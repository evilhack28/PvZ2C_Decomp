//
//  PVZCheats.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVZCheats.h"
#include "PvZ/ProfileMgr.h"
#include "PvZ/PlayerInfo.h"
#include "PvZ/AutoTest.h"
#include "PvZ/ProfileUtils.h"
#include "PvZ/Collectable.h"
#include "PvZ/BoardTransforms.h"
#include "PvZ/Zombie.h"
#include "PvZ/Board.h"
#include "PvZ/CrazyNPCManager.h"

#include "PvZ/GameStateMgr.h"
#include "PvZ/LawnApp.h"
#include "PvZ/DangerRoomManager.h"
#include "PvZ/DangerRoomModule.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

CheatVariable::~CheatVariable()
{
}

CheatGameUnlockToEvent::~CheatGameUnlockToEvent()
{
}

CheatGameStartNarrative::~CheatGameStartNarrative()
{
}

CheatGameSpawnCollectable::~CheatGameSpawnCollectable()
{
}

CheatGameSpawnPlantCommand::~CheatGameSpawnPlantCommand()
{
}

CheatGameStartLevelCommand::~CheatGameStartLevelCommand()
{
}

CheatGameSpawnZombieCommand::~CheatGameSpawnZombieCommand()
{
}

CheatGameSpawnCreatureCommand::~CheatGameSpawnCreatureCommand()
{
}

CheatAutoTestStartLevelCommand::~CheatAutoTestStartLevelCommand()
{
}

CheatDangerRoomStartLevelCommand::~CheatDangerRoomStartLevelCommand()
{
}

CheatAutoTestStartUnlockLevelCommand::~CheatAutoTestStartUnlockLevelCommand()
{
}

CheatPlantsVsZombiesStartWorldCommand::~CheatPlantsVsZombiesStartWorldCommand()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(CheatVariable);

RT_CLASS_IMPLEMENT(CheatGameFeatureToggle);

RT_CLASS_IMPLEMENT(CheatGameUnlockToEvent);

RT_CLASS_IMPLEMENT(CheatGameStartNarrative);

RT_CLASS_IMPLEMENT(CheatGameSpawnCollectable);

RT_CLASS_IMPLEMENT(CheatGameProfileLockToggle);

RT_CLASS_IMPLEMENT(CheatGameSpawnPlantCommand);

RT_CLASS_IMPLEMENT(CheatGameStartLevelCommand);

RT_CLASS_IMPLEMENT(CheatGameSpawnZombieCommand);

RT_CLASS_IMPLEMENT(CheatGameSpawnCreatureCommand);

RT_CLASS_IMPLEMENT(CheatAutoTestStartLevelCommand);

RT_CLASS_IMPLEMENT(CheatDangerRoomStartLevelCommand);

RT_CLASS_IMPLEMENT(CheatAutoTestStartUnlockLevelCommand);

RT_CLASS_IMPLEMENT(CheatPlantsVsZombiesStartWorldCommand);

/////////////// Logic ///////////////

void CheatVariable::SetValue(float i_value)
{
	m_value = i_value;
	if (m_action)
	{
		m_action(m_value);
	}
}

void CheatVariable::SetValue2(float i_value)
{
	m_value = i_value;
	if (m_action2)
	{
		m_action2(m_type, m_value);
	}
}

bool CheatGameFeatureToggle::GetValue() const
{
	if (!ProfileMgr::GetInstance().HasValidProfile())
	{
		return false;
	}
	return ProfileMgr::GetInstance().GetCurrentProfile()->GameFeatureIsUnlocked(m_feature);
}

void CheatGameFeatureToggle::SetValue(bool i_newValue)
{
	if (!ProfileMgr::GetInstance().HasValidProfile())
	{
		return;
	}
	ProfileMgr::GetInstance().GetCurrentProfile()->SetGameFeatureUnlockState(m_feature, i_newValue);
	CrashTracking::Log(StrFormat("PVZ_T: %f - [CHEAT] Cheat %s toggled with Value: %s", PVZ_T(), GetName().c_str(), GetValue() ? "true" : "false"));
}

bool CheatGameProfileLockToggle::GetValue() const
{
	if (!ProfileMgr::GetInstance().HasValidProfile())
	{
		return false;
	}
	return ProfileMgr::GetInstance().GetReadOnlyMode();
}

void CheatGameProfileLockToggle::SetValue(bool i_newValue)
{
	if (!ProfileMgr::GetInstance().HasValidProfile())
	{
		return;
	}
	ProfileMgr::GetInstance().SetReadOnlyMode(i_newValue);
	CrashTracking::Log(StrFormat("PVZ_T: %f - [CHEAT] CheatGameProfileLockToggle %s toggled with Value: %s", PVZ_T(), GetName().c_str(), i_newValue ? "true" : "false"));
}

void CheatAutoTestStartLevelCommand::changeLevel()
{
	gMessageRouter->Post(Message::changeAutoTestStartLevel, std::string(m_eventName));
}

void CheatAutoTestStartUnlockLevelCommand::changeLevel()
{
	gMessageRouter->Post(Message::changeAutoTestStartUnlockLevel, std::string(m_eventName));
}

void CheatPlantsVsZombiesStartWorldCommand::changeWorld()
{
	gMessageRouter->Post(Message::changePlantsVsZombiesStartWorld, std::string(m_worldName));
}

void CheatDangerRoomStartLevelCommand::startLevel()
{
	S2C_DangerRoomRecord record;
	Sexy::LazySingleton<DangerRoomManager>::GetInstancePtr()->SetRecord(record);
	DangerRoomModule::StartDangerRoomLevel(m_worldName, false);
}

static std::string sEmptyWorld;

void CheatGameStartLevelCommand::startLevel()
{
	CrashTracking::Log(StrFormat("[#43966] CheatGameStartLevelCommand::startLevel - Loading level from cheats: %s", m_levelName.c_str()));
	gGameStateMgr->StartLevel(sEmptyWorld, m_levelName, -1, GAMETRANSITION_QuickWhite, GAMETRANSITION_QuickWhite, LEVELSOURCE_Arcade);
}

void CheatGameStartNarrative::startNarrative()
{
	if (!gLawnApp->GetNarrationSystem()->IsNarrationActive())
	{
		gLawnApp->GetNarrationSystem()->StartNarrativeID(m_narrative, CrazyNPCManager::NarrativeFinishedDelegate(), "");
	}
}

void CheatGameSpawnCreatureCommand::spawnCreature()
{
	CreatureTypePtr type = ObjectTypeDirectory<CreatureType>::GetInstancePtr()->GetTypeFromTypeName(m_creatureTypeName);
	if (type)
	{
		gLawnApp->m_board->CheatAddCreature(type, -1);
	}
}

extern int cheat_spawn_zombie_row;

extern int cheat_spawn_zombie_level;

void CheatGameSpawnZombieCommand::spawnZombie()
{
	ZombieTypePtr type = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName(m_zombieTypeName);
	if (type)
	{
		Zombie* zombie = gLawnApp->m_board->CheatAddZombie(type, cheat_spawn_zombie_row, true);
		zombie->SetCurrentLevel(cheat_spawn_zombie_level);
		zombie->RefreshStats();
	}
}

void CheatGameSpawnCollectable::spawnCollectable()
{
	Collectable* collectable = gLawnApp->m_board->AddCollectable(m_collectableType);
	Sexy::Point pos = BoardTransforms::GridToBoardSpacePos(4, 2);
	collectable->SetPosition(SexyVector3(pos.mX, pos.mY, 0));
	SexyVector3 velocity;
	velocity.x = Sexy::Rand(100.0f) - 50.0f;
	velocity.z = Sexy::Rand(200.0f) + 300.0f;
	collectable->SetMotionNewtonian(velocity, SexyVector3(0, 0, -600.0f), true);
	collectable->SetKeepOnBoard(true);
	collectable->StartExpirationTimerAfterMotion();
}

void CheatGameSpawnPlantCommand::spawnPlant()
{
	PlantTypePtr type = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(m_plantTypeName);
	if (type)
	{
		for (int x = 0; x < 5; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				if (gLawnApp->m_board->CanPlantAt(Sexy::Point(x, y), type))
				{
					gLawnApp->m_board->TestSpawnPlant(m_plantTypeName, x, y);
					return;
				}
			}
		}
	}
}

std::string getWorldNameFromEventName(const std::string& i_eventName);

void CheatGameUnlockToEvent::unlockToEvent()
{
	if (!ProfileMgr::GetInstance().HasValidProfile())
	{
		return;
	}
	if (ProfileUtils::Profile()->GetHasBeenConvertedToNewMap() != m_newMap)
	{
		if (m_newMap)
		{
			ProfileUtils::Profile()->SetMapConversionState(MAPCONVERSION_NotNeeded);
		}
		else
		{
			ProfileUtils::Profile()->SetMapConversionState(MAPCONVERSION_None);
		}
	}
	ProfileUtils::DeleteAndRecreatePlayerInfo(ProfileMgr::GetInstance().GetCurrentProfile());
	if (m_newMap)
	{
		ProfileUtils::CompleteToEventFloodFill(m_eventName, ProfileMgr::GetInstance().GetCurrentProfile());
	}
	std::string eventName = m_eventName;
	std::string worldName = getWorldNameFromEventName(eventName);
	if (!worldName.empty())
	{
		if ("egypt" != worldName)
		{
			PVZCheats::CheatSkipAllTutorials();
			ProfileUtils::Profile()->CompleteNarrationEvent("nar_minigame_intro");
		}
		ProfileUtils::Profile()->SetCurrentLevel(StrFormat("%s%d", worldName.c_str(), 1));
	}
	ProfileUtils::Profile()->ResetStarTotal();
	StrFormat("Completed up to %s!", eventName.c_str());
}
