//
//  PVZVersion.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "PVZVersion.h"

TotalRewardData& PVZVersion::GetUpdateReward(bool i_firstReward)
{
	return i_firstReward ? first_reward : second_reward;
}
