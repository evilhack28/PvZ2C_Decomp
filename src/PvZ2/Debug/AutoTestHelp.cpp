//
//  AutoTestHelp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include <string>

#include "AutoTestHelp.h"
#include "LawnApp.h"
#include "MapEventItem.h"
#include "WorldData.h"
#include "WorldMapUtils.h"

const MapEventItem* GetNextItem(const MapEventItem* i_level);
const MapEventItem* GetNextStarGate(const MapEventItem* i_level);

/////////////// AutoTestHelp ///////////////

namespace AutoTestHelp {

const MapEventItem* GetNextMainLineItem(const MapEventItem* i_level)
{
	const MapEventItem* next;
	do
	{
		next = GetNextItem(i_level);
		if (next == NULL)
			return GetNextStarGate(i_level);

		i_level = next;
	} while (next->GetEventType() != MAPEVENT_LEVEL_ENTRANCE);

	return next;
}

const MapEventItem* GetStartMainLineItem(const MapEventItem* i_item)
{
	gLawnApp->GetWorldMapList();
	return NULL;
}

std::vector<std::vector<std::string>> GetAllWorldLevels()
{
	std::vector<std::vector<std::string>> result;
	result.push_back(std::vector<std::string>());

	const WorldDataManager* worldData = WorldMapUtils::GetWorldData();
	const MapEventItem* item = worldData->FindEvent(gLawnApp->GetWorldMapList()->MapList[1].EntryPoint);
	for (;;)
	{
		if (item->GetEventType() == MAPEVENT_STAR_GATE)
		{
			item = GetStartMainLineItem(item);
			if (item == NULL)
				return result;

			result.push_back(std::vector<std::string>());
			continue;
		}

		result.back().push_back(item->GetDataString());
		item = GetNextMainLineItem(item);
	}
}

}
