//
//  RenderEffect.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "RenderEffect.h"
#include "ResourceManager.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RenderEffectDefinition);

/////////////// Reflection ///////////////

void RenderEffectDefinition::StaticClassInit()
{
	StaticGetClass()->SetInfoClass(InfoClass::StaticGetClass());
}

bool RenderEffectDefinition::LoadFromMem(uint32 inDataLen, const void* inData, const char* inSrcFileName, const char* inDataFormat)
{
	mData.reserve(inDataLen);
	mData.resize(inDataLen);
	if (inDataLen != 0)
		memcpy(&mData[0], inData, inDataLen);
	mSrcFileName = inSrcFileName;
	mDataFormat = inDataFormat;
	return true;
}

bool RenderEffectDefinition::LoadFromFile(const char* inFileName, const char* inSrcFileName)
{
	std::string aPath = inFileName;
	aPath = GetFileDir(inFileName, true);
	aPath += GetFileName(inFileName, true);
	aPath += ".popfx";
	Buffer aBuffer;
	if (!gSexyAppBase->ReadBufferFromFile(aPath, &aBuffer, true))
		return false;

	std::string anExt;
	int aDot = aPath.find_last_of('.');
	if (aDot != -1)
		anExt = Lower(aPath.substr(aDot));
	if (anExt.length() > 1)
		anExt = anExt.substr(1);
	return LoadFromMem(aBuffer.GetDataLen(), aBuffer.GetDataPtr(), inSrcFileName, anExt.c_str());
}
