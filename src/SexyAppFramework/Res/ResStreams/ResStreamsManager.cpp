//
//  ResStreamsManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

using namespace Sexy;

bool CheckFileTag(std::string, std::string);


/////////////// Groups ///////////////

bool ResStreamsManager::IsGroupLoaded(const std::string& theGroupName)
{
	return IsGroupLoaded(LookupGroup(theGroupName));
}

bool ResStreamsManager::LoadGroup(const std::string& theGroupName)
{
	return LoadGroup(LookupGroup(theGroupName));
}

bool ResStreamsManager::ForceLoadGroup(const std::string& theGroupName, const std::string& theDbgReason)
{
	return ForceLoadGroup(LookupGroup(theGroupName), theDbgReason);
}

bool ResStreamsManager::ForceLoadGroup(uint32 theGroupId, const std::string& theDbgReason)
{
	if (theGroupId == UNKNOWN_GROUP)
		return false;

	GroupStatus aStatus = GetGroupStatus(theGroupId);
	if (aStatus == RESIDENT)
		return true;

	std::string aGroupName;
	if (IS_COMPOSITE_GROUP(theGroupId))
	{
		aGroupName = (const char*)GetComposite(GET_COMPOSITE_GROUP(theGroupId));
	}
	else
	{
		RSBDesc* aRsbDesc = NULL;
		for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
		{
			RSBDesc* aDesc = *anItr;
			if (aDesc && theGroupId < aDesc->mBaseIndex + aDesc->mNumGroups)
			{
				aRsbDesc = aDesc;
				break;
			}
		}

		aGroupName = aRsbDesc->mGroups[theGroupId - aRsbDesc->mBaseIndex].mName;
	}

	if (aStatus == NOT_RESIDENT)
	{
		if (!LoadGroup(theGroupId))
			return false;
	}

	while (!IsGroupLoaded(theGroupId) && !gSexyAppBase->mShutdown)
	{
		if (HasError())
		{
			OutputDebugStrF("RSB Error: Could not load group '%s'.\n", aGroupName.c_str());
			return false;
		}

		Update();
	}

	return IsGroupLoaded(theGroupId);
}

bool ResStreamsManager::DeleteGroup(const std::string& theGroupName)
{
	return DeleteGroup(LookupGroup(theGroupName));
}

bool ResStreamsManager::IsGroupLoaded(uint32 theGroupId)
{
	return theGroupId != UNKNOWN_GROUP && GetGroupStatus(theGroupId) == RESIDENT;
}

/////////////// Loading ///////////////

void ResStreamsManager::OnGPUDataFinished(ResStreamsLoadDesc* theDesc)
{
	theDesc->gpu_data_loaded = true;
}

/////////////// Stats ///////////////

uint32 ResStreamsManager::GetTotalBytesForGroup(RSBDesc* pRsbDesc, uint32 theGroupId)
{
	if (!pRsbDesc)
		return -1;

	ResStreamGroupDescriptor* aDesc = pRsbDesc->mGroups[theGroupId].mDesc;
	return aDesc->data_resident_total_size + aDesc->data_gpu_total_size + aDesc->data_transient_total_size;
}

void ResStreamsManager::ExecuteTasks()
{
}

void ResStreamsManager::LostFocus()
{
}

void ResStreamsManager::ForceLoadGPUData(int theGroupId)
{
	RSBDesc* aRsbDesc = NULL;
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aDesc = *anItr;
		if (aDesc && aDesc->mBaseIndex + aDesc->mNumGroups > theGroupId)
		{
			aRsbDesc = aDesc;
			break;
		}
	}

	aRsbDesc->mGroups[theGroupId - aRsbDesc->mBaseIndex].mStatus = PREPARING;
	ResStreamsLoadDesc* aLoadDesc = new ResStreamsLoadDesc();
	aLoadDesc->file = aRsbDesc->mFile;
	aLoadDesc->group = &aRsbDesc->mGroups[theGroupId];
	aLoadDesc->instance = aLoadDesc->group->mLoadedAtInstance;
	aLoadDesc->pool = &aRsbDesc->mPools[aLoadDesc->group->mPoolIndex];
	aLoadDesc->want_resident_data = false;
	aLoadDesc->report_load_stats = false;
	mLoadingQueue.push_back(aLoadDesc);
	mIsIdle = false;
}

void ResStreamsManager::GotFocus()
{
	if (mbShouldForceReloadOnFocus)
	{
		for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
		{
			RSBDesc* aDesc = *anItr;
			for (uint32 i = 0; i < aDesc->mNumGroups; i++)
			{
				if (GetGroupStatus(aDesc->mBaseIndex + i) == PREPARING)
				{
					DeleteGroup(aDesc->mBaseIndex + i);
					ForceLoadGroup(aDesc->mBaseIndex + i, "Preparing group");
				}
			}

			std::vector<bool> aValidGroups;
			aValidGroups.resize(aDesc->mNumGroups);
			for (uint32 i = 0; i < aDesc->mNumGroups; i++)
			{
				if (IsGroupLoaded(aDesc->mBaseIndex + i) && ValidateGroupResources(aDesc->mBaseIndex + i))
					aValidGroups[i] = true;
			}
			for (uint32 i = 0; i < aDesc->mNumGroups; i++)
			{
				if (aValidGroups[i])
					ForceLoadGPUData(aDesc->mBaseIndex + i);
			}
		}
		while (true)
		{
			if (mIsIdle)
				break;
			Update();
		}
	}
}

bool ResStreamsManager::IsCompositeChildActive(ResStreamCompositeDescriptor::Child& theChildGroup)
{
	if (theChildGroup.resolution != 0 && theChildGroup.resolution != mApp->mResourceManager->mCurArtRes)
		return false;

	if (theChildGroup.locale != 0)
		return theChildGroup.locale == mApp->mResourceManager->mCurLocSet;

	return true;
}

bool ResStreamsManager::LoadGroup(RSBDesc* pRsbDesc, uint32 theGroupId)
{
	if (!pRsbDesc || theGroupId == UNKNOWN_GROUP)
		return false;

	AutoCrit aCrit(mLoadingQueueCritSect);
	if (pRsbDesc->mGroups[theGroupId].mStatus != PREPARING && pRsbDesc->mGroups[theGroupId].mStatus != RESIDENT)
	{
		mIsIdle = false;
		ResStreamsLoadDesc* aLoadDesc = new ResStreamsLoadDesc();
		aLoadDesc->file = pRsbDesc->mFile;
		aLoadDesc->group = &pRsbDesc->mGroups[theGroupId];
		aLoadDesc->pool = &pRsbDesc->mPools[pRsbDesc->mGroups[theGroupId].mPoolIndex];
		aLoadDesc->instance = aLoadDesc->pool->LockInstanceForGroup(&pRsbDesc->mGroups[theGroupId], theGroupId);
		mLoadingQueue.push_back(aLoadDesc);
		pRsbDesc->mGroups[theGroupId].mStatus = PREPARING;
	}

	return true;
}

bool ResStreamsManager::DeleteGroup(RSBDesc* pRsbDesc, uint32 theGroupId)
{
	if (!pRsbDesc || theGroupId == UNKNOWN_GROUP)
		return false;

	ResStreamsGroup* aGroup = &pRsbDesc->mGroups[theGroupId];
	if (aGroup->GetStatus() == RESIDENT)
	{
		aGroup->mPool->UnlockInstanceForGroup(aGroup);
		if (pRsbDesc->mGroups[theGroupId].mPool->GetOccupantCount() == 0 && !(pRsbDesc->mGroups[theGroupId].mPool->mFlags & 2))
			pRsbDesc->mGroups[theGroupId].mPool->Destroy();

		pRsbDesc->mGroups[theGroupId].mStatus = NOT_RESIDENT;
		pRsbDesc->mGroups[theGroupId].Reset();
	}

	return true;
}

bool ResStreamsManager::DeleteGroup(uint32 theGroupId)
{
	if (theGroupId == UNKNOWN_GROUP)
		return false;

	if (IS_COMPOSITE_GROUP(theGroupId))
	{
		uint32 aCompositeId = GET_COMPOSITE_GROUP(theGroupId);
		RSBDesc* aRsbDesc = NULL;
		for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
		{
			RSBDesc* aDesc = *anItr;
			if (aDesc && aCompositeId < aDesc->mBaseIndex + aDesc->mNumGroups)
			{
				aRsbDesc = aDesc;
				break;
			}
		}

		ResStreamCompositeDescriptor* aComposite = GetComposite(aCompositeId);
		for (uint32 i = 0; i < aComposite->children_count; i++)
		{
			if (IsCompositeChildActive(aComposite->children[i]))
				DeleteGroup(aRsbDesc, aComposite->children[i].group_id);
		}

		return true;
	}

	RSBDesc* aRsbDesc = NULL;
	uint32 aLocalId = -1;
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aDesc = *anItr;
		if (aDesc && theGroupId < aDesc->mBaseIndex + aDesc->mNumGroups)
		{
			aRsbDesc = aDesc;
			aLocalId = theGroupId - aDesc->mBaseIndex;
			break;
		}
	}

	return DeleteGroup(aRsbDesc, aLocalId);
}

bool ResStreamsManager::LoadGroupFileIndex(uint32 theGroupId)
{
	if (IS_COMPOSITE_GROUP(theGroupId))
		return false;

	RSBDesc* aRsbDesc = NULL;
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aDesc = *anItr;
		if (aDesc && theGroupId < aDesc->mBaseIndex + aDesc->mNumGroups)
		{
			aRsbDesc = aDesc;
			break;
		}
	}

	return aRsbDesc->mGroups[theGroupId - aRsbDesc->mBaseIndex].LoadGroupFileIndex(aRsbDesc->mFile);
}

bool ResStreamsManager::UnloadGroupFileIndex(uint32 theGroupId)
{
	if (IS_COMPOSITE_GROUP(theGroupId))
		return false;

	RSBDesc* aRsbDesc = NULL;
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aDesc = *anItr;
		if (aDesc && theGroupId < aDesc->mBaseIndex + aDesc->mNumGroups)
		{
			aRsbDesc = aDesc;
			break;
		}
	}

	aRsbDesc->mGroups[theGroupId - aRsbDesc->mBaseIndex].Reset();
	return true;
}

bool ResStreamsManager::LoadGroupFileIndex(const std::string& theGroupName)
{
	return LoadGroupFileIndex(LookupGroup(theGroupName));
}

bool ResStreamsManager::UnloadGroupFileIndex(const std::string& theGroupName)
{
	return UnloadGroupFileIndex(LookupGroup(theGroupName));
}

ResStreamsManager::GroupStatus ResStreamsManager::GetGroupStatus(const std::string& theGroupName)
{
	return GetGroupStatus(LookupGroup(theGroupName));
}

bool ResStreamsManager::CanLoadGroup(const std::string theGroupName)
{
	return CanLoadGroup(LookupGroup(theGroupName));
}

void ResStreamsManager::PurgeResidentData(uint32 i_groupId)
{
	if (IS_COMPOSITE_GROUP(i_groupId))
	{
		uint32 aCompositeId = GET_COMPOSITE_GROUP(i_groupId);
		for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
		{
			RSBDesc* aRsbDesc = *anItr;
			if (aRsbDesc && aCompositeId < aRsbDesc->mBaseIndex + aRsbDesc->mNumGroups)
			{
				ResStreamCompositeDescriptor* aComposite = GetComposite(aCompositeId);
				for (uint32 i = 0; i < aComposite->children_count; i++)
				{
					ResStreamsPool* aPool = aRsbDesc->mGroups[aComposite->children[i].group_id].mPool;
					if (aPool->mResidentBuffer)
					{
						free(aPool->mResidentBuffer);
						aPool->mResidentBuffer = NULL;
						for (uint32 j = 0; j < aPool->mNumInstances; j++)
							aPool->mInstances[j].mResidentData = NULL;
					}
				}

				break;
			}
		}
	}
}

void ResStreamsManager::PurgeResidentData(const std::string& i_groupName)
{
	PurgeResidentData(LookupGroup(i_groupName));
}

bool ResStreamsManager::HasError()
{
	return mHasError;
}

void ResStreamsManager::FlagError()
{
	mHasError = true;
}

uint32 ResStreamsManager::GetBytesLoadedForGroup(RSBDesc* pRsbDesc, uint32 theGroupId)
{
	if (!pRsbDesc)
		return 0;

	GroupStatus aStatus = pRsbDesc->mGroups[theGroupId].GetStatus();
	if (aStatus == RESIDENT)
		return GetTotalBytesForGroup(pRsbDesc->mBaseIndex + theGroupId);

	if (aStatus == NOT_RESIDENT || aStatus == DELETING)
		return 0;

	for (ResStreamsLoadList::iterator anItr = mLoadingQueue.begin(); anItr != mLoadingQueue.end(); ++anItr)
	{
		ResStreamsLoadDesc* aDesc = *anItr;
		if (aDesc->group == &pRsbDesc->mGroups[theGroupId])
			return aDesc->curGPUDecompBytes + aDesc->curResidentDecompBytes + aDesc->curTransientDecompBytes;
	}

	return 0;
}

uint32 ResStreamsManager::GetDiscSpaceForGroup(RSBDesc* pRsbDesc, uint32 theGroupId)
{
	if (!pRsbDesc)
		return -1;

	return pRsbDesc->mGroups[theGroupId].mDesc->file_size;
}

PFILE* ResStreamsManager::GetPakFileFromResidentBuffer(uint32 theGroupId, const std::string& theFileName)
{
	uint8* aBuffer;
	uint32 aSize;
	if (!GetResidentFileBuffer(theGroupId, theFileName, &aBuffer, &aSize))
		return NULL;

	PFILE* aFile = new PFILE;
	aFile->mRecord = NULL;
	aFile->mFile = NULL;
	aFile->mBuffer = aBuffer;
	aFile->mSize = aSize;
	aFile->mBufferOwner = false;
	aFile->mPointer = 0;
	return aFile;
}

uint32 ResStreamsManager::LookupGroup(const std::string& theGroupName)
{
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aRsbDesc = *anItr;
		if (aRsbDesc)
		{
			uint32* aCompositeId = (uint32*)aRsbDesc->mCompositeNameToIdIndex.Find(theGroupName.c_str());
			if (aCompositeId)
				return MAKE_COMPOSITE_GROUP(*aCompositeId + aRsbDesc->mBaseIndex);

			uint32* aGroupId = (uint32*)aRsbDesc->mGroupNameToIdIndex.Find(theGroupName.c_str());
			if (aGroupId)
				return *aGroupId + aRsbDesc->mBaseIndex;
		}
	}

	return UNKNOWN_GROUP;
}

int ResStreamsManager::LookupGroupIndex(const std::string& theGroupName)
{
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aRsbDesc = *anItr;
		if (aRsbDesc)
		{
			uint32* aCompositeId = (uint32*)aRsbDesc->mCompositeNameToIdIndex.Find(theGroupName.c_str());
			if (aCompositeId)
				return *aCompositeId + aRsbDesc->mBaseIndex;

			uint32* aGroupId = (uint32*)aRsbDesc->mGroupNameToIdIndex.Find(theGroupName.c_str());
			if (aGroupId)
				return *aGroupId + aRsbDesc->mBaseIndex;
		}
	}

	return -1;
}

bool ResStreamsManager::IsInitialized(const std::string& theRsbName)
{
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aRsbDesc = *anItr;
		if (aRsbDesc && aRsbDesc->mRsbName == theRsbName)
			return true;
	}

	return false;
}

bool ResStreamsManager::HasGlobalFileIndex()
{
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aRsbDesc = *anItr;
		if (!aRsbDesc)
			return false;
		if (!aRsbDesc->mFileToGroupIndex.Initialized())
			return false;
	}

	return true;
}

uint32 ResStreamsManager::GetLoadedGroupForFile(const std::string& theFileName)
{
	uint32 aGroup;
	if (GetLoadedFileData(theFileName, aGroup))
		return aGroup;

	return UNKNOWN_GROUP;
}

ResStreamsLoadDesc* ResStreamsManager::FindNextGroupToLoad()
{
	for (ResStreamsLoadList::iterator anItr = mLoadingQueue.begin(); anItr != mLoadingQueue.end(); ++anItr)
	{
		ResStreamsLoadDesc* aDesc = *anItr;
		if (!aDesc->loading)
			return aDesc;
	}

	return NULL;
}

void ResStreamsManager::StartLoadNextGroup()
{
	if (!mApp->IsMainThread())
		return;

	ResStreamsLoadDesc* aDesc = FindNextGroupToLoad();
	if (!aDesc)
		return;

	aDesc->loading = true;
	if (aDesc->want_resident_data)
		StartResidentDataLoad(aDesc);
	else if (aDesc->want_gpu_data)
		StartGPUDataLoad(aDesc);
}

void ResStreamsManager::OnResidentDataFinished(ResStreamsLoadDesc* theLoadDesc)
{
	ResStreamGroupHeader* aHeader = (ResStreamGroupHeader*)theLoadDesc->pool->GetResidentDataMemory(theLoadDesc->instance);
	theLoadDesc->group->InitGroupStream(aHeader, theLoadDesc->instance);
	theLoadDesc->resident_loaded = true;
}

ResStreamCompositeDescriptor* ResStreamsManager::GetComposite(uint32 theIndex)
{
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aRsbDesc = *anItr;
		ResStreamHeader* aHeader = (ResStreamHeader*)aRsbDesc->mCommonBuffer;
		if (aRsbDesc->mBaseIndex + aHeader->v1.composites_count > theIndex)
			return (ResStreamCompositeDescriptor*)(aRsbDesc->mCommonBuffer + aHeader->v1.composites_location + (theIndex - aRsbDesc->mBaseIndex) * aHeader->v1.composites_size);
	}

	return NULL;
}

void ResStreamsManager::ClearRSB(const std::string& theRSBName)
{
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aRsbDesc = *anItr;
		if (aRsbDesc && aRsbDesc->mRsbName == theRSBName)
		{
			delete aRsbDesc;
			mRsbList.erase(anItr);
			return;
		}
	}
}

void ResStreamsManager::Clear()
{
	mLoadingQueue.clear();
	mPendingTasks.clear();
	mExecutedTasks.clear();
	mIsIdle = true;
	mHasError = false;

	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aRsbDesc = *anItr;
		if (aRsbDesc)
			delete aRsbDesc;
	}

	mRsbList.clear();
	mBaseIndex = 0;
}

bool ResStreamsManager::NeedDecompressRsb(const std::string& theFileName, const std::string& PhonePath, const std::string& SDCardPath)
{
	if (!mApp->mResStreamsDriver)
	{
		OutputDebugStrF("ResStreamsManager::InitializeWithRSB mResStreamsDriver\n");
		return false;
	}

	std::string aTag = ".tag";
	std::string aRsbPath = mApp->mFileDriver->GetLoadDataPath() + theFileName + aTag;
	std::string aPhonePath = PhonePath;
	std::string aSDCardPath = SDCardPath;
	if (aPhonePath == "")
		aPhonePath = Android::Resources::GetUserDataFolder((Sexy::AndroidAppDriver*)mApp);
	if (aSDCardPath == "")
		aSDCardPath = Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)mApp);

	if (!gSexyAppBase->mFileDriver->FileExists(aRsbPath, NULL))
		return false;
	if (!aPhonePath.empty() && !CheckFileTag(aRsbPath, aPhonePath + "/" + theFileName + aTag + ".smf"))
		return false;
	if (aSDCardPath.empty())
		return true;
	return CheckFileTag(aRsbPath, aSDCardPath + "/" + theFileName + aTag + ".smf");
}

bool ResStreamsManager::InitializeWithRSB(const std::string& theFileName, const std::string& PhonePath, const std::string& SDCardPath, bool canIgnore)
{
	std::string aBasePath = mApp->mFileDriver->GetLoadDataPath();
	return AddRSB(aBasePath, theFileName, PhonePath, SDCardPath, canIgnore);
}

bool ResStreamsManager::ValidateGroupResources(int iGroupIdx)
{
	RSBDesc* aRsbDesc = NULL;
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aDesc = *anItr;
		if (aDesc && aDesc->mBaseIndex + aDesc->mNumGroups > iGroupIdx)
		{
			aRsbDesc = aDesc;
			break;
		}
	}

	return mApp->mResStreamsDriver->ValidateGroupTextures(&aRsbDesc->mGroups[iGroupIdx - aRsbDesc->mBaseIndex]);
}

std::string ResStreamsManager::GetRSBPath(uint32 i_groupId)
{
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aDesc = *anItr;
		if (aDesc && i_groupId < aDesc->mBaseIndex + aDesc->mNumGroups)
			return aDesc->mRsbPath;
	}

	return GetRSBPath();
}

uint32 ResStreamsManager::GetTotalBytesForGroup(uint32 theGroupId)
{
	if (theGroupId == UNKNOWN_GROUP)
		return -1;

	if (IS_COMPOSITE_GROUP(theGroupId))
	{
		uint32 aCompositeId = GET_COMPOSITE_GROUP(theGroupId);
		RSBDesc* aRsbDesc = NULL;
		for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
		{
			RSBDesc* aDesc = *anItr;
			if (aDesc && aCompositeId < aDesc->mBaseIndex + aDesc->mNumGroups)
			{
				aRsbDesc = aDesc;
				break;
			}
		}

		ResStreamCompositeDescriptor* aComposite = GetComposite(aCompositeId);
		uint32 aTotal = 0;
		for (uint32 i = 0; i < aComposite->children_count; i++)
		{
			if (IsCompositeChildActive(aComposite->children[i]))
				aTotal += GetTotalBytesForGroup(aRsbDesc, aComposite->children[i].group_id);
		}

		return aTotal;
	}

	RSBDesc* aRsbDesc = NULL;
	uint32 aLocalId = 0;
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aDesc = *anItr;
		if (aDesc && theGroupId < aDesc->mBaseIndex + aDesc->mNumGroups)
		{
			aRsbDesc = aDesc;
			aLocalId = theGroupId - aDesc->mBaseIndex;
			break;
		}
	}

	return GetTotalBytesForGroup(aRsbDesc, aLocalId);
}

uint32 ResStreamsManager::GetDiscSpaceForGroup(uint32 theGroupId)
{
	uint32 aSpace = -1;
	if (theGroupId == UNKNOWN_GROUP)
		return aSpace;

	if (IS_COMPOSITE_GROUP(theGroupId))
	{
		uint32 aCompositeId = GET_COMPOSITE_GROUP(theGroupId);
		RSBDesc* aRsbDesc = NULL;
		for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
		{
			RSBDesc* aDesc = *anItr;
			if (aDesc && aCompositeId < aDesc->mBaseIndex + aDesc->mNumGroups)
			{
				aRsbDesc = aDesc;
				break;
			}
		}

		ResStreamCompositeDescriptor* aComposite = GetComposite(aCompositeId);
		aSpace = 0;
		for (uint32 i = 0; i < aComposite->children_count; i++)
		{
			if (aComposite->children[i].resolution <= 768)
				aSpace += GetDiscSpaceForGroup(aRsbDesc, aComposite->children[i].group_id);
		}

		return aSpace;
	}

	RSBDesc* aRsbDesc = NULL;
	uint32 aLocalId = 0;
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aDesc = *anItr;
		if (aDesc && theGroupId < aDesc->mBaseIndex + aDesc->mNumGroups)
		{
			aRsbDesc = aDesc;
			aLocalId = theGroupId - aDesc->mBaseIndex;
			break;
		}
	}

	return GetDiscSpaceForGroup(aRsbDesc, aLocalId);
}

uint32 ResStreamsManager::GetBytesLoadedForGroup(uint32 theGroupId)
{
	if (theGroupId == UNKNOWN_GROUP)
		return -1;

	if (IS_COMPOSITE_GROUP(theGroupId))
	{
		uint32 aCompositeId = GET_COMPOSITE_GROUP(theGroupId);
		RSBDesc* aRsbDesc = NULL;
		for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
		{
			RSBDesc* aDesc = *anItr;
			if (aDesc && aCompositeId < aDesc->mBaseIndex + aDesc->mNumGroups)
			{
				aRsbDesc = aDesc;
				break;
			}
		}

		ResStreamCompositeDescriptor* aComposite = GetComposite(aCompositeId);
		uint32 aTotal = 0;
		for (uint32 i = 0; i < aComposite->children_count; i++)
		{
			if (IsCompositeChildActive(aComposite->children[i]))
				aTotal += GetBytesLoadedForGroup(aRsbDesc, aComposite->children[i].group_id);
		}

		return aTotal;
	}

	RSBDesc* aRsbDesc = NULL;
	uint32 aLocalId = 0;
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aDesc = *anItr;
		if (aDesc && theGroupId < aDesc->mBaseIndex + aDesc->mNumGroups)
		{
			aRsbDesc = aDesc;
			aLocalId = theGroupId - aDesc->mBaseIndex;
			break;
		}
	}

	return GetBytesLoadedForGroup(aRsbDesc, aLocalId);
}

uint8* ResStreamsManager::GetLoadedFileData(const std::string& theFileName, uint32& theGroup)
{
	theGroup = UNKNOWN_GROUP;
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aRsbDesc = *anItr;
		if (!aRsbDesc)
			continue;

		for (uint32 i = 0; i < aRsbDesc->mNumGroups; i++)
		{
			ResStreamsGroup* aGroup = &aRsbDesc->mGroups[i];
			if (aGroup->GetStatus() == RESIDENT && aGroup->mPool->mResidentBuffer)
			{
				uint8* aData = aGroup->GetFileIndexData(theFileName);
				if (aData)
				{
					theGroup = i + aRsbDesc->mBaseIndex;
					return aData;
				}
			}
		}
	}

	return NULL;
}

/////////////// Lifecycle ///////////////

ResStreamsManager::RSBDesc::RSBDesc()
{
	mFile = NULL;
	mBaseIndex = -1;
	mCommonBuffer = NULL;
	mCommonSize = 0;
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

ResStreamsManager::ResStreamsManager(SexyAppBase* theApp) :
	mRSBPath("")
{
	mApp = theApp;
	mIsIdle = true;
	mHasError = false;
	mbShouldForceReloadOnFocus = true;
	mRsbList.clear();
	mBaseIndex = 0;
}

ResStreamsManager::~ResStreamsManager()
{
	for (std::list<RSBDesc*>::iterator anItr = mRsbList.begin(); anItr != mRsbList.end(); ++anItr)
	{
		RSBDesc* aRsbDesc = *anItr;
		if (aRsbDesc)
			delete aRsbDesc;
	}

	mRsbList.clear();
}
