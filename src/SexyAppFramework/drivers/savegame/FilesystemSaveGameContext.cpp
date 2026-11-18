//
//  FilesystemSaveGameContext.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/savegame/filesystem/FilesystemSaveGameDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

FilesystemSaveGameContext::FilesystemSaveGameContext(UserProfile* i_player, const std::string& i_filename)
{
    mPlayer = i_player;
    mSaveName = i_filename;
    mDone = false;
    mError = false;
}

void FilesystemSaveGameContext::Destroy()
{
    delete this;
}
