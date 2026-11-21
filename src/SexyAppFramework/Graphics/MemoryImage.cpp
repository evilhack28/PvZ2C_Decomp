//
//  MemoryImage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "AtlasedImageStore.h"
#include "Graphics.h"
#include "MemoryImage.h"
#include "RenderDevice.h"
#include "SexyAppBase.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MemoryImage);

void MemoryImage::AdditiveDrawLineAA(double i_arg0, double i_arg1, double i_arg2, double i_arg3, const Color& i_arg4)
{
}

void MemoryImage::Init()
{
	mBits = NULL;
	mColorTable = NULL;
	mColorIndices = NULL;
	mNativeAlphaData = NULL;
	mRLAlphaData = NULL;
	mRLAdditiveData = NULL;
	mHasTrans = false;
	mHasAlpha = false;
	mBitsChanged = false;
	mForcedMode = false;
	mIsVolatile = false;
	mBitsChangedCount = 0;
	mPurgeBits = false;
	mWantPal = false;
	mDither16 = false;
	mApp->AddMemoryImage(this);
}
