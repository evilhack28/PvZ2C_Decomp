//
//  Leaderboard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "GameCenterProxy.h"
#include "Leaderboard.h"

static GameCenterProxy* gGameCenterProxy = NULL;

/////////////// Leaderboard ///////////////

void Leaderboard::Init(GameCenterProxy* i_gcp)
{
	gGameCenterProxy = i_gcp;
}

void Leaderboard::Shutdown()
{
	gGameCenterProxy = NULL;
}

void Leaderboard::SubmitScore(const std::string& i_leaderboard, int i_score)
{
	gGameCenterProxy->SubmitScoreToLeaderboard(i_score, i_leaderboard);
}

void Leaderboard::Show(const std::string& i_leaderboard)
{
	gGameCenterProxy->ShowLeaderboardView(i_leaderboard);
}
