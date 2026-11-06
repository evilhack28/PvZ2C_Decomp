//
//  ResStreamsGroup.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResStreamsManager.h"

using namespace Sexy;


/////////////// Lifecycle ///////////////

ResStreamsGroup::ResStreamsGroup()
{
    mPool = NULL;
    mLoadedHeader = NULL;
    mLoadedAtInstance = (uint32)-1;
    mTextures_Main = NULL;
    mTextures_Multi = NULL;
    mTextureDatas = NULL;
    mFileIndexPtr = NULL;
    mFileIndexSize = 0;
    Reset();
}

ResStreamsGroup::~ResStreamsGroup()
{
    Reset();
}

void ResStreamsGroup::Reset()
{
    mStatus = ResStreamsManager::NOT_RESIDENT;
    mTotalLoadTime = 0;
    mDecodeTime = 0;
    mDiskIOTime = 0;
    mLoadStartTime = 0;
    mDecodeStartTime = 0;
    if (mFileIndexPtr)
    {
        delete[] mFileIndexPtr;
        mFileIndexPtr = NULL;
    }
    mFileIndexSize = 0;
}

void ResStreamsGroup::InitDescriptor(ResStreamGroupDescriptor* theDesc, uint8* theTexDescsPtr, uint32 theTexDescSize)
{
    mName = (const char*)theDesc->name;
    mFileLocation = theDesc->file_location;
    mFileSize = theDesc->file_size;
    mPoolIndex = theDesc->pool;
    mNumTexDescs = theDesc->texture_count;
    mDesc = theDesc;
    mTexDescSize = theTexDescSize;
    mTexDescsPtr = theTexDescsPtr + theDesc->texture_offset * theTexDescSize;
}

void ResStreamsGroup::InitGroupStream(ResStreamGroupHeader* theHeader, uint32 theInstanceId)
{
    mLoadedHeader = theHeader;
    mFileIndex.Init((uint8*)theHeader + theHeader->file_index_location, theHeader->file_index_size);
    mLoadedAtInstance = theInstanceId;
}

/////////////// File index ///////////////

bool ResStreamsGroup::LoadGroupFileIndex(IFile* aFile)
{
    uint8 aBuffer[2048];
    aFile->DirectSeek(mFileLocation);
    uint8 aResult = aFile->DirectRead(aBuffer, 2048);
    if (aResult)
    {
        while (aFile->DirectReadStatus() == IFile::READ_PENDING)
            ;
        if (aFile->DirectReadStatus() != IFile::READ_ERROR)
        {
            ResStreamGroupHeader* aHeader = (ResStreamGroupHeader*)aBuffer;
            uint32 aSize;
            if (aHeader->file_index_location > sizeof(ResStreamGroupHeader))
                aSize = aHeader->file_index_location + aHeader->file_index_size;
            else
                aSize = sizeof(ResStreamGroupHeader) + aHeader->file_index_size;
            uint32 aAllocSize = aSize;
            if (aSize > 2048)
            {
                aSize &= ~2047;
                aAllocSize = aSize + 2048;
            }
            mFileIndexPtr = new uint8[aAllocSize];
            mFileIndexSize = aAllocSize;
            if (aAllocSize > 2048)
            {
                memcpy(mFileIndexPtr, aBuffer, 2048);
                if (!aFile->DirectRead(mFileIndexPtr + 2048, aSize))
                    goto fail;
                while (aFile->DirectReadStatus() == IFile::READ_PENDING)
                    ;
                if (aFile->DirectReadStatus() == IFile::READ_ERROR)
                    goto fail;
            }
            else
            {
                memcpy(mFileIndexPtr, aBuffer, aAllocSize);
            }
            mLoadedHeader = (ResStreamGroupHeader*)mFileIndexPtr;
            mFileIndex.Init(mFileIndexPtr + mLoadedHeader->file_index_location, mLoadedHeader->file_index_size);
            goto done;
        fail:
            if (mFileIndexPtr)
                delete[] mFileIndexPtr;
            mFileIndexPtr = NULL;
        }
    }
    aResult = false;
done:
    return aResult;
}

/////////////// Loading ///////////////

void ResStreamsGroup::StartLoad()
{
    mTotalLoadTime = 0;
    mDecodeTime = 0;
    mDiskIOTime = 0;
    mLoadStartTime = 0;
    mDecodeStartTime = 0;
}

bool ResStreamsGroup::CanLoad()
{
    if (mStatus == ResStreamsManager::DELETING)
        return false;
    if (mStatus == ResStreamsManager::PREPARING || mStatus == ResStreamsManager::RESIDENT)
        return true;
    return mPool->IsInstanceAvailable();
}

/////////////// Accessors ///////////////

uint8* ResStreamsGroup::GetResidentDataBaseAddress()
{
    return (uint8*)mPool->GetResidentDataMemory(mLoadedAtInstance) + mDesc->data_resident_location;
}

uint8* ResStreamsGroup::GetGPUDataBaseAddress()
{
    return (uint8*)mPool->GetGPUDataMemory(mLoadedAtInstance);
}

ResStreamTextureDescriptor* ResStreamsGroup::GetTextureDescriptor(uint32 theTextureId)
{
    return (ResStreamTextureDescriptor*)(mTexDescsPtr + theTextureId * mTexDescSize);
}

GLuint ResStreamsGroup::GetTextureReference(GLuint theTextureId)
{
    return mTextures_Main[theTextureId];
}

GLuint ResStreamsGroup::GetTextureMultiReference(GLuint theTextureId)
{
    if (mTextures_Multi)
        return mTextures_Multi[theTextureId];
    return 0;
}

void* ResStreamsGroup::GetRenderData(uint32 theTextureId)
{
    return mTextureDatas[theTextureId];
}

/////////////// Assignment ///////////////

void ResStreamsGroup::operator=(ResStreamsGroup& right)
{
    mName = right.mName;
    mStatus = right.mStatus;
    mPoolIndex = right.mPoolIndex;
    mPool = right.mPool;
    mFileLocation = right.mFileLocation;
    mFileSize = right.mFileSize;
    mDesc = right.mDesc;
    mTotalLoadTime = right.mTotalLoadTime;
    mDecodeTime = right.mDecodeTime;
    mDiskIOTime = right.mDiskIOTime;
    mLoadStartTime = right.mLoadStartTime;
    mDecodeStartTime = right.mDecodeStartTime;
    mDiskIOStartTime = right.mDiskIOStartTime;
    mLoadedAtInstance = right.mLoadedAtInstance;
    mLoadedHeader = right.mLoadedHeader;
    mNumTexDescs = right.mNumTexDescs;
    mTexDescsPtr = right.mTexDescsPtr;
    mTexDescSize = right.mTexDescSize;
    mTextures_Main = right.mTextures_Main;
    mTextures_Multi = right.mTextures_Multi;
    mTextureDatas = right.mTextureDatas;
    if (right.mFileIndexPtr)
    {
        mFileIndexPtr = new uint8[right.mFileIndexSize];
        mFileIndexSize = right.mFileIndexSize;
        memcpy(mFileIndexPtr, right.mFileIndexPtr, right.mFileIndexSize);
        if (mFileIndexPtr)
        {
            mFileIndex.Init(mFileIndexPtr + mLoadedHeader->file_index_location, mLoadedHeader->file_index_size);
            return;
        }
    }
    else
    {
        mFileIndexPtr = NULL;
    }
    mFileIndex = right.mFileIndex;
}
