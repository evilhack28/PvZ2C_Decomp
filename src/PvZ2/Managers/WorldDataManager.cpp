//
//  WorldDataManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "WorldData.h"
#include "WorldMapUtils.h"
#include "LawnApp.h"

/////////////// Lookup ///////////////

MapEventItem* WorldDataManager::FindEventByName(const std::string& i_eventName) const
{
	return FindEventOfTypeByName(MAPEVENT_NONE, i_eventName);
}

MapEventItem* WorldDataManager::FindEventByDataName(const std::string& i_dataName) const
{
	return FindEventOfTypeByDataName(MAPEVENT_NONE, i_dataName);
}

MapEventItem* WorldDataManager::FindEventByLevelName(const std::string& i_levelName) const
{
	return FindEventOfTypeByDataName(MAPEVENT_LEVEL_ENTRANCE, i_levelName);
}

/////////////// Accessors ///////////////

int WorldDataManager::GetWorldDataCount() const
{
	return m_worldDataList.size();
}

WorldData* WorldDataManager::GetWorldDataByIdx(int i_idx) const
{
	return m_worldDataList[i_idx];
}

bool WorldDataManager::IsValidWorldId(int i_worldID)
{
	const WorldMapList* worldMapList = WorldMapUtils::GetWorldMapList();
	return worldMapList && worldMapList->GetMapListNodeById(i_worldID) != NULL;
}

WorldDataManager::WorldDataManager()
{
}

/////////////// Data ///////////////

void WorldDataManager::RebuildWorldData()
{
	clearData();
	const WorldMapList* worldMapList = WorldMapUtils::GetWorldMapList();
	std::vector<MapListNode>::const_iterator it = worldMapList->MapList.begin();
	std::vector<MapListNode>::const_iterator end = worldMapList->MapList.end();
	for (; it != end; ++it)
	{
		const std::string& worldName = (*it).MapName;
		if (worldMapList->IsWorldEnabled(worldName))
		{
			std::string groupName = Sexy::StrFormat("WorldPackages_%s", worldName.c_str());
			if (gLawnApp->mResourceManager->GetResourceGroupNamed(groupName))
			{
				gLawnApp->LoadGroup(groupName);
				m_loadedWorldMapPackageGroups.push_back(groupName);
			}
			WorldData* worldData = WorldMapUtils::LoadSerializedMapData(worldName, WorldMapUtils::FILTER_Active);
			m_worldDataList.push_back(worldData);
		}
	}
	RemapWorldMapEvents();
}
