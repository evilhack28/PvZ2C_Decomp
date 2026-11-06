//
//  BaseGLResStreamsDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/resstreams/BaseGLResStreamsDriver.h"
#include "SexyAppFramework/ResStreamsFormat.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyAppFramework/drivers/graphics/opengl/OpenGLIdRegistry.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

BaseGLResStreamsDriver::BaseGLResStreamsDriver()
{
}

BaseGLResStreamsDriver::~BaseGLResStreamsDriver()
{
}

/////////////// Compressed textures ///////////////

bool BaseGLResStreamsDriver::TestCompressedFormatAvailable(int rsbFormat) const
{
	return true;
}

void BaseGLResStreamsDriver::ClearCompressedTextureBuffer()
{
	mTextureRestitchBuffer.Clear(true);
}

bool BaseGLResStreamsDriver::IsCompressedFormatAvailable(int rsbFormat) const
{
	switch (rsbFormat)
	{
	case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_2BIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT_ALPHA_SPLIT:
		return mExtensionsSupported.mSupportsCompressedPVRTC;
	case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1:
	case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_ALPHA_SPLIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_COMPRESS_ALPHA_SPLIT:
		return mExtensionsSupported.mSupportsCompressedETC1;
	case RSB_TEXTURE_FORMAT_COMPRESSED_DXT1_RGB:
	case RSB_TEXTURE_FORMAT_COMPRESSED_DXT3_RGBA:
	case RSB_TEXTURE_FORMAT_COMPRESSED_DXT5_RGBA:
		return mExtensionsSupported.mSupportsCompressedDXT;
	case RSB_TEXTURE_FORMAT_COMPRESSED_ATITC_RGB:
	case RSB_TEXTURE_FORMAT_COMPRESSED_ATITC_RGBA:
		return mExtensionsSupported.mSupportsCompressedATITC;
	}
	return false;
}

/////////////// Texture arrays ///////////////

void BaseGLResStreamsDriver::TextureArrayRegister(void* textures, int count) const
{
	glGenTextures(count, (GLuint*)textures);
	OpenGLIdRegistry::StaticRegisterIds(count, (const uint*)textures);
}

void BaseGLResStreamsDriver::TextureArrayUnregister(void* textures, int count) const
{
	GLuint* aTextures = (GLuint*)textures;
	if (aTextures != NULL && count > 0)
	{
		GLuint* anId = aTextures;
		for (uint i = 0; i < (uint)count; i++, anId++)
		{
			if (*anId != 0)
			{
				if (OpenGLIdRegistry::StaticIsTextureIdValid(*anId))
					glDeleteTextures(count, aTextures);
				OpenGLIdRegistry::StaticUnregisterIds(1, anId);
				*anId = 0;
			}
		}
	}
}

void BaseGLResStreamsDriver::GroupTexturesDeallocate(ResStreamsGroup* theGroup) const
{
	if (theGroup->mTextures_Main != NULL)
	{
		TextureArrayUnregister(theGroup->mTextures_Main, theGroup->mNumTexDescs);
		delete[] theGroup->mTextures_Main;
		theGroup->mTextures_Main = NULL;
	}
	if (theGroup->mTextures_Multi != NULL)
	{
		TextureArrayUnregister(theGroup->mTextures_Multi, theGroup->mNumTexDescs);
		delete[] theGroup->mTextures_Multi;
		theGroup->mTextures_Multi = NULL;
	}
}

GLuint BaseGLResStreamsDriver::GroupTexturesAllocateMultiAtIndex(ResStreamsGroup* theGroup, int index) const
{
	if (theGroup->mTextures_Multi == NULL)
	{
		theGroup->mTextures_Multi = new GLuint[theGroup->mNumTexDescs];
		for (int i = 0; i < theGroup->mNumTexDescs; i++)
			theGroup->mTextures_Multi[i] = 0;
	}
	if (theGroup->mTextures_Multi[index] == 0)
	{
		glGenTextures(1, &theGroup->mTextures_Multi[index]);
		OpenGLIdRegistry::StaticRegisterIds(1, &theGroup->mTextures_Multi[index]);
	}
	return theGroup->mTextures_Multi[index];
}

/////////////// Multi texture ///////////////

void BaseGLResStreamsDriver::AllocateMultiTexture2(ResStreamsGroup* theNewGroup, int index, ResStreamTextureDescriptor& theTextureDesc) const
{
	int aHeight, aWidth, aBytes;
	GetAttachedTextureSize(theTextureDesc, aHeight, aWidth, aBytes);
	GLuint aTexture = GroupTexturesAllocateMultiAtIndex(theNewGroup, index);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, aTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGetError();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

/////////////// Pool ///////////////

bool BaseGLResStreamsDriver::DestroyPool(ResStreamsPool* thePool)
{
	if (thePool->mResidentBuffer != NULL)
	{
		free(thePool->mResidentBuffer);
		thePool->mResidentBuffer = NULL;
	}

	GetGraphicsDriver()->GetRenderDevice3D()->Flush(RenderDevice3D::FLUSHF_BufferedState);
	GetGraphicsDriver()->GetRenderDevice3D()->SetTexture(0, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	for (uint i = 0; i < thePool->mNumInstances; i++)
	{
		thePool->mInstances[i].mResidentData = NULL;
		thePool->mInstances[i].mGPUData = NULL;
	}
	return true;
}

void BaseGLResStreamsDriver::AllocateMultiTexture(ResStreamsGroup* theNewGroup, int index, ResStreamTextureDescriptor& theTextureDesc) const
{
	int aHeight, aWidth, aBytes;
	GetAttachedTextureSize(theTextureDesc, aHeight, aWidth, aBytes);
	GLuint aTexture = GroupTexturesAllocateMultiAtIndex(theNewGroup, index);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, aTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, aWidth, aHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, NULL);
	glGetError();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void BaseGLResStreamsDriver::LoadMultiTexture2(int texID, uint aColorType, uint bytesTextureTotal, void* data, ResStreamTextureDescriptor& theTextureDesc) const
{
	int aHeight, aWidth, aBytes;
	GetAttachedTextureSize(theTextureDesc, aHeight, aWidth, aBytes);
	glGetError();
	glActiveTexture(GL_TEXTURE1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, aWidth, aHeight, GL_ALPHA, GL_UNSIGNED_BYTE, data);
	GLenum anError = glGetError();
	if (anError != GL_NO_ERROR)
		OutputDebugStrF("==> GL Error %d in glTexSubImage2D push of alpha uncompressed texture id %d : bytes=%d", anError, texID, aBytes);
	glActiveTexture(GL_TEXTURE0);
}

/////////////// Alpha extraction ///////////////

uchar* BaseGLResStreamsDriver::ExtractAlphaTextureData(const uchar* pCompressAlphaData, int pixels)
{
	if (pCompressAlphaData != NULL && pixels > 0)
	{
		uchar* anAlphaData = new uchar[pixels];
		uchar aPalletSize = pCompressAlphaData[0];
		if (aPalletSize == 0)
			ExtractNonPalletAlphaTextureData(pCompressAlphaData + 1, anAlphaData, pixels);
		else
			ExtractPalletAlphaTextureData(pCompressAlphaData + 1, aPalletSize, anAlphaData, pixels);
		return anAlphaData;
	}
	return NULL;
}
