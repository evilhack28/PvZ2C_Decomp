//
//  RenderEffectRes.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "ResourceManager.h"
#include "RenderEffect.h"
#include "ReflectionBuilder.h"

using namespace Sexy;

/////////////// Load ///////////////

bool ResourceInfoTypes::RenderEffectRes::DoLoad()
{
	AutoCrit aCrit(mManager->mLoadCrit);
	RenderEffectDefinition* aRes = new RenderEffectDefinition;
	if (!aRes->LoadFromFile(mPath, mSrcFilePath.c_str()))
	{
		mManager->Fail(std::string("RenderEffect loading error on file ") + mPath);
		delete aRes;
		return false;
	}
	mInstanceRtId = mManager->RegisterResourceInternal(NULL, aRes, GetRtId(), BaseResource::RRT_Normal);
	return true;
}

bool ResourceInfoTypes::RenderEffectRes::ParseRton()
{
	mSrcFilePath.clear();
	uint32 aCount = 0;
	if (mManager->mRtonReader->BeginArray("srcpath", aCount))
	{
		for (uint32 i = 0; i < aCount; i++)
		{
			if (!mSrcFilePath.empty())
				mSrcFilePath += "\\";
			mSrcFilePath += mManager->mRtonReader->ReadString(NULL, "");
		}
		mManager->mRtonReader->EndArray();
	}
	return true;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ResourceInfoTypes::RenderEffectRes);

void ResourceInfoTypes::RenderEffectRes::StaticClassInit()
{
	StaticGetClass()->SetInstanceClass(RenderEffectDefinition::StaticGetClass());
	StaticGetClass()->SetManifestTypeName(RtName(L"RenderEffect"));
}
