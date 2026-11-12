//
//  AndroidGraphicsDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-07.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidRenderDeviceES20.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ImageLib/ImageLib.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGraphicsDriver.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGL20RenderDevice.h"
#include "SexyAppFramework/drivers/app/android/AndroidAppDriver.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/AutoCrit.h"
#include "SexyAppFramework/Mesh.h"
#include "SexyAppFramework/Ratio.h"
#include "SexyAppFramework/DeviceImage.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

AndroidGraphicsDriver::AndroidGraphicsDriver(AndroidAppDriver* theAppDriver, SexyAppBase* theApp)
{
	mRenderDeviceES11 = NULL;
	mRenderDeviceES20 = NULL;
	if (Android::Graphics::IsOpenGLES20(theAppDriver))
		mRenderDeviceES20 = CreateGL20RenderDevice(this);
	mApp = theApp;
	mWidth = 0;
	mHeight = 0;
	mScreenWidth = 0;
	mScreenHeight = 0;
	mAppDriver = theAppDriver;
	mScreenImage = NULL;
	mScreenImageForSwaps = NULL;
	mCursorX = 0;
	mCursorY = 0;
}

AndroidGraphicsDriver::~AndroidGraphicsDriver()
{
}

void AndroidGraphicsDriver::Init(UI_ORIENTATION theOrientation)
{
}

void AndroidGraphicsDriver::ReinitForSurfaceChange(UI_ORIENTATION theOrientation, int iNewWidth, int iNewHeight, bool bForceReinit)
{
	Android::Graphics::GetScreenSizeInPoints(&mScreenWidth, &mScreenHeight);
	if (!bForceReinit && mWidth == iNewWidth && mHeight == iNewHeight)
	{
		OutputDebugStrF("SKIP ReinitForSurfaceChange");
		return;
	}
	OutputDebugStrF("ACTUALLY DO ReinitForSurfaceChange");

	int aWidth;
	int aHeight;
	if (theOrientation == UI_ORIENTATION_LANDSCAPE_RIGHT || theOrientation == UI_ORIENTATION_LANDSCAPE_LEFT)
	{
		aWidth = std::max(mApp->mWidth, mApp->mHeight);
		aHeight = std::min(mApp->mWidth, mApp->mHeight);
	}
	else if (theOrientation == UI_ORIENTATION_PORTRAIT || theOrientation == UI_ORIENTATION_PORTRAIT_UPSIDE_DOWN)
	{
		aWidth = std::min(mApp->mWidth, mApp->mHeight);
		aHeight = std::max(mApp->mWidth, mApp->mHeight);
	}

	if (Android::Graphics::CanSetGLViewScaleFactor(mAppDriver))
	{
		float aScale;
		if (abs(mScreenWidth - aWidth) > abs(mScreenHeight - aHeight))
			aScale = (float)aWidth / mScreenWidth;
		else
			aScale = (float)aHeight / mScreenHeight;
		int aScaledHeight = (int)(aScale * mScreenHeight);
		int aScaledWidth = (int)(aScale * mScreenWidth);
		if (aScaledWidth < aWidth || aScaledHeight < aHeight)
		{
			if (aWidth - aScaledWidth > aHeight - aScaledHeight)
				aScale *= (float)aWidth / aScaledWidth;
			else
				aScale *= (float)aHeight / aScaledHeight;
		}
		Android::Graphics::SetGLViewScaleFactor(mAppDriver, aScale);
	}

	mWidth = aWidth;
	mHeight = aHeight;
	mRenderModeFlags = 0;
	if (mRenderDeviceES20)
	{
		SetGL20RenderModeFlags(mRenderDeviceES20, GetRenderModeFlags());
		SetGL20FramebufferSize(mRenderDeviceES20, iNewWidth, iNewHeight);
	}
	Android::Graphics::SetGLViewContext(mAppDriver);
	if (mRenderDeviceES20)
		SetGL20RenderTargetImage(mRenderDeviceES20, NULL);

	if (mScreenImage)
	{
		mAppDriver->Remove3DData(mScreenImage);
		delete mScreenImage;
		mScreenImage = NULL;
	}
	if (mScreenImageForSwaps)
	{
		mAppDriver->Remove3DData(mScreenImageForSwaps);
		delete mScreenImageForSwaps;
		mScreenImageForSwaps = NULL;
	}

	mScreenImage = new DeviceImage(mApp);
	mScreenImage->AddImageFlags(ImageFlag_RenderTarget);
	mScreenImage->mBits = NULL;
	mScreenImage->mWidth = mWidth;
	mScreenImage->mHeight = mHeight;
	mScreenImage->SetImageMode(false, false);

	mScreenImageForSwaps = NULL;
	if (!mRenderDeviceES11 && mAppDriver->mApp->mAllowSwapScreenImage)
	{
		mScreenImageForSwaps = new DeviceImage(mApp);
		mScreenImageForSwaps->AddImageFlags(ImageFlag_RenderTarget);
		mScreenImageForSwaps->mBits = NULL;
		mScreenImageForSwaps->mWidth = mWidth;
		mScreenImageForSwaps->mHeight = mHeight;
		mScreenImageForSwaps->SetImageMode(false, false);
		mScreenImageForSwaps->CreateRenderData();
	}

	if (mRenderDeviceES20)
		SetGL20BackbufferImages(mAppDriver, mRenderDeviceES20, mScreenImage, mScreenImageForSwaps);
}

/////////////// Accessors ///////////////

bool AndroidGraphicsDriver::Is3D()
{
	return true;
}

int AndroidGraphicsDriver::GetVersion()
{
	return 0;
}

uint32 AndroidGraphicsDriver::GetRenderModeFlags()
{
	return mRenderModeFlags;
}

void AndroidGraphicsDriver::SetRenderModeFlags(uint32 inRenderModeFlags)
{
	mRenderModeFlags = inRenderModeFlags;
}

IGraphicsDriver::ERenderMode AndroidGraphicsDriver::GetRenderMode()
{
	return mRenderMode;
}

void AndroidGraphicsDriver::SetRenderMode(ERenderMode inRenderMode)
{
	mRenderMode = inRenderMode;
}

std::string AndroidGraphicsDriver::GetRenderModeString(ERenderMode inRenderMode, uint32 inRenderModeFlags, bool inIgnoreMode, bool inIgnoreFlags)
{
	return "";
}

NativeDisplay* AndroidGraphicsDriver::GetNativeDisplayInfo()
{
	return this;
}

RenderDevice* AndroidGraphicsDriver::GetRenderDevice()
{
	if (mRenderDeviceES20)
		return mRenderDeviceES20;
	return mRenderDeviceES11;
}

RenderDevice3D* AndroidGraphicsDriver::GetRenderDevice3D()
{
	if (mRenderDeviceES20)
		return mRenderDeviceES20;
	return mRenderDeviceES11;
}

Ratio AndroidGraphicsDriver::GetAspectRatio()
{
	return Ratio(0, 1);
}

int AndroidGraphicsDriver::GetDisplayWidth()
{
	return 0;
}

int AndroidGraphicsDriver::GetDisplayHeight()
{
	return 0;
}

CritSect& AndroidGraphicsDriver::GetCritSect()
{
	return mCritSect;
}

DeviceImage* AndroidGraphicsDriver::GetScreenImage()
{
	if (mRenderDeviceES11)
		return mScreenImage;
	return GetGL20ScreenImage(mRenderDeviceES20);
}

/////////////// Images ///////////////

void AndroidGraphicsDriver::AddDeviceImage(DeviceImage* theDDImage)
{
}

void AndroidGraphicsDriver::RemoveDeviceImage(DeviceImage* theDDImage)
{
}

void AndroidGraphicsDriver::Remove3DData(MemoryImage* theImage)
{
	if (mRenderDeviceES20)
		mRenderDeviceES20->RemoveImageRenderData(theImage);
	else
		mRenderDeviceES11->RemoveImageRenderData(theImage);
}

DeviceImage* AndroidGraphicsDriver::GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps)
{
	if (mRenderDeviceES20)
		return GetGL20OptimizedImage(mRenderDeviceES20, theFileName, commitBits, allowTriReps);
	return NULL;
}

DeviceImage* AndroidGraphicsDriver::GetOptimizedImage(ImageLib::Image* image, bool commitBits, bool allowTriReps, bool shouldDeleteSrcImage)
{
	if (mRenderDeviceES20)
		return GetGL20OptimizedImage(mRenderDeviceES20, image, commitBits, allowTriReps, shouldDeleteSrcImage);
	return NULL;
}

DeviceImage* AndroidGraphicsDriver::GetImageFromResStream(const std::string& theFileName, void* theTextureData, ResStreamFileGPULocationInfo* locationInfo)
{
	if (mRenderDeviceES20)
		return GetGL20ImageFromResStream(mRenderDeviceES20, theFileName, theTextureData, locationInfo);
	return NULL;
}

void AndroidGraphicsDriver::DetermineScreenImageType()
{
	if (mRenderDeviceES20)
	{
		SetGL20BackbufferImages(mAppDriver, mRenderDeviceES20, mScreenImage, mScreenImageForSwaps);
		mApp->mWidgetManager->mImage = GetScreenImage();
	}
}

/////////////// Drawing ///////////////

void AndroidGraphicsDriver::WindowResize(int theWidth, int theHeight)
{
}

bool AndroidGraphicsDriver::Redraw(Rect* theClipRect)
{
	if (mRenderDeviceES20)
	{
		mRenderDeviceES20->Flush();
		SetGL20RenderTargetFBO(mRenderDeviceES20, 0);
		DeviceImage* aScreenImage = GetGL20ScreenImage(mRenderDeviceES20);
		if (mScreenImageForSwaps == aScreenImage)
			GL20BltSwapScreen(mRenderDeviceES20, mScreenImageForSwaps, 0, 0, mScreenImageForSwaps->mWidth, mScreenImageForSwaps->mHeight);
	}
	if (mRenderDeviceES20)
		mRenderDeviceES20->Flush();
	else
		mRenderDeviceES11->Flush();
	return true;
}

void AndroidGraphicsDriver::ClearBuffers()
{
	if (mRenderDeviceES20)
	{
		mRenderDeviceES20->ClearColorBuffer();
		mRenderDeviceES20->ClearDepthBuffer();
	}
	else
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void AndroidGraphicsDriver::RemapMouse(int& theX, int& theY)
{
}

bool AndroidGraphicsDriver::SetCursorImage(Image* theImage)
{
	return true;
}

void AndroidGraphicsDriver::SetCursorPos(int theCursorX, int theCursorY)
{
}

void AndroidGraphicsDriver::SetRotationForDeviceOrientation(float theRot)
{
}

/////////////// Shaders and meshes ///////////////

void AndroidGraphicsDriver::RemoveShader(const void* theShader)
{
}

RenderEffectDefinition* AndroidGraphicsDriver::CreateRenderEffectDefinition(uint32 theDataLen, const void* theData, const char* theSrc)
{
	return NULL;
}

DeviceSurface* AndroidGraphicsDriver::CreateDeviceSurface()
{
	return NULL;
}

Mesh* AndroidGraphicsDriver::LoadMesh(const std::string& thePath, MeshListener* theListener)
{
	AutoCrit aAutoCrit(mCritSect);
	Mesh* aMesh = new Mesh();
	aMesh->mListener = theListener;
	aMesh->mFileName = thePath;
	if (mRenderDeviceES20)
	{
		if (!mRenderDeviceES20->LoadMesh(aMesh))
		{
			delete aMesh;
			return NULL;
		}
	}
	else if (mRenderDeviceES11)
	{
		if (!mRenderDeviceES11->LoadMesh(aMesh))
		{
			delete aMesh;
			return NULL;
		}
	}
	return aMesh;
}

void AndroidGraphicsDriver::AddMesh(Mesh* theMesh)
{
}

void AndroidGraphicsDriver::RemoveMesh(Mesh* theMesh)
{
}
