//
//  NullLeaderboardDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
/////////////// Lifecycle ///////////////

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/leaderboard/NullLeaderboardDriver.h"

namespace Sexy
{

NullLeaderboardDriver::NullLeaderboardDriver()
{
}

bool NullLeaderboardDriver::Init()
{
	return true;
}

void NullLeaderboardDriver::Update()
{
}

/////////////// Schema ///////////////

void NullLeaderboardDriver::RegisterSchema(LeaderboardId id, LeaderboardSchema *schema)
{
}

const LeaderboardSchema *NullLeaderboardDriver::GetSchema(LeaderboardId id)
{
	return NULL;
}

/////////////// Scores ///////////////

uint32 NullLeaderboardDriver::MaxReadEntries()
{
	return 100;
}

LeaderboardWriteContext *NullLeaderboardDriver::StartWriteScore(UserProfile *player, LeaderboardId leaderboardId, const std::string &secondaryId, LeaderboardEntry *entry)
{
	return NULL;
}

LeaderboardReadContext *NullLeaderboardDriver::StartReadScores(UserProfile *player, LeaderboardId leaderboardId, const std::string &secondaryId, Leaderboard::Type type, uint32 startRank, uint32 maxEntries)
{
	return NULL;
}

}
