//
//  WorldCupConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldCupConfig.h"
#include "PVZDB.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

WorldCupConfig::~WorldCupConfig()
{
}

WorldCupConfig::WorldCupConfig()
{
	m_inited = 0;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(WorldCupConfig);

/////////////// Accessors ///////////////

std::vector<PlayerSet> WorldCupConfig::GetPlayerSetList()
{
	if (m_inited)
		return m_setList;
	return std::vector<PlayerSet>();
}

/////////////// Logic ///////////////

std::vector<ObstacleNonSpawnData> WorldCupConfig::GetTargetSetLocations(int i_id)
{
	if (m_inited)
	{
		std::vector<PlayerSet>::iterator it = m_setList.begin();
		std::vector<PlayerSet>::iterator end = m_setList.end();
		for (; it != end; ++it)
		{
			if ((*it).setId == i_id)
				return (*it).setLocations;
		}
	}
	return std::vector<ObstacleNonSpawnData>();
}

void WorldCupConfig::Refresh()
{
	Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_WORLDCUP_CONFIG);
	for (; it; it++)
	{
		Sexy::RtWeakPtr<Sexy::RtObject> config = *it;
		WorldCupConfig* other = NULL;
		if (config)
			other = config->Cast<WorldCupConfig>();
		if (other)
		{
			m_setList = other->m_setList;
			m_inited = true;
			break;
		}
	}
}

void WorldCupConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ObstacleNonSpawnData);
		REFLECTION_CLASSBUILDER_FIELD(int, GridX);
		REFLECTION_CLASSBUILDER_FIELD(int, GridY);
	REFLECTION_CLASSBUILDER_END(ObstacleNonSpawnData);

	REFLECTION_CLASSBUILDER_BEGIN(PlayerSet);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, setId, SetId);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<ObstacleNonSpawnData>, setLocations, SetLocations);
	REFLECTION_CLASSBUILDER_END(PlayerSet);

	REFLECTION_CLASSBUILDER_BEGIN(WorldCupConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<PlayerSet>, m_setList, SetList);
	REFLECTION_CLASSBUILDER_END(WorldCupConfig);

}
