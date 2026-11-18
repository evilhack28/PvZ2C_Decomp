//
//  IAppDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IAppDriver.h"
#include "SexyAppFramework/drivers/app/android/AndroidAppDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IAppDriver* IAppDriver::CreateAppDriver(SexyAppBase* i_app)
{
    return new AndroidAppDriver(i_app);
}
