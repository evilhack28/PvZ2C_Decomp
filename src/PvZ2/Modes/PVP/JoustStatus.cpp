//
//  JoustStatus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "JoustStatus.h"

JoustStatus::~JoustStatus()
{
}

const std::string& JoustStatus::GetURLOverride()
{
	return URLOverride;
}

JoustTournamentData& JoustStatus::GetTournamentData()
{
	return TournamentData;
}

JoustLeaderboardData& JoustStatus::GetLeaderboardData()
{
	return LeaderboardData;
}

const JoustAPIResponseLeagueChange& JoustStatus::GetLeagueChangeEvent()
{
	return LeagueChangeEvent;
}

const JoustAPIResponseMatchComplete& JoustStatus::GetMatchCompleteData()
{
	return MatchCompleteData;
}

void JoustStatus::SetLeagueChangeEvent(JoustAPIResponseLeagueChange& i_leagueChange)
{
	LeagueChangeEvent = i_leagueChange;
}

void JoustStatus::SetMatchCompleteData(JoustAPIResponseMatchComplete& i_matchComplete)
{
	MatchCompleteData = i_matchComplete;
}
