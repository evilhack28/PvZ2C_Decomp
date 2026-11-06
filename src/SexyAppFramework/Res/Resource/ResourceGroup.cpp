//
//  ResourceGroup.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ResStreamsManager.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

ResourceGroup::ResourceGroup()
: mManager(NULL)
, mIsComposite(false)
, mIsLoaded(false)
, mArtRes(0)
, mLocSet(0)
, mParentGroup(NULL)
, mLoadPercent(0.0f)
, mIsFileIndexLoaded(false)
{
}

ResourceGroup::~ResourceGroup()
{
}

/////////////// Loading ///////////////

void ResourceGroup::Preload()
{
	ResStreamsManager* streamsManager = mManager->mApp->mResStreamsManager;
	if (streamsManager && streamsManager->IsInitialized("dynamic.rsb"))
		streamsManager->LoadGroup(WStringToString(mGroupName.GetString()));
}

bool ResourceGroup::LoadFileIndex()
{
	if (mIsLoaded || mIsFileIndexLoaded)
		return false;

	ResStreamsManager* streamsManager = mManager->mApp->mResStreamsManager;
	if (streamsManager && streamsManager->IsInitialized("dynamic.rsb"))
	{
		streamsManager->LoadGroupFileIndex(WStringToString(mGroupName.GetString()));
		mIsFileIndexLoaded = true;
	}

	for (unsigned int i = 0; i < mResInfoVector.size(); i++)
	{
		ResourceInfo* info = mResInfoVector[i];
		if (!info->mFromProgram && info->IsA<ResourceInfoTypes::SoundBankRes>())
			info->Cast<ResourceInfoTypes::SoundBankRes>()->DoPrepare();
	}
	return true;
}

bool ResourceGroup::UnloadFileIndex()
{
	if (!mIsFileIndexLoaded)
		return false;

	ResStreamsManager* streamsManager = mManager->mApp->mResStreamsManager;
	if (streamsManager && streamsManager->IsInitialized("dynamic.rsb"))
	{
		streamsManager->UnloadGroupFileIndex(WStringToString(mGroupName.GetString()));
		mIsFileIndexLoaded = false;
	}
	return true;
}

int ResourceGroup::GetResourceCount(ResourceInfoClass* theType, bool curArtResOnly, bool curLocSetOnly)
{
	if (theType == NULL)
	{
		int count = 0;
		uint32 classCount = mManager->GetInfoClassCount();
		for (uint32 i = 0; i < classCount; i++)
			count += GetResourceCount(mManager->GetInfoClassIndexed(i), curArtResOnly, curLocSetOnly);
		return count;
	}

	int count = 0;
	for (ResourceInfoClass::ResMap::iterator it = theType->mResMap.begin(); it != theType->mResMap.end(); ++it)
	{
		ResourceInfo* info = it->second;
		if (curArtResOnly && info->mArtRes != 0 && info->mArtRes != mManager->mCurArtRes)
			continue;
		if (curLocSetOnly && info->mLocSet != 0 && info->mLocSet != mManager->mCurLocSet)
			continue;
		if ((info->mResGroup == this || info->mResGroup->mParentGroup == this) && !info->mFromProgram)
			count++;
	}
	return count;
}

void ResourceGroup::GetResources(std::vector<ResourceInfo*>& outResourceInfoList, ResourceInfoClass* theType, bool curArtResOnly, bool curLocSetOnly)
{
	if (theType == NULL)
	{
		uint32 classCount = mManager->GetInfoClassCount();
		for (uint32 i = 0; i < classCount; i++)
			GetResources(outResourceInfoList, mManager->GetInfoClassIndexed(i), curArtResOnly, curLocSetOnly);
		return;
	}

	for (ResourceInfoClass::ResMap::iterator it = theType->mResMap.begin(); it != theType->mResMap.end(); ++it)
	{
		ResourceInfo* info = it->second;
		if (curArtResOnly && info->mArtRes != 0 && info->mArtRes != mManager->mCurArtRes)
			continue;
		if (curLocSetOnly && info->mLocSet != 0 && info->mLocSet != mManager->mCurLocSet)
			continue;
		if ((info->mResGroup == this || info->mResGroup->mParentGroup == this) && !info->mFromProgram)
			outResourceInfoList.push_back(info);
	}
}

bool ResourceGroup::Unload()
{
	bool wasLoaded = mIsLoaded;
	if (wasLoaded)
	{
		mManager->ClearError();
		std::vector<ResourceGroup*> groups;
		if (mIsComposite)
		{
			int subCount = mSubGroups.size();
			for (int i = 0; i < subCount; i++)
			{
				ResourceGroup* subGroup = mSubGroups[i];
				if (subGroup->mGroupName)
					groups.push_back(subGroup);
			}
		}
		else
			groups.push_back(this);

		unsigned int groupCount = groups.size();
		for (unsigned int i = 0; i < groupCount; i++)
		{
			ResourceGroup* group = groups[i];
			unsigned int n = group->mResInfoVector.size();
			for (unsigned int j = 0; j < n; j++)
				group->mResInfoVector[j]->DeleteResource();
		}

		ResStreamsManager* streamsManager = mManager->mApp->mResStreamsManager;
		if (streamsManager && streamsManager->IsInitialized("dynamic.rsb"))
			streamsManager->DeleteGroup(WStringToString(mGroupName.GetString()));

		for (unsigned int i = 0; i < groupCount; i++)
		{
			groups[i]->mIsLoaded = false;
			groups[i]->mSharedImageMap.clear();
		}
		if (mIsComposite)
		{
			mIsLoaded = false;
			mSharedImageMap.clear();
		}
	}
	return wasLoaded;
}

/////////////// Debug ///////////////

void ResourceGroup::DebugDump(std::string& theDestStr)
{
	theDestStr += StrFormat("ResourceGroup::DebugDump: Begin Group %S, ResInfoCount %d\r\n", mGroupName.GetString(), (int)mResInfoVector.size());

	for (ResInfoVector::const_iterator it = mResInfoVector.begin(); it != mResInfoVector.end(); ++it)
	{
		ResourceInfo* info = *it;
		std::string infoId;
		std::string instanceId;
		info->GetRtId().ToString(infoId, true);
		info->mInstanceRtId.ToString(instanceId, true);
		theDestStr += StrFormat("Info(%s) Inst(%s) %s %s: \"%s\"%s\r\n", infoId.c_str(), instanceId.c_str(), info->GetClass()->GetName(), info->mId, info->mPath, info->mFromProgram ? " (from program)" : "");
	}

	if (mIsComposite)
	{
		for (int i = 0; i < (int)mSubGroups.size(); i++)
			mSubGroups[i]->DebugDump(theDestStr);
	}

	theDestStr += StrFormat("ResourceGroup::DebugDump: End Group %S\r\n", mGroupName.GetString());
}

bool ResourceGroup::VerifyHasNoSoundBanks()
{
	for (unsigned int i = 0; i < mResInfoVector.size(); i++)
	{
		if (mResInfoVector[i]->IsA<ResourceInfoTypes::SoundBankRes>())
			return false;
	}
	return true;
}

/////////////// Reflection ///////////////
RT_CLASS_IMPLEMENT(ResourceGroup);
