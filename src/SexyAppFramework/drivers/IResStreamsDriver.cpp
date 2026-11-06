//
//  IResStreamsDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IResStreamsDriver.h"
#include "SexyAppFramework/drivers/resstreams/android/AndroidResStreamsDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IResStreamsDriver* IResStreamsDriver::CreateResStreamsDriver()
{
    return new AndroidResStreamsDriver();
}
