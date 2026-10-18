//
//  DangerRoomSpecialOfferSaveData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "PlayerInfo.h"

/////////////// Lifecycle ///////////////

DangerRoomSpecialOfferSaveData::DangerRoomSpecialOfferSaveData()
{
	Reset();
}

/////////////// Accessors ///////////////

void DangerRoomSpecialOfferSaveData::Reset()
{
	_hasBought = false;
	_expiredTime = 0;
	_popUpUICount = 0;
	_bCheck = false;
}
