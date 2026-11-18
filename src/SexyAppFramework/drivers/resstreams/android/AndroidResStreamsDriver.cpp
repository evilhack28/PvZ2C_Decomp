//
//  AndroidResStreamsDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/resstreams/android/AndroidResStreamsDriver.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGraphicsDriver.h"
#include "SexyAppFramework/DeviceImage.h"
#include "SexyAppFramework/SexyMath.h"
#include "SexyAppFramework/drivers/app/android/AndroidAppDriver.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include "SexyAppFramework/ResStreamsFormat.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyAppFramework/drivers/graphics/opengl/OpenGLIdRegistry.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

AndroidResStreamsDriver::AndroidResStreamsDriver()
{
}

AndroidResStreamsDriver::~AndroidResStreamsDriver()
{
}

bool AndroidResStreamsDriver::InitWithApp(SexyAppBase* theAppBase)
{
	bool aResult = BaseResStreamsDriver::InitWithApp(theAppBase);
	if (aResult)
		mGraphicsDriver = NULL;
	return aResult;
}

bool AndroidResStreamsDriver::AttachGraphicsDriver(IGraphicsDriver* theGraphicsDriver)
{
	mGraphicsDriver = (AndroidGraphicsDriver*)theGraphicsDriver;
	GetExtensionsSupported();
	return true;
}

DeviceImage* AndroidResStreamsDriver::GetImageFromResStream(std::string const theFileName, void* theTextureData, void* theTextureRefMulti_Unused, ResStreamFileGPULocationInfo* theLocationInfo, ResStreamTextureDescriptor* theTextureDesc)
{
	DeviceImage* anImage = mGraphicsDriver->GetImageFromResStream(theFileName, theTextureData, theLocationInfo);
	if (anImage != NULL)
	{
		if (theTextureDesc->format == RSB_TEXTURE_FORMAT_R5G6B5 || theTextureDesc->format == RSB_TEXTURE_FORMAT_R5G6B5_TILED)
		{
			anImage->mHasAlpha = false;
			anImage->mHasTrans = false;
		}
		anImage->mScalePercent = theTextureDesc->scalePercent * 0.01f;
	}
	return anImage;
}

bool AndroidResStreamsDriver::AllocatePool(ResStreamsPool* thePool)
{
	thePool->mResidentBuffer = (uint8*)memalign(128, thePool->mResidentDataSize * thePool->mNumInstances);
	uint8* aBuffer = thePool->mResidentBuffer;
	for (uint32 i = 0; i < thePool->mNumInstances; i++)
	{
		thePool->mInstances[i].mResidentData = aBuffer;
		thePool->mInstances[i].mGPUData = NULL;
		aBuffer += thePool->mResidentDataSize;
	}
	return true;
}

bool AndroidResStreamsDriver::DestroyPool(ResStreamsPool* thePool)
{
	if (thePool->mResidentBuffer != NULL)
	{
		free(thePool->mResidentBuffer);
		thePool->mResidentBuffer = NULL;
	}
	mGraphicsDriver->GetRenderDevice3D()->Flush(RenderDevice3D::FLUSHF_BufferedState);
	mGraphicsDriver->GetRenderDevice3D()->SetTexture(0, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	for (uint32 i = 0; i < thePool->mNumInstances; i++)
	{
		thePool->mInstances[i].mResidentData = NULL;
		thePool->mInstances[i].mGPUData = NULL;
	}
	return true;
}

bool AndroidResStreamsDriver::ValidateTextureArray(void* textureArray, int count, int& firstIndexNeedsRealloc) const
{
	firstIndexNeedsRealloc = 0;
	for (uint32 i = 0; i < count; i++)
	{
		if (!OpenGLIdRegistry::StaticIsTextureIdValid(((GLuint*)textureArray)[i]))
		{
			firstIndexNeedsRealloc = i;
			return true;
		}
	}
	firstIndexNeedsRealloc = -1;
	return false;
}

void AndroidResStreamsDriver::ReallocateGroupTextures(ResStreamsGroup* theGroup) const
{
	uint32 aNumTextures = theGroup->GetNumTextures();
	TextureArrayUnregister(theGroup->mTextures_Main, aNumTextures);
	TextureArrayUnregister(theGroup->mTextures_Multi, aNumTextures);
	TextureArrayRegister(theGroup->mTextures_Main, aNumTextures);
	void** aTextureDatas = theGroup->mTextureDatas;
	ConfigureGroupTextures(theGroup);
	for (uint32 i = 0; i < aNumTextures; i++)
	{
		void* aTextureData = aTextureDatas[i];
		GLuint* aMulti = theGroup->mTextures_Multi ? &theGroup->mTextures_Multi[i] : NULL;
		mGraphicsDriver->GetRenderDevice3D()->SetTextureInfoIntoTextureData(aTextureData, &theGroup->mTextures_Main[i], aMulti);
	}
}

void AndroidResStreamsDriver::ConfigureGroupTextures(ResStreamsGroup* theGroup) const
{
	GLuint* aTextures = theGroup->mTextures_Main;
	for (uint32 i = 0; i < theGroup->GetNumTextures(); i++)
	{
		ResStreamTextureDescriptor& aDesc = *theGroup->GetTextureDescriptor(i);
		GLuint aTexture = aTextures[i];
		uint32 aWidth = aDesc.width;
		uint32 aHeight = aDesc.height;
		if (mExtensionsSupported.mRequiresPowerOf2Textures)
		{
			if (!IsPowerOf2(aWidth))
				aWidth = GetClosestPowerOf2Above(aWidth);
			if (!IsPowerOf2(aHeight))
				aHeight = GetClosestPowerOf2Above(aHeight);
		}
		switch (aDesc.format)
		{
		case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_ALPHA_SPLIT:
		case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT_ALPHA_SPLIT:
		case RSB_TEXTURE_FORMAT_COMPRESSED_RGBA_ALPHA_SPLIT:
			AllocateMultiTexture(theGroup, i, aDesc);
			break;
		case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_COMPRESS_ALPHA_SPLIT:
			AllocateMultiTexture2(theGroup, i, aDesc);
			break;
		}
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, aTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		GLenum aInternalFormat;
		GLenum aFormat;
		GLenum aType;
		switch (aDesc.format)
		{
		case RSB_TEXTURE_FORMAT_A8R8G8B8:
		case RSB_TEXTURE_FORMAT_COMPRESSED_RGBA_ALPHA_SPLIT:
			aInternalFormat = GL_RGBA;
			aFormat = GL_RGBA;
			aType = GL_UNSIGNED_BYTE;
			break;
		case RSB_TEXTURE_FORMAT_A4R4G4B4_TILED:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		case RSB_TEXTURE_FORMAT_A4R4G4B4:
			aInternalFormat = GL_RGBA;
			aFormat = GL_RGBA;
			aType = GL_UNSIGNED_SHORT_4_4_4_4;
			break;
		case RSB_TEXTURE_FORMAT_R5G6B5_TILED:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		case RSB_TEXTURE_FORMAT_R5G6B5:
			aInternalFormat = GL_RGB;
			aFormat = GL_RGB;
			aType = GL_UNSIGNED_SHORT_5_6_5;
			break;
		case RSB_TEXTURE_FORMAT_R5G5B5A1_TILED:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		case RSB_TEXTURE_FORMAT_R5G5B5A1:
			aInternalFormat = GL_RGBA;
			aFormat = GL_RGBA;
			aType = GL_UNSIGNED_SHORT_5_5_5_1;
			break;
		case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT:
		case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_2BIT:
		case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1:
		case RSB_TEXTURE_FORMAT_COMPRESSED_DXT1_RGB:
		case RSB_TEXTURE_FORMAT_COMPRESSED_DXT3_RGBA:
		case RSB_TEXTURE_FORMAT_COMPRESSED_DXT5_RGBA:
		case RSB_TEXTURE_FORMAT_COMPRESSED_ATITC_RGB:
		case RSB_TEXTURE_FORMAT_COMPRESSED_ATITC_RGBA:
		case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_ALPHA_SPLIT:
		case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT_ALPHA_SPLIT:
		case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_COMPRESS_ALPHA_SPLIT:
			continue;
		default:
			aInternalFormat = GL_UNSIGNED_SHORT_4_4_4_4;
			aFormat = GL_RGBA;
			aType = GL_UNSIGNED_SHORT_4_4_4_4;
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, aInternalFormat, aWidth, aHeight, 0, aFormat, aType, NULL);
	}
}

bool AndroidResStreamsDriver::IsPoolInstanceBusy(ResStreamsPool* thePool, int theInstanceId)
{
	return false;
}

bool AndroidResStreamsDriver::CanReadGPUResourcesDirectly()
{
	return false;
}

void AndroidResStreamsDriver::GetExtensionsSupported()
{
	const char* anExtensions = (const char*)glGetString(GL_EXTENSIONS);
	if (Android::Graphics::IsOpenGLES20(mGraphicsDriver->mAppDriver))
		mExtensionsSupported.mRequiresPowerOf2Textures = false;
	else
		mExtensionsSupported.mRequiresPowerOf2Textures = !(strstr(anExtensions, "GL_OES_texture_npot") || strstr(anExtensions, "GL_IMG_texture_npot") || strstr(anExtensions, "GL_APPLE_texture_2D_limited_npot") || strstr(anExtensions, "GL_ARB_texture_non_power_of_two"));
	mExtensionsSupported.mSupportsCompressedETC1 = strstr(anExtensions, "GL_OES_compressed_ETC1_RGB8_texture") != NULL;
	mExtensionsSupported.mSupportsCompressedPVRTC = strstr(anExtensions, "GL_IMG_texture_compression_pvrtc") != NULL;
	mExtensionsSupported.mSupportsCompressedATITC = strstr(anExtensions, "GL_AMD_compressed_ATC_texture") || strstr(anExtensions, "GL_ATI_texture_compression_atitc");
	mExtensionsSupported.mSupportsCompressedDXT = strstr(anExtensions, "GL_OES_texture_compression_S3TC") || strstr(anExtensions, "GL_EXT_texture_compression_s3tc") || strstr(anExtensions, "GL_EXT_texture_compression_dxt1") || strstr(anExtensions, "GL_EXT_texture_compression_dxt3") || strstr(anExtensions, "GL_EXT_texture_compression_dxt5");
	mExtensionsSupported.mSupportsCompressed3DC = strstr(anExtensions, "GL_AMD_compressed_3DC_texture") != NULL;
	mExtensionsSupported.mSupportsTextureSwizzle = strstr(anExtensions, "EXT_texture_swizzle") != NULL;
	mExtensionsSupported.OutputDebugSupported();
}
