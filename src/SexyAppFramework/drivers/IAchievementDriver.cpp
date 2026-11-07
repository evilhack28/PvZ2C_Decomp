//
//  IAchievementDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IAchievementDriver.h"
#include "SexyAppFramework/drivers/achievement/NullAchievementDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IAchievementDriver* IAchievementDriver::CreateAchievementDriver()
{
	return new NullAchievementDriver();
}
