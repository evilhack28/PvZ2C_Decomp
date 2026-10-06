//
//  PowerupRecord.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "PlayerInfo.h"

/////////////// PowerupRecord ///////////////

PowerupRecord::PowerupRecord()
	: Inventory(0)
{
}

PowerupRecord::PowerupRecord(const PowerupRecord& i_other) = default;

PowerupRecord::PowerupRecord(PowerupRecord&& i_other) = default;

PowerupRecord::~PowerupRecord() = default;

PowerupRecord& PowerupRecord::operator=(const PowerupRecord& i_other) = default;

PowerupRecord& PowerupRecord::operator=(PowerupRecord&& i_other) = default;
