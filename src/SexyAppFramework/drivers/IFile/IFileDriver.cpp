//
//  IFileDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IFileDriver.h"
#include "SexyAppFramework/drivers/file/android/AndroidAsyncIOFileDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IFileDriver* IFileDriver::CreateFileDriver()
{
    return new AndroidAsyncIOFileDriver();
}
