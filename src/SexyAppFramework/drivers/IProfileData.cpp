//
//  IProfileData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IProfileDriver.h"
#include "SexyAppFramework/drivers/profile/NullProfileDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IProfileData* IProfileData::CreateProfileData(UserProfile* player)
{
    return new NullProfileData();
}
