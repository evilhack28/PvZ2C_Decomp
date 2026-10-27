//
//  AndroidGL20RenderEffect.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-27.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidRenderDeviceES20.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGL20RenderEffect.h"

using namespace Sexy;
using namespace PopFXFormat;

/////////////// Helpers ///////////////

static void MultiplyMatrix(SexyMatrix4* out, const SexyMatrix4* a, const SexyMatrix4* b)
{
	out->m00 = a->m00 * b->m00 + a->m01 * b->m10 + a->m02 * b->m20 + a->m03 * b->m30;
	out->m01 = a->m00 * b->m01 + a->m01 * b->m11 + a->m02 * b->m21 + a->m03 * b->m31;
	out->m02 = a->m00 * b->m02 + a->m01 * b->m12 + a->m02 * b->m22 + a->m03 * b->m32;
	out->m03 = a->m00 * b->m03 + a->m01 * b->m13 + a->m02 * b->m23 + a->m03 * b->m33;
	out->m10 = a->m10 * b->m00 + a->m11 * b->m10 + a->m12 * b->m20 + a->m13 * b->m30;
	out->m11 = a->m10 * b->m01 + a->m11 * b->m11 + a->m12 * b->m21 + a->m13 * b->m31;
	out->m12 = a->m10 * b->m02 + a->m11 * b->m12 + a->m12 * b->m22 + a->m13 * b->m32;
	out->m13 = a->m10 * b->m03 + a->m11 * b->m13 + a->m12 * b->m23 + a->m13 * b->m33;
	out->m20 = a->m20 * b->m00 + a->m21 * b->m10 + a->m22 * b->m20 + a->m23 * b->m30;
	out->m21 = a->m20 * b->m01 + a->m21 * b->m11 + a->m22 * b->m21 + a->m23 * b->m31;
	out->m22 = a->m20 * b->m02 + a->m21 * b->m12 + a->m22 * b->m22 + a->m23 * b->m32;
	out->m23 = a->m20 * b->m03 + a->m21 * b->m13 + a->m22 * b->m23 + a->m23 * b->m33;
	out->m30 = a->m30 * b->m00 + a->m31 * b->m10 + a->m32 * b->m20 + a->m33 * b->m30;
	out->m31 = a->m30 * b->m01 + a->m31 * b->m11 + a->m32 * b->m21 + a->m33 * b->m31;
	out->m32 = a->m30 * b->m02 + a->m31 * b->m12 + a->m32 * b->m22 + a->m33 * b->m32;
	out->m33 = a->m30 * b->m03 + a->m31 * b->m13 + a->m32 * b->m23 + a->m33 * b->m33;
}

static bool CompileShader(GLuint* outShader, GLenum theType, const char* theSource)
{
	*outShader = glCreateShader(theType);
	glShaderSource(*outShader, 1, &theSource, NULL);
	glCompileShader(*outShader);

	GLint aLogLength;
	glGetShaderiv(*outShader, GL_INFO_LOG_LENGTH, &aLogLength);
	if (aLogLength > 0)
	{
		char* aLog = (char*)malloc(aLogLength);
		glGetShaderInfoLog(*outShader, aLogLength, &aLogLength, aLog);
		OutputDebugStrF("Shader compile log: (%d) %s", aLogLength, aLog);
		free(aLog);
	}

	GLint aStatus;
	glGetShaderiv(*outShader, GL_COMPILE_STATUS, &aStatus);
	if (aStatus == 0)
	{
		glDeleteShader(*outShader);
		OpenGLIdRegistry::StaticUnregisterShaderIds(1, outShader);
	}
	return aStatus != 0;
}

static bool LinkProgram(GLuint theProgram)
{
	glLinkProgram(theProgram);

	GLint aLogLength;
	glGetProgramiv(theProgram, GL_INFO_LOG_LENGTH, &aLogLength);
	if (aLogLength > 0)
	{
		char* aLog = (char*)malloc(aLogLength);
		glGetProgramInfoLog(theProgram, aLogLength, &aLogLength, aLog);
		OutputDebugStrF("Program link log:\n%s", aLog);
		free(aLog);
	}

	GLint aStatus;
	glGetProgramiv(theProgram, GL_LINK_STATUS, &aStatus);
	return aStatus != 0;
}

/////////////// Lifecycle ///////////////

AndroidGL20RenderEffect::AndroidGL20RenderEffect(RenderDevice3D* theDevice, RenderEffectDefinition* theDefinition)
{
	mDevice = theDevice;
	mDefinition = theDefinition;
	mBuffer = &mDefinition->mData[0];
	mCurrentTechnique = NULL;
	mBeginPassRefCount = 0;
	mIsValid = Initialize();
	SetCurrentTechnique("Default");
}

AndroidGL20RenderEffect::~AndroidGL20RenderEffect()
{
	Clear();
}

/////////////// Accessors ///////////////

RenderDevice3D* AndroidGL20RenderEffect::GetDevice()
{
	return mDevice;
}

RenderEffectDefinition* AndroidGL20RenderEffect::GetDefinition()
{
	return mDefinition;
}

void AndroidGL20RenderEffect::GetParameterBySemantic(uint32 inSemantic, float* outFloatData, uint32 inMaxFloatCount)
{
}

PopFXTechnique* AndroidGL20RenderEffect::GetPopFXTechnique(const char* theName)
{
	for (uint32 i = 0; i < mHeader->num_techniques; i++)
	{
		PopFXTechnique* aTech = GetPopFXTechnique(i);
		if (stricmp(GetPopFXString(aTech->name), theName) == 0)
			return aTech;
	}
	return NULL;
}

std::string AndroidGL20RenderEffect::GetCurrentTechniqueName()
{
	return mCurrentTechnique != NULL ? GetPopFXString(mCurrentTechnique->name) : "";
}

/////////////// Initialization ///////////////

bool AndroidGL20RenderEffect::Initialize()
{
	mHeader = (PopFXHeader*)mBuffer;
	if (mHeader->id != PopFXID)
		return false;

	for (uint32 i = 0; i < mHeader->num_techniques; i++)
	{
		PopFXTechnique* aTechnique = GetPopFXTechnique(i);
		if (!InitializeTechnique(aTechnique))
			OutputDebugStrF("Technique %s could not be initialized\n", GetPopFXString(aTechnique->name));
	}
	return true;
}

bool AndroidGL20RenderEffect::InitializeTechnique(PopFXTechnique* theTechnique)
{
	mTechniques.push_back(RenderEffectTechnique());
	RenderEffectTechnique& aTechData = mTechniques.back();

	for (uint32 i = 0; i < theTechnique->num_passes; i++)
	{
		PopFXPass* aPass = GetPopFXPass(i + theTechnique->pass_begin);
		if (!InitializePass(aPass, aTechData))
		{
			aTechData.mIsValid = false;
			return false;
		}
	}

	aTechData.mIsValid = true;
	return true;
}

bool AndroidGL20RenderEffect::InitializePass(PopFXPass* thePass, RenderEffectTechnique& theTechData)
{
	OutputDebugStrF("InitializePass");

	theTechData.mPasses.push_back(RenderEffectPass());
	RenderEffectPass& aPassData = theTechData.mPasses.back();

	GLuint aVertexShader = 0;
	GLuint aPackedVertexShader = 0;
	GLuint aPixelShader = 0;

	if (thePass->vertex_shader == EmptyIndex)
	{
		if (mDevice->GetCapsFlags() & RenderDevice3D::CAPF_VertexShaders)
		{
			CompileShader(&aVertexShader, GL_VERTEX_SHADER,
				"precision mediump float;\n"
				"attribute vec4 position;\n"
				"attribute vec4 color;\n"
				"attribute vec2 texcoord0;\n"
				"attribute vec2 texcoord1;\n"
				"varying vec4 xlat_varying_POSITION;\n"
				"varying vec4 xlat_varying_COLOR0;\n"
				"varying vec4 xlat_varying_TEXCOORD0;\n"
				"varying vec4 xlat_varying_TEXCOORD1;\n"
				"uniform mat4  screenMatrix;\n"
				"void main()\n"
				"{\n"
				"gl_Position = screenMatrix * vec4(position.x,position.y,position.z,1.0);\n"
				"xlat_varying_POSITION = gl_Position;\n"
				"xlat_varying_COLOR0 = color;\n"
				"xlat_varying_TEXCOORD0 = vec4(texcoord0.x,texcoord0.y,0.0,0.0);\n"
				"xlat_varying_TEXCOORD1 = vec4(texcoord1.x,texcoord1.y,0.0,0.0);\n"
				"}\n");
			CompileShader(&aPackedVertexShader, GL_VERTEX_SHADER,
				"precision mediump float;\n"
				"attribute vec4 position;\n"
				"attribute vec4 color;\n"
				"attribute vec2 texcoord0;\n"
				"varying vec4 xlat_varying_POSITION;\n"
				"varying vec4 xlat_varying_COLOR0;\n"
				"varying vec4 xlat_varying_TEXCOORD0;\n"
				"varying vec4 xlat_varying_TEXCOORD1;\n"
				"uniform mat4  screenMatrix;\n"
				"void main()\n"
				"{\n"
				"gl_Position = screenMatrix * vec4(position.x * 1.0/8.0,position.y * 1.0/8.0, position.z * 1.0/8.0,1.0);\n"
				"xlat_varying_POSITION = gl_Position;\n"
				"xlat_varying_COLOR0 = color;\n"
				"xlat_varying_TEXCOORD0 = xlat_varying_TEXCOORD1 = vec4(texcoord0.x * 1.0/8192.0,texcoord0.y * 1.0/8192.0,0.0,0.0);\n"
				"}\n");
		}
checkpixel:
		if (thePass->pixel_shader == EmptyIndex)
		{
link:
			if (aVertexShader == 0 && __builtin_expect(aPixelShader == 0, 1))
			{
				aPassData.mPacked.mProgram = 0;
				aPassData.mUnpacked.mProgram = 0;
				return true;
			}

			if ((mDevice->GetCapsFlags() & RenderDevice3D::CAPF_PixelShaders) && (mDevice->GetCapsFlags() & RenderDevice3D::CAPF_VertexShaders))
			{
				aPassData.mPacked.mProgram = glCreateProgram();
				OpenGLIdRegistry::StaticRegisterShaderIds(1, &aPassData.mPacked.mProgram);
				if (aPackedVertexShader != 0)
					glAttachShader(aPassData.mPacked.mProgram, aPackedVertexShader);
				if (aPixelShader != 0)
					glAttachShader(aPassData.mPacked.mProgram, aPixelShader);
				glBindAttribLocation(aPassData.mPacked.mProgram, ShaderInfo::ATTRIB_POSITION, "position");
				glBindAttribLocation(aPassData.mPacked.mProgram, ShaderInfo::ATTRIB_TEXCOORD0, "texcoord0");
				glBindAttribLocation(aPassData.mPacked.mProgram, ShaderInfo::ATTRIB_COLOR, "color");
				if (LinkProgram(aPassData.mPacked.mProgram))
				{
					aPassData.mPacked.mScreenMatrixLoc = glGetUniformLocation(aPassData.mPacked.mProgram, "screenMatrix");
					aPassData.mPacked.mScreenMatrixRev = 0;

					aPassData.mUnpacked.mProgram = glCreateProgram();
					OpenGLIdRegistry::StaticRegisterShaderIds(1, &aPassData.mUnpacked.mProgram);
					if (aVertexShader != 0)
						glAttachShader(aPassData.mUnpacked.mProgram, aVertexShader);
					if (aPixelShader != 0)
						glAttachShader(aPassData.mUnpacked.mProgram, aPixelShader);
					glBindAttribLocation(aPassData.mUnpacked.mProgram, ShaderInfo::ATTRIB_POSITION, "position");
					glBindAttribLocation(aPassData.mUnpacked.mProgram, ShaderInfo::ATTRIB_TEXCOORD0, "texcoord0");
					glBindAttribLocation(aPassData.mUnpacked.mProgram, ShaderInfo::ATTRIB_TEXCOORD1, "texcoord1");
					glBindAttribLocation(aPassData.mUnpacked.mProgram, ShaderInfo::ATTRIB_COLOR, "color");
					if (LinkProgram(aPassData.mUnpacked.mProgram))
					{
						aPassData.mUnpacked.mScreenMatrixLoc = glGetUniformLocation(aPassData.mUnpacked.mProgram, "screenMatrix");
						aPassData.mUnpacked.mScreenMatrixRev = 0;
						return true;
					}
				}
			}
		}
		else
		{
			if (mDevice->GetCapsFlags() & RenderDevice3D::CAPF_PixelShaders)
			{
				PopFXShader* aShader = GetPopFXShader(thePass->pixel_shader);
				if (CompileShader(&aPixelShader, GL_FRAGMENT_SHADER, GetPopFXString(aShader->data)))
					goto link;
			}
		}
	}
	else
	{
		if (mDevice->GetCapsFlags() & RenderDevice3D::CAPF_VertexShaders)
		{
			PopFXShader* aShader = GetPopFXShader(thePass->vertex_shader);
			if (CompileShader(&aVertexShader, GL_VERTEX_SHADER, GetPopFXString(aShader->data)))
			{
				aPackedVertexShader = aVertexShader;
				goto checkpixel;
			}
		}
	}
	return false;
}

/////////////// Cleanup ///////////////

void AndroidGL20RenderEffect::Clear()
{
	OutputDebugStrF("Effect Clear");
	mHeader = (PopFXHeader*)mBuffer;
	if (mHeader->id != PopFXID)
		return;

	for (uint32 i = 0; i < mHeader->num_techniques; i++)
		ClearTechnique(GetPopFXTechnique(i), mTechniques[i]);
	mTechniques.clear();
}

void AndroidGL20RenderEffect::ClearTechnique(PopFXTechnique* theTechnique, RenderEffectTechnique& theTechData)
{
	for (uint32 i = 0; i < theTechnique->num_passes; i++)
		ClearPass(GetPopFXPass(i + theTechnique->pass_begin), theTechData, theTechData.mPasses[i]);
	theTechData.mPasses.clear();
}

void AndroidGL20RenderEffect::ClearPass(PopFXPass* thePass, RenderEffectTechnique& theTechData, RenderEffectPass& thePassData)
{
	OutputDebugStrF("ClearPass");
	if (OpenGLIdRegistry::StaticIsShaderIdValid(thePassData.mUnpacked.mProgram))
		glDeleteProgram(thePassData.mUnpacked.mProgram);
	OpenGLIdRegistry::StaticUnregisterShaderIds(1, &thePassData.mUnpacked.mProgram);
	if (OpenGLIdRegistry::StaticIsShaderIdValid(thePassData.mPacked.mProgram))
		glDeleteProgram(thePassData.mPacked.mProgram);
	OpenGLIdRegistry::StaticUnregisterShaderIds(1, &thePassData.mPacked.mProgram);
	OutputDebugStrF("ClearPass Done");
}

/////////////// Parameters ///////////////

void AndroidGL20RenderEffect::SetParameter(const std::string& inParamName, const float* inFloatData, uint32 inFloatCount)
{
	ParamData* aParam = mParams.GetParamNamed(inParamName, true);
	aParam->SetValue(inFloatData, inFloatCount);

	if (mBeginPassRefCount && mCurrentTechnique != NULL)
		UpdateParams();
}

void AndroidGL20RenderEffect::SetMatrix(const std::string& inParamName, const float* inValue)
{
	SetParameter(inParamName, inValue, 16);
}

void AndroidGL20RenderEffect::SetCurrentTechnique(const std::string& inName, bool inCheckValid)
{
	mCurrentTechnique = GetPopFXTechnique(inName.c_str());
	if (mCurrentTechnique != NULL)
	{
		if (!mTechniques[mCurrentTechnique->technique_number].mIsValid)
			mCurrentTechnique = NULL;
	}
}

void AndroidGL20RenderEffect::UpdateParams()
{
	RenderEffectPass& aPassData = mTechniques[mCurrentTechnique->technique_number].mPasses[mCurrentPass];
	GLuint aProgram = aPassData.mPacked.mProgram;

	for (ParamCollection::ParamMap::iterator it = mParams.mParamMap.begin(); it != mParams.mParamMap.end(); ++it)
	{
		std::pair<const std::string, ParamData>& aParam = *it;
		GLint aLocation = glGetUniformLocation(aProgram, aParam.first.c_str());
		if (aLocation != -1)
		{
			size_t aVectorCount = aParam.second.mFloatData.size() >> 2;
			if ((int)aVectorCount == 4)
				glUniformMatrix4fv(aLocation, 1, GL_FALSE, &aParam.second.mFloatData[0]);
			else
				glUniform4fv(aLocation, aVectorCount, &aParam.second.mFloatData[0]);
		}
	}

	GLint aLocation = glGetUniformLocation(aProgram, "Tex0");
	if (aLocation != -1)
		glUniform1i(aLocation, 0);
	aLocation = glGetUniformLocation(aProgram, "Tex1");
	if (aLocation != -1)
		glUniform1i(aLocation, 1);
	aLocation = glGetUniformLocation(aProgram, "Tex2");
	if (aLocation != -1)
		glUniform1i(aLocation, 2);

	SexyMatrix4 aWorld;
	SexyMatrix4 aView;
	SexyMatrix4 aProj;

	aLocation = glGetUniformLocation(aProgram, "world");
	if (aLocation != -1)
	{
		((AndroidRenderDeviceES20*)mDevice)->mStateMgr->GetTransform(OGL_TRANSFORM_WORLD, &aWorld);
		glUniformMatrix4fv(aLocation, 1, GL_FALSE, (const float*)&aWorld);
	}
	aLocation = glGetUniformLocation(aProgram, "view");
	if (aLocation != -1)
	{
		((AndroidRenderDeviceES20*)mDevice)->mStateMgr->GetTransform(OGL_TRANSFORM_VIEW, &aWorld);
		glUniformMatrix4fv(aLocation, 1, GL_FALSE, (const float*)&aWorld);
	}
	aLocation = glGetUniformLocation(aProgram, "projection");
	if (aLocation != -1)
	{
		((AndroidRenderDeviceES20*)mDevice)->mStateMgr->GetTransform(OGL_TRANSFORM_PROJECTION, &aWorld);
		glUniformMatrix4fv(aLocation, 1, GL_FALSE, (const float*)&aWorld);
	}
	aLocation = glGetUniformLocation(aProgram, "worldViewProj");
	if (aLocation != -1)
	{
		((AndroidRenderDeviceES20*)mDevice)->mStateMgr->GetTransform(OGL_TRANSFORM_WORLD, &aWorld);
		((AndroidRenderDeviceES20*)mDevice)->mStateMgr->GetTransform(OGL_TRANSFORM_VIEW, &aView);
		((AndroidRenderDeviceES20*)mDevice)->mStateMgr->GetTransform(OGL_TRANSFORM_PROJECTION, &aProj);
		SexyMatrix4 aResult;
		MultiplyMatrix(&aResult, &aWorld, &aView);
		aWorld = aResult;
		MultiplyMatrix(&aResult, &aWorld, &aProj);
		glUniformMatrix4fv(aLocation, 1, GL_FALSE, (const float*)&aResult);
	}
}

/////////////// Rendering ///////////////

int AndroidGL20RenderEffect::Begin(HRunHandle& outRunHandle, const HRenderContext& inRenderContext)
{
	HRenderContext aContext = inRenderContext;
	if (aContext.IsValid())
	{
		mDevice->SetCurrentContext(aContext);
	}
	else
	{
		aContext = mDevice->GetCurrentContext();
	}

	outRunHandle = aContext.GetPointer();

	mCurrentPass = 0;
	if (mCurrentTechnique != NULL)
		return mCurrentTechnique->num_passes;
	return 1;
}

void AndroidGL20RenderEffect::BeginPass(const HRunHandle& inRunHandle, int inPass)
{
	mDevice->SetCurrentContext(HRenderContext(inRunHandle));
	mCurrentPass = inPass;
	++mBeginPassRefCount;
	mDevice->PushState();

	if (mCurrentTechnique != NULL)
	{
		RenderEffectPass& aPassData = mTechniques[mCurrentTechnique->technique_number].mPasses[inPass];
		if (aPassData.mUnpacked.mProgram != 0)
		{
			AndroidRenderDeviceES20* aDevice = (AndroidRenderDeviceES20*)mDevice;
			aDevice->FlushBufferedTriangles();
			aDevice->SetShader(&aPassData);
			aDevice->mStateMgr->CommitState();
			UpdateParams();
		}
	}
}

void AndroidGL20RenderEffect::EndPass(const HRunHandle& inRunHandle, int inPass)
{
	mDevice->SetCurrentContext(HRenderContext(inRunHandle));
	mDevice->PopState();
	--mBeginPassRefCount;
}

void AndroidGL20RenderEffect::End(const HRunHandle& inRunHandle)
{
	mDevice->SetCurrentContext(HRenderContext(inRunHandle));
}

bool AndroidGL20RenderEffect::PassUsesVertexShader(int inPass)
{
	if (mCurrentTechnique != NULL)
	{
		PopFXPass* aPass = GetPopFXPass(inPass + mCurrentTechnique->pass_begin);
		return aPass->vertex_shader != EmptyIndex;
	}
	return false;
}

bool AndroidGL20RenderEffect::PassUsesPixelShader(int inPass)
{
	if (mCurrentTechnique != NULL)
	{
		PopFXPass* aPass = GetPopFXPass(inPass + mCurrentTechnique->pass_begin);
		return aPass->pixel_shader != EmptyIndex;
	}
	return false;
}
