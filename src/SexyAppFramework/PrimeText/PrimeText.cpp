//
//  PrimeText.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PrimeText/PrimeText.h"
#include "SexyAppFramework/PrimeText/PrimeTypeface.h"
#include "SexyAppFramework/PrimeText/PrimeGlyphCache.h"
#include "SexyAppFramework/PrimeText/PrimeGlyphMesh.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/Graphics.h"

using namespace Sexy;

static PrimeText* sPrimeText;
static eastl::basic_string<char16_t> sString32to16Buffer;

/////////////// Lifecycle ///////////////

PrimeText::PrimeText(SexyAppBase* appPointer)
{
	mEmbeddedTypeface = NULL;
	mDefaultTypeface = NULL;
	mShowDebugRects = false;
	mGlyphCacheVersion = 0;
	Init(appPointer);
}

PrimeText::~PrimeText()
{
	mFontServer->Shutdown();
	delete mFontServer;
	mFontServer = NULL;

	mGlyphCache->Shutdown();
	delete mGlyphCache;
	mGlyphCache = NULL;

	EA::Text::Shutdown();
}

void PrimeText::InstanceCreate(SexyAppBase* appPointer)
{
	sPrimeText = new PrimeText(appPointer);
}

PrimeText* PrimeText::Instance()
{
	return sPrimeText;
}

void PrimeText::Init(SexyAppBase* appPointer)
{
	FontFusionMemObject::SetAllocatorCallbacks(FF_Alloc, FF_Free, FF_Realloc);

	if (appPointer->mOrigScreenHeight > 1023)
		appPointer->isReducedResolutionIPhone();

	mGlyphCache = new PrimeGlyphCache(GetPrimeAllocator(), appPointer, 1024);
	mGlyphCache->SetGlyphPadding(1);
	mGlyphCache->Init(2, 1);

	EA::Text::SetAllocator(GetPrimeAllocator());
	mFontServer = new EA::Text::FontServer(NULL);
	mFontServer->SetAllocator(GetPrimeAllocator());
	EA::Text::SetFontServer(mFontServer);
	mFontServer->Init();

	EA::Text::TextStyle aStyle = TextStyle_Create(L"Embedded", 7, Color(Color::White));
	aStyle.mEffectColor = Color(Color::Black).ToInt();
	aStyle.mEffect = EA::Text::kEffectOutline;
	mEmbeddedTypeface = Typeface(aStyle);
	mDefaultTypeface = mEmbeddedTypeface;
}

/////////////// Typefaces ///////////////

PrimeTypeface* PrimeText::TypefaceSimple(SexyString familyName, int size, Color defaultColor)
{
	EA::Text::TextStyle aStyle = TextStyle_Create(familyName, size, defaultColor);
	return Typeface(aStyle);
}

PrimeTypeface* PrimeText::Typeface(EA::Text::TextStyle& textStyle)
{
	EA::Text::Font* aFont = mFontServer->GetFont(&textStyle, NULL, 0, EA::Text::kCharInvalid, EA::Text::kScriptUnknown, true);
	return new PrimeTypeface(aFont, textStyle);
}

EA::Text::TextStyle PrimeText::TextStyle_Create(EA::Text::Char* familyName, int size, Color defaultColor)
{
	EA::Text::TextStyle aStyle;
	EA::StdC::Strcpy(aStyle.mFamilyNameArray[0], familyName);
	aStyle.mfSize = (float)size;
	aStyle.mColor = defaultColor.ToInt();
	aStyle.mSmooth = EA::Text::kSmoothEnabled;
	return aStyle;
}

EA::Text::TextStyle PrimeText::TextStyle_Create(SexyString familyName, int size, Color defaultColor)
{
	EA::Text::TextStyle aStyle;
	const char16_t* aFamily = String32to16(SexyString(familyName.c_str()));
	EA::StdC::Strcpy(aStyle.mFamilyNameArray[0], aFamily);
	aStyle.mfSize = (float)size;
	aStyle.mColor = defaultColor.ToInt();
	aStyle.mSmooth = EA::Text::kSmoothEnabled;
	return aStyle;
}

PrimeTypeface* PrimeText::TypefaceDefault()
{
	return mDefaultTypeface;
}

/////////////// Drawing ///////////////

void PrimeText::DrawDebugText(Graphics* g, SexyString text, int x, int y, const Color& color)
{
	PrimeText::Instance()->TypefaceDefault()->DrawString_Simple(g, (float)x, (float)y, text, color, NULL);
}

void PrimeText::DebugDrawCache(Graphics* g, int x, int y)
{
	mGlyphCache->DebugDrawCache(g, x, y);
}

/////////////// Glyph cache ///////////////

void PrimeText::ClearGlyphCache()
{
	mGlyphCache->Clear();
	GlyphCacheVersionIncrement();
}

void PrimeText::GlyphCacheVersionIncrement()
{
	if (mGlyphCacheVersion == std::numeric_limits<int>::max())
		mGlyphCacheVersion = 1;
	else
		mGlyphCacheVersion++;
}

PrimeGlyphMesh* PrimeText::GlyphMesh()
{
	PrimeGlyphMesh* aMesh = new PrimeGlyphMesh();
	aMesh->Init(GetPrimeAllocator(), mGlyphCache);
	return aMesh;
}

int PrimeText::CalculateGlyphCacheResolution(int screenHeight, int& glyphPadding)
{
	if (screenHeight > 2047)
	{
		glyphPadding = 1;
		return 2048;
	}
	else if (screenHeight > 1024)
	{
		glyphPadding = 1;
		return 1024;
	}
	else
	{
		glyphPadding = 1;
		return 512;
	}
}

/////////////// Fonts ///////////////

void PrimeText::Font_AddTrueType(const void* inData, ulong inDataLen, EA::Text::FontDescription* mFontDescription)
{
	EA::IO::EATextMemoryStream* aStream = new EA::IO::EATextMemoryStream((void*)inData, inDataLen, true, true, NULL);
	aStream->AddRef();
	mFontServer->AddFace(aStream, EA::Text::kFontTypeOutline, mFontDescription);
	aStream->Release();
}

void PrimeText::Font_Remove(EA::Text::FontDescription& mFontDescription)
{
	mFontServer->RemoveFace(mFontDescription.mFamily);
}

void PrimeText::Font_AddUserEffect(uint32_t effectId, const EA::Text::EIWord* pInstructionList, uint32_t instructionCount)
{
	mFontServer->AddEffect(effectId, pInstructionList, instructionCount);
}

void PrimeText::Font_DebugOutputAllFontNames()
{
	EA::Text::FontDescription aDescriptions[10];
	int aCount = mFontServer->EnumerateFonts(aDescriptions, 10);
	OutputDebugStrF("- Showing %d Fonts\n", aCount);
	for (int i = 0; i < aCount; i++)
	{
		wchar_t* aName = String16ToWString(aDescriptions[i].mFamily, 32);
		OutputDebugStrF("[");
		OutputDebugStrF((const char*)aName);
		OutputDebugStrF("]");
		OutputDebugStrF("\n");
		delete[] aName;
	}
	OutputDebugStrF("---\n");
}

/////////////// String conversion ///////////////

const char16_t* PrimeText::String32to16(SexyString text)
{
	if (sString32to16Buffer.capacity() == 0)
		sString32to16Buffer.resize(1024);
	EA::StdC::Strlcpy(sString32to16Buffer.begin(), text.c_str(), sString32to16Buffer.capacity(), text.size());
	return sString32to16Buffer.c_str();
}

wchar_t* PrimeText::String16ToWString(EA::Text::Char* string, int length)
{
	wchar_t* aResult = new wchar_t[length];
	int i = 0;
	while (i < length)
	{
		aResult[i] = string[i];
		if (string[i] == 0)
			break;
		i++;
	}
	return aResult;
}
