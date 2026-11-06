//
//  ResStreamsUnpacker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/IFileDriver.h"
#include "SexyAppFramework/Endian.h"

using namespace Sexy;

uint8* AllocRSBCommonBuffer(IFile* theFile, uint32& outSize, bool& outIsHostEndian, bool theArg);


/////////////// Lifecycle ///////////////

ResStreamsUnpacker::ResStreamsUnpacker(SexyAppBase* inApp)
{
    mApp = inApp;
}

ResStreamsUnpacker::~ResStreamsUnpacker()
{
    Close();
}

bool ResStreamsUnpacker::Init(const std::string& inRsbFilePath)
{
    mFile = mApp->mFileDriver->CreateFileDirect(inRsbFilePath);
    if (mFile == NULL)
        return false;

    bool aIsHostEndian = true;
    mHeader = (ResStreamHeader*)AllocRSBCommonBuffer(mFile, mCommonBufferSize, aIsHostEndian, true);
    mCommonBuffer = (uint8*)mHeader;
    mRsbRequiresByteSwapping = !aIsHostEndian;
    if (mHeader == NULL)
        return false;

    uint32 aGroupCount = ByteSwapUINT32(mHeader->v1.groups_count, mRsbRequiresByteSwapping);
    uint32 aGroupHeaderSize = ByteSwapUINT32(mHeader->v1.group_header_size, mRsbRequiresByteSwapping);
    uint32 aGroupsLocation = ByteSwapUINT32(mHeader->v1.groups_location, mRsbRequiresByteSwapping);
    uint32 i = 0;
    uint32 anOffset = 0;
    for (; i < aGroupCount; i++)
    {
        ResStreamGroupDescriptor* aGroup = (ResStreamGroupDescriptor*)(mCommonBuffer + aGroupsLocation + anOffset);
        anOffset += aGroupHeaderSize;
        uint32 aFileLocation = ByteSwapUINT32(aGroup->file_location, mRsbRequiresByteSwapping);
        uint32 aDataSize = ByteSwapUINT32(aGroup->file_size, mRsbRequiresByteSwapping);
        GroupInfo aGroupInfo((const char*)aGroup, aFileLocation, aDataSize);
        mGroupInfos.push_back(aGroupInfo);
    }
    return true;
}

void ResStreamsUnpacker::Close()
{
    delete[] mCommonBuffer;
    mCommonBuffer = NULL;
    mCommonBufferSize = 0;
    mHeader = NULL;
    if (mFile != NULL)
    {
        mFile->Close();
        delete mFile;
        mFile = NULL;
    }
}


/////////////// Accessors ///////////////

uint8* ResStreamsUnpacker::GetCommonData(uint32& outCommonDataByteCount)
{
    outCommonDataByteCount = mCommonBufferSize;
    return mCommonBuffer;
}

bool ResStreamsUnpacker::RsbHasSwappedBytes()
{
    return mRsbRequiresByteSwapping;
}

std::vector<std::string> ResStreamsUnpacker::GetResourceGroupNameOrder()
{
    std::vector<std::string> aNames;
    for (std::vector<GroupInfo>::iterator anItr = mGroupInfos.begin(); anItr != mGroupInfos.end(); ++anItr)
        aNames.push_back(anItr->name);
    return aNames;
}


/////////////// Group data ///////////////

uint8* ResStreamsUnpacker::AllocResGroupData(const std::string& inGroupName, uint32& outResGroupDataByteCount)
{
    outResGroupDataByteCount = 0;
    for (std::vector<GroupInfo>::iterator anItr = mGroupInfos.begin(); anItr != mGroupInfos.end(); ++anItr)
    {
        if (inGroupName == anItr->name)
        {
            mFile->DirectSeek(anItr->file_location);
            uint8* aBuffer = new uint8[anItr->data_size];
            if (!mFile->DirectRead(aBuffer, anItr->data_size))
            {
                delete[] aBuffer;
                return NULL;
            }
            while (mFile->DirectReadStatus() == IFile::READ_PENDING)
                ;
            if (mFile->DirectReadStatus() == IFile::READ_ERROR)
            {
                delete[] aBuffer;
                return NULL;
            }
            outResGroupDataByteCount = anItr->data_size;
            return aBuffer;
        }
    }
    return NULL;
}
