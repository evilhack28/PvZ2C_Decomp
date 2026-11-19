//
//  WorldMapList.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "WorldData.h"
#include "ReflectionBuilder.h"
#include "Throttles.h"

RT_CLASS_IMPLEMENT(WorldMapList);

void WorldMapList::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MapListNode);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, LastLevel);
		REFLECTION_CLASSBUILDER_FIELD(Point, UniverseIconOffset);
		REFLECTION_CLASSBUILDER_FIELD(WorldResourcesData, WorldResources);
	REFLECTION_CLASSBUILDER_END(MapListNode);

	REFLECTION_CLASSBUILDER_BEGIN(WorldMapList);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<MapListNode>, MapList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<uint8> >, MapResourceGrid);
	REFLECTION_CLASSBUILDER_END(WorldMapList);
}

/////////////// Accessors ///////////////

const MapListNode* WorldMapList::GetMapListNodeByName(const std::string& i_name) const
{
	for (std::vector<MapListNode>::const_iterator it = MapList.begin(), end = MapList.end(); it != end; ++it)
	{
		const MapListNode& node = *it;
		if (node.MapName == i_name)
			return &node;
	}
	return NULL;
}

const MapListNode* WorldMapList::GetMapListNodeById(const int& i_worldId) const
{
	for (std::vector<MapListNode>::const_iterator it = MapList.begin(), end = MapList.end(); it != end; ++it)
	{
		const MapListNode& node = *it;
		if (node.WorldId == i_worldId)
			return &node;
	}
	return NULL;
}

bool WorldMapList::IsWorldEnabled(const std::string& i_name) const
{
	return !(i_name == "coming_soon");
}

bool WorldMapList::IsWorldComingSoon(const std::string& i_name) const
{
	const MapListNode* node = GetMapListNodeByName(i_name);
	if (node && !node->Disabled && node->ComingSoon)
		return Throttles::GetInstance().WorldIsDisabled(i_name);
	return false;
}
