//
//  PopAnimRes.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/PopAnim.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "ReflectionBuilder.h"

using namespace Sexy;
using namespace Sexy::ResourceInfoTypes;

/////////////// Lifecycle ///////////////

PopAnimRes::PopAnimRes()
{
	mScale = 1.0;
	mRasterizedScale = 1.0;
}

/////////////// Load ///////////////

bool PopAnimRes::DoLoad()
{
	AutoCrit aCrit(mManager->mLoadCrit);
	PopAnim* aPopAnim = new PopAnim(0, NULL);
	double aScale = (double)mManager->mCurArtRes / (double)mManager->mBaseArtRes;
	float aDrawScale;
	if (IsNear(mRasterizedScale, mScale))
	{
		aDrawScale = aScale * mScale;
		aPopAnim->mImgScale = aScale;
	}
	else if (IsNear(mRasterizedScale, 1.0f))
	{
		aDrawScale = aScale * mScale;
		aPopAnim->mImgScale = aDrawScale;
	}
	else
	{
		aDrawScale = aScale * mScale;
		aPopAnim->mImgScale = aScale;
	}
	aPopAnim->mDrawScale = aDrawScale;
	aPopAnim->LoadFile(mPath);
	aPopAnim->mImgScale = aScale * mRasterizedScale;
	bool aOk = aPopAnim->mMainAnimDef->mError.empty();
	if (!aOk)
	{
		mManager->Fail("PopAnim loading error: " + aPopAnim->mMainAnimDef->mError + " on file " + mPath);
		delete aPopAnim;
	}
	else
	{
		mInstanceRtId = mManager->RegisterResourceInternal(NULL, aPopAnim, GetRtId(), BaseResource::RRT_Normal);
	}
	return aOk;
}

bool PopAnimRes::ParseRton()
{
	mScale = mManager->mRtonReader->ReadDouble(RtSerialRtonKey("scale"), 1.0);
	mRasterizedScale = mManager->mRtonReader->ReadDouble(RtSerialRtonKey("rasterizedScale"), 1.0);
	return true;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ResourceInfoTypes::PopAnimRes);

void PopAnimRes::StaticClassInit()
{
	StaticGetClass()->SetInstanceClass(PopAnim::StaticGetClass());
	StaticGetClass()->SetManifestTypeName(RtName(L"P"));
}
