//
//  DeviceImage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "DeviceImage.h"
#include "MemoryImage.h"
#include "IGraphicsDriver.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DeviceImage);

void DeviceImage::AdditiveDrawLineAA(double i_arg0, double i_arg1, double i_arg2, double i_arg3, const Color& i_arg4)
{
}

bool DeviceImage::Palletize()
{
	return false;
}

void DeviceImage::Init()
{
	mSurface = NULL;
	if (mDriver)
		mDriver->AddDeviceImage(this);
	mpCachedImageDrawInfo = NULL;
	mNoLock = false;
	mWantDeviceSurface = false;
	mDrawToBits = false;
	mSurfaceSet = false;
	mLockCount = 0;
	mScalePercent = 1.0f;
}
