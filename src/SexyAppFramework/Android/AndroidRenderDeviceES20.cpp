//
//  AndroidRenderDeviceES20.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-26.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidRenderDeviceES20.h"
#include "SexyAppFramework/drivers/app/android/AndroidAppDriver.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include "SexyAppFramework/ResStreamsFormat.h"
#include "TodLib/TodDebug.h"

using namespace Sexy;

/////////////// Helpers ///////////////

static bool CheckFrameBufferStatus()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != 0)
		return status == GL_FRAMEBUFFER_COMPLETE;
	glGetError();
	return false;
}

__attribute__((noclone)) static uint32 GetVertexSize(uint32 inFVF)
{
	uint32 result = 0;
	if (inFVF & SexyVF_XYZ)
		result += sizeof(float) * 3;
	else if (inFVF & SexyVF_XYZRHW)
		result += sizeof(float) * 4;
	if (inFVF & SexyVF_Normal)
		result += sizeof(float) * 3;
	if (inFVF & SexyVF_Diffuse)
		result += sizeof(uint32);
	if (inFVF & SexyVF_Specular)
		result += sizeof(uint32);

	int aNumTexCoords = ((inFVF >> 8) & 15);

	int aTexCoordElementSize = sizeof(float);
	for (int iTexCoord = 0; iTexCoord < aNumTexCoords; ++iTexCoord)
	{
		int aFlagTcs1 = SexyVF_TexCoordSize1(iTexCoord);
		int aFlagTcs3 = SexyVF_TexCoordSize3(iTexCoord);
		int aFlagTcs4 = SexyVF_TexCoordSize4(iTexCoord);

		if ((inFVF & aFlagTcs1) == aFlagTcs1)
			result += aTexCoordElementSize;
		else if ((inFVF & aFlagTcs3) == aFlagTcs3)
			result += aTexCoordElementSize * 3;
		else if ((inFVF & aFlagTcs4) == aFlagTcs4)
			result += aTexCoordElementSize * 4;
		else
			result += aTexCoordElementSize * 2;
	}

	return result;
}

static void BindVertexStream(AndroidGL20StateManager* theStateMgr, void* theVertexBuf)
{
	uint8* aVertexBuf = (uint8*)theVertexBuf;
	uint32 aVertexFormat = theStateMgr->GetVertexFormat();
	uint32 aVertexSize = theStateMgr->GetVertexSize();

	int offset = 0;
	if (aVertexFormat & SexyVF_XYZ)
	{
		glVertexAttribPointer(ShaderInfo::ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, aVertexSize, aVertexBuf);
		glEnableVertexAttribArray(ShaderInfo::ATTRIB_POSITION);
		offset += 12;
	}
	else if (aVertexFormat & SexyVF_XYZRHW)
	{
		if (aVertexFormat & SexyVF_PackedFormat)
		{
			glVertexAttribPointer(ShaderInfo::ATTRIB_POSITION, 2, GL_SHORT, GL_FALSE, aVertexSize, aVertexBuf);
			glEnableVertexAttribArray(ShaderInfo::ATTRIB_POSITION);
			offset += 4;
		}
		else
		{
			glVertexAttribPointer(ShaderInfo::ATTRIB_POSITION, 4, GL_FLOAT, GL_FALSE, aVertexSize, aVertexBuf);
			glEnableVertexAttribArray(ShaderInfo::ATTRIB_POSITION);
			offset += 16;
		}
	}

	if (aVertexFormat & SexyVF_Normal)
	{
		glVertexAttribPointer(ShaderInfo::ATTRIB_NORMAL, 2, GL_SHORT, GL_FALSE, aVertexSize, aVertexBuf + offset);
		glEnableVertexAttribArray(ShaderInfo::ATTRIB_NORMAL);
		offset += 12;
	}

	if (aVertexFormat & SexyVF_Diffuse)
	{
		glVertexAttribPointer(ShaderInfo::ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, aVertexSize, aVertexBuf + offset);
		glEnableVertexAttribArray(ShaderInfo::ATTRIB_COLOR);
		offset += 4;
	}

	if (aVertexFormat & SexyVF_Specular)
		offset += 4;

	if (aVertexFormat & SexyVF_Tex2)
	{
		glVertexAttribPointer(ShaderInfo::ATTRIB_TEXCOORD0, 2, GL_FLOAT, GL_FALSE, aVertexSize, aVertexBuf + offset);
		glEnableVertexAttribArray(ShaderInfo::ATTRIB_TEXCOORD0);
		offset += 8;

		glVertexAttribPointer(ShaderInfo::ATTRIB_TEXCOORD1, 2, GL_FLOAT, GL_FALSE, aVertexSize, aVertexBuf + offset);
		glEnableVertexAttribArray(ShaderInfo::ATTRIB_TEXCOORD1);
	}
	else if (aVertexFormat & SexyVF_Tex1)
	{
		if (aVertexFormat & SexyVF_PackedFormat)
			glVertexAttribPointer(ShaderInfo::ATTRIB_TEXCOORD0, 2, GL_SHORT, GL_FALSE, aVertexSize, aVertexBuf + offset);
		else
			glVertexAttribPointer(ShaderInfo::ATTRIB_TEXCOORD0, 2, GL_FLOAT, GL_FALSE, aVertexSize, aVertexBuf + offset);
		glEnableVertexAttribArray(ShaderInfo::ATTRIB_TEXCOORD0);
	}
}

/////////////// Lifecycle ///////////////

AndroidRenderDeviceES20::AndroidRenderDeviceES20(IGraphicsDriver* theDriver) : SuperOpenGLRenderDevice(theDriver)
{
	mAndroidDriver = (AndroidGraphicsDriver*)theDriver;
	mStateMgrES20 = new AndroidGL20StateManager();
	mTextureSizeMustBePow2 = false;
	mMinTextureWidth = 16;
	mMinTextureHeight = 16;
	mMaxTextureWidth = 2048;
	mMaxTextureHeight = 2048;
	mMaxTextureAspectRatio = 65536;
	mSupportedTextureFormats = PixelFormat_A8R8G8B8;
	mFlipYCoords = true;
	mCurOrthoImage = NULL;
	mRenderTargetMustBePow2 = false;
	const char* anExtensions = (const char*)glGetString(GL_EXTENSIONS);
	if (anExtensions != NULL)
		mHasDiscardFramebuffer = strstr(anExtensions, "GL_EXT_discard_framebuffer") != NULL;
	OutputDebugStrF("*** GL Extensions = %s ***", anExtensions);
	mStateMgr = mStateMgrES20;
	mStateMgr->Init();
}

AndroidRenderDeviceES20::~AndroidRenderDeviceES20()
{
}

/////////////// Accessors ///////////////

uint32 AndroidRenderDeviceES20::GetCapsFlags()
{
	return 270;
}

void AndroidRenderDeviceES20::BindVertexStream(void* theVertexBuf)
{
}

void AndroidRenderDeviceES20::UnbindVertexStream()
{
}

void AndroidRenderDeviceES20::CopyScreenImage(DeviceImage* ioDstImage, uint32 flags)
{
}

void AndroidRenderDeviceES20::GotFocus()
{
	SuperOpenGLRenderDevice::GotFocus();
	ClearRenderEffects();
}

/////////////// Texture data ///////////////

void* AndroidRenderDeviceES20::CreateTextureData(ResStreamFileGPULocationInfo* theLocationInfo, void* theTextureBacking, void* theTextureMulti)
{
	TextureData* aTextureData = new TextureData(this);
	aTextureData->mWidth = theLocationInfo->atlas_width;
	aTextureData->mTexPieceWidth = theLocationInfo->atlas_width;
	aTextureData->mHeight = theLocationInfo->atlas_height;
	aTextureData->mTexPieceHeight = theLocationInfo->atlas_height;
	aTextureData->mTexVecWidth = 1;
	aTextureData->mTexVecHeight = 1;
	aTextureData->mPixelFormat = PixelFormat_A8R8G8B8;
	aTextureData->mImageFlags = 0;
	aTextureData->mTextures.resize(1);
	aTextureData->mExtraData.mFromRSB = true;
	aTextureData->mOptimizedLoad = true;
	aTextureData->mImageFlags = 0;
	aTextureData->mMaxTotalU = 1.0f;
	aTextureData->mMaxTotalV = 1.0f;
	TextureDataPiece* aPiece = &aTextureData->mTextures[0];
	int aPieceHeight = theLocationInfo->atlas_height;
	aPiece->mWidth = theLocationInfo->atlas_width;
	aPiece->mHeight = aPieceHeight;
	aPiece->mTexture = GLTexHolder((int)(intptr_t)theTextureBacking);
	aPiece->mMultiTexture = GLTexHolder((int)(intptr_t)theTextureMulti);
	return aTextureData;
}

void AndroidRenderDeviceES20::DestroyTextureData(void* textureDatas)
{
	if (textureDatas != NULL)
		delete (TextureData*)textureDatas;
}

void AndroidRenderDeviceES20::SetTextureInfoIntoTextureData(void* pTextureData, void* pTextureInfo, void* pTextureInfoMulti)
{
	TextureDataPiece* aPiece = &((TextureData*)pTextureData)->mTextures[0];
	aPiece->mTexture.tex = *(GLuint*)pTextureInfo;
	if (pTextureInfoMulti != NULL)
		aPiece->mMultiTexture.tex = *(GLuint*)pTextureInfoMulti;
}

GLTexHolder AndroidRenderDeviceES20::CreateTextureSurface(int theWidth, int theHeight, PixelFormat theFormat, bool renderTarget, TextureData* theTexData, TextureDataPiece* theTexDataPiece)
{
	SetTextureSingle(0, 0);

	GLTexHolder aTex;
	glGenTextures(1, &aTex.tex);
	OpenGLIdRegistry::StaticRegisterIds(1, &aTex.tex);
	aTex.src = GL_TEXTURE_2D;

	GLenum theGLFormat = GL_RGBA;
	GLenum aType = GL_UNSIGNED_SHORT_4_4_4_4;
	if (theFormat == PixelFormat_X8R8G8B8)
	{
		theGLFormat = GL_RGB;
		aType = GL_UNSIGNED_SHORT_5_6_5;
	}

	if (theTexDataPiece != NULL)
		theTexDataPiece->mTexFormat = theGLFormat;

	glGetError();
	if (!renderTarget)
	{
		GLint aPrevTexture = 0;
		glGetIntegerv(aTex.src == GL_TEXTURE_2D ? GL_TEXTURE_BINDING_2D : GL_TEXTURE_BINDING_CUBE_MAP, &aPrevTexture);
		glBindTexture(aTex.src, aTex.tex);
		glBindTexture(aTex.src, aTex.tex);
		glTexParameteri(aTex.src, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(aTex.src, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(aTex.src, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(aTex.src, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(aTex.src, aPrevTexture);
	}
	else
	{
		glGenFramebuffers(1, &theTexData->mExtraData.mFBO);
		glGetError();
		glBindFramebuffer(GL_FRAMEBUFFER, theTexData->mExtraData.mFBO);
		glGetError();
		glBindTexture(aTex.src, aTex.tex);
		glGetError();
		glTexParameteri(aTex.src, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(aTex.src, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(aTex.src, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(aTex.src, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(aTex.src, 0, theGLFormat, theWidth, theHeight, 0, theGLFormat, aType, NULL);
		glGetError();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, aTex.src, aTex.tex, 0);
		CheckFrameBufferStatus();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(aTex.src, 0);
	}
	return aTex;
}

void AndroidRenderDeviceES20::ReleaseExtraRenderDataInfo(TextureData* theTexData, GLExtraRenderDataInfo& theInfo)
{
	if (theInfo.mDeleteFBO)
	{
		if (theInfo.mFBO != 0)
		{
			glDeleteFramebuffers(1, &theInfo.mFBO);
			theInfo.mFBO = 0;
		}
		if (theInfo.mDepth != 0)
		{
			if (OpenGLIdRegistry::StaticIsTextureIdValid(theInfo.mDepth))
				glDeleteTextures(1, &theInfo.mDepth);
			OpenGLIdRegistry::StaticUnregisterIds(1, &theInfo.mDepth);
			theInfo.mDepth = 0;
		}
	}
	else
	{
		theInfo.mFBO = 0;
		theInfo.mDepth = 0;
	}
}

/////////////// Render state ///////////////

void AndroidRenderDeviceES20::SetDefaultState(Image* theImage, bool isInScene)
{
	mStateMgr->SetVertexFormat(AndroidGL20Vertex::FVF, ::GetVertexSize(AndroidGL20Vertex::FVF));
	mStateMgr->SetDefaultShader();
	SetOrthoMatrix(theImage);
}

void AndroidRenderDeviceES20::SetOrthoMatrix(Image* theImage)
{
	if (mCurOrthoImage == theImage || theImage == NULL)
	{
		mStateMgr->SetViewport(0, 0, mWidth, mHeight, 0.0f, 1.0f);
		mStateMgr->SetOrthoProjection(&mAndroidDriver->mAppDriver->GetScreenMatrix());
		int anOrientation = mAndroidDriver->mAppDriver->GetOrientation();
		if (anOrientation - 1U < 2)
		{
			mScreenWidth = mWidth;
			mScreenHeight = mHeight;
		}
		else
		{
			mScreenWidth = mHeight;
			mScreenHeight = mWidth;
		}
	}
	else if (theImage != NULL)
	{
		mScreenWidth = theImage->mWidth;
		mScreenHeight = theImage->mHeight;
		SexyMatrix4 aProj;
		memset(&aProj.m00, 0, 16 * sizeof(float));
		aProj.m00 = 2.0f / theImage->mWidth;
		aProj.m11 = 2.0f / theImage->mHeight;
		aProj.m22 = 1.0f;
		aProj.m32 = 0.0f;
		aProj.m33 = 1.0f;
		aProj.m30 = -1.0f;
		aProj.m31 = -1.0f;
		mStateMgr->SetViewport(0, 0, theImage->mWidth, theImage->mHeight, 0.0f, 1.0f);
		mStateMgr->SetOrthoProjection(&aProj);
	}
}

void AndroidRenderDeviceES20::SetOrthoMatrixForSwapScreen(int theWidth, int theHeight)
{
	mStateMgr->SetViewport(0, 0, theWidth, theHeight, 0.0f, 1.0f);
	mStateMgr->SetOrthoProjection(&mAndroidDriver->mAppDriver->GetDeviceScreenMatrix());
	mScreenWidth = mWidth;
	mScreenHeight = mHeight;
}

void AndroidRenderDeviceES20::SetShader(ShaderInfo* theShader)
{
	if (theShader != mStateMgr->GetShader())
	{
		FlushBufferedTriangles();
		mStateMgr->SetShader(theShader);
	}
}

bool AndroidRenderDeviceES20::SetRenderTargetFBO(GLuint fbo)
{
	bool aResult = PreDraw();
	if (!aResult)
		return aResult;
	if (mCurRenderTargetFBO == fbo)
		return aResult;

	FlushBufferedTriangles();
	mCurRenderTargetImage = NULL;
	GLuint aSysFBO = Android::Graphics::GetGLViewSysFBO(mAndroidDriver->mAppDriver);
	if (fbo != 0)
	{
		if (mCurRenderTargetFBO != 0 || fbo != aSysFBO)
		{
			if (fbo == -1)
				goto bindzero;
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		}
	}
	else if (mCurRenderTargetFBO != aSysFBO)
	{
		if (aSysFBO == -1)
			goto bindzero;
		glBindFramebuffer(GL_FRAMEBUFFER, aSysFBO);
	}
	mCurRenderTargetFBO = fbo;
	return aResult;
bindzero:
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	mCurRenderTargetFBO = fbo;
	return aResult;
}

void AndroidRenderDeviceES20::ClearColorBuffer(const Color& inColor)
{
	FlushBufferedTriangles();
	mStateMgr->PushState();

	uint32_t vX, vY, vWidth, vHeight;
	mStateMgr->GetViewport(vX, vY, vWidth, vHeight);
	if ((vX != 0) ||
		(vY != 0) ||
		(mCurRenderTargetImage != NULL && ((vWidth != mCurRenderTargetImage->mWidth) || (vHeight != mCurRenderTargetImage->mHeight))) ||
		(mCurRenderTargetImage == NULL && ((vWidth != mWidth) || (vHeight != mHeight))))
	{
		mStateMgr->SetScissorRectToViewportRect();
	}
	mStateMgr->CommitState();
	glClearColor((float)inColor.GetRed() * (1.0f / 255.0f), (float)inColor.GetGreen() * (1.0f / 255.0f), (float)inColor.GetBlue() * (1.0f / 255.0f), (float)inColor.GetAlpha() * (1.0f / 255.0f));
	glClear(GL_COLOR_BUFFER_BIT);
	mStateMgr->PopState();
}

void AndroidRenderDeviceES20::ClearDepthBuffer()
{
	FlushBufferedTriangles();
	mStateMgr->PushState();
	mStateMgr->SetRenderState(SEXY3DRS_ZWRITEENABLE, 1);
	mStateMgr->CommitState();
	glClearDepthf(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	mStateMgr->PopState();
}

void AndroidRenderDeviceES20::SetViewport(int theX, int theY, int theWidth, int theHeight, float theMinZ, float theMaxZ)
{
	mStateMgr->SetViewport((uint32)theX, (uint32)theY, (uint32)theWidth, (uint32)theHeight, theMinZ, theMaxZ);
}

Image* AndroidRenderDeviceES20::SwapScreenImage(DeviceImage*& ioSrcImage, RenderSurface*& ioSrcSurface, uint32 flags)
{
	if (ioSrcImage == NULL)
		return NULL;

	if (ioSrcSurface == NULL)
	{
		mCurRenderTargetImage = NULL;
		SetRenderTarget(ioSrcImage);
		ioSrcSurface = new RenderSurface();
		ioSrcSurface->AddRef();
		ioSrcSurface->mData = mCurRenderTargetFBO;
		ClearColorBuffer(Color::FromInt(0xff000000));
	}
	else
	{
		SetRenderTargetFBO(ioSrcSurface->mData);
	}

	void* aTempPtr;
	aTempPtr = mGraphicsDriver->GetScreenImage()->GetRenderData();
	mGraphicsDriver->GetScreenImage()->SetRenderData(ioSrcImage->GetRenderData());
	ioSrcImage->SetRenderData(aTempPtr);

	aTempPtr = mSysSurface;
	mSysSurface = ioSrcSurface;
	ioSrcSurface = (RenderSurface*)aTempPtr;

	mCurRenderTargetImage = mGraphicsDriver->GetScreenImage();
	return ioSrcImage;
}

/////////////// Render effects ///////////////

RenderEffect* AndroidRenderDeviceES20::GetEffect(RenderEffectDefinition* inDefinition)
{
	RenderEffectMap::iterator it = mRenderEffects.find(inDefinition);
	if (it != mRenderEffects.end())
		return it->second;

	AndroidGL20RenderEffect* anEffect = new AndroidGL20RenderEffect(this, inDefinition);
	mRenderEffects[inDefinition] = anEffect;
	return anEffect;
}

void AndroidRenderDeviceES20::ClearRenderEffects()
{
	TodHesitationTrace("ClearRenderEffects");
	for (RenderEffectMap::iterator it = mRenderEffects.begin(); it != mRenderEffects.end(); ++it)
		it->second->Clear();
	mRenderEffects.clear();
	::BindVertexStream(mStateMgr, mBatchedTriangleBuffer);
}
