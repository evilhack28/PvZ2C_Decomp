//
//  PrimeTypeface.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PrimeText/PrimeTypeface.h"
#include "SexyAppFramework/PrimeText/PrimeText.h"
#include "SexyAppFramework/PrimeText/PrimeGlyphMesh.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/Graphics.h"

using namespace Sexy;

namespace EA { namespace Text {
	struct LayoutSettings;
	uint32_t LayoutSimple(const Char* pText, uint32_t nTextSize, float x, float y, Font* pFont, LineLayout& lineLayout, LayoutSettings* pLayoutSettings, uint32_t componentFlags);
} }

/////////////// Lifecycle ///////////////

PrimeTypeface::PrimeTypeface(EA::Text::Font* font, EA::Text::TextStyle& defaultStyle)
{
	mFont = font;
	mDefaultStyle = defaultStyle;
	mTypefaceIfShrunk = NULL;
}

PrimeTypeface::~PrimeTypeface()
{
	mFont->Release();
}

/////////////// Accessors ///////////////

PrimeTypeface* PrimeTypeface::ShrunkTypeface()
{
	return mTypefaceIfShrunk;
}

void PrimeTypeface::SetTypefaceIfShrunk(PrimeTypeface* typeface)
{
	mTypefaceIfShrunk = typeface;
}

/////////////// Font metrics ///////////////

float PrimeTypeface::GetHeight()
{
	EA::Text::FontMetrics aMetrics;
	mFont->GetFontMetrics(aMetrics);
	return aMetrics.mfCapsHeight;
}

float PrimeTypeface::GetLineHeight()
{
	EA::Text::FontMetrics aMetrics;
	mFont->GetFontMetrics(aMetrics);
	return aMetrics.mfLineHeight;
}

float PrimeTypeface::GetLineSpacing()
{
	EA::Text::FontMetrics aMetrics;
	mFont->GetFontMetrics(aMetrics);
	return aMetrics.mfLeading;
}

float PrimeTypeface::GetAscent()
{
	EA::Text::FontMetrics aMetrics;
	mFont->GetFontMetrics(aMetrics);
	return aMetrics.mfAscent;
}

float PrimeTypeface::GetDescent()
{
	EA::Text::FontMetrics aMetrics;
	mFont->GetFontMetrics(aMetrics);
	return aMetrics.mfDescent;
}

float PrimeTypeface::GetAscentPadding()
{
	return 0;
}

float PrimeTypeface::GetCharWidth(SexyChar thisChar)
{
	return 1;
}

float PrimeTypeface::GetCharWidthKern(SexyChar curChar, SexyChar prevChar)
{
	return 1;
}

/////////////// Prepare ///////////////

EA::Text::Typesetter PrimeTypeface::PrepareTypesetter(EA::Text::TextStyle& startingTextStyle, float x, float y, float width, float height, EA::Text::HAlignment horiz, EA::Text::VAlignment vert, const Color& color)
{
	EA::Text::Typesetter aTypesetter;
	aTypesetter.SetLayoutSpace(width, x, y);
	startingTextStyle = mDefaultStyle;
	startingTextStyle.mHAlignment = horiz;
	startingTextStyle.mVAlignment = vert;
	if (!color.IsInvalid())
		startingTextStyle.mColor = color.ToInt();
	aTypesetter.SetDefaultTextStyle(&startingTextStyle);
	return aTypesetter;
}

PrimeGlyphMesh* PrimeTypeface::PrepareGlyphMesh(EA::Text::LineLayout& lineLayout, const Color& color, bool useTypesetterColorChanges)
{
	PrimeGlyphMesh* aMesh = PrimeText::Instance()->GlyphMesh();
	aMesh->SetColorRGBA(color.ToInt());
	aMesh->SetLineLayout(&lineLayout);
	aMesh->SetTextStyleColorEnabled(useTypesetterColorChanges);
	aMesh->Build();
	return aMesh;
}

PrimeGlyphMesh* PrimeTypeface::PrepareString_Typesetter(EA::Text::Typesetter& typesetter, float height, bool useTypesetterColorChanges)
{
	EA::Text::LineLayout aLineLayout;
	typesetter.FinalizeParagraph(height);
	aLineLayout = typesetter.GetLineLayout();
	Color aColor(typesetter.GetDefaultTextStyle().mColor);
	return PrepareGlyphMesh(aLineLayout, aColor, useTypesetterColorChanges);
}

void PrimeTypeface::DrawString_Typesetter(Graphics* g, EA::Text::Typesetter& typesetter, float fRectHeight, bool useTypesetterColorChanges)
{
	PrimeGlyphMesh* aMesh = PrepareString_Typesetter(typesetter, fRectHeight, useTypesetterColorChanges);
	aMesh->Draw(g);
	delete aMesh;
}

void PrimeTypeface::ApplyOptionalParameters(PrimeGlyphMesh* glyphMesh, PrimeTextExtraParameters* optionalParameters, float originX, float originY, float width, float height)
{
	if (optionalParameters)
	{
		if (optionalParameters->scaleX != 1.0f || optionalParameters->scaleY != 1.0f)
			glyphMesh->SetPostScale(optionalParameters->scaleX, optionalParameters->scaleY, originX, originY, width, height);
	}
}

PrimeGlyphMesh* PrimeTypeface::PrepareString_Simple(float x, float y, SexyString text, const Color& color)
{
	Color aColor = color.IsInvalid() ? Color(mDefaultStyle.mColor) : color;
	EA::Text::LineLayout aLineLayout;
	EA::Text::LayoutSimple(PrimeText::String32to16(text.c_str()), text.length(), x, y, mFont, aLineLayout, NULL, 20);
	return PrepareGlyphMesh(aLineLayout, aColor, false);
}

PrimeGlyphMesh* PrimeTypeface::PrepareString_Line(float x, float y, float width, SexyString text, EA::Text::HAlignment alignment, const Color& color)
{
	Color aColor = color.IsInvalid() ? Color(mDefaultStyle.mColor) : color;
	EA::Text::Typesetter aTypesetter;
	EA::Text::LineLayout aLineLayout;
	int aResultWidth;
	PrimeTypeface* aTypeface = FitString_Line(text, width, aResultWidth);
	EA::Text::TextStyle& aStyle = aTypeface->GetDefaultStyle();
	EA::Text::HAlignment aOldAlignment = aStyle.mHAlignment;
	aStyle.mHAlignment = alignment;
	aTypesetter.LayoutParagraph(PrimeText::String32to16(text), text.length(), x, y, width + x, y, &aStyle, aLineLayout, 127);
	aStyle.mHAlignment = aOldAlignment;
	return PrepareGlyphMesh(aLineLayout, aColor, false);
}

PrimeGlyphMesh* PrimeTypeface::PrepareString_Paragraph(float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal, EA::Text::VAlignment alignmentVertical, const Color& color)
{
	Color aColor = color.IsInvalid() ? Color(mDefaultStyle.mColor) : color;
	EA::Text::Typesetter aTypesetter;
	EA::Text::LineLayout aLineLayout;
	PrimeTypeface* aTypeface = this;
	if (height < ParagraphHeightUnlimited)
	{
		int aResultHeight;
		aTypeface = FitString_Paragraph(text, width, height, aResultHeight);
	}
	EA::Text::TextStyle& aStyle = aTypeface->GetDefaultStyle();
	EA::Text::HAlignment aOldHAlignment = aStyle.mHAlignment;
	EA::Text::VAlignment aOldVAlignment = aStyle.mVAlignment;
	aStyle.mHAlignment = alignmentHorizontal;
	aStyle.mVAlignment = alignmentVertical;
	aTypesetter.LayoutParagraph(PrimeText::String32to16(text.c_str()), text.length(), x, y, width + x, height + y, &aStyle, aLineLayout, 127);
	aStyle.mHAlignment = aOldHAlignment;
	aStyle.mVAlignment = aOldVAlignment;
	return PrepareGlyphMesh(aLineLayout, aColor, false);
}

/////////////// Draw ///////////////

void PrimeTypeface::DrawString_Simple(Graphics* g, float x, float y, SexyString text, Color color, PrimeTextExtraParameters* optionalParameters)
{
	PrimeGlyphMesh* aMesh = PrepareString_Simple(x, y, text, color);
	ApplyOptionalParameters(aMesh, optionalParameters, x, y, 0, 0);
	aMesh->Draw(g);
	delete aMesh;
}

void PrimeTypeface::DrawString_Line(Graphics* g, float x, float y, float width, SexyString text, EA::Text::HAlignment alignment, Color color, PrimeTextExtraParameters* optionalParameters)
{
	PrimeGlyphMesh* aMesh = PrepareString_Line(x, y, width, text, alignment, color);
	ApplyOptionalParameters(aMesh, optionalParameters, x, y, width, 0);
	aMesh->Draw(g);
	delete aMesh;
}

void PrimeTypeface::DrawString_Paragraph(Graphics* g, float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal, EA::Text::VAlignment alignmentVertical, Color color, PrimeTextExtraParameters* optionalParameters)
{
	PrimeGlyphMesh* aMesh = PrepareString_Paragraph(x, y, width, height, text, alignmentHorizontal, alignmentVertical, color);
	ApplyOptionalParameters(aMesh, optionalParameters, x, y, width, height);
	aMesh->Draw(g);
	delete aMesh;
}

void PrimeTypeface::DrawString_Paragraph(Graphics* g, Rect extents, SexyString text, EA::Text::HAlignment alignmentHorizontal, EA::Text::VAlignment alignmentVertical, Color color, PrimeTextExtraParameters* optionalParameters)
{
	PrimeGlyphMesh* aMesh = PrepareString_Paragraph(extents.mX, extents.mY, extents.mWidth, extents.mHeight, text, alignmentHorizontal, alignmentVertical, color);
	ApplyOptionalParameters(aMesh, optionalParameters, extents.mX, extents.mY, extents.mWidth, extents.mHeight);
	aMesh->Draw(g);
	delete aMesh;
}

/////////////// Fit ///////////////

PrimeTypeface* PrimeTypeface::FitString_Line(SexyString text, int maxWidth, int& resultWidth)
{
	EA::Text::Typesetter aTypesetter;
	PrimeTypeface* aTypeface = this;
	PrimeTypeface* aCurrent;
	int aWidth;
	do
	{
		aCurrent = aTypeface;
		aWidth = aCurrent->SizeString_Line(text);
		if (__builtin_expect(aWidth <= maxWidth, 1))
			break;
		aTypeface = aCurrent->ShrunkTypeface();
	}
	while (aTypeface);
	resultWidth = aWidth;
	return aCurrent;
}

PrimeTypeface* PrimeTypeface::FitString_Paragraph(SexyString text, int maxWidth, int maxHeight, int& resultHeight)
{
	float aLayoutWidth = maxWidth;
	EA::Text::Typesetter aTypesetter;
	PrimeTypeface* aTypeface = this;
	int aWidth, aHeight;
	int aLimit = maxHeight + ParagraphFitSlack;
	for (;;)
	{
		aTypeface->SizeString_Paragraph(text, aWidth, aHeight, aLayoutWidth);
		if (__builtin_expect(aHeight > aLimit, 0))
		{
			PrimeTypeface* aShrunk = aTypeface->ShrunkTypeface();
			if (aShrunk)
			{
				aTypeface = aShrunk;
				continue;
			}
		}
		break;
	}
	resultHeight = aHeight;
	return aTypeface;
}

/////////////// Size ///////////////

int PrimeTypeface::SizeString_Line(SexyString text)
{
	EA::Text::Typesetter aTypesetter;
	EA::Text::Point aSize = aTypesetter.GetParagraphSize(PrimeText::String32to16(text.c_str()), text.length(), &mDefaultStyle);
	return aSize.mX;
}

void PrimeTypeface::SizeString_Paragraph(SexyString text, int& x, int& y, float layoutWidth)
{
	EA::Text::Typesetter aTypesetter;
	EA::Text::Point aSize = aTypesetter.GetParagraphSize(PrimeText::String32to16(text.c_str()), text.length(), &mDefaultStyle, layoutWidth);
	x = (int)aSize.mX;
	y = (int)aSize.mY;
}

int PrimeTypeface::StringWidth(SexyString text)
{
	return SizeString_Line(text);
}
