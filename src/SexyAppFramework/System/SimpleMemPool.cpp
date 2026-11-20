//
//  SimpleMemPool.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/MemPools.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

SimpleMemPool::~SimpleMemPool()
{
	delete[] mItemBuffer;
}

/////////////// Pool ///////////////

uint8* SimpleMemPool::GetMemory(uint32 theSize)
{
	if (mItemBuffer == nullptr)
	{
		mItemBuffer = new uint8[mItemSize * mMaxItems + mMaxItems];
		mOccupied = mItemBuffer + mItemSize * mMaxItems;
		for (uint32 i = 0; i < mMaxItems; i++)
			mOccupied[i] = 0;
	}

	for (uint32 i = 0; i < mMaxItems; i++)
	{
		if (!mOccupied[i])
		{
			mOccupied[i] = 1;
			mNumItems++;
			return mItemBuffer + i * mItemSize;
		}
	}

	return nullptr;
}

void SimpleMemPool::ReturnMemory(uint8* thePtr)
{
	uint32 anIndex = (uint32)(thePtr - mItemBuffer) / mItemSize;
	mOccupied[anIndex] = 0;
	mNumItems--;
}
