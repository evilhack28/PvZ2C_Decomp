//
//  ResourceManager.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-27.
//

#include "ResourceManager.h"

using namespace Sexy;

ResourceGroup* ResourceManager::GetResourceGroupNamed(const RtName& inName)
{
	RtId anId = mResGroupTable->GetIdForAlias(inName);
	RtWeakPtr<ResourceGroup> aGroup(anId);
	return aGroup;
}

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
