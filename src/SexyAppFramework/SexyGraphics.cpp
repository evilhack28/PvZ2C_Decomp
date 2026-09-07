//
//  SexyGraphics.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Sexy::Graphics + Sexy::GraphicsState. (src/SexyAppFramework/Graphics.cpp is
//  Android::Graphics, an unrelated JNI bridge.)
//  Reconstructed by EvilHack28 on 2026-09-07.
//

#include "Graphics.h"
#include "RenderDevice.h"

using namespace Sexy;

/////////////// GraphicsState ///////////////

void GraphicsState::CopyStateFrom(const GraphicsState* theState)
{
	mDestImage = theState->mDestImage;
	mTransX = theState->mTransX;
	mTransY = theState->mTransY;
	mClipRect = theState->mClipRect;
	mFont = theState->mFont;
	mPushedColorVector = theState->mPushedColorVector;
	mDrawMode = theState->mDrawMode;
	mColor = theState->mColor;
	mFinalColor = theState->mFinalColor;
	mColorizeImages = theState->mColorizeImages;
	mFastStretch = theState->mFastStretch;
	mWriteColoredString = theState->mWriteColoredString;
	mLinearBlend = theState->mLinearBlend;
	mIs3D = theState->mIs3D;
	mScaleX = theState->mScaleX;
	mScaleY = theState->mScaleY;
	mScaleOrigX = theState->mScaleOrigX;
	mScaleOrigY = theState->mScaleOrigY;
}

/////////////// Graphics ctors / dtor ///////////////

Graphics::Graphics(const Graphics& theGraphics)
	: mStateStack(PooledAllocator<GraphicsState, SimpleMemPool>(&msGraphicsStatePoolAllocator))
{
	CopyStateFrom(&theGraphics);
	InitRenderInfo(&theGraphics);
}

Graphics::~Graphics()
{
	if (mGraphics3D != NULL)
		delete mGraphics3D;

	if (mRenderDevice != NULL)
		mRenderDevice->DeleteContext(mRenderContext);
}

/////////////// small accessors ///////////////

void Graphics::SetFont(Font* theFont) { mFont = theFont; }
Font* Graphics::GetFont() { return mFont; }
const Color& Graphics::GetColor() { return mColor; }
Graphics3D* Graphics::Get3D() { return mGraphics3D; }
void Graphics::SetDrawMode(int theDrawMode) { mDrawMode = theDrawMode; }
int Graphics::GetDrawMode() { return mDrawMode; }
void Graphics::SetColorizeImages(bool colorizeImages) { mColorizeImages = colorizeImages; }
bool Graphics::GetColorizeImages() { return mColorizeImages; }
void Graphics::SetFastStretch(bool fastStretch) { mFastStretch = fastStretch; }
bool Graphics::GetFastStretch() { return mFastStretch; }
void Graphics::SetLinearBlend(bool linear) { mLinearBlend = linear; }
bool Graphics::GetLinearBlend() { return mLinearBlend; }

/////////////// color ///////////////

void Graphics::SetColor(const Color& theColor)
{
	mColor = theColor;
	CalcFinalColor();
}

void Graphics::PushColorMult()
{
	mPushedColorVector.push_back(mFinalColor);
	CalcFinalColor();
}

void Graphics::PopColorMult()
{
	mPushedColorVector.pop_back();
	CalcFinalColor();
}

const Color& Graphics::GetFinalColor()
{
	if (mPushedColorVector.size() > 0)
		return mFinalColor;
	else
		return mColor;
}

void Graphics::CalcFinalColor()
{
	if (mPushedColorVector.size() == 0)
	{
		mFinalColor = mColor;
	}
	else
	{
		const Color& aMult = mPushedColorVector.back();
		mFinalColor = Color(
			std::min(255, aMult.mRed * mColor.mRed / 255),
			std::min(255, aMult.mGreen * mColor.mGreen / 255),
			std::min(255, aMult.mBlue * mColor.mBlue / 255),
			std::min(255, aMult.mAlpha * mColor.mAlpha / 255));
	}
}

/////////////// transform ///////////////

void Graphics::Translate(int theTransX, int theTransY)
{
	mTransX += theTransX;
	mTransY += theTransY;
}

void Graphics::TranslateF(float theTransX, float theTransY)
{
	mTransX += theTransX;
	mTransY += theTransY;
}

void Graphics::SetScale(float theScaleX, float theScaleY, float theOrigX, float theOrigY)
{
	mScaleX = theScaleX;
	mScaleY = theScaleY;
	mScaleOrigX = theOrigX + mTransX;
	mScaleOrigY = theOrigY + mTransY;
}

/////////////// clip ///////////////

void Graphics::SetClipRect(const Rect& theRect)
{
	SetClipRect(theRect.mX, theRect.mY, theRect.mWidth, theRect.mHeight);
}

void Graphics::SetClipRect(int theX, int theY, int theWidth, int theHeight)
{
	Rect aClipRect(0, 0, mDestImage->GetWidth(), mDestImage->GetHeight());
	mClipRect = aClipRect.Intersection(Rect((int)mTransX + theX, (int)mTransY + theY, theWidth, theHeight));
}

void Graphics::ClipRect(const Rect& theRect)
{
	ClipRect(theRect.mX, theRect.mY, theRect.mWidth, theRect.mHeight);
}

void Graphics::ClipRect(int theX, int theY, int theWidth, int theHeight)
{
	mClipRect = mClipRect.Intersection(Rect((int)mTransX + theX, (int)mTransY + theY, theWidth, theHeight));
}

void Graphics::ClearClipRect()
{
	mClipRect = Rect(0, 0, mDestImage->GetWidth(), mDestImage->GetHeight());
}

/////////////// rect forwarders ///////////////

void Graphics::ClearRect(const Rect& theRect)
{
	ClearRect(theRect.mX, theRect.mY, theRect.mWidth, theRect.mHeight);
}

void Graphics::ClearRect(int theX, int theY, int theWidth, int theHeight)
{
	SetAsCurrentContext();
	Rect aRect = Rect((int)mTransX + theX, (int)mTransY + theY, theWidth, theHeight).Intersection(mClipRect);
	mRenderDevice->ClearRect(aRect);
}

void Graphics::FillRect(const Rect& theRect)
{
	FillRect(theRect.mX, theRect.mY, theRect.mWidth, theRect.mHeight);
}

void Graphics::DrawRect(const Rect& theRect)
{
	DrawRect(theRect.mX, theRect.mY, theRect.mWidth, theRect.mHeight);
}

void Graphics::FillRect(int theX, int theY, int theWidth, int theHeight)
{
	const Color& aColor = GetFinalColor();
	if (aColor.mAlpha == 0)
		return;

	SetAsCurrentContext();
	Rect aRect = Rect((int)mTransX + theX, (int)mTransY + theY, theWidth, theHeight).Intersection(mClipRect);
	mRenderDevice->FillRect(aRect, aColor, mDrawMode);
}

const Color& Graphics::GetImageColor()
{
	if (mPushedColorVector.size() != 0)
	{
		if (mColorizeImages)
			return mFinalColor;

		return mPushedColorVector.back();
	}

	if (mColorizeImages)
		return mColor;

	return mDefaultImageColor;
}

/////////////// image forwarders ///////////////

void Graphics::DrawImageBox(const Rect& theDest, Image* theComponentImage)
{
	DrawImageBox(Rect(0, 0, theComponentImage->mWidth, theComponentImage->mHeight), theDest, theComponentImage);
}

void Graphics::DrawImageBoxStretch(const Rect& theDest, Image* theComponentImage)
{
	DrawImageBoxStretch(Rect(0, 0, theComponentImage->mWidth, theComponentImage->mHeight), theDest, theComponentImage);
}

void Graphics::DrawImageCel(Image* theImageStrip, int theX, int theY, int theCel)
{
	DrawImageCel(theImageStrip, theX, theY, theCel % theImageStrip->mNumCols, theCel / theImageStrip->mNumCols);
}

void Graphics::DrawImageCel(Image* theImageStrip, const Rect& theDestRect, int theCel)
{
	DrawImageCel(theImageStrip, theDestRect, theCel % theImageStrip->mNumCols, theCel / theImageStrip->mNumCols);
}

void Graphics::DrawImageTransform(Image* theImage, const Transform& theTransform, const Rect& theSrcRect, float x, float y)
{
	DrawImageTransformHelper(theImage, theTransform, theSrcRect, x, y, false);
}

void Graphics::DrawImageTransformF(Image* theImage, const Transform& theTransform, const Rect& theSrcRect, float x, float y)
{
	DrawImageTransformHelper(theImage, theTransform, theSrcRect, x, y, true);
}

void Graphics::DrawImageRotated(Image* theImage, int theX, int theY, double theRot, int theRotCenterX, int theRotCenterY, const Rect* theSrcRect)
{
	DrawImageRotatedF(theImage, (float)theX, (float)theY, theRot, (float)theRotCenterX, (float)theRotCenterY, theSrcRect);
}

void Graphics::DrawImageMirror(Image* theImage, int theX, int theY, bool mirror)
{
	DrawImageMirror(theImage, theX, theY, Rect(0, 0, theImage->mWidth, theImage->mHeight), mirror);
}

void Graphics::DrawImage(Image* theImage, int theX, int theY)
{
	if (mScaleX == 1.0f && mScaleY == 1.0f)
	{
		int aX = (int)mTransX + theX;
		int aY = (int)mTransY + theY;

		Rect aClippedRect = Rect(aX, aY, theImage->GetWidth(), theImage->GetHeight()).Intersection(mClipRect);
		Rect aSrcRect(aClippedRect.mX - aX, aClippedRect.mY - aY, aClippedRect.mWidth, aClippedRect.mHeight);

		if (aSrcRect.mWidth > 0 && aSrcRect.mHeight > 0)
		{
			SetAsCurrentContext();
			mRenderDevice->Blt(theImage, aClippedRect.mX, aClippedRect.mY, aSrcRect, GetImageColor(), mDrawMode);
		}
	}
	else
	{
		DrawImage(theImage, theX, theY, Rect(0, 0, theImage->mWidth, theImage->mHeight));
	}
}

void Graphics::DrawImage(Image* theImage, int theX, int theY, int theStretchedWidth, int theStretchedHeight)
{
	Rect aDestRect((int)mTransX + theX, (int)mTransY + theY, theStretchedWidth, theStretchedHeight);
	Rect aSrcRect(0, 0, theImage->mWidth, theImage->mHeight);

	SetAsCurrentContext();
	mRenderDevice->BltStretched(theImage, aDestRect, aSrcRect, mClipRect, GetImageColor(), mDrawMode, mFastStretch, false);
}

void Graphics::CopyIntoImage(Image* theTexture, int offsetX, int offsetY, int widthX, int widthY, void* sourceTextureData)
{
	mRenderDevice->CopyIntoImage(theTexture, offsetX, offsetY, widthX, widthY, sourceTextureData);
}

void Graphics::DrawImageF(Image* theImage, float theX, float theY, const Rect& theSrcRect)
{
	float aX = theX + mTransX;
	float aY = theY + mTransY;

	SetAsCurrentContext();
	mRenderDevice->BltF(theImage, aX, aY, theSrcRect, mClipRect, GetImageColor(), mDrawMode);
}

void Graphics::DrawImageF(Image* theImage, float theX, float theY)
{
	float aX = theX + mTransX;
	float aY = theY + mTransY;
	Rect aSrcRect(0, 0, theImage->mWidth, theImage->mHeight);

	SetAsCurrentContext();
	mRenderDevice->BltF(theImage, aX, aY, aSrcRect, mClipRect, GetImageColor(), mDrawMode);
}

void Graphics::DrawImageMatrix2(Image* theImage, const SexyMatrix3& theMatrix, const Rect& theSrcRect)
{
	SetAsCurrentContext();
	mRenderDevice->BltMatrix2(theImage, mTransX, mTransY, theMatrix, mClipRect, GetImageColor(), mDrawMode, theSrcRect, mLinearBlend, false);
}

void Graphics::DrawImageMatrix2(Image* theImage, const SexyMatrix3& theMatrix)
{
	Rect aSrcRect(0, 0, theImage->mWidth, theImage->mHeight);
	SetAsCurrentContext();
	mRenderDevice->BltMatrix2(theImage, mTransX, mTransY, theMatrix, mClipRect, GetImageColor(), mDrawMode, aSrcRect, mLinearBlend, false);
}

void Graphics::DrawImageMatrix(Image* theImage, const SexyMatrix3& theMatrix, const Rect& theSrcRect, float x, float y)
{
	SetAsCurrentContext();
	mRenderDevice->BltMatrix(theImage, x + mTransX, y + mTransY, theMatrix, mClipRect, GetImageColor(), mDrawMode, theSrcRect, mLinearBlend);
}

void Graphics::DrawImageMatrix(Image* theImage, const SexyMatrix3& theMatrix, float x, float y)
{
	Rect aSrcRect(0, 0, theImage->mWidth, theImage->mHeight);
	SetAsCurrentContext();
	mRenderDevice->BltMatrix(theImage, x + mTransX, y + mTransY, theMatrix, mClipRect, GetImageColor(), mDrawMode, aSrcRect, mLinearBlend);
}

/////////////// polygon fill comparators ///////////////

int Graphics::PFCompareInd(const void* u, const void* v)
{
	return mPFPoints[*(const int*)u].mY > mPFPoints[*(const int*)v].mY ? 1 : -1;
}

int Graphics::PFCompareActive(const void* u, const void* v)
{
	return ((const Edge*)u)->mX > ((const Edge*)v)->mX ? 1 : -1;
}

/////////////// lines ///////////////

void Graphics::DrawLine(float theStartX, float theStartY, float theEndX, float theEndY)
{
	double aStartX = theStartX + mTransX;
	double aStartY = theStartY + mTransY;
	double aEndX = theEndX + mTransX;
	double aEndY = theEndY + mTransY;

	if (DrawLineClipHelper(&aStartX, &aStartY, &aEndX, &aEndY))
	{
		SetAsCurrentContext();
		mRenderDevice->DrawLine(aStartX, aStartY, aEndX, aEndY, GetFinalColor(), mDrawMode, false);
	}
}

/////////////// text ///////////////

int Graphics::StringWidth(const SexyString& theString)
{
	return mFont->StringWidth(theString);
}

/////////////// state stack ///////////////

void Graphics::SetAsCurrentContext()
{
	mRenderDevice->SetCurrentContext(mRenderContext);
}

void Graphics::PushState()
{
	mStateStack.push_back(GraphicsState());
	mStateStack.back().CopyStateFrom(this);
	SetAsCurrentContext();
	mRenderDevice->PushState();
}

void Graphics::PopState()
{
	if (mStateStack.size() != 0)
	{
		CopyStateFrom(&mStateStack.back());
		mStateStack.pop_back();
	}

	SetAsCurrentContext();
	mRenderDevice->PopState();
}
