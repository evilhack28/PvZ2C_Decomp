//
//  AutoTestAllLevelUnlock.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-16.
//

#include "SexyAppFramework/Common.h"

#include "AutoTest.h"
#include "LawnApp.h"
#include "WorldMap.h"
#include "UniverseMap.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "ProfileUtils.h"
#include "DebugLog.h"
#include "PVZ2UIDialog.h"
#include "PrimeText_Game.h"
#include "PVZCheats.h"
#include "Cheats.h"
#include "WorldMapUtils.h"
#include "WorldData.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

AutoTestAllLevelUnlock::AutoTestAllLevelUnlock() :
	m_changeTime(PVZ_EOT()),
	m_curLevelIndex(0),
	m_curWorldIndex(0),
	m_bWorldmapFinish(false)
{
	gMessageRouter->Subscribe(&Message::changeAutoTestStartUnlockLevel, Sexy::MakeDelegate(*this, &AutoTestAllLevelUnlock::ChangeWorldMap));
}

AutoTestAllLevelUnlock::~AutoTestAllLevelUnlock()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Logic ///////////////

void AutoTestAllLevelUnlock::AutoConfirmOver()
{
	gLawnApp->KillPVZ2Dialog();
}

void AutoTestAllLevelUnlock::EnterWorldMap()
{
	if (m_changWorldName.empty())
		return;

	std::string levelName = Sexy::StrFormat("%s1", m_changWorldName.c_str());
	MapEventItem* event = WorldMapUtils::GetWorldData()->FindEventByLevelName(levelName);
	WorldMap* worldMap = gLawnApp->GetWorldMap();
	if (worldMap && worldMap->GetUniverseMap() && event)
	{
		if (!m_changWorldName.empty())
		{
			m_curWorldName = m_changWorldName;
			m_changWorldName = "";
		}

		const WorldMapList* worldMapList = WorldMapUtils::GetWorldMapList();
		for (int i = m_curWorldIndex; i < worldMapList->MapList.size(); i++)
		{
			const std::string& name = worldMapList->MapList[i].MapName;
			if (worldMapList->IsWorldEnabled(name))
			{
				if (name == m_curWorldName)
					break;
				m_curWorldIndex++;
			}
		}
		m_bWorldmapFinish = false;
		gLawnApp->ShowWorldPreview(m_curWorldName);
	}
}

void AutoTestAllLevelUnlock::EnterWorldMapFinish()
{
	m_bWorldmapFinish = true;
}

void AutoTestAllLevelUnlock::EnterUniverse()
{
	if (m_changWorldName.empty())
	{
		m_changWorldName = "egypt";
		m_curLevelIndex = 0;
		m_curWorldIndex = 0;
		gLawnApp->GetWorldMap()->GetUniverseMap()->TransitionToUniverse(false);
	}
}

void AutoTestAllLevelUnlock::ChangeWorldMap(const std::string& i_world)
{
	gLawnApp->GetWorldMap()->GetUniverseMap()->TransitionToUniverse(false);
	m_changWorldName = i_world;
	CheatManager::GetInstancePtr()->SetToggleValue("AutoTestUnlockLevel", true);
}

void AutoTestAllLevelUnlock::updateState(bool i_isOn)
{
	if (i_isOn)
	{
		PVZCheats::CheatSkipAllTutorials();
		gMessageRouter->Subscribe(&Message::UniverseMapReady, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestAllLevelUnlock::EnterWorldMap)));
		gMessageRouter->Subscribe(&Message::AutoTestEnterWorldMap, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestAllLevelUnlock::EnterWorldMapFinish)));
		gMessageRouter->Subscribe(&Message::AutoTestUpdateLevelUnlockState, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestAllLevelUnlock::UpdateUnlockState)));
		gMessageRouter->Subscribe(&Message::AutoTestShowWorldPreview, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestAllLevelUnlock::ShowWorldPrebview)));
		WorldMap* worldMap = gLawnApp->GetWorldMap();
		if (worldMap && worldMap->GetCurrentWorld())
			EnterUniverse();
	}
	else
	{
		gMessageRouter->Unsubscribe(&Message::UniverseMapReady, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestAllLevelUnlock::EnterWorldMap)));
		gMessageRouter->Unsubscribe(&Message::AutoTestEnterWorldMap, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestAllLevelUnlock::EnterWorldMapFinish)));
		gMessageRouter->Unsubscribe(&Message::AutoTestUpdateLevelUnlockState, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestAllLevelUnlock::UpdateUnlockState)));
		gMessageRouter->Unsubscribe(&Message::AutoTestShowWorldPreview, Sexy::Delegate0(Sexy::MakeDelegate(*this, &AutoTestAllLevelUnlock::ShowWorldPrebview)));
	}
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(AutoTestAllLevelUnlock);
