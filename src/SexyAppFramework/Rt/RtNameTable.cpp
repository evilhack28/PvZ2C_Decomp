//
//  RtNameTable.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtId.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

RtNameTable::RtNameTable()
{
}

RtNameTable::~RtNameTable()
{
	uint32 count = mEntries.size();
	for (uint32 i = 0; i < count; i++)
	{
		Entry* entry = mEntries[i];
		if (entry)
			delete entry;
	}
}

RtNameTable* RtNameTable::GetNameTable()
{
	static RtNameTable* nameTable = NULL;
	if (!nameTable)
	{
		nameTable = new RtNameTable;
		sRtNameTable = nameTable;
	}
	return nameTable;
}

/////////////// Entries ///////////////

RtNameTable::Entry* RtNameTable::FindEntry(const wchar_t* inStr)
{
	StringMap::iterator it = mStringMap.find(inStr);
	if (it != mStringMap.end())
		return mEntries[it->second];
	return NULL;
}

RtNameTable::Entry* RtNameTable::AddEntry(const wchar_t* inStr)
{
	Entry* entry = FindEntry(inStr);
	if (!entry)
	{
		entry = mEntryFreeListHead.RingGetNext();
		if (entry == &mEntryFreeListHead)
		{
			entry = new Entry;
			entry->mIndex = mEntries.size();
			mEntries.push_back(entry);
		}
		entry->mString = inStr;
		entry->mRefCount = 0;
		entry->RingLinkAfter(&mEntryUsedListHead);
		mStringMap[entry->mString.c_str()] = entry->mIndex;
	}
	return entry;
}

void RtNameTable::RemoveEntry(Entry* inEntry)
{
	mStringMap.erase(inEntry->mString.c_str());
	inEntry->mString = L"";
	inEntry->RingLinkAfter(&mEntryFreeListHead);
}

/////////////// Table ///////////////

uint32 RtNameTable::TableGetCount()
{
	return mEntries.size() + 1;
}

uint32 RtNameTable::TableIndexForString(const wchar_t* inStr)
{
	if (inStr && *inStr)
		return AddEntry(inStr)->mIndex + 1;
	return 0;
}

const wchar_t* RtNameTable::TableStringForIndex(uint32 inIndex)
{
	if (inIndex)
		return mEntries[inIndex - 1]->mString.c_str();
	return L"";
}

uint32 RtNameTable::TableGetRefCountForString(uint32 inIndex)
{
	if (inIndex)
		return mEntries[inIndex - 1]->mRefCount;
	return 0;
}

uint32 RtNameTable::TableRetainString(uint32 inIndex)
{
	if (inIndex)
		return ++mEntries[inIndex - 1]->mRefCount;
	return 0;
}

uint32 RtNameTable::TableReleaseString(uint32 inIndex)
{
	uint32 refCount = 0;
	if (inIndex)
	{
		Entry* entry = mEntries[inIndex - 1];
		refCount = --entry->mRefCount;
		if (!refCount)
			RemoveEntry(entry);
	}
	return refCount;
}
