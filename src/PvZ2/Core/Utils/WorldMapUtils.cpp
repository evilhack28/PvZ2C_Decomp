//
//  WorldMapUtils.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "WorldData.h"
#include "WorldMapUtils.h"

void loadWorldMapData();

__attribute__((visibility("hidden"))) WorldMapList* sWorldMapList;
__attribute__((visibility("hidden"))) WorldDataManager* sWorldData;

/////////////// World data ///////////////

void WorldMapUtils::LoadWorldMapData()
{
	loadWorldMapData();
	sWorldData->RebuildWorldData();
}

WorldMapList* WorldMapUtils::GetWorldMapListForEdit()
{
	if (!sWorldMapList)
		LoadWorldMapData();
	return sWorldMapList;
}

const WorldMapList* WorldMapUtils::GetWorldMapList()
{
	return GetWorldMapListForEdit();
}

WorldDataManager* WorldMapUtils::GetWorldDataForEdit()
{
	return sWorldData;
}

const WorldDataManager* WorldMapUtils::GetWorldData()
{
	return sWorldData;
}

/////////////// World queries ///////////////

bool WorldMapUtils::IsRiftWorld(const std::string& i_worldName)
{
	return GetWorldMapList()->GetMapListNodeByName(i_worldName)->IsRiftWorld;
}

bool WorldMapUtils::IsPVZ1World(const std::string& i_worldName)
{
	return GetWorldMapList()->GetMapListNodeByName(i_worldName)->IsPVZ1World;
}

bool WorldMapUtils::IsUnchartedWorld(const std::string& i_worldName)
{
	return GetWorldMapList()->GetMapListNodeByName(i_worldName)->IsUnchartedWorld;
}

bool WorldMapUtils::IsCardGameWorld(const std::string& i_worldName)
{
	return GetWorldMapList()->GetMapListNodeByName(i_worldName)->IsCardGameWorld;
}

std::string WorldMapUtils::DetermineNextLevelToPlay()
{
	return "";
}
