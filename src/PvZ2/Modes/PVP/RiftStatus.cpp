//
//  RiftStatus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "RiftStatus.h"

/////////////// RiftStatus ///////////////

RiftStatus::RiftStatus()
{
	DifficultyForNextLevel = 0;
	ZombossPointOfLossExtensions = 0;
	LevelOverride = "";
}

void RiftStatus::SetLevelOverride(const std::string& i_level)
{
	LevelOverride = i_level;
}

const std::string& RiftStatus::GetLevelOverride()
{
	return LevelOverride;
}
