//
//  IHttpDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IHttpDriver.h"
#include "SexyAppFramework/drivers/http/android/AndroidHttpDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IHttpDriver* IHttpDriver::CreateHttpDriver(SexyAppBase* app)
{
    return new AndroidHttpDriver();
}
