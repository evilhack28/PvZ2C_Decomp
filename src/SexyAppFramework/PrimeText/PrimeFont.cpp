//
//  PrimeFont.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PrimeText/PrimeFont.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ResourceManager.h"
#include "ReflectionBuilder.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PrimeFont::PrimeFont()
{
}

PrimeFont::PrimeFont(const PrimeFont& otherPrimeFont)
{
}

PrimeFont::~PrimeFont()
{
	PrimeText::Instance()->Font_Remove(mFontDescription);
}

/////////////// Loading ///////////////

bool PrimeFont::LoadResourceFile(const char* inFileName)
{
	void* aData = NULL;
	unsigned long aDataLen = 0;
	if (!gSexyAppBase->ReadBufferFromFile(inFileName, aData, aDataLen))
		return false;
	return LoadFromMem(aDataLen, aData, inFileName);
}

bool PrimeFont::LoadFromMem(ulong inDataLen, const void* inData, const char* inSrcFileName)
{
	PrimeText::Instance()->Font_AddTrueType(inData, inDataLen, &mFontDescription);
	return true;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PrimeFont);

void PrimeFont::StaticClassInit()
{
	StaticGetClass()->SetInfoClass(InfoClass::StaticGetClass());
}
