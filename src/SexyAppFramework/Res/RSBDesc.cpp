//
//  RSBDesc.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResStreamsManager.h"

using namespace Sexy;


/////////////// Lifecycle ///////////////

ResStreamsManager::RSBDesc::RSBDesc()
{
    mFile = NULL;
    mCommonBuffer = NULL;
    mCommonSize = 0;
    mBaseIndex = (uint32)-1;
    mNumGroups = 0;
    mGroups = NULL;
    mNumPools = 0;
    mPools = NULL;
}

ResStreamsManager::RSBDesc::~RSBDesc()
{
    delete[] mCommonBuffer;
    delete[] mGroups;
    delete[] mPools;
}
