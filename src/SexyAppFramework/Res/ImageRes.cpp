//
//  ImageRes.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/DeviceImage.h"
#include "ReflectionBuilder.h"

using namespace Sexy;
using namespace Sexy::ResourceInfoTypes;

/////////////// Load ///////////////

bool ImageRes::StaticPreCreateFilter(ResourceManager* theManager)
{
	if (theManager->mRtonReader->ReadStringDirect("id") == NULL)
		return false;

	uint32 aPathCount = 0;
	if (!theManager->mRtonReader->BeginArray("path", aPathCount))
		return false;

	theManager->mRtonReader->EndArray();
	return true;
}

void ImageRes::ApplyConfig()
{
	if (mSrcRefResInfo)
		return;
	if (!mInstanceRtId)
		return;
	DeviceImage* anImage = GetImage()->Cast<DeviceImage>();
	if (anImage == NULL)
		return;
	anImage->ReplaceImageFlags(0);
	if (mNoTriRep)
		anImage->AddImageFlags(ImageFlag_NoTriRep);

	anImage->mNumRows = mRows;
	anImage->mNumCols = mCols;
	if (mDither16)
		anImage->mDither16 = true;

	if (mA4R4G4B4)
		anImage->AddImageFlags(ImageFlag_UseA4R4G4B4);
	if (mA8R8G8B8)
		anImage->AddImageFlags(ImageFlag_UseA8R8G8B8);

	anImage->AddImageFlags(ImageFlag_MinimizeNumSubdivisions);
	if (mIsAtlas)
		anImage->AddImageFlags(ImageFlag_Atlas | ImageFlag_MinimizeNumSubdivisions);

	bool anAtlasNameEmpty = mAtlasNameStorage.empty();
	if (!anAtlasNameEmpty)
	{
		anImage->mAtlasImage = mManager->GetResourceForStringIdT<Image>(mAtlasNameStorage.c_str(), anAtlasNameEmpty);
		anImage->mAtlasStartX = mAtlasX;
		anImage->mAtlasStartY = mAtlasY;
		anImage->mAtlasEndX = mAtlasX + (int)ceilf(mAtlasW * anImage->mAtlasImage->Cast<DeviceImage>()->mScalePercent);
		anImage->mAtlasEndY = mAtlasY + (int)ceilf(mAtlasH * anImage->mAtlasImage->Cast<DeviceImage>()->mScalePercent);
	}

	anImage->CommitBits();
	anImage->mPurgeBits = mPurgeBits;
	if (mPurgeBits)
	{
		AutoCrit aCrit(gSexyAppBase->mImageSetCritSect);
		anImage->PurgeBits();
	}
}

bool ImageRes::ParseRton()
{
	mA4R4G4B4 = mManager->mRtonReader->ReadBool("a4r4g4b4", false);
	mPurgeBits = mManager->mRtonReader->ReadBool("nobits", false);
	if (mPurgeBits && !mManager->mApp->Is3DAccelerated())
		mPurgeBits = false;

	mA8R8G8B8 = mManager->mRtonReader->ReadBool("a8r8g8b8", false);
	mDither16 = mManager->mRtonReader->ReadBool("dither16", false);
	bool aCubeMap = mManager->mRtonReader->ReadBool("cubemap", false);
	bool aVolumeMap = mManager->mRtonReader->ReadBool("volumemap", false);
	mNoTriRep = mManager->mRtonReader->ReadBool("notrirep", false);
	mIsAtlas = mManager->mRtonReader->ReadBool("atlas", false);

	mOffset = Point(0, 0);
	int aX = mManager->mRtonReader->ReadInt32("x", 0x7fffffff);
	if (aX != 0x7fffffff)
		mOffset.mX = aX;
	int aY = mManager->mRtonReader->ReadInt32("y", 0x7fffffff);
	if (aY != 0x7fffffff)
		mOffset.mY = aY;

	std::string aVariant = mManager->mRtonReader->ReadString("variant", "");
	mRows = mManager->mRtonReader->ReadInt32("rows", 1);
	mCols = mManager->mRtonReader->ReadInt32("cols", 1);

	mAtlasH = 0;
	mAtlasW = 0;
	mAtlasY = 0;
	mAtlasX = 0;
	mAtlasNameStorage = mManager->mRtonReader->ReadString("parent", "");
	if (!mAtlasNameStorage.empty())
	{
		mAtlasX = mManager->mRtonReader->ReadInt32("ax", 0);
		mAtlasY = mManager->mRtonReader->ReadInt32("ay", 0);
		mAtlasW = mManager->mRtonReader->ReadInt32("aw", 0);
		mAtlasH = mManager->mRtonReader->ReadInt32("ah", 0);
	}

	if (aCubeMap)
	{
		if (mRows * mCols != 6)
		{
			mManager->Fail("Invalid CubeMap definition; must have 6 cells (check rows & cols values).");
			return false;
		}
	}
	else if (aVolumeMap)
	{
		int aCells = mRows * mCols;
		if (aCells == 0 || (aCells & (aCells - 1)))
		{
			mManager->Fail("Invalid VolumeMap definition; must have a pow2 cell count (check rows & cols values).");
			return false;
		}
	}

	return true;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ResourceInfoTypes::ImageRes);

void ImageRes::StaticClassInit()
{
	StaticGetClass()->SetInstanceClass(Image::StaticGetClass());
	StaticGetClass()->SetPreCreateFilterFunc(StaticPreCreateFilter);
	StaticGetClass()->SetManifestTypeName(RtName(L"Image"));
}
