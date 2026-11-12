//
//  AndroidGL20StateManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-07.
//
//  The static helpers compileShader and linkProgram have no name in the game; their names here are not real.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidRenderDeviceES20.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGL20StateManager.h"
#include "SexyAppFramework/drivers/graphics/opengl/OpenGLIdRegistry.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/TriVertex.h"

using namespace Sexy;

/////////////// Helpers ///////////////

static bool compileShader(GLuint* shader, GLenum type, const GLchar* source)
{
	GLint status;
	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, &source, NULL);
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		glDeleteShader(*shader);
		return false;
	}
	return true;
}

static bool linkProgram(GLuint prog)
{
	GLint status;
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (status == 0)
		return false;
	return true;
}

/////////////// Lifecycle ///////////////

AndroidGL20StateManager::AndroidGL20StateManager()
{
}

AndroidGL20StateManager::~AndroidGL20StateManager()
{
}

void AndroidGL20StateManager::Init()
{
	super::Init();
	mCurShader = NULL;
	mScreenMatrix.LoadIdentity();
	mScreenMatrixRev = 0;
	GenerateGPUResources();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void AndroidGL20StateManager::Reset()
{
	super::Reset();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void AndroidGL20StateManager::LostFocus()
{
	if (!gSexyAppBase->mLostFocusOnly)
		ReleaseGPUResources();
}

void AndroidGL20StateManager::GotFocus()
{
	Reset();
	GenerateGPUResources();
}

/////////////// States ///////////////

void AndroidGL20StateManager::InitStates()
{
	super::InitStates();

	for (uint32 i = 0; i < ST_COUNT_GL20; ++i)
	{
		mGL20States.push_back(StateVector());
	}

	for (uint32 i = 0; i < ST_COUNT_GL20; ++i)
	{
		mGL20States[i].push_back(State(this, SG_GL20, i));
	}

	mGL20States[ST_GL20_SHADERPROGRAM_ORTHO][0].Init((void*)NULL, "GL20:SHADERPROGRAM_ORTHO");
	mGL20States[ST_GL20_SHADERPROGRAM_3D][0].Init((void*)NULL, "GL20:SHADERPROGRAM_3D");

	InvalidateShader();
}

void AndroidGL20StateManager::ResetStates()
{
	super::ResetStates();
	size_t aCount = mGL20States.size();
	for (size_t i = 0; i < aCount; ++i)
	{
		size_t aStateCount = mGL20States[i].size();
		for (size_t j = 0; j < aStateCount; ++j)
		{
			mGL20States[i][j].Reset();
		}
	}
}

void AndroidGL20StateManager::SetTexture(int theStage, GLuint theTexture, GLuint theSrc)
{
	super::SetTexture(theStage, theTexture, theSrc);
}

void AndroidGL20StateManager::InvalidateShader()
{
	void* aShader = mGL20States[ST_GL20_SHADERPROGRAM_ORTHO][0].GetPtr();
	mGL20States[ST_GL20_SHADERPROGRAM_ORTHO][0].Reset();
	mGL20States[ST_GL20_SHADERPROGRAM_ORTHO][0].SetValue(aShader);
	mGL20States[ST_GL20_SHADERPROGRAM_ORTHO][0].SetDirty();
}

bool AndroidGL20StateManager::DoCommitGL20State(RenderStateManager::State* inState)
{
	AndroidGL20StateManager* m = (AndroidGL20StateManager*)inState->mManager;

	switch (inState->mContext[1])
	{
		case ST_GL20_SHADERPROGRAM_ORTHO:
			if (m->GetVertexFormat() & SexyVF_PackedFormat)
			{
				m->mCurShader = (ShaderInfo*)inState->GetPtr();
				if (m->mCurShader)
				{
					glGetError();
					glUseProgram(m->mCurShader->mPacked.mProgram);
					glGetError();
					float aMatrix[] =
					{
						m->mScreenMatrix.m00, m->mScreenMatrix.m01, m->mScreenMatrix.m02, m->mScreenMatrix.m03,
						m->mScreenMatrix.m10, m->mScreenMatrix.m11, m->mScreenMatrix.m12, m->mScreenMatrix.m13,
						m->mScreenMatrix.m20, m->mScreenMatrix.m21, m->mScreenMatrix.m22, m->mScreenMatrix.m23,
						m->mScreenMatrix.m30, m->mScreenMatrix.m31, m->mScreenMatrix.m32, m->mScreenMatrix.m33
					};
					glUniformMatrix4fv(m->mCurShader->mPacked.mScreenMatrixLoc, 1, GL_FALSE, aMatrix);
					m->mCurShader->mPacked.mScreenMatrixRev = m->mScreenMatrixRev;
				}
			}
			else
			{
				m->mCurShader = (ShaderInfo*)inState->GetPtr();
				if (m->mCurShader)
				{
					glUseProgram(m->mCurShader->mUnpacked.mProgram);
					float aMatrix[] =
					{
						m->mScreenMatrix.m00, m->mScreenMatrix.m01, m->mScreenMatrix.m02, m->mScreenMatrix.m03,
						m->mScreenMatrix.m10, m->mScreenMatrix.m11, m->mScreenMatrix.m12, m->mScreenMatrix.m13,
						m->mScreenMatrix.m20, m->mScreenMatrix.m21, m->mScreenMatrix.m22, m->mScreenMatrix.m23,
						m->mScreenMatrix.m30, m->mScreenMatrix.m31, m->mScreenMatrix.m32, m->mScreenMatrix.m33
					};
					glUniformMatrix4fv(m->mCurShader->mUnpacked.mScreenMatrixLoc, 1, GL_FALSE, aMatrix);
					m->mCurShader->mUnpacked.mScreenMatrixRev = m->mScreenMatrixRev;
				}
			}
			inState->ClearDirty();
			break;
		case ST_GL20_SHADERPROGRAM_3D:
			inState->ClearDirty();
			break;
	}
	return true;
}

bool AndroidGL20StateManager::DoCommitTexGL20State(RenderStateManager::State* inState)
{
	AndroidGL20StateManager* m = (AndroidGL20StateManager*)inState->mManager;

	auto stateId = inState->mContext[1];
	auto subIndex = inState->mContext[2];

	switch (stateId)
	{
		case ST_MISC_VERTEXFORMAT:
			m->InvalidateShader();
			inState->ClearDirty();
			break;
		case ST_MISC_TEXTURE:
			if (inState->GetDword() == 0)
			{
				glActiveTexture(GL_TEXTURE0 + subIndex);
				glBindTexture(GL_TEXTURE_2D, m->mWhiteTex);
			}
			else
			{
				GLuint aTex = inState->GetDword();
				glActiveTexture(GL_TEXTURE0 + subIndex);

				GLuint aSrc = m->mMiscStates[ST_MISC_TEXTURE_SRC][subIndex].GetDword();
				glBindTexture(aSrc, aTex);

				glTexParameteri(aSrc, GL_TEXTURE_WRAP_S, m->mMiscStates[ST_MISC_TEXTURE_WRAP_S][subIndex].GetDword());
				glTexParameteri(aSrc, GL_TEXTURE_WRAP_T, m->mMiscStates[ST_MISC_TEXTURE_WRAP_T][subIndex].GetDword());
				glTexParameteri(aSrc, GL_TEXTURE_MAG_FILTER, m->mMiscStates[ST_MISC_TEXTURE_MAG_FILTER][subIndex].GetDword());
				glTexParameteri(aSrc, GL_TEXTURE_MIN_FILTER, m->mMiscStates[ST_MISC_TEXTURE_MIN_FILTER][subIndex].GetDword());
				m->mMiscStates[ST_MISC_TEXTURE_WRAP_S][subIndex].ClearDirty(true);
				m->mMiscStates[ST_MISC_TEXTURE_WRAP_T][subIndex].ClearDirty(true);
				m->mMiscStates[ST_MISC_TEXTURE_MAG_FILTER][subIndex].ClearDirty(true);
				m->mMiscStates[ST_MISC_TEXTURE_MIN_FILTER][subIndex].ClearDirty(true);
			}
			inState->ClearDirty();
			break;
	}
	return true;
}

RenderStateManager::State::FCommitFunc AndroidGL20StateManager::GetCommitFunc(State* inState)
{
	if (inState->mContext[0] == SG_GL20)
		return DoCommitGL20State;
	if (inState->mContext[0] == SG_MISC && (inState->mContext[1] == ST_MISC_TEXTURE || inState->mContext[1] == ST_MISC_VERTEXFORMAT))
		return DoCommitTexGL20State;
	return super::GetCommitFunc(inState);
}

/////////////// Shaders ///////////////

void AndroidGL20StateManager::GenerateGPUResources()
{
	OutputDebugStrF("GenerateGPUResources");

	mDefaultShader.mPacked.mProgram = glCreateProgram();
	mDefaultShader.mUnpacked.mProgram = glCreateProgram();
	mDefaultShaderMultiTex.mUnpacked.mProgram = glCreateProgram();
	OpenGLIdRegistry::StaticRegisterShaderIds(1, &mDefaultShader.mPacked.mProgram);
	OpenGLIdRegistry::StaticRegisterShaderIds(1, &mDefaultShader.mUnpacked.mProgram);
	OpenGLIdRegistry::StaticRegisterShaderIds(1, &mDefaultShaderMultiTex.mUnpacked.mProgram);

	{
		GLuint vertShader, fragShader;

		compileShader(&vertShader, GL_VERTEX_SHADER,
			"attribute vec4 position;\n"
			"attribute vec4 color;\n"
			"attribute vec2 texcoord0;\n"
			"varying lowp vec4 colorVarying;\n"
			"varying mediump vec2 texVarying0;\n"
			"uniform mat4  screenMatrix;\n"
			"void main()\n"
			"{\n"
			"gl_Position = screenMatrix * vec4(position.x,position.y, position.z,1.0);\n"
			"colorVarying = color;\n"
			"texVarying0 = texcoord0;\n"
			"}\n");
		compileShader(&fragShader, GL_FRAGMENT_SHADER,
			"varying lowp vec4 colorVarying;\n"
			"varying mediump vec2 texVarying0;\n"
			"uniform sampler2D Tex0;\n"
			"uniform sampler2D Tex1;\n"
			"void main()\n"
			"{\n"
			"\t lowp vec4 color = texture2D(Tex0,texVarying0.xy);\n"
			"\t color.a = texture2D(Tex1,texVarying0.xy).a;\n"
			"\t gl_FragColor = color * colorVarying;\n"
			"}\n");
		glAttachShader(mDefaultShaderMultiTex.mUnpacked.mProgram, vertShader);
		glAttachShader(mDefaultShaderMultiTex.mUnpacked.mProgram, fragShader);
		glBindAttribLocation(mDefaultShaderMultiTex.mUnpacked.mProgram, ShaderInfo::ATTRIB_POSITION, "position");
		glBindAttribLocation(mDefaultShaderMultiTex.mUnpacked.mProgram, ShaderInfo::ATTRIB_TEXCOORD0, "texcoord0");
		glBindAttribLocation(mDefaultShaderMultiTex.mUnpacked.mProgram, ShaderInfo::ATTRIB_COLOR, "color");
		linkProgram(mDefaultShaderMultiTex.mUnpacked.mProgram);
		mDefaultShaderMultiTex.mUnpacked.mScreenMatrixLoc = glGetUniformLocation(mDefaultShaderMultiTex.mUnpacked.mProgram, "screenMatrix");
		glUseProgram(mDefaultShaderMultiTex.mUnpacked.mProgram);
		GLint aLoc = glGetUniformLocation(mDefaultShaderMultiTex.mUnpacked.mProgram, "Tex0");
		if (aLoc != -1)
			glUniform1i(aLoc, 0);
		aLoc = glGetUniformLocation(mDefaultShaderMultiTex.mUnpacked.mProgram, "Tex1");
		if (aLoc != -1)
			glUniform1i(aLoc, 1);
		aLoc = glGetUniformLocation(mDefaultShaderMultiTex.mUnpacked.mProgram, "Tex2");
		if (aLoc != -1)
			glUniform1i(aLoc, 2);

		compileShader(&vertShader, GL_VERTEX_SHADER,
			"attribute vec4 position;\n"
			"attribute vec4 color;\n"
			"attribute vec2 texcoord0;\n"
			"varying lowp vec4 colorVarying;\n"
			"varying mediump vec2 texVarying0;\n"
			"uniform mat4  screenMatrix;\n"
			"void main()\n"
			"{\n"
			"gl_Position = screenMatrix * vec4(position.x,position.y, position.z,1.0);\n"
			"colorVarying = color;\n"
			"texVarying0 = texcoord0;\n"
			"}\n");
		compileShader(&fragShader, GL_FRAGMENT_SHADER,
			"varying lowp vec4 colorVarying;\n"
			"varying mediump vec2 texVarying0;\n"
			"uniform sampler2D tex;\n"
			"void main()\n"
			"{\n"
			"\t lowp vec4 color = texture2D(tex,texVarying0.xy);\n"
			"\t gl_FragColor = color * colorVarying;\n"
			"}\n");
		glAttachShader(mDefaultShader.mUnpacked.mProgram, vertShader);
		glAttachShader(mDefaultShader.mUnpacked.mProgram, fragShader);
		glBindAttribLocation(mDefaultShader.mUnpacked.mProgram, ShaderInfo::ATTRIB_POSITION, "position");
		glBindAttribLocation(mDefaultShader.mUnpacked.mProgram, ShaderInfo::ATTRIB_TEXCOORD0, "texcoord0");
		glBindAttribLocation(mDefaultShader.mUnpacked.mProgram, ShaderInfo::ATTRIB_COLOR, "color");
		linkProgram(mDefaultShader.mUnpacked.mProgram);
		mDefaultShader.mUnpacked.mScreenMatrixLoc = glGetUniformLocation(mDefaultShader.mUnpacked.mProgram, "screenMatrix");

		compileShader(&vertShader, GL_VERTEX_SHADER,
			"attribute vec4 position;\n"
			"attribute vec4 color;\n"
			"attribute vec2 texcoord0;\n"
			"varying lowp vec4 colorVarying;\n"
			"varying mediump vec2 texVarying0;\n"
			"uniform mat4  screenMatrix;\n"
			"void main()\n"
			"{\n"
			"gl_Position = screenMatrix * vec4(position.x * 1.0/8.0,position.y * 1.0/8.0, position.z * 1.0/8.0,1.0);\n"
			"colorVarying = color;\n"
			"texVarying0 = texcoord0 * 1.0/8192.0;\n"
			"}\n");
		compileShader(&fragShader, GL_FRAGMENT_SHADER,
			"varying lowp vec4 colorVarying;\n"
			"varying mediump vec2 texVarying0;\n"
			"uniform sampler2D tex;\n"
			"void main()\n"
			"{\n"
			"\t lowp vec4 color = texture2D(tex,texVarying0.xy);\n"
			"\t gl_FragColor = color * colorVarying;\n"
			"}\n");
		glAttachShader(mDefaultShader.mPacked.mProgram, vertShader);
		glAttachShader(mDefaultShader.mPacked.mProgram, fragShader);
		glBindAttribLocation(mDefaultShader.mPacked.mProgram, ShaderInfo::ATTRIB_POSITION, "position");
		glBindAttribLocation(mDefaultShader.mPacked.mProgram, ShaderInfo::ATTRIB_TEXCOORD0, "texcoord0");
		glBindAttribLocation(mDefaultShader.mPacked.mProgram, ShaderInfo::ATTRIB_COLOR, "color");
		linkProgram(mDefaultShader.mPacked.mProgram);
		mDefaultShader.mPacked.mScreenMatrixLoc = glGetUniformLocation(mDefaultShader.mPacked.mProgram, "screenMatrix");
	}

	if (mWhiteTex != 0)
	{
		if (OpenGLIdRegistry::StaticIsTextureIdValid(mWhiteTex))
			glDeleteTextures(1, &mWhiteTex);
		OpenGLIdRegistry::StaticUnregisterIds(1, &mWhiteTex);
		mWhiteTex = 0;
	}
	glGenTextures(1, &mWhiteTex);
	OpenGLIdRegistry::StaticRegisterIds(1, &mWhiteTex);
	glBindTexture(GL_TEXTURE_2D, mWhiteTex);
	uint32 aWhite = 0xFFFFFFFF;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, &aWhite);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void AndroidGL20StateManager::ReleaseGPUResources()
{
	OutputDebugStrF("ReleaseGPUResources");

	if (glIsProgram(mDefaultShader.mPacked.mProgram))
		glDeleteProgram(mDefaultShader.mPacked.mProgram);
	OpenGLIdRegistry::StaticUnregisterShaderIds(1, &mDefaultShader.mPacked.mProgram);
	mDefaultShader.mPacked.mProgram = 0;

	if (glIsProgram(mDefaultShader.mUnpacked.mProgram))
		glDeleteProgram(mDefaultShader.mUnpacked.mProgram);
	OpenGLIdRegistry::StaticUnregisterShaderIds(1, &mDefaultShader.mUnpacked.mProgram);
	mDefaultShader.mUnpacked.mProgram = 0;

	if (glIsProgram(mDefaultShaderMultiTex.mUnpacked.mProgram))
		glDeleteProgram(mDefaultShaderMultiTex.mUnpacked.mProgram);
	OpenGLIdRegistry::StaticUnregisterShaderIds(1, &mDefaultShaderMultiTex.mUnpacked.mProgram);
	mDefaultShaderMultiTex.mUnpacked.mProgram = 0;

	if (mWhiteTex != 0)
	{
		if (OpenGLIdRegistry::StaticIsTextureIdValid(mWhiteTex))
			glDeleteTextures(1, &mWhiteTex);
		OpenGLIdRegistry::StaticUnregisterIds(1, &mWhiteTex);
		mWhiteTex = 0;
	}
}

void AndroidGL20StateManager::SetOrthoProjection(const SexyMatrix4* matrix)
{
	mScreenMatrix = *matrix;
	mScreenMatrixRev++;
	if (mCurShader)
	{
		float aMatrix[] =
		{
			matrix->m00, matrix->m01, matrix->m02, matrix->m03,
			matrix->m10, matrix->m11, matrix->m12, matrix->m13,
			matrix->m20, matrix->m21, matrix->m22, matrix->m23,
			matrix->m30, matrix->m31, matrix->m32, matrix->m33
		};
		glUniformMatrix4fv(mCurShader->mPacked.mScreenMatrixLoc, 1, GL_FALSE, aMatrix);
		glUniformMatrix4fv(mCurShader->mUnpacked.mScreenMatrixLoc, 1, GL_FALSE, aMatrix);
		mCurShader->mPacked.mScreenMatrixRev = mScreenMatrixRev;
		mCurShader->mUnpacked.mScreenMatrixRev = mScreenMatrixRev;
	}
}

ShaderInfo* AndroidGL20StateManager::GetShader()
{
	return (ShaderInfo*)mGL20States[ST_GL20_SHADERPROGRAM_ORTHO][0].GetPtr();
}

void AndroidGL20StateManager::SetShader(ShaderInfo* theShader)
{
	mGL20States[ST_GL20_SHADERPROGRAM_ORTHO][0].SetValue(theShader);
}

bool AndroidGL20StateManager::IsDefaultShader()
{
	ShaderInfo* aShader = GetShader();
	return aShader == &mDefaultShader || aShader == &mDefaultShaderMultiTex;
}
