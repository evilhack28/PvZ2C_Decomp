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

Graphics::Graphics(Image* theDestImage)
	: mStateStack(PooledAllocator<GraphicsState, SimpleMemPool>(&msGraphicsStatePoolAllocator))
{
	mFont = NULL;
	mDestImage = theDestImage;
	mDrawMode = 0;
	mColorizeImages = false;
	mFastStretch = false;
	mWriteColoredString = true;
	mLinearBlend = false;
	mRenderDevice = NULL;
	mGraphics3D = NULL;
	mTransX = 0;
	mTransY = 0;
	mScaleX = 1;
	mScaleY = 1;
	mScaleOrigX = 0;
	mScaleOrigY = 0;

	if (theDestImage != NULL)
	{
		mClipRect = Rect(0, 0, mDestImage->GetWidth(), mDestImage->GetHeight());
		InitRenderInfo(NULL);
	}
}

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

void Graphics::DrawRect(int theX, int theY, int theWidth, int theHeight)
{
	const Color& aColor = GetFinalColor();
	if (aColor.mAlpha != 0)
	{
		Rect aRect((int)mTransX + theX, (int)mTransY + theY, theWidth, theHeight);
		Rect aTestRect((int)mTransX + theX, (int)mTransY + theY, theWidth + 1, theHeight + 1);

		if (aTestRect == aTestRect.Intersection(mClipRect))
		{
			SetAsCurrentContext();
			mRenderDevice->DrawRect(aRect, aColor, mDrawMode);
		}
		else
		{
			FillRect(theX, theY, theWidth + 1, 1);
			FillRect(theX, theY + theHeight, theWidth + 1, 1);
			FillRect(theX, theY + 1, 1, theHeight - 1);
			FillRect(theX + theWidth, theY + 1, 1, theHeight - 1);
		}
	}
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

void Graphics::DrawImageCel(Image* theImageStrip, int theX, int theY, int theCelCol, int theCelRow)
{
	if (theCelRow >= 0 && theCelCol >= 0 &&
		theCelRow < theImageStrip->mNumRows && theCelCol < theImageStrip->mNumCols)
	{
		int aCelWidth = 0;
		if (theImageStrip->mNumCols != 0)
			aCelWidth = theImageStrip->mWidth / theImageStrip->mNumCols;

		int aCelHeight = 0;
		if (theImageStrip->mNumRows != 0)
			aCelHeight = theImageStrip->mHeight / theImageStrip->mNumRows;

		DrawImage(theImageStrip, theX, theY,
			Rect(aCelWidth * theCelCol, aCelHeight * theCelRow, aCelWidth, aCelHeight));
	}
}

void Graphics::DrawImageCel(Image* theImageStrip, const Rect& theDestRect, int theCelCol, int theCelRow)
{
	if (theCelRow >= 0 && theCelCol >= 0 &&
		theCelRow < theImageStrip->mNumRows && theCelCol < theImageStrip->mNumCols)
	{
		int aCelWidth = 0;
		if (theImageStrip->mNumCols != 0)
			aCelWidth = theImageStrip->mWidth / theImageStrip->mNumCols;

		int aCelHeight = 0;
		if (theImageStrip->mNumRows != 0)
			aCelHeight = theImageStrip->mHeight / theImageStrip->mNumRows;

		DrawImage(theImageStrip, theDestRect,
			Rect(aCelWidth * theCelCol, aCelHeight * theCelRow, aCelWidth, aCelHeight));
	}
}

void Graphics::DrawImageTransform(Image* theImage, const Transform& theTransform, const Rect& theSrcRect, float x, float y)
{
	DrawImageTransformHelper(theImage, theTransform, theSrcRect, x, y, false);
}

void Graphics::DrawImageTransformF(Image* theImage, const Transform& theTransform, const Rect& theSrcRect, float x, float y)
{
	DrawImageTransformHelper(theImage, theTransform, theSrcRect, x, y, true);
}

void Graphics::DrawImageTransform(Image* theImage, const Transform& theTransform, float x, float y)
{
	DrawImageTransformHelper(theImage, theTransform, Rect(0, 0, theImage->mWidth, theImage->mHeight), x, y, false);
}

void Graphics::DrawImageTransformF(Image* theImage, const Transform& theTransform, float x, float y)
{
	DrawImageTransformHelper(theImage, theTransform, Rect(0, 0, theImage->mWidth, theImage->mHeight), x, y, true);
}

void Graphics::DrawImageRotated(Image* theImage, int theX, int theY, double theRot, int theRotCenterX, int theRotCenterY, const Rect* theSrcRect)
{
	DrawImageRotatedF(theImage, (float)theX, (float)theY, theRot, (float)theRotCenterX, (float)theRotCenterY, theSrcRect);
}

void Graphics::DrawImageRotatedF(Image* theImage, float theX, float theY, double theRot, const Rect* theSrcRect)
{
	if (theSrcRect != NULL)
		DrawImageRotatedF(theImage, theX, theY, theRot, theSrcRect->mWidth * 0.5f, theSrcRect->mHeight * 0.5f, theSrcRect);
	else
		DrawImageRotatedF(theImage, theX, theY, theRot, theImage->GetWidth() * 0.5f, theImage->GetHeight() * 0.5f, NULL);
}

void Graphics::DrawImageRotatedF(Image* theImage, float theX, float theY, double theRot, float theRotCenterX, float theRotCenterY, const Rect* theSrcRect)
{
	SetAsCurrentContext();

	if (theSrcRect == NULL)
	{
		Rect aSrcRect(0, 0, theImage->mWidth, theImage->mHeight);
		mRenderDevice->BltRotated(theImage, theX + mTransX, theY + mTransY, aSrcRect, mClipRect, GetImageColor(), mDrawMode, theRot, theRotCenterX, theRotCenterY);
	}
	else
	{
		mRenderDevice->BltRotated(theImage, theX + mTransX, theY + mTransY, *theSrcRect, mClipRect, GetImageColor(), mDrawMode, theRot, theRotCenterX, theRotCenterY);
	}
}

void Graphics::DrawImageRotated(Image* theImage, int theX, int theY, double theRot, const Rect* theSrcRect)
{
	if (theSrcRect != NULL)
		DrawImageRotatedF(theImage, (float)theX, (float)theY, theRot, (float)(theSrcRect->mWidth / 2), (float)(theSrcRect->mHeight / 2), theSrcRect);
	else
		DrawImageRotatedF(theImage, (float)theX, (float)theY, theRot, (float)(theImage->GetWidth() / 2), (float)(theImage->GetHeight() / 2), NULL);
}

void Graphics::DrawImageMirror(Image* theImage, int theX, int theY, bool mirror)
{
	DrawImageMirror(theImage, theX, theY, Rect(0, 0, theImage->mWidth, theImage->mHeight), mirror);
}

void Graphics::DrawImageMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, bool mirror)
{
	if (!mirror)
	{
		DrawImage(theImage, theX, theY, theSrcRect);
		return;
	}

	if (theSrcRect.mX + theSrcRect.mWidth <= theImage->GetWidth() &&
		theSrcRect.mY + theSrcRect.mHeight <= theImage->GetHeight())
	{
		int aX = (int)mTransX + theX;
		int aY = (int)mTransY + theY;

		Rect aClippedRect = Rect(aX, aY, theSrcRect.mWidth, theSrcRect.mHeight).Intersection(mClipRect);
		Rect aSrcRect(
			((theSrcRect.mWidth - aClippedRect.mWidth) - (aClippedRect.mX - aX)) + theSrcRect.mX,
			(theSrcRect.mY + aClippedRect.mY) - aY,
			aClippedRect.mWidth, aClippedRect.mHeight);

		if (aSrcRect.mWidth > 0 && aSrcRect.mHeight > 0)
		{
			SetAsCurrentContext();
			mRenderDevice->BltMirror(theImage, aClippedRect.mX, aClippedRect.mY, aSrcRect, GetImageColor(), mDrawMode);
		}
	}
}

void Graphics::DrawImageMirror(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, bool mirror)
{
	if (!mirror)
	{
		DrawImage(theImage, theDestRect, theSrcRect);
		return;
	}

	Rect aDestRect((int)mTransX + theDestRect.mX, (int)mTransY + theDestRect.mY, theDestRect.mWidth, theDestRect.mHeight);

	SetAsCurrentContext();
	mRenderDevice->BltStretched(theImage, aDestRect, theSrcRect, mClipRect, GetImageColor(), mDrawMode, mFastStretch, true);
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

void Graphics::DrawImage(Image* theImage, int theX, int theY, const Rect& theSrcRect)
{
	if (theSrcRect.mX + theSrcRect.mWidth <= theImage->GetWidth() &&
		theSrcRect.mY + theSrcRect.mHeight <= theImage->GetHeight())
	{
		int aX = (int)mTransX + theX;
		int aY = (int)mTransY + theY;

		if (mScaleX == 1.0f && mScaleY == 1.0f)
		{
			Rect aClippedRect = Rect(aX, aY, theSrcRect.mWidth, theSrcRect.mHeight).Intersection(mClipRect);
			Rect aSrcRect(theSrcRect.mX + aClippedRect.mX - aX, theSrcRect.mY + aClippedRect.mY - aY, aClippedRect.mWidth, aClippedRect.mHeight);

			if (aSrcRect.mWidth > 0 && aSrcRect.mHeight > 0)
			{
				SetAsCurrentContext();
				mRenderDevice->Blt(theImage, aClippedRect.mX, aClippedRect.mY, aSrcRect, GetImageColor(), mDrawMode);
			}
		}
		else
		{
			Rect aDestRect(
				(int)(floor(((float)aX - mScaleOrigX) * mScaleX) + mScaleOrigX),
				(int)(floor(mScaleY * ((float)aY - mScaleOrigY)) + mScaleOrigY),
				(int)ceilf((float)theSrcRect.mWidth * mScaleX),
				(int)ceilf(mScaleY * (float)theSrcRect.mHeight));

			SetAsCurrentContext();
			mRenderDevice->BltStretched(theImage, aDestRect, theSrcRect, mClipRect, GetImageColor(), mDrawMode, mFastStretch, false);
		}
	}
}

void Graphics::DrawImage(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect)
{
	Rect aDestRect((int)mTransX + theDestRect.mX, (int)mTransY + theDestRect.mY, theDestRect.mWidth, theDestRect.mHeight);

	if (mScaleX != 1.0f || mScaleY != 1.0f)
	{
		aDestRect = Rect(
			(int)(floor(((float)aDestRect.mX - mScaleOrigX) * mScaleX) + mScaleOrigX),
			(int)(floor(mScaleY * ((float)aDestRect.mY - mScaleOrigY)) + mScaleOrigY),
			(int)ceilf((float)aDestRect.mWidth * mScaleX),
			(int)ceilf(mScaleY * (float)aDestRect.mHeight));
	}

	SetAsCurrentContext();
	mRenderDevice->BltStretched(theImage, aDestRect, theSrcRect, mClipRect, GetImageColor(), mDrawMode, mFastStretch, false);
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

/////////////// triangles ///////////////

void Graphics::DrawTriangleTex(Image* theTexture, const TriVertex& v1, const TriVertex& v2, const TriVertex& v3)
{
	TriVertex aVertices[3] = { v1, v2, v3 };

	SetAsCurrentContext();
	mRenderDevice->BltTriangles(theTexture, &aVertices, 1, GetImageColor(), mDrawMode, mTransX, mTransY, mLinearBlend, &mClipRect);
}

void Graphics::DrawTrianglesTex(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles)
{
	SetAsCurrentContext();
	mRenderDevice->BltTriangles(theTexture, theVertices, theNumTriangles, GetImageColor(), mDrawMode, mTransX, mTransY, mLinearBlend, &mClipRect);
}

void Graphics::DrawTrianglesTex(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Color& theColor, int theDrawMode, float tx, float ty, bool blend, const Rect* theClipRect)
{
	SetAsCurrentContext();
	mRenderDevice->BltTriangles(theTexture, theVertices, theNumTriangles, theColor, theDrawMode, tx, ty, blend, theClipRect);
}

void Graphics::DrawTrianglesTexStrip(Image* theTexture, const TriVertex theVertices[], int theNumTriangles)
{
	DrawTrianglesTexStrip(theTexture, theVertices, theNumTriangles, GetImageColor(), mDrawMode, mTransX, mTransY, mLinearBlend);
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

void Graphics::DrawLineAA(float theStartX, float theStartY, float theEndX, float theEndY)
{
	double aStartX = theStartX + mTransX;
	double aStartY = theStartY + mTransY;
	double aEndX = theEndX + mTransX;
	double aEndY = theEndY + mTransY;

	if (DrawLineClipHelper(&aStartX, &aStartY, &aEndX, &aEndY))
	{
		SetAsCurrentContext();
		mRenderDevice->DrawLine(aStartX, aStartY, aEndX, aEndY, GetFinalColor(), mDrawMode, true);
	}
}

/////////////// text ///////////////

int Graphics::StringWidth(const SexyString& theString)
{
	return mFont->StringWidth(theString);
}

void Graphics::DrawString(const SexyString& theString, int theX, int theY)
{
	if (mFont != NULL)
	{
		const Color& aColor = GetFinalColor();
		mFont->DrawString(this, theX, theY, theString, aColor, mClipRect);
	}
}

int Graphics::DrawStringColor(const SexyString& theString, int theX, int theY, int theOldColor)
{
	return WriteString(theString, theX, theY, -1, -1, true, 0, -1, theOldColor);
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
