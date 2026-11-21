//
//  PlantAdventureConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAdventureConfig.h"
#include "PVZDB.h"

PlantAdventureConfig::~PlantAdventureConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAdventureConfig);

void PlantAdventureConfig::Refresh()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANT_ADVENTURE_CONFIG); it; it++)
	{
		Sexy::RtWeakPtr<Sexy::RtObject> object = *it;
		PlantAdventureConfig* config = NULL;
		if (object)
			config = object->Cast<PlantAdventureConfig>();
		if (config)
		{
			m_maxTeam = config->m_maxTeam;
			m_monthlyCardTeamPro = config->m_monthlyCardTeamPro;
			m_dungeonList = config->m_dungeonList;
			m_surpriseInfo = config->m_surpriseInfo;
			m_inited = true;
			break;
		}
	}
}
