//
//  ProfileUtils.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "PlayerInfo.h"
#include "ProfileUtils.h"

/////////////// Progress ///////////////

bool ProfileUtils::HasCompletedLevel(const std::string& i_levelName, bool i_hard, PlayerInfo* i_info)
{
	return i_hard ? i_info->GetHardLevelCompleted(i_levelName) : i_info->GetLevelCompleted(i_levelName);
}
