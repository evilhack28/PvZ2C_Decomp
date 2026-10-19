//
//  PrimeTextWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PrimeTextWidget.h"
#include "SexyAppFramework/PrimeText/PrimeGlyphMesh.h"
#include "SexyAppFramework/PrimeText/PrimeTypeface.h"
#include "SexyAppFramework/Graphics.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PrimeTextWidget::PrimeTextWidget()
{
	mClip = false;
	mGlyphMesh = NULL;
	mPrimeTextPotentialText = NULL;
	mFontTextPotentialText = NULL;
	mDontDrawOffscreen = false;
	SetIgnoreMouseInput(true);
}

PrimeTextWidget::PrimeTextWidget(PrimeText_PotentialText* potentialText)
{
	mClip = false;
	mGlyphMesh = NULL;
	mPrimeTextPotentialText = NULL;
	mFontTextPotentialText = NULL;
	mDontDrawOffscreen = false;
	SetPotentialText(potentialText);
	SetIgnoreMouseInput(true);
}

PrimeTextWidget::PrimeTextWidget(FontText_PotentialText* potentialText)
{
	mClip = false;
	mGlyphMesh = NULL;
	mPrimeTextPotentialText = NULL;
	mFontTextPotentialText = NULL;
	mDontDrawOffscreen = false;
	SetPotentialText(potentialText);
	SetIgnoreMouseInput(true);
}

PrimeTextWidget::~PrimeTextWidget()
{
	Clear();
}

/////////////// Potential text ///////////////

void PrimeTextWidget::SetPotentialText(PrimeText_PotentialText* potentialText)
{
	if (mPrimeTextPotentialText)
	{
		delete mPrimeTextPotentialText;
		mPrimeTextPotentialText = NULL;
		ClearGlyphMesh();
	}
	mPrimeTextPotentialText = potentialText;
}

void PrimeTextWidget::SetPotentialText(FontText_PotentialText* potentialText)
{
	if (mFontTextPotentialText)
		delete mFontTextPotentialText;
	mFontTextPotentialText = potentialText;
}

/////////////// Glyph mesh ///////////////

void PrimeTextWidget::SetGlyphMesh(PrimeGlyphMesh* glyphMesh)
{
	ClearGlyphMesh();
	mGlyphMesh = glyphMesh;
}

void PrimeTextWidget::ClearGlyphMesh()
{
	if (mGlyphMesh)
	{
		delete mGlyphMesh;
		mGlyphMesh = NULL;
	}
}

void PrimeTextWidget::UpdateGlyphMeshCacheVersion()
{
	if (mPrimeTextPotentialText)
		mGlyphCacheVersionUsed = PrimeText::Instance()->GlyphCacheVersion();
}

void PrimeTextWidget::Clear()
{
	if (mPrimeTextPotentialText)
	{
		delete mPrimeTextPotentialText;
		mPrimeTextPotentialText = NULL;
	}
	if (mFontTextPotentialText)
	{
		delete mFontTextPotentialText;
		mFontTextPotentialText = NULL;
	}
	ClearGlyphMesh();
}

void PrimeTextWidget::CreateGlyphMesh()
{
	if (mPrimeTextPotentialText)
	{
		mGlyphMesh = mPrimeTextPotentialText->Prepare();
		mGlyphCacheVersionUsed = PrimeText::Instance()->GlyphCacheVersion();
	}
}

void PrimeTextWidget::UpdateGlyphMesh()
{
	if (mPrimeTextPotentialText)
	{
		if (mGlyphMesh)
		{
			if (mGlyphCacheVersionUsed != PrimeText::Instance()->GlyphCacheVersion())
				ClearGlyphMesh();
		}
		if (!mGlyphMesh)
			CreateGlyphMesh();
	}
}

/////////////// Draw ///////////////

void PrimeTextWidget::DrawWithFont(Graphics* g)
{
	FontText_PotentialText* aText = mFontTextPotentialText;
	switch (aText->mRegion)
	{
	case FontText_PotentialText::TextRegionSimple:
		aText->mFont->DrawString_Simple(g, aText->mX, aText->mY, aText->mText);
		break;
	case FontText_PotentialText::TextRegionLine:
		aText->mFont->DrawString_Line(g, aText->mX, aText->mY, aText->mWidth, aText->mText);
		break;
	case FontText_PotentialText::TextRegionParagraph:
		aText->mFont->DrawString_Paragraph(g, aText->mX, aText->mY, aText->mWidth, aText->mHeight, aText->mText);
		break;
	default:
		break;
	}
}

void PrimeTextWidget::DrawWithPrimeFont(Graphics* g)
{
	UpdateGlyphMesh();
	if (!mGlyphMesh)
		return;
	if (mDontDrawOffscreen)
	{
		Point aAbsPos = GetAbsPos();
		Rect aRect(aAbsPos.mX, aAbsPos.mY, mWidth, mHeight);
		if (mPrimeTextPotentialText)
		{
			aRect.mWidth = mPrimeTextPotentialText->mWidth;
			aRect.mHeight = mPrimeTextPotentialText->mHeight;
			if (aRect.mHeight == PrimeTypeface::ParagraphHeightUnlimited)
				aRect.mHeight = 10000;
		}
		if (g->mClipRect != Rect(0, 0, 0, 0))
		{
			if (!g->mClipRect.Intersects(aRect))
				return;
		}
		else if (!gSexyAppBase->mScreenBounds.Intersects(aRect))
			return;
	}
	mGlyphMesh->Draw(g);
}

void PrimeTextWidget::Draw(Graphics* g)
{
	if (mFontTextPotentialText)
		DrawWithFont(g);
	else if (mGlyphMesh || mPrimeTextPotentialText)
		DrawWithPrimeFont(g);
}

/////////////// Accessors ///////////////

void PrimeTextWidget::SetColor(int theIdx, const Color& theColor)
{
	UpdateGlyphMesh();
	if (mGlyphMesh)
		mGlyphMesh->SetColorRGBA(theColor.ToInt());
}

SexyString PrimeTextWidget::GetText()
{
	if (mFontTextPotentialText)
		return mFontTextPotentialText->mText;
	if (mPrimeTextPotentialText)
		return mPrimeTextPotentialText->mText;
	return L"";
}

void PrimeTextWidget::SetText(const SexyString& text)
{
	if (mFontTextPotentialText)
	{
		if (mFontTextPotentialText->mText != text)
			mFontTextPotentialText->mText = text;
	}
	else if (mPrimeTextPotentialText)
	{
		if (mPrimeTextPotentialText->mText != text)
		{
			mPrimeTextPotentialText->mText = text;
			ClearGlyphMesh();
		}
	}
}

Point PrimeTextWidget::GetPosition()
{
	if (mFontTextPotentialText)
		return Point(mFontTextPotentialText->mX, mFontTextPotentialText->mY);
	if (mPrimeTextPotentialText)
		return Point(mPrimeTextPotentialText->mX, mPrimeTextPotentialText->mY);
	return Point();
}

void PrimeTextWidget::SetPosition(int x, int y)
{
	if (mFontTextPotentialText)
	{
		if (mFontTextPotentialText->mX != x || mFontTextPotentialText->mY != y)
		{
			mFontTextPotentialText->mX = x;
			mFontTextPotentialText->mY = y;
		}
	}
	else if (mPrimeTextPotentialText)
	{
		if (mPrimeTextPotentialText->mX != x || mPrimeTextPotentialText->mY != y)
		{
			mPrimeTextPotentialText->mX = x;
			mPrimeTextPotentialText->mY = y;
			ClearGlyphMesh();
		}
	}
}

void PrimeTextWidget::SetRect(Rect region)
{
	if (mPrimeTextPotentialText)
	{
		if (mPrimeTextPotentialText->mX != region.mX || mPrimeTextPotentialText->mY != region.mY ||
			mPrimeTextPotentialText->mWidth != region.mWidth || mPrimeTextPotentialText->mHeight != region.mHeight)
		{
			mPrimeTextPotentialText->mX = region.mX;
			mPrimeTextPotentialText->mY = region.mY;
			mPrimeTextPotentialText->mWidth = region.mWidth;
			mPrimeTextPotentialText->mHeight = region.mHeight;
			ClearGlyphMesh();
		}
	}
}

void PrimeTextWidget::SetScale(float x, float y)
{
	if (mFontTextPotentialText)
	{
		mFontTextPotentialText->mHasOptionalParameters = true;
		mFontTextPotentialText->mOptionalParameters.scaleX = x;
		mFontTextPotentialText->mOptionalParameters.scaleY = y;
	}
	else if (mPrimeTextPotentialText)
	{
		mPrimeTextPotentialText->mHasOptionalParameters = true;
		mPrimeTextPotentialText->mOptionalParameters.scaleX = x;
		mPrimeTextPotentialText->mOptionalParameters.scaleY = y;
		if (mGlyphMesh)
			mGlyphMesh->SetPostScale(x, y, mPrimeTextPotentialText->mX, mPrimeTextPotentialText->mY, mPrimeTextPotentialText->mWidth, mPrimeTextPotentialText->mHeight);
	}
}

void PrimeTextWidget::SetDontDrawWhenOffscreen(bool i_dontDraw)
{
	mDontDrawOffscreen = i_dontDraw;
}
