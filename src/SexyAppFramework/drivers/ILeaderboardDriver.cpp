//
//  ILeaderboardDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ILeaderboardDriver.h"
#include "SexyAppFramework/drivers/leaderboard/NullLeaderboardDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

ILeaderboardDriver* ILeaderboardDriver::CreateLeaderboardDriver()
{
    return new NullLeaderboardDriver();
}
