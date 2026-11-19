//
//  WorldMapUtils.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "WorldData.h"
#include "WorldMapUtils.h"

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
