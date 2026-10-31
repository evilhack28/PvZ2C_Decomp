//
//  RtDbTable.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtDb.h"
#include "SexyAppFramework/RtSerial.h"
#include "SexyAppFramework/Buffer.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/Reflection.h"
#include "SexyAppFramework/IAntiHackDriver.h"
#include <algorithm>

using namespace Sexy;

static int sPackagesPrefixLength = StringLength("packages/");

/////////////// Lifecycle ///////////////

RtDbTable::RtDbTable(uint32 inTableIndex, const TableOptions* inOptions)
: mTableIndex(inTableIndex)
, mSlots(NULL)
, mFromLocalFile(false)
{
	TableOptions defaultOptions;
	if (!inOptions)
		inOptions = &defaultOptions;
	mTableOptions = *inOptions;

	if (!mTableOptions.mTableName)
	{
		char buffer[64];
		sprintf(buffer, "%d", mTableIndex);
		mTableOptions.mTableName = RtName(StringToWString(buffer));
	}

	std::wstring tableName(L"$");
	tableName += mTableOptions.mTableName.GetString();
	mTableOptions.mTableName = RtName(tableName.c_str());

	RtDb::GetDb()->mNameToTableIndexMap[mTableOptions.mTableName.GetIndex()] = mTableIndex;
	Reset(true);
}

RtDbTable::~RtDbTable()
{
	mTableOptions.mInitialSlotCount = 0;
	Reset(true);

	if (mTableOptions.mTableName)
	{
		RtDb::NameToTableIndexMap::iterator it = RtDb::GetDb()->mNameToTableIndexMap.find(mTableOptions.mTableName.GetIndex());
		if (it != RtDb::GetDb()->mNameToTableIndexMap.end())
			RtDb::GetDb()->mNameToTableIndexMap.erase(it);
	}

	SetCurrentPackageName(RtName());
	RtDb::GetDb()->InternalRemoveTable(mTableIndex);
}

void RtDbTable::Reset(bool inHardReset)
{
	OnTableUnloadingEvent(*this);

	if (!inHardReset)
	{
		Slot* usedListHead = &mUsedListHead;
		Slot* slot = mUsedListHead.RingGetNext();
		while (slot != usedListHead)
		{
			{
				RtId id = GetIdForSlot(slot);
				while (GetRefCountForId(id))
					ReleaseId(id);
			}
			slot = mUsedListHead.RingGetNext();
		}
		mAliasNameToUidMap.clear();
	}
	else
	{
		if (mSlots)
		{
			RunDeferredDeletions();

			for (Slot* slot = mUsedListHead.RingGetNext(); slot != &mUsedListHead; slot = slot->RingGetNext())
			{
				if (slot->mObject)
				{
					if (!(slot->mRefCountAndFlags & Slot::SLOTF_NeverDelete))
						slot->mObject->Delete();
					slot->mObject = NULL;
					slot->mUid = RtId::Uid();
				}
			}

			mFreeListHead.RingUnlink();
			mUsedListHead.RingUnlink();
			mCondemnedListHead.RingUnlink();
			mRetiredListHead.RingUnlink();

			free(mSlots);
			mSlots = NULL;
		}

		mSlotCount = 0;
		mFreeSlotCount = 0;
		mUsedSlotCount = 0;
		mCondemnedSlotCount = 0;
		mRetiredSlotCount = 0;

		mUidToIdMap.clear();
		mAliasNameToUidMap.clear();

		uint32 slotCount = mTableOptions.mInitialSlotCount;
		if (slotCount)
			GrowSlotVector(slotCount, "Reset()");
	}

	OnTableUnloadedEvent(*this);
}

/////////////// Accessors ///////////////

void RtDbTable::SetFromLocalFile(bool bFromLocal)
{
	mFromLocalFile = bFromLocal;
}

void RtDbTable::SetCurrentPackageName(const RtName& inName)
{
	RtName name(inName);
	if (name)
		name = RtName(StringToWString(MakePackageNameFromPackageNameOrFileName(WStringToString(name.GetString()))));

	if (mCurrentPackage == name)
		return;

	if (mCurrentPackage)
	{
		RtDb::NameToTableIndexMap::iterator it = RtDb::GetDb()->mNameToTableIndexMap.find(mCurrentPackage.GetIndex());
		if (it != RtDb::GetDb()->mNameToTableIndexMap.end())
			RtDb::GetDb()->mNameToTableIndexMap.erase(it);
	}

	mCurrentPackage = name;
	mCurrentPackageFileName = StringToWString(MakeFileNameFromPackageNameOrFileName(WStringToString(inName.GetString())));

	if (mCurrentPackage)
		RtDb::GetDb()->mNameToTableIndexMap[mCurrentPackage.GetIndex()] = mTableIndex;
}

bool RtDbTable::HasCurrentPackage() const
{
	return mCurrentPackage;
}

const RtName& RtDbTable::GetCurrentPackageName() const
{
	if (!mCurrentPackage)
		return mTableOptions.mTableName;
	return mCurrentPackage;
}

/////////////// Slots ///////////////

void RtDbTable::IntegrityCheck()
{
	for (Slot* slot = mFreeListHead.RingGetNext(); slot != &mFreeListHead; slot = slot->RingGetNext())
	{
	}
	for (Slot* slot = mUsedListHead.RingGetNext(); slot != &mUsedListHead; slot = slot->RingGetNext())
	{
	}
	for (Slot* slot = mCondemnedListHead.RingGetNext(); slot != &mCondemnedListHead; slot = slot->RingGetNext())
	{
	}
	for (Slot* slot = mRetiredListHead.RingGetNext(); slot != &mRetiredListHead; slot = slot->RingGetNext())
	{
	}
}

void RtDbTable::GrowSlotVector(uint32 inSlotCount, const std::string& theFilename)
{
	if (gSexyAppBase && gSexyAppBase->mResourceManager && gSexyAppBase->mResourceManager->GetDelayLoadedRSBSlotCount())
	{
		if (theFilename == gSexyAppBase->mResourceManager->GetLastNonDelayLoadRSBManifestName())
			inSlotCount += gSexyAppBase->mResourceManager->GetDelayLoadedRSBSlotCount();
	}

	uint32 oldSlotCount = mSlotCount;
	Slot* oldSlots = mSlots;
	Slot* slot = (Slot*)malloc(inSlotCount * sizeof(Slot));
	mSlotCount = inSlotCount;
	mSlots = slot;

	if (oldSlotCount == 0)
	{
		memset(slot, 0, inSlotCount * sizeof(Slot));
	}
	else
	{
		intptr_t delta = (char*)slot - (char*)oldSlots;
		size_t oldSize = oldSlotCount * sizeof(Slot);
		Slot* oldSlotsEnd = (Slot*)((char*)oldSlots + oldSize);
		memcpy(slot, oldSlots, oldSize);
		memset((char*)slot + oldSize, 0, (inSlotCount - oldSlotCount) * sizeof(Slot));

		for (uint32 i = 0; i < oldSlotCount; i++, slot++)
		{
			Slot* prev = slot->RingGetPrev();
			if (oldSlotsEnd > prev && oldSlots <= prev)
				slot->RingSetPrevDirect((Slot*)((char*)prev + delta));
			Slot* next = slot->RingGetNext();
			if (oldSlotsEnd > next && oldSlots <= next)
				slot->RingSetNextDirect((Slot*)((char*)next + delta));
		}

		for (Slot* head : { &mFreeListHead, &mUsedListHead, &mCondemnedListHead, &mRetiredListHead })
		{
			Slot* prev = head->RingGetPrev();
			if (oldSlotsEnd > prev && oldSlots <= prev)
				head->RingSetPrevDirect((Slot*)((char*)prev + delta));
			Slot* next = head->RingGetNext();
			if (oldSlotsEnd > next && oldSlots <= next)
				head->RingSetNextDirect((Slot*)((char*)next + delta));
		}

		slot = (Slot*)((char*)mSlots + oldSize);
	}

	for (uint32 i = oldSlotCount; i < mSlotCount; i++, slot++)
	{
		slot->RingSetPrevDirect(slot);
		slot->RingSetNextDirect(slot);
		slot->RingLinkBefore(&mFreeListHead);
		slot->mRevision = 1;
	}
	mFreeSlotCount += mSlotCount - oldSlotCount;

	if (oldSlotCount)
		free(oldSlots);
}

bool RtDbTable::ResizeTable(uint32 uIncreaseSlotCount, const std::string& theFilename)
{
	if (uIncreaseSlotCount)
	{
		GrowSlotVector(uIncreaseSlotCount + mTableOptions.mInitialSlotCount, theFilename);
		mTableOptions.mInitialSlotCount += uIncreaseSlotCount;
	}
	return true;
}

RtDbTable::Slot* RtDbTable::AllocSlot()
{
	Slot* slot = mFreeListHead.RingGetNext();
	if (slot == &mFreeListHead)
	{
		uint32 slotCount = mSlotCount;
		uint32 growCount = slotCount >> 1;
		uint32 addCount = growCount;
		if (!(growCount >= 256))
			addCount = 256;
		addCount += slotCount;
		GrowSlotVector(addCount, StrFormat("AllocSlot() count: %d", slotCount));
		slot = mFreeListHead.RingGetNext();
	}
	slot->RingLinkAfter(&mUsedListHead);
	mFreeSlotCount--;
	return slot;
}

void RtDbTable::FreeSlot(Slot* inSlot, bool inDeferDelete)
{
	if (inDeferDelete)
	{
		inSlot->RingLinkAfter(&mCondemnedListHead);
		mCondemnedSlotCount++;
		return;
	}
	if (inSlot - mSlots <= 0xffff)
	{
		if (inSlot->mRevision < 0xfffffffe)
		{
			inSlot->RingLinkAfter(&mFreeListHead);
		mFreeSlotCount++;
			return;
		}
	}
	else if (inSlot->mRevision < 0xffffff)
	{
		inSlot->RingLinkBefore(&mFreeListHead);
		mFreeSlotCount++;
		return;
	}
	inSlot->RingLinkAfter(&mRetiredListHead);
		mRetiredSlotCount++;
}

void RtDbTable::RunDeferredDeletions()
{
	Slot* slot;
	while ((slot = mCondemnedListHead.RingGetNext()) != &mCondemnedListHead)
	{
		if (slot->mObject)
		{
			slot->mObject->Delete();
			slot->mObject = NULL;
		}
		FreeSlot(slot, false);
	}
	mCondemnedSlotCount = 0;
}

RtDbTable::Slot* RtDbTable::GetSlotForId(const RtId& inId, bool inDoWarn) const
{
	if (inId.GetTableIndex() != mTableIndex)
		return NULL;
	uint32 slotIndex = inId.GetSlotIndex();
	if (slotIndex >= mSlotCount)
		return NULL;
	Slot* slot = &mSlots[slotIndex];
	if (slot)
		return inId.GetRevision() == slot->mRevision ? slot : NULL;
	return slot;
}

void RtDbTable::SetSlotObjectDeletionMode(Slot* inSlot, EObjectDeletionMode inMode) const
{
	uint32 flags = inSlot->mRefCountAndFlags & ~(Slot::SLOTF_DeferDelete | Slot::SLOTF_NeverDelete);
	if (inMode == ODM_Deferred)
		inSlot->mRefCountAndFlags = flags | Slot::SLOTF_DeferDelete;
	else if (inMode != ODM_Never)
		inSlot->mRefCountAndFlags = flags;
	else
		inSlot->mRefCountAndFlags = flags | Slot::SLOTF_NeverDelete;
}

/////////////// Ids ///////////////

RtId RtDbTable::AllocId(RtObject* inObject, EObjectDeletionMode inObjectDeletionMode, bool inIsStandalone, RtId::Uid* inOptExistingUid)
{
	Slot* slot = AllocSlot();
	uint32 refCount = slot->mRefCountAndFlags + 1;
	if (__builtin_expect(!inIsStandalone, 1))
		slot->mRefCountAndFlags = refCount | Slot::SLOTF_Used;
	else
		slot->mRefCountAndFlags = refCount | Slot::SLOTF_Used | Slot::SLOTF_Standalone;
	mUsedSlotCount++;
	slot->mObject = inObject;
	SetSlotObjectDeletionMode(slot, inObjectDeletionMode);

	RtId id = GetIdForSlot(slot);
	if (inOptExistingUid)
		slot->mUid = *inOptExistingUid;
	else
		slot->mUid = RtId::Uid(id);

	mUidToIdMap[slot->mUid] = id.GetValue();
	OnIdCreated(id);
	return id;
}

bool RtDbTable::RetainId(const RtId& inId)
{
	Slot* slot = GetSlotForId(inId, true);
	if (!slot)
		return false;
	slot->mRefCountAndFlags++;
	return true;
}

bool RtDbTable::ReleaseId(const RtId& inId)
{
	Slot* slot = GetSlotForId(inId, true);
	if (!slot)
		return false;

	slot->mRefCountAndFlags--;
	if ((slot->mRefCountAndFlags & Slot::SLOTF_REFCOUNTMASK) == 0)
	{
		OnIdDestroyed(inId);

		uint32 flags = slot->mRefCountAndFlags;
		mUsedSlotCount--;
		slot->mRefCountAndFlags = 0;
		bool deferDelete = (flags & Slot::SLOTF_DeferDelete) != 0;

		UidToIdMap::iterator it = mUidToIdMap.find(slot->mUid);
		if (it != mUidToIdMap.end())
			mUidToIdMap.erase(it);

		slot->mUid = RtId::Uid();
		slot->mRevision++;

		if (!deferDelete && slot->mObject)
		{
			if (!(flags & Slot::SLOTF_NeverDelete))
				slot->mObject->Delete();
			slot->mObject = NULL;
		}
		FreeSlot(slot, deferDelete);
	}
	return true;
}

bool RtDbTable::SetIdForAlias(const RtName& inAlias, const RtId& inId)
{
	AliasNameToUidMap::iterator it = mAliasNameToUidMap.find(inAlias);
	if (it != mAliasNameToUidMap.end())
		mAliasNameToUidMap.erase(it);

	if (inId.GetValue())
	{
		Slot* slot = GetSlotForId(inId, false);
		if (!slot)
			return false;
		mAliasNameToUidMap[inAlias] = slot->mUid;
	}
	return true;
}

uint32 RtDbTable::GetRefCountForId(const RtId& inId) const
{
	Slot* slot = GetSlotForId(inId, false);
	return slot ? slot->mRefCountAndFlags & Slot::SLOTF_REFCOUNTMASK : 0;
}

RtObject* RtDbTable::GetObjectForId(const RtId& inId) const
{
	Slot* slot = GetSlotForId(inId, false);
	if (!slot)
		return NULL;

	if (!slot->mObject && (slot->mRefCountAndFlags & Slot::SLOTF_Watched))
		const_cast<RtDbTable*>(this)->OnWatchedIdObjectAccessFault(inId);
	return slot->mObject;
}

bool RtDbTable::ReplaceObjectForId(const RtId& inId, RtObject* inObject) const
{
	Slot* slot = GetSlotForId(inId, true);
	if (!slot)
		return false;
	slot->mObject = inObject;
	return true;
}

bool RtDbTable::SetObjectDeletionMode(const RtId& inId, EObjectDeletionMode inMode) const
{
	Slot* slot = GetSlotForId(inId, true);
	if (!slot)
		return false;
	SetSlotObjectDeletionMode(slot, inMode);
	return true;
}

RtDbTable::EObjectDeletionMode RtDbTable::GetObjectDeletionMode(const RtId& inId) const
{
	Slot* slot = GetSlotForId(inId, true);
	if (!slot || (slot->mRefCountAndFlags & Slot::SLOTF_NeverDelete))
		return ODM_Never;
	return (slot->mRefCountAndFlags & Slot::SLOTF_DeferDelete) ? ODM_Deferred : ODM_Auto;
}

bool RtDbTable::SetObjectIsStandalone(const RtId& inId, bool inIsStandalone) const
{
	Slot* slot = GetSlotForId(inId, true);
	if (!slot)
		return false;
	if (inIsStandalone)
		slot->mRefCountAndFlags |= Slot::SLOTF_Standalone;
	else
		slot->mRefCountAndFlags &= ~Slot::SLOTF_Standalone;
	return true;
}

bool RtDbTable::GetObjectIsStandalone(const RtId& inId) const
{
	Slot* slot = GetSlotForId(inId, true);
	return slot ? (slot->mRefCountAndFlags & Slot::SLOTF_Standalone) != 0 : false;
}

bool RtDbTable::SetObjectIsWatched(const RtId& inId, bool inIsWatched) const
{
	Slot* slot = GetSlotForId(inId, true);
	if (!slot)
		return false;
	if (inIsWatched)
		slot->mRefCountAndFlags |= Slot::SLOTF_Watched;
	else
		slot->mRefCountAndFlags &= ~Slot::SLOTF_Watched;
	return true;
}

bool RtDbTable::GetObjectIsWatched(const RtId& inId) const
{
	Slot* slot = GetSlotForId(inId, true);
	return slot ? (slot->mRefCountAndFlags & Slot::SLOTF_Watched) != 0 : false;
}

RtId::Uid RtDbTable::GetUidForId(const RtId& inId) const
{
	Slot* slot = GetSlotForId(inId, true);
	RtId::Uid uid = slot ? slot->mUid : RtId::Uid();
	return uid;
}

RtId RtDbTable::GetIdForUid(const RtId::Uid& inUid) const
{
	UidToIdMap::const_iterator it = mUidToIdMap.find(inUid);
	if (it != mUidToIdMap.end())
	{
		RtId id(it->second);
		Slot* slot = GetSlotForId(id, false);
		if (slot && slot->mUid == inUid)
			return GetIdForSlot(slot);
	}
	return RtId();
}

RtId RtDbTable::GetIdForAlias(const RtName& inAlias) const
{
	AliasNameToUidMap::const_iterator it = mAliasNameToUidMap.find(inAlias);
	if (it != mAliasNameToUidMap.end())
		return GetIdForUid(it->second);
	return RtId();
}

/////////////// Iteration ///////////////

uint32 RtDbTable::IteratorStorage::PushIterator(uint32 inCount, RtDbTable* inTable)
{
	uint32 start = mData.size();
	mData.resize(start + inCount);
	mDataFloorStack.push_back(start);
	int offset = 0;
	for (Slot* slot = inTable->mUsedListHead.RingGetNext(); slot != &inTable->mUsedListHead; slot = slot->RingGetNext())
		mData[offset++ + start] = inTable->GetIdForSlot(slot);
	return start;
}

void RtDbTable::IteratorStorage::PopIterator(uint32 inCount)
{
	mData.resize(mDataFloorStack.back());
	mDataFloorStack.pop_back();
}

RtDbTable::Iterator::Iterator(RtDbTable* inTable, RtDbTable::IteratorStorage* inStorage)
: mAllocatedStorage(inStorage ? NULL : new RtDbTable::IteratorStorage())
, mStorage(inStorage ? inStorage : mAllocatedStorage.get())
, mIdCount(inTable->mUsedSlotCount)
{
	mStartId = mStorage->PushIterator(mIdCount, inTable);
	mIdOffset = 0;
}

RtDbTable::Iterator::Iterator(Iterator&& inIter)
: mAllocatedStorage(std::move(inIter.mAllocatedStorage))
, mStorage(std::move(inIter.mStorage))
, mIdCount(std::move(inIter.mIdCount))
, mStartId(std::move(inIter.mStartId))
, mIdOffset(std::move(inIter.mIdOffset))
{
	inIter.mStorage = NULL;
}

RtDbTable::Iterator::~Iterator()
{
	if (mStorage)
		mStorage->PopIterator(mIdCount);
}

RtId RtDbTable::Iterator::operator * () const
{
	if (mStorage)
		return mStorage->mData[mStartId + mIdOffset];
	return RtId();
}

RtId* RtDbTable::Iterator::operator -> () const
{
	if (mStorage)
		return &mStorage->mData[mStartId + mIdOffset];
	return NULL;
}

RtDbTable::Iterator::operator bool () const
{
	return mIdOffset != mIdCount;
}

RtDbTable::Iterator& RtDbTable::Iterator::operator ++ (void)
{
	mIdOffset = std::min(mIdOffset + 1, mIdCount);
	return *this;
}

RtDbTable::Iterator& RtDbTable::Iterator::operator ++ (int)
{
	mIdOffset = std::min(mIdOffset + 1, mIdCount);
	return *this;
}

void RtDbTable::Iterate(const IterateFilterDelegateType& inFilterDelegate, const IterateActionDelegateType& inActionDelegate, IteratorStorage* inIteratorStorage)
{
	if (!inIteratorStorage)
		inIteratorStorage = GetSharedIteratorStorage();

	for (Iterator it(this, inIteratorStorage); it; ++it)
	{
		if (inFilterDelegate(*it))
			inActionDelegate(*it);
	}
}

void RtDbTable::Iterate(const IterateActionDelegateType& inActionDelegate, IteratorStorage* inIteratorStorage)
{
	if (!inIteratorStorage)
		inIteratorStorage = GetSharedIteratorStorage();

	for (Iterator it(this, inIteratorStorage); it; ++it)
		inActionDelegate(*it);
}

void RtDbTable::Sort(const SortDelegateType& inSortDelegate)
{
	if (mSlotCount)
	{
		std::vector<Slot*> slots;
		slots.reserve(mSlotCount);
		slots.resize(mSlotCount);
		for (uint32 i = 0; i < mSlotCount; i++)
			slots[i] = &mSlots[i];

		SlotCompare::sSortCurDelegate = inSortDelegate;
		SlotCompare::sSortCurTable = this;
		qsort(&slots[0], mSlotCount, sizeof(Slot*), SlotCompare::Func);
		SlotCompare::sSortCurTable = NULL;

		Slot** sortedSlots = &slots[0];
		for (uint32 i = 0; i < mSlotCount; i++, sortedSlots++)
		{
			Slot* slot = *sortedSlots;
			if (!(slot->mRefCountAndFlags & Slot::SLOTF_Used))
				break;
			slot->RingLinkBefore(&mUsedListHead);
		}
	}
}

/////////////// Packages ///////////////

std::string RtDbTable::MakeFileNameFromPackageNameOrFileName(const std::string& inPackageNameOrFileName)
{
	if (inPackageNameOrFileName.empty())
		return inPackageNameOrFileName;

	std::string fileName = GetFileDir(inPackageNameOrFileName, true) + GetFileName(inPackageNameOrFileName, true) + ".rton";
	std::replace(fileName.begin(), fileName.end(), '\\', '/');
	if (strncasecmp(fileName.c_str(), "packages/", sPackagesPrefixLength) != 0)
		fileName = "packages/" + fileName;
	return fileName;
}

std::string RtDbTable::MakePackageNameFromPackageNameOrFileName(const std::string& inPackageNameOrFileName)
{
	if (inPackageNameOrFileName.empty())
		return inPackageNameOrFileName;

	std::string packageName = GetFileDir(inPackageNameOrFileName, true) + GetFileName(inPackageNameOrFileName, true);
	std::replace(packageName.begin(), packageName.end(), '\\', '/');
	const char* str = packageName.c_str();
	if (strncasecmp(str, "packages/", sPackagesPrefixLength) == 0)
		packageName = str + sPackagesPrefixLength;
	return packageName;
}

bool RtDbTable::LoadPackage(const std::string& inPackageFileName, const bool isFileEncryption)
{
	Buffer fileBuffer;

	if (!inPackageFileName.empty())
	{
		std::string fileName = MakeFileNameFromPackageNameOrFileName(inPackageFileName);
		if (!gSexyAppBase->ReadBufferFromFile(fileName, &fileBuffer, true))
			return false;
		std::string packageName = MakePackageNameFromPackageNameOrFileName(inPackageFileName);
		RtName name(StringToWString(packageName));
		SetCurrentPackageName(name);
	}
	else
	{
		std::string fileName = MakeFileNameFromPackageNameOrFileName(WStringToString(mCurrentPackageFileName));
		if (!gSexyAppBase->ReadBufferFromFile(fileName, &fileBuffer, true))
			return false;
	}

	RtId::StaticSetImplicitTableIndex(mTableIndex);

	Buffer decodedBuffer;
	uchar* data;
	int dataLen;
	if (isFileEncryption)
	{
		gSexyAppBase->mAntiHackDriver->DecodeBuffer(fileBuffer, decodedBuffer);
		data = decodedBuffer.GetDataPtr();
		dataLen = decodedBuffer.GetDataLen();
	}
	else
	{
		data = fileBuffer.GetDataPtr();
		dataLen = fileBuffer.GetDataLen();
	}

	RtSerialRtonReader reader(data, dataLen);
	RtId::StaticSetImplicitTableIndex(0xffffffff);
	RtSerialRtonSync sync(&reader);
	bool result = SerializeTable(&sync);
	SetFromLocalFile(false);
	return result;
}

bool RtDbTable::RefreshPackage(const std::string& inPackageFileName, const bool isFileEncryption)
{
	Buffer fileBuffer;

	if (!inPackageFileName.empty())
	{
		std::string fileName(inPackageFileName);
		if (!gSexyAppBase->ReadBufferFromFile(fileName, &fileBuffer, true))
			return false;
		std::string packageName = MakePackageNameFromPackageNameOrFileName(inPackageFileName);
		RtName name(StringToWString(packageName));
		SetCurrentPackageName(name);
	}
	else
	{
		std::string fileName = MakeFileNameFromPackageNameOrFileName(WStringToString(mCurrentPackageFileName));
		if (!gSexyAppBase->ReadBufferFromFile(fileName, &fileBuffer, true))
			return false;
	}

	RtId::StaticSetImplicitTableIndex(mTableIndex);

	Buffer decodedBuffer;
	uchar* data;
	int dataLen;
	if (isFileEncryption)
	{
		gSexyAppBase->mAntiHackDriver->DecodeBuffer(fileBuffer, decodedBuffer);
		data = decodedBuffer.GetDataPtr();
		dataLen = decodedBuffer.GetDataLen();
	}
	else
	{
		data = fileBuffer.GetDataPtr();
		dataLen = fileBuffer.GetDataLen();
	}

	RtSerialRtonReader reader(data, dataLen);
	RtId::StaticSetImplicitTableIndex(0xffffffff);
	RtSerialRtonSync sync(&reader);
	bool result = SerializeTable(&sync);
	SetFromLocalFile(false);
	return result;
}

bool RtDbTable::saveToFile(RtSerialRtonWriter& rtonWriter, const std::string& fileName, const bool inAsJSON, const bool doEncryption)
{
	std::string json;
	const uchar* data;
	int dataLen;
	if (inAsJSON)
	{
		RtSerial::RtonToJson(rtonWriter.GetBuffer()->GetDataPtr(), rtonWriter.GetBuffer()->GetDataSize(), json);
		data = (const uchar*)json.c_str();
		dataLen = json.length();
	}
	else
	{
		data = rtonWriter.GetBuffer()->GetDataPtr();
		dataLen = rtonWriter.GetBuffer()->GetDataSize();
	}

	Buffer encodedBuffer;
	if (__builtin_expect(doEncryption, 0))
	{
		Buffer plainBuffer;
		plainBuffer.SetData(data, dataLen);
		gSexyAppBase->mAntiHackDriver->EncodeBuffer(plainBuffer, encodedBuffer);
		data = encodedBuffer.GetDataPtr();
		dataLen = encodedBuffer.GetDataLen();
	}

	return gSexyAppBase->WriteBytesToFile(fileName, data, dataLen);
}

bool RtDbTable::SavePackage(RtSerialRtonWriter& rtonWriter, const std::string& inPackageFileName, const bool inAsJSON, const bool doEncryption)
{
	bool result = false;
	RtSerialRtonSync sync(&rtonWriter);
	if (SerializeTable(&sync))
	{
		if (inPackageFileName.empty())
		{
			result = saveToFile(rtonWriter, WStringToString(mCurrentPackageFileName), inAsJSON, doEncryption);
		}
		else
		{
			result = saveToFile(rtonWriter, inPackageFileName, inAsJSON, doEncryption);
			if (result)
			{
				RtName name(StringToWString(inPackageFileName));
				SetCurrentPackageName(name);
			}
		}
	}
	return result;
}

/////////////// Serialization ///////////////

void RtDbTable::SerializeAllAliasesToRton(RtSerialRtonWriter& inRtonWriter, const std::string& inArrayKeyName)
{
	inRtonWriter.BeginArray(inArrayKeyName, mAliasNameToUidMap.size());
	for (AliasNameToUidMap::iterator it = mAliasNameToUidMap.begin(); it != mAliasNameToUidMap.end(); ++it)
	{
		inRtonWriter.BeginObject(NULL);
		inRtonWriter.WriteString("alias", WStringToString(it->first.GetString()), true);
		inRtonWriter.WriteRtId("id", GetIdForUid(it->second));
		inRtonWriter.EndObject();
	}
	inRtonWriter.EndArray();
}

bool RtDbTable::SerializeRtIdAliasesToRton(RtSerialRtonWriter& inRtonWriter, const RtId& inAliasesForId, const std::string& inArrayKeyName)
{
	if (inAliasesForId.GetTableIndex() != GetTableIndex())
		return false;

	uint32 aliasCount = 0;
	for (AliasNameToUidMap::iterator it = mAliasNameToUidMap.begin(); it != mAliasNameToUidMap.end(); ++it)
	{
		if (inAliasesForId == GetIdForUid(it->second))
			aliasCount++;
	}

	inRtonWriter.BeginArray(inArrayKeyName, aliasCount);
	if (__builtin_expect(aliasCount != 0, 1))
	{
		for (AliasNameToUidMap::iterator it = mAliasNameToUidMap.begin(); it != mAliasNameToUidMap.end(); ++it)
		{
			if (inAliasesForId == GetIdForUid(it->second))
			{
				inRtonWriter.BeginObject(NULL);
				inRtonWriter.WriteString("alias", WStringToString(it->first.GetString()), true);
				inRtonWriter.WriteRtId("id", inAliasesForId);
				inRtonWriter.EndObject();
			}
		}
	}
	inRtonWriter.EndArray();
	return true;
}

bool RtDbTable::SerializeTableFirstPass(RtSerialRtonSync* inSync, std::vector<RtObject*>& inoutObjectList, const std::string& fileName)
{
	if (inSync->IsWriting())
		return true;

	RtSerialRtonReader* reader = inSync->GetReader();
	reader->BeginDocumentObject();
	if (reader->ReadInt32("version", 0) != 1)
		return false;

	Reset(false);
	OnTableLoadingEvent(*this);
	RtId::StaticSetImplicitTableIndex(mTableIndex);

	uint32 objectCount = 0;
	if (reader->BeginArray("objects", objectCount))
	{
		inoutObjectList.reserve(objectCount);
		inoutObjectList.resize(objectCount);

		for (uint32 i = 0; i < objectCount; i++)
		{
			reader->BeginObject(NULL);

			RtId::Uid uid;
			std::string uidString = reader->ReadString("uid", "");
			uid = !uidString.empty() ? RtId::Uid::StaticParse(uidString) : RtId::Uid(i, 1, 0xffffffff);

			Slot* slot = AllocSlot();
			slot->mRefCountAndFlags = (slot->mRefCountAndFlags + 1) | Slot::SLOTF_Used | Slot::SLOTF_Standalone;
			mUsedSlotCount++;
			slot->mObject = NULL;
			SetSlotObjectDeletionMode(slot, ODM_Auto);

			RtId id = GetIdForSlot(slot);
			slot->mUid = uid;
			mUidToIdMap[slot->mUid] = id.GetValue();
			OnIdCreated(id);

			RtClass* objectClass;
			RtObject* object;
			const char* className = reader->ReadStringDirect("objclass");
			if (className && (objectClass = RtClass::StaticGetClassNamed(className)) && (object = slot->mObject = objectClass->New()))
			{
				inoutObjectList[i] = object;

				uint32 aliasCount = 0;
				if (reader->BeginArray("aliases", aliasCount))
				{
					for (uint32 j = 0; j < aliasCount; j++)
					{
						std::wstring alias = reader->ReadWString(NULL, L"");
						if (!alias.empty())
						{
							RtName aliasName(alias);
							if (!(mAliasNameToUidMap.find(aliasName) != mAliasNameToUidMap.end()))
								mAliasNameToUidMap[RtName(alias)] = slot->mUid;
						}
					}
					reader->EndArray();
				}
			}
			else
			{
				ReleaseId(id);
			}

			reader->EndObject();
		}
		reader->EndArray();
	}

	RtId::StaticSetImplicitTableIndex(0xffffffff);
	reader->EndDocumentObject();
	return true;
}

bool RtDbTable::SerializeTableSecondPass(RtSerialRtonSync* inSync, std::vector<RtObject*>& inoutObjectList)
{
	if (inSync->IsReading())
	{
		RtId::StaticSetImplicitTableIndex(mTableIndex);

		RtSerialRtonReader* reader = inSync->GetReader();
		reader->BeginDocumentObject();

		uint32 objectCount = 0;
		if (reader->BeginArray("objects", objectCount))
		{
			for (uint32 i = 0; i < objectCount; i++)
			{
				reader->BeginObject(NULL);
				RtObject* object = inoutObjectList[i];
				if (object)
					object->Serialize(RtSerializeContext(inSync, "objdata"));
				reader->EndObject();
			}
			reader->EndArray();
		}

		RtId::StaticSetImplicitTableIndex(0xffffffff);
		reader->EndDocumentObject();
		OnTableLoadedEvent(*this);
	}
	else
	{
		RtId::StaticSetImplicitTableIndex(mTableIndex);

		RtSerialRtonWriter* writer = inSync->GetWriter();
		writer->BeginDocumentObject();
		writer->WriteInt32("version", 1);
		Slot* usedListHead = &mUsedListHead;
		uint32 usedSlotCount = mUsedSlotCount;
		writer->BeginArray("objects", usedSlotCount);

		for (Slot* slot = mUsedListHead.RingGetPrev(); usedListHead != slot; slot = slot->RingGetPrev())
		{
			writer->BeginObject(NULL);

			RtId id = GetIdForSlot(slot);
			RtId::Uid uid = slot->mUid;
			writer->WriteString("uid", StrFormat("%d.%d.%08x", uid.mRevision, uid.mSlot, uid.mDbTime));

			if (slot->mObject)
			{
				if (slot->mRefCountAndFlags & Slot::SLOTF_Standalone)
				{
					RtClass* objectClass = slot->mObject->GetClass();
					writer->WriteString("objclass", objectClass->GetName(), true);
					slot->mObject->Serialize(RtSerializeContext(inSync, "objdata"));

					std::vector<std::wstring> aliases;
					for (AliasNameToUidMap::iterator it = mAliasNameToUidMap.begin(); it != mAliasNameToUidMap.end(); ++it)
					{
						if (it->second != slot->mUid)
							continue;
						RtName aliasName(it->first);
						const wchar_t* alias = aliasName.GetString();
						if (alias && *alias == L'$')
							continue;
						aliases.push_back(alias);
					}

					if (!aliases.empty())
					{
						int aliasCount = aliases.size();
						writer->BeginArray("aliases", aliasCount);
						for (int i = 0; i < aliasCount; i++)
							writer->WriteUTF8String(NULL, aliases[i]);
						writer->EndArray();
					}
				}
				else
				{
					std::string idString;
					id.ToString(idString);
					OutputDebugStrF("RtDbTable::Serialize: Attempted to write non-standalone object %s, skipping...\n", idString.c_str());
				}
			}

			writer->EndObject();
		}

		writer->EndArray();
		writer->EndDocumentObject();
		RtId::StaticSetImplicitTableIndex(0xffffffff);
	}
	return true;
}

bool RtDbTable::SerializeTable(RtSerialRtonSync* inSync, const std::string& fileName)
{
	RunDeferredDeletions();
	Reflection::CRefSymbolDb::GetManualReflection()->EnsureFullyLoaded();

	std::vector<RtObject*> objectList;
	bool result = SerializeTableFirstPass(inSync, objectList);
	if (result)
		result = SerializeTableSecondPass(inSync, objectList);
	return result;
}

bool RtDbTable::WriteRtonRtIdList(RtSerialBuffer* inBuffer) const
{
	uint32 idCount = 0;
	for (Slot* slot = mUsedListHead.RingGetNext(); slot != &mUsedListHead; slot = slot->RingGetNext())
		idCount++;

	RtSerialRtonWriter writer(inBuffer);
	writer.BeginDocumentObject();
	writer.WriteInt32VarU("version", 1);
	writer.WriteInt32("table_index", GetTableIndex());
	writer.BeginArray("ids", idCount, RtSerialRtonTag::RtId);
	for (Slot* slot = mUsedListHead.RingGetNext(); slot != &mUsedListHead; slot = slot->RingGetNext())
		writer.WriteRtId(NULL, GetIdForSlot(slot));
	writer.EndArray();
	writer.EndDocumentObject();
	return true;
}

void RtDbTable::WriteTableRtonKeys(RtSerialRtonWriter& inRtonWriter) const
{
	const TableOptions* options = GetTableOptions();
	uint32 tableIndex = GetTableIndex();
	inRtonWriter.WriteInt32("table_index", tableIndex);
	inRtonWriter.WriteBool("is_system_table", IsSystemTable() && !options->mSysTableActAsUserTable);
	if (options->mTableName)
		inRtonWriter.WriteString("table_name", WStringToString(options->mTableName.GetString() + 1));
	if (!options->mDisplayName.empty())
		inRtonWriter.WriteString("display_name", options->mDisplayName);
	if (options->mIsFixedContent)
		inRtonWriter.WriteBool("is_fixed_content", true);
	inRtonWriter.WriteUTF8String("current_package", GetCurrentPackageName().GetString());
}

/////////////// Diagnostics ///////////////

void RtDbTable::DebugPrintTableInfo()
{
	uint32 idCount = GetRtIdCount();
	const TableOptions* options = GetTableOptions();

	OutputDebugStrF("==============================================\n");

	std::wstring tableName(options->mTableName.GetString());
	OutputDebugStrF("Table Name: \t%s\n", WStringToString(tableName).c_str());
	OutputDebugStrF("Display Name: \t%s\n", options->mDisplayName.c_str());

	if (HasCurrentPackage())
	{
		std::wstring packageName(GetCurrentPackageName().GetString());
		OutputDebugStrF("Package Name:\t%s\n", WStringToString(packageName).c_str());
	}

	OutputDebugStrF("Table Index:   %d\n", GetTableIndex());
	OutputDebugStrF("Entity Count: \t%d\n", idCount);
	OutputDebugStrF("Free Slots:\t%d\tUsed Slots:\t\t%d\tCondemned:\t%d\tRetired:\t%d\n", mFreeSlotCount, mUsedSlotCount, mCondemnedSlotCount, mRetiredSlotCount);
}
