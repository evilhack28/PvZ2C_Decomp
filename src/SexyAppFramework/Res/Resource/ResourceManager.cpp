//
//  ResourceManager.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-27.
//

#include "ResourceManager.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/IAppDriver.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyAppFramework/SoundBank.h"
#include "SexyAppFramework/SexyTime.h"

using namespace Sexy;

static std::string sLastNonDelayLoadRSBManifestName;

static std::map<std::string, std::string> sDelayLoadedRSBs;

/////////////// Lifecycle ///////////////

ResourceManager::GetImageOptions::GetImageOptions()
	: mTestOnly(false)
	, mAllowTriReps(true)
	, mIsInAtlas(false)
	, mNoShare(false)
	, mResGroup(NULL)
	, mUseWidth(0), mUseHeight(0)
{
}

ResourceManager::GetImageOptions::~GetImageOptions()
{
}

ResourceManager::PreLoadTask::PreLoadTask()
{
	RSBBuffer = NULL;
}

ResourceManager::PreLoadTask::~PreLoadTask()
{
	delete RSBBuffer;
}

/////////////// Accessors ///////////////

ResourceGroup* ResourceManager::GetResourceGroupNamed(const RtName& inName)
{
	RtId anId = mResGroupTable->GetIdForAlias(inName);
	RtWeakPtr<ResourceGroup> aGroup(anId);
	return aGroup;
}

const std::string& ResourceManager::GetLastNonDelayLoadRSBManifestName()
{
	return sLastNonDelayLoadRSBManifestName;
}

uint32 ResourceManager::GetDelayLoadedRSBSlotCount()
{
	return mDelayLoadedRSBSlotCount;
}

ResourceGroup* ResourceManager::GetResourceGroupNamed(const std::string& inName)
{
	return GetResourceGroupNamed(StringToWString(inName));
}

/////////////// Logic ///////////////

ResourceGroup* ResourceManager::CreateResourceGroup(const RtName& inName, bool inIsComposite, bool& bExisted)
{
	ResourceGroup* aGroup = GetResourceGroupNamed(inName);
	if (aGroup != NULL)
	{
		bExisted = true;
		return aGroup;
	}

	bExisted = false;
	aGroup = new ResourceGroup();
	aGroup->mManager = this;
	aGroup->mGroupName = inName;
	aGroup->mIsComposite = inIsComposite;
	aGroup->mRtId = RtDb::GetDb()->AllocId(RtDb::SYSTEMTABLE_ResourceGroups, aGroup);
	mResGroupTable->SetIdForAlias(inName, aGroup->mRtId);

	return aGroup;
}

ResourceInfo* ResourceManager::GetResInfoForStringId(ResourceInfoClass* theType, const std::string& theId)
{
	if (mCurArtResKey.empty() || mCurArtRes != mCurArtResCached)
	{
		mCurArtResCached = mCurArtRes;
		mCurArtResKey = StrFormat("|%d", mCurArtRes);
		mCurLocSetKey = StrFormat("||%8x", mCurLocSet);
		mCurArtResAndLocSetKey = StrFormat("|%d||%8x", mCurArtRes, mCurLocSet);
	}

	std::string aDlcId = "CFDLC_" + theId;

	if (theType != NULL)
	{
		ResourceInfoClass::ResMap& aMap = theType->mResMap;

		ResourceInfoClass::ResMap::iterator anItr = aMap.find(RES_HASH_FUNC((aDlcId + mCurArtResAndLocSetKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC((aDlcId + mCurArtResKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC((aDlcId + mCurLocSetKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC(aDlcId.c_str()));

		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC((theId + mCurArtResAndLocSetKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC((theId + mCurArtResKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC((theId + mCurLocSetKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC(theId.c_str()));

		if (anItr != aMap.end())
			return anItr->second;

		return NULL;
	}

	uint32 aCount = GetInfoClassCount();
	for (uint32 i = 0; i < aCount; i++)
	{
		ResourceInfoClass::ResMap& aMap = GetInfoClassIndexed(i)->mResMap;

		ResourceInfoClass::ResMap::iterator anItr = aMap.find(RES_HASH_FUNC((aDlcId + mCurArtResAndLocSetKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC((aDlcId + mCurArtResKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC((aDlcId + mCurLocSetKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC(aDlcId.c_str()));

		if (anItr != aMap.end())
			return anItr->second;

		anItr = aMap.find(RES_HASH_FUNC((theId + mCurArtResAndLocSetKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC((theId + mCurArtResKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC((theId + mCurLocSetKey).c_str()));
		if (anItr == aMap.end())
			anItr = aMap.find(RES_HASH_FUNC(theId.c_str()));

		if (anItr != aMap.end())
			return anItr->second;
	}

	return NULL;
}

bool ResourceManager::ParseGroupResources(ResourceGroup* theGroup, uint32 uBaseIndex)
{
	uint32 aCount = 0;
	if (!mRtonReader->BeginArray("resources", aCount))
		return Fail("Missing resources array");

	for (uint32 i = 0; i < aCount; i++)
	{
		mRtonReader->BeginObject(NULL);

		const char* aTypeName = mRtonReader->ReadStringDirect("type");
		if (aTypeName == NULL)
			return Fail("No resource \"type\" found");

		RtName aTypeRtName = StringToWString(aTypeName);
		ManifestTypeNameToInfoClassMap::iterator aTypeItr = mManifestTypeNameToInfoClassMap.find(aTypeRtName);
		if (aTypeItr == mManifestTypeNameToInfoClassMap.end())
			return Fail(StrFormat("Unsupported resource type \"%s\"", aTypeName));

		ResourceInfoClass* aResType = aTypeItr->second;

		ResourceInfoClass::FPreCreateFilter aFilter = aResType->GetPreCreateFilterFunc();
		if (aFilter != NULL && !aFilter(this))
		{
			mRtonReader->EndObject();
			continue;
		}

		ResourceInfo* aResInfo = aResType->GetInstanceClass()->New()->Cast<ResourceInfo>();

		int aSlot = mRtonReader->ReadInt32("slot", -1);

		RtId anId;
		if (aSlot >= 0)
		{
			anId = RtId(RtDb::SYSTEMTABLE_ResourceInfo, aSlot + uBaseIndex, true);
			mInfoTable->ReplaceObjectForId(anId, aResInfo);
			aResInfo->SetRtId(anId);
		}
		else
		{
			anId = mHiddenInfoTable->AllocId(aResInfo);
			aResInfo->SetRtId(anId);
		}

		if (!ParseCommonResource(aResInfo, aResType, theGroup) || !aResInfo->IsResourceValid())
			return false;

		aResInfo->ApplyConfig();
		aResInfo->mReloadIdx = mReloadIdx;

		mRtonReader->EndObject();
	}

	mRtonReader->EndArray();
	return true;
}

bool ResourceManager::ParseCommonResource(ResourceInfo*& ioRes, ResourceInfoClass* inResType, ResourceGroup* inGroup)
{
	ioRes->mManager = this;

	std::string aPath;
	uint32 aPathCount = 0;
	if (mRtonReader->BeginArray("path", aPathCount))
	{
		for (uint32 i = 0; i < aPathCount; i++)
		{
			if (!aPath.empty())
				aPath += "\\";
			aPath += mRtonReader->ReadString(NULL, "");
		}
		mRtonReader->EndArray();
	}

	if (aPath.empty())
		return Fail("No path specified.");

	ioRes->mFromProgram = false;
	if (aPath[0] == '!')
	{
		ioRes->mPathStorage = aPath;
		ioRes->mPath = ioRes->mPathStorage.c_str();

		if (aPath == "!program")
			ioRes->mFromProgram = true;
	}
	else
	{
		ioRes->mPathStorage = aPath;
		ioRes->mPath = ioRes->mPathStorage.c_str();

		RES_HASH_TYPE aPathHash = RES_HASH_FUNC(Upper(ioRes->mPathStorage).c_str());
		mResFromPathMap[aPathHash] = ioRes;
	}

	std::string anId = mRtonReader->ReadString("id", "");

	if (anId.empty())
		anId = GetFileName(ioRes->mPath, true);

	if (inGroup->mArtRes != 0)
		anId = StrFormat("%s|%d", anId.c_str(), inGroup->mArtRes);

	if (inGroup->mLocSet != 0)
		anId = StrFormat("%s||%8x", anId.c_str(), inGroup->mLocSet);

	ioRes->mResGroup = inGroup;
	ioRes->mIdStorage = anId;
	ioRes->mId = ioRes->mIdStorage.c_str();
	ioRes->mArtRes = inGroup->mArtRes;
	ioRes->mLocSet = inGroup->mLocSet;

	RES_HASH_TYPE anIdHash = RES_HASH_FUNC(ioRes->mId);
	std::pair<ResourceInfoClass::ResMap::iterator, bool> aResult = inResType->mResMap.insert(std::pair<const RES_HASH_TYPE, ResourceInfo*>(anIdHash, ioRes));
	if (!aResult.second)
	{
		bool aFailed = Fail(StrFormat("Resource already defined: %s", aPath.c_str()));

		if (ioRes != NULL)
			delete ioRes;

		return aFailed;
	}

	inGroup->mResInfoVector.push_back(ioRes);
	return true;
}

bool ResourceManager::Fail(const std::string& theErrorText)
{
	OutputDebugStrF(theErrorText.c_str());
	if (mError.empty())
	{
		mError = theErrorText;
		if (mError.empty())
			mError = "Unknown error";
	}
	return false;
}

void ResourceManager::InitDelayLoadedRSBSlotCount()
{
	mDelayLoadedRSBSlotCount = GetAllDelayLoadedRSBSlotCount();
}

void ResourceManager::InitResourceGen(const ResGenInfo& theInfo)
{
	mResGenInfo = theInfo;
}

bool ResourceManager::IsDelayLoadRSB(const std::string& inRSBFileName)
{
	std::map<std::string, std::string>::iterator it;
	for (it = sDelayLoadedRSBs.begin(); it != sDelayLoadedRSBs.end(); ++it)
	{
		if (it->second == inRSBFileName)
			return true;
	}
	return false;
}

uint32 ResourceManager::GetAllDelayLoadedRSBSlotCount()
{
	uint32 aCount = 0;
	std::map<std::string, std::string>::iterator it;
	for (it = sDelayLoadedRSBs.begin(); it != sDelayLoadedRSBs.end(); ++it)
		aCount += ReadResourceFileSlotCount(it->second);
	return aCount;
}

void ResourceManager::ShowResourceError(bool doExit)
{
	OutputDebugStrF(GetErrorText().c_str());
	gSexyAppBase->Popup(GetErrorText());
	if (doExit && gSexyAppBase->mAppDriver)
		gSexyAppBase->mAppDriver->DoExit(0);
}

std::string ResourceManager::GetLocaleFolder(bool addTrailingSlash)
{
	if (mCurLocSet == 0)
		return "";

	std::string aFolder = StrFormat("locales/%c%c-%c%c", mCurLocSet >> 24, (mCurLocSet >> 16) & 0xff, (mCurLocSet >> 8) & 0xff, mCurLocSet & 0xff);
	if (addTrailingSlash)
		aFolder += '/';
	return aFolder;
}

bool ResourceManager::RemoveAllDelayLoadedRSBConfigFiles()
{
	bool aResult = false;
	std::map<std::string, std::string>::iterator it;
	for (it = sDelayLoadedRSBs.begin(); it != sDelayLoadedRSBs.end(); ++it)
	{
		if (gSexyAppBase->FileExists(it->second))
			aResult = gSexyAppBase->EraseFile(it->second);
	}
	return aResult;
}

void ResourceManager::RegisterResource(RtMixedPtrBase& outId, BaseResource* inRes)
{
	RegisterResourceInternal(&outId, inRes, RtId(), BaseResource::RRT_Ungrouped);
}

ResourceManager::GetImageOptions& ResourceManager::GetImageOptions::operator=(GetImageOptions&& theOther)
{
	mTestOnly = theOther.mTestOnly;
	mAllowTriReps = theOther.mAllowTriReps;
	mIsInAtlas = theOther.mIsInAtlas;
	mNoShare = theOther.mNoShare;
	mInfoId = theOther.mInfoId;
	mResGroup = theOther.mResGroup;
	mUseWidth = theOther.mUseWidth;
	mUseHeight = theOther.mUseHeight;
	mVariant = theOther.mVariant;
	return *this;
}

bool ResourceManager::ReplaceResource(ResourceInfoClass* theType, const std::string& theId, BaseResource* theRes)
{
	ResourceInfo* aResInfo = GetResInfoForStringId(theType, theId);
	if (aResInfo == NULL)
		return false;

	RtId anId = aResInfo->mInstanceRtId;
	aResInfo->DeleteResource();
	if (theRes != NULL)
	{
		aResInfo->mInstanceRtId = anId;
		RtDb::GetDb()->ReplaceObjectForId(anId, theRes);
		RtDb::GetDb()->SetObjectDeletionMode(anId, RtDbTable::ODM_Auto);
	}
	return true;
}

bool ResourceManager::LoadAllRsb()
{
	while (mPreLoadList.size() != 0)
	{
		PreLoadTask* aTask = *mPreLoadList.begin();
		mApp->mResStreamsManager->CreateRSBinLocalPath(mPhonePath, mSDCardPath, aTask->RSBFileName, aTask->RSBBuffer, i_phoneBlockFree, i_phoneBlockSize, i_sdcardBlockFree, i_sdcardBlockSize);
		mPreLoadList.pop_front();
	}
	return true;
}

bool ResourceManager::AddDLCRsb(const std::string& basePath, const std::string& inRSBFileName, const std::string& inManifestFileName)
{
	if (inManifestFileName.empty())
		return false;

	if (!inRSBFileName.empty())
	{
		ResStreamsManager* aStreamsManager = mApp->mResStreamsManager;
		if (aStreamsManager == NULL)
			return false;
		if (!aStreamsManager->AddDLCRSB(basePath, inRSBFileName, mPhonePath, mSDCardPath, false))
			return false;
	}
	return ParseResourcesFile(inManifestFileName);
}

void ResourceManager::OnInstanceTableObjectFault(const RtId& inId)
{
	ResourceInfo* aResInfo = RtWeakPtr<ResourceInfo>(RtId(RtDb::SYSTEMTABLE_ResourceInfo, inId.GetSlotIndex(), inId.GetRevision()));
	if (aResInfo != NULL && aResInfo->mResGroup != NULL && !aResInfo->mResGroup->mIsLoaded)
	{
		ResourceGroup* aGroup = aResInfo->mResGroup;
		std::string aResId = aResInfo->GetCoreIdString();
		aGroup->GetLoadableGroup()->Load();
	}
}

void ResourceManager::SetSoundBankInvaild()
{
	ResourceInfoClass::ResMap aResMap = RTC(ResourceInfoTypes::SoundBankRes)->mResMap;
	for (ResourceInfoClass::ResMap::iterator anItr = aResMap.begin(); anItr != aResMap.end(); ++anItr)
	{
		if (anItr->second == NULL)
			continue;

		ResourceInfoTypes::SoundBankRes* aSoundBankRes = anItr->second->Cast<ResourceInfoTypes::SoundBankRes>();
		if (aSoundBankRes == NULL)
			continue;

		if (aSoundBankRes->IsResourceValid())
			aSoundBankRes->GetSoundBank()->SetBankError();
	}
}

void ResourceManager::RemoveUngroupedSharedImage(Image* inImage)
{
	AutoCrit anAutoCrit(gSexyAppBase->mCritSect);
	std::string aUpperPath = StringToUpper(inImage->mFilePath);
	std::pair<std::string, std::string> aKey(aUpperPath, "");
	SharedImageMap::iterator anItr = mUngroupedSharedImageMap.find(aKey);
	if (anItr != mUngroupedSharedImageMap.end())
		mUngroupedSharedImageMap.erase(anItr);
	else
		OutputDebugStrF("ResourceManager::RemoveUngroupedSharedImage: Image not found in ungrouped image map: %s\n", aUpperPath.c_str());
}

void ResourceManager::PrepareLoadResourcesList(const char** theGroups)
{
	ResStreamsManager* aStreamsManager = mApp->mResStreamsManager;
	if (aStreamsManager == NULL)
		return;

	if (!aStreamsManager->IsInitialized("dynamic.rsb"))
		return;

	const char* aGroupName = *theGroups++;
	while (aGroupName != NULL)
	{
		uint32 aGroupIndex = mApp->mResStreamsManager->LookupGroup(aGroupName);
		if (aGroupIndex != 0xFFFFFFFF)
			mApp->mResStreamsManager->LoadGroup(aGroupIndex);
		aGroupName = *theGroups++;
	}
}

RtWeakPtr<BaseResource> ResourceManager::LoadResourceForStringId(ResourceInfoClass* theType, const std::string& theId)
{
	AutoCrit anAutoCrit(mLoadCrit);
	ResourceInfo* aResInfo = GetResInfoForStringId(theType, theId);
	if (aResInfo == NULL || aResInfo->mFromProgram)
		return RtWeakPtr<BaseResource>(RtId());

	if (aResInfo->IsResourceValid())
		return RtWeakPtr<BaseResource>(aResInfo->GetInstanceRtId());

	ResourceGroup* aGroup = aResInfo->mResGroup;
	if (aGroup != NULL && !aGroup->mIsLoaded)
	{
		std::string aCoreId = aResInfo->GetCoreIdString();
		aGroup->GetLoadableGroup()->Load();
	}

	return RtWeakPtr<BaseResource>(aResInfo->IsResourceValid() ? aResInfo->GetInstanceRtId() : RtId());
}

ResourceInfo* ResourceManager::GetResInfoForPath(ResourceInfoClass* theType, const std::string& thePath)
{
	std::string aPath = Upper(thePath);
	int aLen = (int)aPath.length();
	for (int i = 0; i < aLen; i++)
	{
		if (aPath[i] == '/')
			aPath[i] = '\\';
	}

	uint64 aHash = RES_HASH_FUNC(aPath.c_str());
	ResourceInfoClass::ResMap::iterator anItr = mResFromPathMap.find(aHash);
	ResourceInfoClass::ResMap::iterator anEnd = mResFromPathMap.end();
	if (anItr != anEnd)
	{
		ResourceInfo* aResInfo = anItr->second;
		if (theType == NULL || aResInfo->IsA(theType))
			return aResInfo;
	}

	return NULL;
}

float ResourceManager::GetLoadResourcesListProgress(const std::vector<std::string>& theGroups)
{
	ResStreamsManager* aStreamsManager = mApp->mResStreamsManager;
	if (aStreamsManager != NULL && aStreamsManager->IsInitialized("dynamic.rsb"))
	{
		uint32 aTotalBytes = 0;
		uint32 aBytesLoaded = 0;
		for (size_t i = 0; i < theGroups.size(); i++)
		{
			uint32 aGroupIndex = mApp->mResStreamsManager->LookupGroup(theGroups[i]);
			if (aGroupIndex != 0xFFFFFFFF)
			{
				aBytesLoaded += mApp->mResStreamsManager->GetBytesLoadedForGroup(aGroupIndex);
				aTotalBytes += mApp->mResStreamsManager->GetTotalBytesForGroup(aGroupIndex);
			}
		}
		return (float)((double)aBytesLoaded / (double)aTotalBytes);
	}
	return 0.0f;
}

uint32 ResourceManager::GetLocaleSetForLocaleName(const std::string& theLocaleName)
{
	std::string aLanguage = theLocaleName.substr(0, 2);
	if (aLanguage == "en")
		return 'ENUS';
	if (aLanguage == "fr")
		return 'FRFR';
	if (aLanguage == "es")
		return 'ESES';
	if (aLanguage == "it")
		return 'ITIT';
	if (aLanguage == "de")
		return 'DEDE';
	if (aLanguage == "pt")
		return 'PTBR';
	if (aLanguage == "zh")
		return 'ZHCN';
	return 'ENUS';
}

bool ResourceManager::InitForDecompressRsbFile(int inBaseArtRes, int inCurArtRes, const std::string& inRSBFileName, const std::string& inManifestFileName, bool canIgnore)
{
	bool aResult = false;
	if (!inManifestFileName.empty())
	{
		mBaseArtRes = inBaseArtRes;
		mCurArtRes = inCurArtRes;

		bool aNoRSB = inRSBFileName.empty();
		aResult = aNoRSB;
		if (!aNoRSB && mApp->mResStreamsManager != NULL)
		{
			std::string aBasePath = mApp->mFileDriver->GetLoadDataPath();
			std::string aTarRsbPath = "";
			aResult = mApp->mResStreamsManager->DecompressRsbFile(aBasePath, inRSBFileName, mPhonePath, mSDCardPath, canIgnore, aTarRsbPath);
			if (!aResult)
				aResult = aNoRSB;
		}
	}
	return aResult;
}

void ResourceManager::PreLoadRsb(const std::string& inRSBFileName)
{
	PreLoadTask* aTask = new PreLoadTask();
	aTask->RSBFileName = inRSBFileName;
	aTask->RSBBuffer = new Buffer();

	std::string aLoadPath = mApp->mFileDriver->GetLoadDataPath();
	std::string aPath = aLoadPath + inRSBFileName;
	gSexyAppBase->ReadBufferFromFile(aPath, aTask->RSBBuffer, false);
	if (aTask->RSBBuffer->GetDataLen() <= 0)
	{
		delete aTask->RSBBuffer;
		aTask->RSBBuffer = NULL;
		delete aTask;
		aTask = NULL;
		return;
	}

	if (aTask->RSBBuffer != NULL)
		mPreLoadList.push_back(aTask);
}

bool ResourceManager::ResizeTables(uint32 iAdvancedSlotCount, const std::string& theFilename)
{
	if (GetDelayLoadedRSBSlotCount() != 0)
	{
		if (IsDelayLoadRSB(theFilename))
			return true;
	}

	uint32 aSlotIndex = mInfoTable->GetTableOptions()->mInitialSlotCount;
	mInfoTable->ResizeTable(iAdvancedSlotCount, theFilename);
	mHiddenInfoTable->ResizeTable(iAdvancedSlotCount, theFilename);
	mInstanceTable->ResizeTable(iAdvancedSlotCount, theFilename);

	if (GetDelayLoadedRSBSlotCount() != 0 && theFilename == GetLastNonDelayLoadRSBManifestName())
		iAdvancedSlotCount += mDelayLoadedRSBSlotCount;	uint32 aEndIndex = aSlotIndex + iAdvancedSlotCount;
	if (aSlotIndex < aEndIndex)
	{
		do
		{
		aSlotIndex++;
		RtId anInfoId = mInfoTable->AllocId(NULL, RtDbTable::ODM_Auto, true, NULL);
		anInfoId = mInstanceTable->AllocId(NULL, RtDbTable::ODM_Auto, true, NULL);
		mInstanceTable->SetObjectIsWatched(anInfoId, true);
		} while (aSlotIndex < aEndIndex);
	}
	return true;
}

void ResourceManager::Clear()
{
	for (RtDbTable::Iterator anItr(mResGroupTable); anItr; ++anItr)
	{
		ResourceGroup* aGroup = RtWeakPtr<ResourceGroup>(*anItr);
		if (aGroup != NULL && aGroup->IsLoadableGroup())
		{
			if (aGroup->IsFileIndexLoaded())
				aGroup->UnloadFileIndex();

			if (aGroup->IsLoaded())
				aGroup->Unload();
		}
	}

	int aCount = (int)mResInfoClasses.size();
	for (int i = 0; i < aCount; i++)
		mResInfoClasses[i]->mResMap.clear();

	if (mApp->mResStreamsManager != NULL)
		mApp->mResStreamsManager->Clear();

	mResFromPathMap.clear();
	mUngroupedSharedImageMap.clear();
}

bool ResourceManager::Init(int inBaseArtRes, int inCurArtRes, const std::string& inRSBFileName, const std::string& inManifestFileName, bool canIgnore)
{
	if (inManifestFileName.empty())
	{
		Fail("ResourceManager::Init: Manifest file name is empty; please supply relative path to resources RTON file.");
		ShowResourceError(true);
		return false;
	}

	mBaseArtRes = inBaseArtRes;
	mCurArtRes = inCurArtRes;

	if (!inRSBFileName.empty())
	{
		if (mApp->mResStreamsManager == NULL)
		{
			Fail("ResourceManager::Init: RSB path provided but ResStreamsManager does not exist");
			ShowResourceError(true);
			return false;
		}

		if (!mApp->mResStreamsManager->InitializeWithRSB(inRSBFileName, mPhonePath, mSDCardPath, canIgnore))
		{
			Fail("ResourceManager::Init: RSB Initialization failed");
			if (canIgnore)
				return false;

			ShowResourceError(true);
			return false;
		}
	}

	SexyTime();
	if (!ParseResourcesFile(inManifestFileName))
	{
		ShowResourceError(true);
		return false;
	}
	return true;
}

bool ResourceManager::AddRsb(const std::string& basePath, const std::string& inRSBFileName, const std::string& inManifestFileName)
{
	if (inManifestFileName.empty())
	{
		Fail("ResourceManager::Init: Manifest file name is empty; please supply relative path to resources RTON file.");
		ShowResourceError(true);
		return false;
	}

	uint8 aResult = inRSBFileName.empty();
	if (!aResult)
	{
		if (mApp->mResStreamsManager == NULL)
		{
			Fail("ResourceManager::Init: RSB path provided but ResStreamsManager does not exist");
			ShowResourceError(true);
			return false;
		}

		aResult = mApp->mResStreamsManager->AddRSB(basePath, inRSBFileName, mPhonePath, mSDCardPath, aResult);
		if (!aResult)
		{
			Fail("ResourceManager::Init: RSB Initialization failed");
			ShowResourceError(true);
			return false;
		}
	}

	SexyTime();
	aResult = ParseResourcesFile(inManifestFileName);
	if (!aResult)
		ShowResourceError(true);
	return aResult;
}

uint32 ResourceManager::ReadResourceFileSlotCount(const std::string& theFilename)
{
	RtSerialBuffer* aBuffer = gSexyAppBase->CreateReadBufferFromFile(theFilename, true);
	if (aBuffer == NULL)
	{
		OutputDebugStrF("ResourceManager::ParseResourcesFile: Failed ReadBuffer from [%s]", theFilename.c_str());
		Fail("Unable to read resource file: " + theFilename);
		return 0;
	}

	mRtonReader = new RtSerialRtonReader(aBuffer->GetDataPtr(), aBuffer->GetDataSize());
	if (!mRtonReader->BeginDocumentObject())
	{
		Fail("Invalid document object in resource file: " + theFilename);
		delete mRtonReader;
		mRtonReader = NULL;
		delete aBuffer;
		return 0;
	}

	uint32 aSlotCount = mRtonReader->ReadInt32("slot_count", 0);
	delete aBuffer;
	mRtonReader->EndDocumentObject();
	delete mRtonReader;
	mRtonReader = NULL;
	return aSlotCount;
}

RtWeakPtr<BaseResource> ResourceManager::GetResourceForStringId(ResourceInfoClass* theType, const std::string& theId, bool optional)
{
	ResourceInfo* aResInfo;
	const char* aTypeName;
	int i;

	if (gSexyAppBase->mShutdown || theId.empty())
		goto Empty;

	if (theType == NULL)
	{
		i = 0;
		do
		{
			if (i >= (int)mResInfoClasses.size())
			{
				if (optional)
					goto Empty;
				aTypeName = "Unknown-type";
				goto NotFound;
			}
			aResInfo = GetResInfoForStringId(mResInfoClasses[i], theId);
			i++;
		} while (aResInfo == NULL);

		if (!optional)
			goto Check;
	}
	else
	{
		aResInfo = GetResInfoForStringId(theType, theId);
		if (!optional)
		{
			if (aResInfo != NULL)
				goto Check;
			goto NamedNotFound;
		}
		if (aResInfo == NULL)
			goto Empty;
	}
	return RtWeakPtr<BaseResource>(aResInfo->GetInstanceRtId());

Check:
	{
		RtWeakPtr<BaseResource> aResource = aResInfo->GetInstanceRtId();
		if (aResource)
			return RtWeakPtr<BaseResource>(aResource.GetId());
	}
	if (theType == NULL)
	{
		aTypeName = "Unknown-type";
		goto NotFound;
	}

NamedNotFound:
	aTypeName = theType->GetName();

NotFound:
	Fail(StrFormat("%s resource not found: %s", aTypeName, theId.c_str()));

Empty:
	return RtWeakPtr<BaseResource>(RtId());
}

int ResourceManager::GetResourceCount(ResourceInfoClass* theType, bool curArtResOnly, bool curLocSetOnly)
{
	int aCount = 0;
	if (theType == NULL)
	{
		for (int i = 0; i < (int)mResInfoClasses.size(); i++)
			aCount += GetResourceCount(mResInfoClasses[i], curArtResOnly, curLocSetOnly);
		return aCount;
	}

	ResourceInfoClass::ResMap& aMap = theType->mResMap;
	if (!curArtResOnly && !curLocSetOnly)
		return (int)aMap.size();

	for (ResourceInfoClass::ResMap::iterator anItr = aMap.begin(); anItr != aMap.end(); ++anItr)
	{
		ResourceInfo* aResInfo = anItr->second;
		if (curArtResOnly && aResInfo->mArtRes != 0 && aResInfo->mArtRes != mCurArtRes)
			continue;
		if (curLocSetOnly && aResInfo->mLocSet != 0 && aResInfo->mLocSet != mCurLocSet)
			continue;
		if (!aResInfo->mFromProgram)
			aCount++;
	}
	return aCount;
}

RtId ResourceManager::RegisterResourceInternal(RtMixedPtrBase* outId, BaseResource* inRes, const RtId& inInfoId, BaseResource::EResourceRegistrationType inType)
{
	if (outId != NULL)
		outId->SetId(RtId(), false);

	if (inRes != NULL)
	{
		bool aIsRegistered = inRes->GetRtId();
		if (!aIsRegistered)
		{
			if (inType == BaseResource::RRT_Ungrouped)
			{
				RtId anId = RtDb::GetDb()->AllocId(RtDb::SYSTEMTABLE_ResourceInstancesUngrouped, inRes, RtDbTable::ODM_Auto, true, NULL);
				inRes->mResourceRtId = anId;
				inRes->mInfoRtId = RtId();
				if (outId != NULL)
				{
					outId->SetId(anId, true);
					outId->Possess();
				}
				return anId;
			}
			if (inType == BaseResource::RRT_Normal)
			{
				RtId anId(RtDb::SYSTEMTABLE_ResourceInstances, inInfoId.GetSlotIndex(), inInfoId.GetRevision());
				RtDb::GetDb()->ReplaceObjectForId(anId, inRes);
				RtDb::GetDb()->SetObjectDeletionMode(anId, RtDbTable::ODM_Auto);
				inRes->mResourceRtId = anId;
				inRes->mInfoRtId = inInfoId;
				if (outId != NULL)
					outId->SetId(anId, aIsRegistered);
				return anId;
			}
			if (inType == BaseResource::RRT_Hidden)
			{
				RtId anId = RtDb::GetDb()->AllocId(RtDb::SYSTEMTABLE_ResourceInstancesHidden, inRes, RtDbTable::ODM_Auto, true, NULL);
				inRes->mResourceRtId = anId;
				inRes->mInfoRtId = inInfoId;
				if (outId != NULL)
					outId->SetId(anId, aIsRegistered);
				return anId;
			}
		}
	}

	return RtId();
}
