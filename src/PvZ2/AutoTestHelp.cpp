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

const MapEventItem* GetNextItem(const MapEventItem* i_level);
const MapEventItem* GetNextStarGate(const MapEventItem* i_level);

/////////////// AutoTestHelp ///////////////

namespace AutoTestHelp {

const MapEventItem* GetNextMainLineItem(const MapEventItem* i_level)
{
	const MapEventItem* item = GetNextItem(i_level);
	while (item != NULL)
	{
		if (item->m_eventType == MAPEVENT_LEVEL_ENTRANCE)
		{
			return item;
		}

		item = GetNextItem(item);
	}

	return GetNextStarGate(i_level);
}

const MapEventItem* GetStartMainLineItem(const MapEventItem* i_item)
{
	gLawnApp->GetWorldMapList();
	return NULL;
}

std::vector<std::vector<std::string>> GetAllWorldLevels()
{
	return std::vector<std::vector<std::string>>();
}

}
