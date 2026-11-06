//
//  ResStreamsPool.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/IResStreamsDriver.h"

using namespace Sexy;


/////////////// Lifecycle ///////////////

ResStreamsPool::ResStreamsPool()
{
    mOccupant = NULL;
    mPrevOccupant = NULL;
    mOccupantIndex = NULL;
    mPrevOccupantIndex = NULL;
    mAllocated = false;
    mResidentBuffer = NULL;
}

ResStreamsPool::~ResStreamsPool()
{
    delete[] mOccupantIndex;
    delete[] mPrevOccupantIndex;
    delete[] mOccupant;
    delete[] mPrevOccupant;
    delete[] mInstances;
}

void ResStreamsPool::operator=(ResStreamsPool& right)
{
    mName = right.mName;
    mAllocated = right.mAllocated;
    mNumInstances = right.mNumInstances;
    mResidentDataSize = right.mResidentDataSize;
    mGPUDataSize = right.mGPUDataSize;
    mFlags = right.mFlags;
    mResidentBuffer = right.mResidentBuffer;
    mGPUBuffer = right.mGPUBuffer;
    mOccupant = NULL;
    mPrevOccupant = NULL;
    mInstances = NULL;
    mOccupantIndex = NULL;
    mPrevOccupantIndex = NULL;
    if (right.mOccupant != NULL)
    {
        mOccupant = new ResStreamsGroup*[right.mNumInstances];
        memcpy(mOccupant, right.mOccupant, right.mNumInstances * sizeof(ResStreamsGroup*));
    }
    if (right.mPrevOccupant != NULL)
    {
        mPrevOccupant = new ResStreamsGroup*[right.mNumInstances];
        memcpy(mPrevOccupant, right.mPrevOccupant, right.mNumInstances * sizeof(ResStreamsGroup*));
    }
    if (right.mOccupantIndex != NULL)
    {
        mOccupantIndex = new int[right.mNumInstances];
        memcpy(mOccupantIndex, right.mOccupantIndex, right.mNumInstances * sizeof(int));
    }
    if (right.mPrevOccupantIndex != NULL)
    {
        mPrevOccupantIndex = new int[right.mNumInstances];
        memcpy(mPrevOccupantIndex, right.mPrevOccupantIndex, right.mNumInstances * sizeof(int));
    }
    if (right.mInstances != NULL)
    {
        mInstances = new PoolInstance[right.mNumInstances];
        memcpy(mInstances, right.mInstances, right.mNumInstances * sizeof(PoolInstance));
    }
}

void ResStreamsPool::InitDescriptor(ResStreamPoolDescriptor* theDesc)
{
    mName = (const char*)theDesc->name;
    mResidentDataSize = theDesc->resident_data_size;
    mGPUDataSize = theDesc->gpu_data_size;
    mNumInstances = theDesc->instance_count;
    mFlags = theDesc->flags;
    mAllocated = false;
    mOccupant = new ResStreamsGroup*[mNumInstances];
    mPrevOccupant = new ResStreamsGroup*[mNumInstances];
    mOccupantIndex = new int[mNumInstances];
    mPrevOccupantIndex = new int[mNumInstances];
    mInstances = new PoolInstance[mNumInstances];
    for (uint32 i = 0; i < mNumInstances; i++)
    {
        mOccupant[i] = NULL;
        mPrevOccupant[i] = NULL;
        mOccupantIndex[i] = -1;
        mPrevOccupantIndex[i] = -1;
        mInstances[i].mResidentData = NULL;
        mInstances[i].mGPUData = NULL;
    }
}

void ResStreamsPool::Allocate()
{
    if (!mAllocated)
    {
        if (gSexyAppBase->mResStreamsDriver->AllocatePool(this))
            mAllocated = true;
    }
}

void ResStreamsPool::Destroy()
{
    if (mAllocated)
    {
        for (uint32 i = 0; i < mNumInstances; i++)
        {
            if (mPrevOccupant[i] != NULL)
                gSexyAppBase->mResStreamsDriver->AttachGroupToPool(this, i, mPrevOccupant[i], NULL);
        }
        if (gSexyAppBase->mResStreamsDriver->DestroyPool(this))
        {
            for (uint32 i = 0; i < mNumInstances; i++)
            {
                mOccupant[i] = NULL;
                mPrevOccupant[i] = NULL;
                mOccupantIndex[i] = -1;
                mPrevOccupantIndex[i] = -1;
            }
            mAllocated = false;
        }
    }
}


/////////////// Accessors ///////////////

const std::string& ResStreamsPool::GetName()
{
    return mName;
}

bool ResStreamsPool::IsInstanceAvailable()
{
    for (uint32 i = 0; i < mNumInstances; i++)
    {
        if (mOccupant[i] == NULL)
            return true;
    }
    return false;
}

int ResStreamsPool::GetOccupantCount()
{
    int aCount = 0;
    for (uint32 i = 0; i < mNumInstances; i++)
    {
        if (mOccupant[i] != NULL)
            aCount++;
    }
    return aCount;
}

void* ResStreamsPool::GetResidentDataMemory(uint32 theInstanceId)
{
    return mInstances[theInstanceId].mResidentData;
}

void* ResStreamsPool::GetGPUDataMemory(uint32 theInstanceId)
{
    return mInstances[theInstanceId].mGPUData;
}


/////////////// Instances ///////////////

uint32 ResStreamsPool::LockInstanceForGroup(ResStreamsGroup* theGroup, int theGroupIndex)
{
    for (uint32 i = 0; i < mNumInstances; i++)
    {
        if (mOccupant[i] == NULL)
        {
            mOccupant[i] = theGroup;
            mOccupantIndex[i] = theGroupIndex;
            return i;
        }
    }
    return (uint32)-1;
}

void ResStreamsPool::UnlockInstanceForGroup(ResStreamsGroup* theGroup)
{
    for (uint32 i = 0; i < mNumInstances; i++)
    {
        if (mOccupant[i] == theGroup)
        {
            mOccupant[i] = NULL;
            return;
        }
    }
}
