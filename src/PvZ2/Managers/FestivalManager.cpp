//
//  FestivalManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FestivalManager.h"

FestivalManager::~FestivalManager()
{
}

bool FestivalManager::IsSummerVacationLevel(const std::string& i_level)
{
	return i_level.find("vacation_boss_") != std::string::npos;
}
