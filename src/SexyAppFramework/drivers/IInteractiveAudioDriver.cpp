//
//  IInteractiveAudioDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IInteractiveAudioDriver.h"
#include "SexyAppFramework/drivers/audio/wwise/WwiseInteractiveAudioDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IInteractiveAudioDriver* IInteractiveAudioDriver::CreateInteractiveAudioDriver(SexyAppBase*)
{
    return new WwiseInteractiveAudioDriver();
}
