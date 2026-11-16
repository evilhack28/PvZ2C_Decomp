//
//  GameCenterProxy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "GameCenterProxy.h"

/////////////// GameCenterProxy ///////////////

GameCenterProxy::GameCenterProxy()
{
	m_driver = NULL;
	m_delegate = NULL;
}

GameCenterProxy::~GameCenterProxy()
{
}

bool GameCenterProxy::IsConnected() const
{
	return false;
}

void GameCenterProxy::Connect()
{
}

void GameCenterProxy::QueueAchievement(const std::string& i_achievement)
{
}

void GameCenterProxy::QueueAchievement(const std::string& i_achievement, float i_percentComplete)
{
}

void GameCenterProxy::SubmitAchievements()
{
}

void GameCenterProxy::SubmitScoreToLeaderboard(int i_score, const std::string& i_leaderboard)
{
}

void GameCenterProxy::ResetAchievements()
{
}

void GameCenterProxy::FetchAchievements()
{
}

void GameCenterProxy::ShowAchievementView()
{
}

void GameCenterProxy::ShowLeaderboardView(const std::string& i_leaderboard)
{
}
