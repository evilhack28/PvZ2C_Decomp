//
//  OpenGLIdRegistry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/graphics/opengl/OpenGLIdRegistry.h"
#include "SexyAppFramework/drivers/graphics/opengl/GLContext.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

OpenGLIdRegistry::OpenGLIdRegistry() : mFocusPending(true)
{
}

void OpenGLIdRegistry::StaticStartup()
{
	spGlobalRegistry = new OpenGLIdRegistry;
}

void OpenGLIdRegistry::StaticShutdown()
{
	delete spGlobalRegistry;
	spGlobalRegistry = NULL;
}

/////////////// Static wrappers ///////////////

void OpenGLIdRegistry::StaticValidateAllIds()
{
	if (spGlobalRegistry)
		spGlobalRegistry->ValidateAllIds();
}

bool OpenGLIdRegistry::StaticIsTextureIdValid(GLuint texId)
{
	if (spGlobalRegistry)
		return spGlobalRegistry->TextureIdIsValid(texId);
	return true;
}

void OpenGLIdRegistry::StaticRegisterIds(int numTexids, GLuint const* texIds)
{
	if (spGlobalRegistry)
		spGlobalRegistry->RegisterTextureIds(numTexids, texIds);
}

void OpenGLIdRegistry::StaticUnregisterIds(int numTexids, GLuint const* texIds)
{
	if (spGlobalRegistry)
		spGlobalRegistry->UnregisterTextureIds(numTexids, texIds);
}

bool OpenGLIdRegistry::StaticIsShaderIdValid(GLuint texId)
{
	if (spGlobalRegistry)
		return spGlobalRegistry->ShaderIdIsValid(texId);
	return true;
}

void OpenGLIdRegistry::StaticRegisterShaderIds(int numTexids, GLuint const* texIds)
{
	if (spGlobalRegistry)
		spGlobalRegistry->RegisterShaderIds(numTexids, texIds);
}

void OpenGLIdRegistry::StaticUnregisterShaderIds(int numTexids, GLuint const* texIds)
{
	if (spGlobalRegistry)
		spGlobalRegistry->UnregisterShaderIds(numTexids, texIds);
}

void OpenGLIdRegistry::StaticLostFocus()
{
	if (spGlobalRegistry)
		spGlobalRegistry->LostFocus();
}

void OpenGLIdRegistry::StaticGotFocus()
{
	if (spGlobalRegistry)
		spGlobalRegistry->GotFocus();
}

/////////////// GLContext ///////////////

GLContext::GLContext(Image* inImage)
: mDestImage(inImage)
, mInitialized(false)
, mParent(NULL)
, mChildren(&msChildrenPool)
{
}

GLContext::GLContext(const GLContext& inContext)
: mDestImage(inContext.mDestImage)
, mStateContext(inContext.mStateContext)
, mInitialized(true)
, mParent((GLContext*)&inContext)
, mChildren(&msChildrenPool)
{
	mParent->mChildren.push_back(this);
}

GLContext::~GLContext()
{
	auto aChildCount = mChildren.size();
	for (int iChild=0; iChild<aChildCount; ++iChild)
	{
		assert(mChildren[iChild]->mParent == this);
		mChildren[iChild]->mParent = NULL;
	}
	mChildren.clear();

	if (mParent)
	{
		aChildCount = mParent->mChildren.size();
		for (int iChild=0; iChild<aChildCount; ++iChild)
		{
			if (mParent->mChildren[iChild] == this)
			{
				mParent->mChildren.erase(mParent->mChildren.begin()+iChild);
				break;
			}
		}
	}
}

void* GLContext::operator new(size_t size)
{
	return msPool.GetMemory(static_cast<uint32_t>(size));
}

void GLContext::operator delete(void* addr)
{
	msPool.ReturnMemory((uint8*)addr);
}

/////////////// Id lists ///////////////

bool OpenGLIdRegistry::TestIdIsValid(RegistryType& validList, RegistryType& invalidList, GLuint id, std::string resourceName)
{
	if (std::find(invalidList.begin(), invalidList.end(), id) != invalidList.end())
		return false;
	return std::find(validList.begin(), validList.end(), id) != validList.end();
}

void OpenGLIdRegistry::RegisterIds(RegistryType& validList, RegistryType& invalidList, int numTexIds, GLuint const* texIds, std::string resourceName)
{
	for (int i = 0; i < numTexIds; i++)
	{
		if (std::find(validList.begin(), validList.end(), texIds[i]) != validList.end())
		{
			invalidList.push_back(texIds[i]);
			OutputDebugStrF("WARNING!! - Registering %s %d in the GLIdRegistry that was already there!!", resourceName.c_str(), texIds[i]);
		}
		else
		{
			validList.push_back(texIds[i]);
		}
	}
}

void OpenGLIdRegistry::UnregisterIds(RegistryType& validList, RegistryType& invalidList, int numIds, GLuint const* deadIdArray, std::string resourceName)
{
	for (int i = 0; i < numIds; i++)
	{
		RegistryType::iterator it;
		it = std::find(invalidList.begin(), invalidList.end(), deadIdArray[i]);
		if (invalidList.end() == it)
		{
			it = std::find(validList.begin(), validList.end(), deadIdArray[i]);
			if (it != validList.end())
				it = validList.erase(it);
		}
		else
			it = invalidList.erase(it);
	}
}

void OpenGLIdRegistry::ValidateAllIds(RegistryType& validList, RegistryType& invalidList, GLboolean (*resourceTest)(GLuint id), std::string resourceName)
{
	if (!mFocusPending)
		invalidList.clear();

	RegistryType::iterator it = validList.begin();
	while (it != validList.end())
	{
		if (!resourceTest(*it))
		{
			if (std::find(invalidList.begin(), invalidList.end(), *it) == invalidList.end())
				invalidList.push_back(*it);
			it = validList.erase(it);
		}
		else
			++it;
	}
}

void OpenGLIdRegistry::ValidateAllIds()
{
	ValidateAllIds(mTextureValidList, mTextureInvalidList, glIsTexture, mResourceNameTexture);
	ValidateAllIds(mShaderValidList, mShaderInvalidList, glIsShader, mResourceNameShader);
}

bool OpenGLIdRegistry::TextureIdIsValid(GLuint texId)
{
	return TestIdIsValid(mTextureValidList, mTextureInvalidList, texId, mResourceNameTexture);
}

bool OpenGLIdRegistry::ShaderIdIsValid(GLuint texId)
{
	return TestIdIsValid(mShaderValidList, mShaderInvalidList, texId, mResourceNameShader);
}

void OpenGLIdRegistry::RegisterTextureIds(int numTexids, GLuint const* texIds)
{
	RegisterIds(mTextureValidList, mTextureInvalidList, numTexids, texIds, mResourceNameTexture);
}

void OpenGLIdRegistry::UnregisterTextureIds(int numTexIds, GLuint const* deadTexIdxs)
{
	UnregisterIds(mTextureValidList, mTextureInvalidList, numTexIds, deadTexIdxs, mResourceNameTexture);
}

void OpenGLIdRegistry::RegisterShaderIds(int numSurfaceids, GLuint const* surfaceIds)
{
	RegisterIds(mShaderValidList, mShaderInvalidList, numSurfaceids, surfaceIds, mResourceNameShader);
}

void OpenGLIdRegistry::UnregisterShaderIds(int numSurfaceIds, GLuint const* deadSurfaceIdxs)
{
	UnregisterIds(mShaderValidList, mShaderInvalidList, numSurfaceIds, deadSurfaceIdxs, mResourceNameShader);
}
