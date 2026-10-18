//
//  RichmanBattleEventSaveData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "PlayerInfo.h"

/////////////// Lifecycle ///////////////

RichmanBattleEventSaveData::RichmanBattleEventSaveData()
{
	Reset();
}

RichmanBattleEventSaveData::RichmanBattleEventSaveData(const RichmanBattleEventSaveData&) = default;

RichmanBattleEventSaveData::~RichmanBattleEventSaveData() = default;

/////////////// Accessors ///////////////

void RichmanBattleEventSaveData::Reset()
{
	_needPopup = false;
	_battleWin = false;
	_battleEventType = -1;
	_levelName = "";
	_rewardID = 0;
	_rewardCount = 0;
	_rewardItemList.clear();
	_rewardChestList.clear();
	_timeStamp = 0;
}

RichmanBattleEventSaveData& RichmanBattleEventSaveData::operator=(const RichmanBattleEventSaveData&) = default;
