//
//  IteratorStorage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtDb.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

RtDbTable::IteratorStorage::IteratorStorage()
{
}

RtDbTable::IteratorStorage::~IteratorStorage()
{
}

/////////////// Iteration ///////////////

uint32 RtDbTable::IteratorStorage::PushIterator(uint32 inCount, RtDbTable* inTable)
{
	uint32 startIndex = mData.size();
	mData.resize(startIndex + inCount);
	mDataFloorStack.push_back(startIndex);

	uint32 offset = 0;
	Slot* slot = inTable->mUsedListHead.RingGetNext();
	while (slot != &inTable->mUsedListHead)
	{
		mData[startIndex + offset] = inTable->GetIdForSlot(slot);
		offset++;
		slot = slot->RingGetNext();
	}
	return startIndex;
}

void RtDbTable::IteratorStorage::PopIterator(uint32 inCount)
{
	mData.resize(mDataFloorStack.back());
	mDataFloorStack.pop_back();
}
