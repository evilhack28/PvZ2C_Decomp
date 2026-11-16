//
//  DifficultyLevelConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "DifficultyLevelConfig.h"

/////////////// DifficultyLevelConfig ///////////////

DifficultyLevelConfig::DifficultyLevelConfig()
{
	NumResultsToStore = 5;
	MinStreakLen = 2;
	LowerThreshold = 0.49f;
	RaiseThreshold = 0.67f;
}

DifficultyLevelConfig& DifficultyLevelConfig::GetInstance()
{
	static DifficultyLevelConfig instance;
	return instance;
}
