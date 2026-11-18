//
//  IAntiHackDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IAntiHackDriver.h"
#include "SexyAppFramework/drivers/antihack/android/AndroidAntiHackDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IAntiHackDriver* IAntiHackDriver::CreateAntiHackDriver()
{
    return new AndroidAntiHackDriver();
}
