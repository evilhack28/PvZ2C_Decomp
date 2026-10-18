//
//  LootEntrySaveData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "Loot.h"

/////////////// Lifecycle ///////////////

LootEntrySaveData::LootEntrySaveData()
{
	UniqueId = "";
	LevelLengthsPlayed = 0.0f;
	NextDropTime = FLT_MAX;
	NextScheduleTime = 0.0f;
}

LootEntrySaveData::LootEntrySaveData(LootEntrySaveData&&) = default;

LootEntrySaveData::~LootEntrySaveData() = default;
