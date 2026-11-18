//
//  ISaveGameDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ISaveGameDriver.h"
#include "SexyAppFramework/drivers/savegame/filesystem/FilesystemSaveGameDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

ISaveGameDriver* ISaveGameDriver::CreateSaveGameDriver()
{
    return new FilesystemSaveGameDriver();
}
