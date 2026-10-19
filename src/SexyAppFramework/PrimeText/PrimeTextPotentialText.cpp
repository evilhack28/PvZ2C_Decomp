//
//  PrimeTextPotentialText.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PrimeText/PrimeTextPotentialText.h"
#include "SexyAppFramework/PrimeText/PrimeTypeface.h"
#include "SexyAppFramework/PrimeText/PrimeGlyphMesh.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PrimeText_PotentialText::PrimeText_PotentialText()
{
	mTypeface = NULL;
	mRegion = TextRegionInvalid;
	mWidth = 0;
	mHeight = 0;
}

PrimeText_PotentialText::~PrimeText_PotentialText()
{
}

/////////////// Accessors ///////////////

void PrimeText_PotentialText::SetOptionalParameters(PrimeTextExtraParameters* optionalParameters)
{
	if (optionalParameters)
	{
		mOptionalParameters = *optionalParameters;
		mHasOptionalParameters = true;
	}
	else
		mHasOptionalParameters = false;
}

/////////////// Prepare ///////////////

PrimeGlyphMesh* PrimeText_PotentialText::Prepare()
{
	PrimeGlyphMesh* aMesh = NULL;
	switch (mRegion)
	{
	case TextRegionSimple:
		aMesh = mTypeface->PrepareString_Simple(mX, mY, mText, mColor);
		break;
	case TextRegionLine:
		aMesh = mTypeface->PrepareString_Line(mX, mY, mWidth, mText, mHorizAlign, mColor);
		break;
	case TextRegionParagraph:
		aMesh = mTypeface->PrepareString_Paragraph(mX, mY, mWidth, mHeight, mText, mHorizAlign, mVertAlign, mColor);
		break;
	default:
		break;
	}

	if (mHasOptionalParameters)
		mTypeface->ApplyOptionalParameters(aMesh, &mOptionalParameters, mX, mY, mWidth, mHeight);
	return aMesh;
}
