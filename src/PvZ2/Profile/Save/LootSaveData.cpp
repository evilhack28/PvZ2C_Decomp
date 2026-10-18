//
//  LootSaveData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "Loot.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

LootSaveData::LootSaveData()
{
	ProfileIndex = 0;
}

LootSaveData::~LootSaveData() = default;

/////////////// Accessors ///////////////

LootEntrySaveData* LootSaveData::GetLootEntryData(const std::string& i_uniqueId)
{
	for (size_t i = 0; i != m_lootEntryInstancedData.size(); i++)
	{
		if (m_lootEntryInstancedData[i].UniqueId == i_uniqueId)
			return &m_lootEntryInstancedData[i];
	}
	m_lootEntryInstancedData.push_back(LootEntrySaveData());
	m_lootEntryInstancedData.back().UniqueId = i_uniqueId;
	return &m_lootEntryInstancedData.back();
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(LootSaveData);

void LootSaveData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LootEntrySaveData);
		REFLECTION_CLASSBUILDER_FIELD(std::string, UniqueId);
		REFLECTION_CLASSBUILDER_FIELD(double, LevelLengthsPlayed);
		REFLECTION_CLASSBUILDER_FIELD(double, NextDropTime);
		REFLECTION_CLASSBUILDER_FIELD(double, NextScheduleTime);
	REFLECTION_CLASSBUILDER_END(LootEntrySaveData);

	REFLECTION_CLASSBUILDER_BEGIN(LootSaveData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD(int32_t, ProfileIndex);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<LootEntrySaveData>, m_lootEntryInstancedData);
	REFLECTION_CLASSBUILDER_END(LootSaveData);
}
