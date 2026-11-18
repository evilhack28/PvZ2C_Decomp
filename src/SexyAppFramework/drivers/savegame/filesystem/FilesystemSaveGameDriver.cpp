//
//  FilesystemSaveGameDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/savegame/filesystem/FilesystemSaveGameDriver.h"
#include "SexyAppFramework/UserProfile.h"
#include "SexyAppFramework/SexyAppBase.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

FilesystemSaveGameDriver::FilesystemSaveGameDriver()
{
}

bool FilesystemSaveGameDriver::Init()
{
    return true;
}

void FilesystemSaveGameDriver::Update()
{
}

ISaveGameContext* FilesystemSaveGameDriver::CreateSaveGameContext(UserProfile* i_player, const std::string& i_filename, uint64 i_requiredBytes)
{
    return new FilesystemSaveGameContext(i_player, i_filename);
}

/////////////// Operations ///////////////

bool FilesystemSaveGameDriver::BeginLoad(ISaveGameContext* i_context, const std::string& i_segment, bool i_checkOnly)
{
    FilesystemSaveGameContext* context = static_cast<FilesystemSaveGameContext*>(i_context);
    context->mSegmentName = i_segment;
    std::string path = GetAppDataFolder() + "userdata/user%d/" + context->GetSaveName();
    path = StrFormat(path.c_str(), context->GetPlayer()->GetId());
    std::string file = path + "/" + context->mSegmentName;
    bool ok = gSexyAppBase->ReadBufferFromFile(file, &context->mBuffer);
    if (!ok)
    {
        context->mError = true;
        return ok;
    }
    context->mDone = true;
    return true;
}

bool FilesystemSaveGameDriver::BeginSave(ISaveGameContext* i_context, const std::string& i_segment, const Buffer& i_buffer)
{
    FilesystemSaveGameContext* context = static_cast<FilesystemSaveGameContext*>(i_context);
    context->mSegmentName = i_segment;
    std::string path = GetAppDataFolder() + "userdata/user%d/" + context->GetSaveName();
    path = StrFormat(path.c_str(), context->GetPlayer()->GetId());
    std::string file = path + "/" + context->mSegmentName;
    MkDir(path);
    bool ok = gSexyAppBase->WriteBytesToFile(file, i_buffer.GetDataPtr(), i_buffer.GetDataLen());
    if (!ok)
    {
        context->mError = true;
        return ok;
    }
    context->mDone = true;
    return true;
}

bool FilesystemSaveGameDriver::BeginDelete(ISaveGameContext* i_context, const std::string& i_segment)
{
    FilesystemSaveGameContext* context = static_cast<FilesystemSaveGameContext*>(i_context);
    std::string path = GetAppDataFolder() + "userdata/user%d/" + context->GetSaveName();
    path = StrFormat(path.c_str(), context->GetPlayer()->GetId());
    std::string file = path + "/" + i_segment;
    return gSexyAppBase->EraseFile(file);
}

bool FilesystemSaveGameDriver::BeginSaveGameDelete(ISaveGameContext* i_context)
{
    FilesystemSaveGameContext* context = static_cast<FilesystemSaveGameContext*>(i_context);
    std::string path = GetAppDataFolder() + "userdata/user%d/" + context->GetSaveName();
    path = StrFormat(path.c_str(), context->GetPlayer()->GetId());
    return Deltree(path);
}
