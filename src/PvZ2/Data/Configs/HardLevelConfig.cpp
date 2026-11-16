//
//  HardLevelConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HardLevelConfig.h"
#include "LawnApp.h"
#include "Board.h"
#include "LevelUtils.h"
#include "LevelDefinition.h"
#include "WorldMapUtils.h"
#include "WorldData.h"
#include "MapEventItem.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

HardLevelConfig::HardLevelConfig()
{
}

HardLevelConfig::~HardLevelConfig()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(HardLevelConfig);

void HardLevelConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HardLevelData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iWorldIndex, world);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iLevelIndex, level);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, iDifficulty, difficulty);
	REFLECTION_CLASSBUILDER_END(HardLevelData);

	REFLECTION_CLASSBUILDER_BEGIN(HardLevelConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<HardLevelData>, m_dataList, ConfigList);
	REFLECTION_CLASSBUILDER_END(HardLevelConfig);
}

/////////////// Accessors ///////////////

HardLevelConfig* HardLevelConfig::GetConfig()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_HARDLEVEL_CONFIG);
	return table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("HardLevelConfig"))))->CastChecked<HardLevelConfig>();
}

ZombieLevelCreater HardLevelConfig::GetZombieLevelCreate(const std::string& i_levelName)
{
	return ZombieLevelCreater(GetDifficulty(i_levelName));
}

/////////////// Logic ///////////////

float HardLevelConfig::GetDifficulty(int i_worldIndex, int i_levelIndex)
{
	std::vector<HardLevelData>::iterator it = m_dataList.begin();
	std::vector<HardLevelData>::iterator end = m_dataList.end();
	for (; it != end; ++it)
	{
		if ((*it).iWorldIndex == i_worldIndex)
		{
			if ((*it).iLevelIndex == i_levelIndex)
				return (*it).iDifficulty;
		}
	}
	return 4;
}

float HardLevelConfig::GetDifficulty(const std::string& i_levelName)
{
	std::string levelName;
	int levelNumber;
	if (i_levelName.empty() && gLawnApp->m_board)
	{
		levelName = gLawnApp->m_board->GetLevel();
		levelNumber = gLawnApp->m_board->GetLevelDefinition()->LevelNumber;
	}
	else
	{
		levelName = i_levelName;
		levelNumber = LevelUtils::GetInstance().LoadLevelDefinition(levelName, true)->LevelNumber;
	}

	MapEventItem* event = WorldMapUtils::GetWorldData()->FindEventByLevelName(levelName);
	if (event)
	{
		WorldData* world = event->GetWorldDataPtr();
		if (world)
		{
			uint8 worldId = world->m_worldId;
			PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
			int index = profile->RecordHardWorld(worldId, false);
			const std::vector<uint8>& order = profile->GetHardWorldOrder();
			if (index >= 0 && (size_t)index < order.size())
				return GetDifficulty(order[index], levelNumber);
			return 1;
		}
	}
	return 4;
}
