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

void BaseGLResStreamsDriver::PushCompressedTexture(ResStreamTextureDescriptor& textureDesc, uint aColorType, uint aTex, uint aMultiTex, uint bytesTextureTotal, uchar* buffer)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, aTex);
	glGetError();
	if (aColorType == GL_RGBA)
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureDesc.width, textureDesc.height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	}
	else
	{
		if (bytesTextureTotal == 76797)
			bytesTextureTotal = 77760;
		glCompressedTexImage2D(GL_TEXTURE_2D, 0, aColorType, textureDesc.width, textureDesc.height, 0, bytesTextureTotal, buffer);
	}
	GLenum anError = glGetError();
	if (anError != GL_NO_ERROR)
		OutputDebugStrF("==> GL Error %d in glCompressedTexSubImage2D push of compressed texture id %d : bytes=%d colorType=%d", anError, aTex, bytesTextureTotal, aColorType);
}

void BaseGLResStreamsDriver::LoadMultiTexture(int texID, void* data, ResStreamTextureDescriptor& theTextureDesc)
{
	int aHeight, aWidth, aBytes;
	GetAttachedTextureSize(theTextureDesc, aHeight, aWidth, aBytes);
	uchar* anAlphaData = ExtractAlphaTextureData((const uchar*)data, aWidth * aHeight);
	if (anAlphaData == NULL)
		return;
	glGetError();
	glActiveTexture(GL_TEXTURE1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, aWidth, aHeight, GL_ALPHA, GL_UNSIGNED_BYTE, anAlphaData);
	GLenum anError = glGetError();
	if (anError != GL_NO_ERROR)
		OutputDebugStrF("==> GL Error %d in glTexSubImage2D push of alpha uncompressed texture id %d : bytes=%d", anError, texID, aBytes);
	glActiveTexture(GL_TEXTURE0);
	delete[] anAlphaData;
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

void BaseGLResStreamsDriver::PushCompressedTextureMulti(ResStreamTextureDescriptor& textureDesc, uint aColorType, uint aTex, uint aMultiTex, uint bytesTextureTotal, uint bytesFileTotal, uchar* buffer)
{
	PushCompressedTexture(textureDesc, aColorType, aTex, aMultiTex, bytesTextureTotal, buffer);
	if (bytesTextureTotal < bytesFileTotal)
	{
		uchar* anAlphaData = buffer + bytesTextureTotal;
		switch (textureDesc.format)
		{
		case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_ALPHA_SPLIT:
		case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT_ALPHA_SPLIT:
		case RSB_TEXTURE_FORMAT_COMPRESSED_RGBA_ALPHA_SPLIT:
			LoadMultiTexture(aMultiTex, anAlphaData, textureDesc);
			break;
		case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_COMPRESS_ALPHA_SPLIT:
			LoadMultiTexture2(aMultiTex, aColorType, bytesTextureTotal, anAlphaData, textureDesc);
			break;
		default:
			OutputDebugStrF("Invalid packed multi texture format");
			break;
		}
	}
}

void BaseGLResStreamsDriver::DecodeCompressedTextureBlock(ResStreamTextureDescriptor& textureDesc, uint aColorType, uint aTex, uint aMultiTex, uchar* buffer, uint bytesToDecode, uint bytesTextureTotal, uint bytesFileTotal)
{
	if (mTextureRestitchBuffer.IsTextureInProgress())
	{
		mTextureRestitchBuffer.Add(mCurrentCompressedTextureID, buffer, bytesToDecode);
	}
	else
	{
		if (bytesToDecode >= bytesFileTotal)
		{
			PushCompressedTextureMulti(textureDesc, aColorType, aTex, aMultiTex, bytesTextureTotal, bytesFileTotal, buffer);
			return;
		}
		mCurrentCompressedTextureID++;
		mTextureRestitchBuffer.Initialize(bytesFileTotal);
		mTextureRestitchBuffer.Add(mCurrentCompressedTextureID, buffer, bytesToDecode);
	}
	if (mTextureRestitchBuffer.GetBytesInBuffer() >= bytesFileTotal)
	{
		PushCompressedTextureMulti(textureDesc, aColorType, aTex, aMultiTex, bytesTextureTotal, bytesFileTotal, mTextureRestitchBuffer.GetTextureBuffer());
		mTextureRestitchBuffer.Clear(true);
	}
}

/////////////// Alpha extraction ///////////////

void BaseGLResStreamsDriver::ExtractNonPalletAlphaTextureData(const uchar* pCompressDataPtr, uchar* pAlphaDataPtr, int pixels)
{
	if (pCompressDataPtr == NULL || pAlphaDataPtr == NULL || pixels <= 0)
		return;
	int anIndex = 0;
	int aBit = 0;
	for (int i = 0; i < pixels; i++)
	{
		int aMask = 1 << (7 - aBit);
		pAlphaDataPtr[i] = (pCompressDataPtr[anIndex] & aMask) ? 0xff : 0;
		aBit++;
		if (aBit == 8)
		{
			anIndex++;
			aBit = 0;
		}
	}
}

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
