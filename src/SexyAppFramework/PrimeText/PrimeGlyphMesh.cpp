//
//  PrimeGlyphMesh.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PrimeText/PrimeGlyphMesh.h"
#include "SexyAppFramework/PrimeText/PrimeText.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/DeviceImage.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PrimeGlyphMesh::PrimeGlyphMesh()
	: mAllocator(NULL)
	, mGlyphCache(NULL)
	, mCacheTextureInfo(NULL)
	, mLineLayout(NULL)
	, mColor(0xff000000)
	, mTextStyleColorEnabled(false)
	, mClippingEnabled(false)
	, mClipLeft(-100000.0f)
	, mClipTop(-100000.0f)
	, mClipRight(100000.0f)
	, mClipBottom(100000.0f)
	, mTriangles(NULL)
	, mTrianglesTmp(NULL)
{
	mIsUsedMVPFlag = false;
	mIsMVPDirty = true;
	mScaleToApply = false;
}

PrimeGlyphMesh::~PrimeGlyphMesh()
{
	Shutdown();
}

bool PrimeGlyphMesh::Init(EA::Allocator::ICoreAllocator* allocator, EA::Text::GlyphCache* glyphCache)
{
	mAllocator = allocator;
	mGlyphCache = glyphCache;
	EA::Allocator::EASTLICoreAllocator aAllocator("EAText::PrimeGlyphMesh::mTextures", allocator);
	mTextures.set_allocator(aAllocator);
	return true;
}

bool PrimeGlyphMesh::Shutdown()
{
	mTextures.set_capacity(0);
	ClearSexyVerts();
	return true;
}

bool PrimeGlyphMesh::Reserve(uint32_t glyphCapacity)
{
	AllocateSexyVerts(glyphCapacity);
	return true;
}

/////////////// Accessors ///////////////

void PrimeGlyphMesh::SetLineLayout(EA::Text::LineLayout* pLineLayout)
{
	mLineLayout = pLineLayout;
}

void PrimeGlyphMesh::SetTextStyleColorEnabled(bool enabled)
{
	mTextStyleColorEnabled = enabled;
}

void PrimeGlyphMesh::SetColorRGBA(uint32_t color)
{
	mColor = color;
}

void PrimeGlyphMesh::SetColor(uint32_t color)
{
	mColor = (color & 0xff00ff00) | ((color >> 16) & 0xff) | ((color & 0xff) << 16);
}

void PrimeGlyphMesh::SetClippingEnabled(bool enabled)
{
	mClippingEnabled = enabled;
}

bool PrimeGlyphMesh::IsClippingEnabled() const
{
	return mClippingEnabled;
}

void PrimeGlyphMesh::SetClippingRect(float left, float top, float right, float bottom)
{
	mClipLeft = left;
	mClipTop = top;
	mClipRight = right;
	mClipBottom = bottom;
}

void PrimeGlyphMesh::SetPostScale(float scaleX, float scaleY, float originX, float originY, float width, float height)
{
	mScaleToApply = true;
	mScaleX = scaleX;
	mScaleY = scaleY;
	mScaleOriginX = originX;
	mScaleOriginY = originY;
	mScaleWidth = width;
	mScaleHeight = height;
}

void PrimeGlyphMesh::SetMVPMatrix(float left, float right, float top, float bottom)
{
	mIsMVPDirty = true;
	mIsUsedMVPFlag = true;
	mMVP[1] = 0;
	mMVP[2] = 0;
	mMVP[3] = 0;
	mMVP[4] = 0;
	mMVP[6] = 0;
	mMVP[7] = 0;
	mMVP[8] = 0;
	mMVP[9] = 0;
	mMVP[10] = 1.0f;
	mMVP[11] = 0;
	mMVP[0] = 2.0f / (right - left);
	mMVP[13] = 1.0f;
	mMVP[12] = -1.0f;
	mMVP[14] = 0;
	mMVP[15] = 1.0f;
	mMVP[5] = 2.0f / (top - bottom);
}

void PrimeGlyphMesh::SetMVPMatrix(float* mat)
{
	memcpy(mMVP, mat, sizeof(mMVP));
	mIsMVPDirty = true;
	mIsUsedMVPFlag = true;
}

/////////////// Vertex storage ///////////////

void PrimeGlyphMesh::ClearSexyVerts()
{
	if (mTriangles != NULL)
	{
		delete[] mTriangles;
		mTriangles = NULL;
	}
	if (mTrianglesTmp != NULL)
	{
		delete[] mTrianglesTmp;
		mTrianglesTmp = NULL;
	}
	mIsMVPDirty = true;
}

void PrimeGlyphMesh::AllocateSexyVerts(int glyphCount)
{
	ClearSexyVerts();
	mTriangles = new SexyVertex_Triangle[glyphCount * 2];
	mTrianglesNum = glyphCount * 2;
}

/////////////// Build ///////////////

void PrimeGlyphMesh::Build(float fYScale)
{
	BuildBegin();
	BuildPart(fYScale);
	BuildEnd();
}

bool PrimeGlyphMesh::BuildBegin(uint32_t glyphCount)
{
	mTextures.clear();
	ClearSexyVerts();
	if (mLineLayout != NULL)
	{
		if (glyphCount == 0xffffffff)
			glyphCount = mLineLayout->mGlyphLayoutInfoArray.size();
		Reserve(glyphCount);
	}
	return true;
}

bool PrimeGlyphMesh::BuildPart(float fYScale, uint32_t glyphIndexBegin, uint32_t glyphIndexEnd)
{
	uint32_t aTriangleCount = 0;
	bool aResult = true;
	if (mLineLayout != NULL)
	{
		if (glyphIndexEnd == 0xffffffff)
			glyphIndexEnd = mLineLayout->mGlyphLayoutInfoArray.size();

		if (glyphIndexEnd > glyphIndexBegin)
		{
			EA::Text::GlyphLayoutInfo* aInfo = mLineLayout->mGlyphLayoutInfoArray.begin() + glyphIndexBegin;
			EA::Text::GlyphLayoutInfo* aInfoEnd = mLineLayout->mGlyphLayoutInfoArray.begin() + glyphIndexEnd;
			EA::Text::GlyphId* aGlyphId = mLineLayout->mGlyphArray.begin() + glyphIndexBegin;

			mCacheTextureInfo = mGlyphCache->GetTextureInfo(0);

			uint32_t aLastColor = 0;
			float aClipU0 = 0.0f;
			float aClipU1 = 1.0f;
			float aClipV0 = 0.0f;
			float aClipV1 = 1.0f;

			for (; aInfo != aInfoEnd; ++aInfo, ++aGlyphId, ++glyphIndexBegin)
			{
				EA::Text::Font* aFont = aInfo->mpFont;
				float aX1 = floorf(aInfo->mfX1);
				float aY1 = floorf(aInfo->mfY1);
				float aX2 = floorf(aInfo->mfX2);
				float aY2 = floorf(aInfo->mfY2);
				if (fYScale < 0.0f)
				{
					float aTemp = aY1;
					aY1 = aY2;
					aY2 = aTemp;
				}

				if (aY1 >= aY2 || aX1 >= aX2)
					continue;

				if (mClippingEnabled)
				{
					if (aX2 < mClipLeft || aX1 > mClipRight || aY2 < mClipTop || aY1 > mClipBottom)
						continue;

					if (aX1 <= mClipLeft)
					{
						aClipU0 = (mClipLeft - aX1) / (aX2 - aX1);
						aX1 = mClipLeft;
					}
					else
						aClipU0 = 0.0f;
					if (aX2 >= mClipRight)
					{
						aClipU1 = (mClipRight - aX1) / (aX2 - aX1);
						aX2 = mClipRight;
					}
					else
						aClipU1 = 1.0f;
					if (aY1 <= mClipTop)
					{
						aClipV0 = (mClipTop - aY1) / (aY2 - aY1);
						aY1 = mClipTop;
					}
					else
						aClipV0 = 0.0f;
					if (aY2 >= mClipBottom)
					{
						aClipV1 = (mClipBottom - aY1) / (aY2 - aY1);
						aY2 = mClipBottom;
					}
					else
						aClipV1 = 1.0f;
				}

				const EA::Text::Font::GlyphBitmap* aBitmap;
				TextureUsageInfo aUsage;
				EA::Text::GlyphTextureInfo aTextureInfo;
				uint32_t aGlyph = *aGlyphId;
				if (!mGlyphCache->GetGlyphTextureInfo(aFont, aGlyph, aTextureInfo))
				{
					if (!aFont->RenderGlyphBitmap(&aBitmap, aGlyph, 0, 0.0f, 0.0f))
					{
						fprintf(stderr, "[WARNING] PrimeGlyphMesh_General::BuildPart - Apparently this glyph cannot be rendered.");
						aResult = false;
						break;
					}
					bool aAdded = mGlyphCache->AddGlyphTexture(aFont, aGlyph, aBitmap->mpData, aBitmap->mnWidth, aBitmap->mnHeight, aBitmap->mnStride, aBitmap->mBitmapFormat, aTextureInfo);
					aFont->DoneGlyphBitmap(aBitmap);
					if (!aAdded)
					{
						fprintf(stderr, "[WARNING] PrimeGlyphMesh_General::BuildPart - There is no place to put this glyph into the glyph cache.  You should clear the cache before building the parts.");
						aResult = false;
						break;
					}
				}

				float aU0 = aTextureInfo.mX1;
				float aV0 = aTextureInfo.mY1;
				float aU1 = aTextureInfo.mX2;
				float aV1 = aTextureInfo.mY2;
				if (mClippingEnabled)
				{
					float aWidth = aU1 - aU0;
					float aHeight = aV1 - aV0;
					aU1 = aU0 + aWidth * aClipU1;
					aV1 = aV0 + aHeight * aClipV1;
					aU0 = aU0 + aWidth * aClipU0;
					aV0 = aV0 + aHeight * aClipV0;
				}
				if (fYScale < 0.0f)
				{
					float aTemp = aV0;
					aV0 = aV1;
					aV1 = aTemp;
				}

				size_t aTextureCount = mTextures.size();
				if (aTextureCount == 0)
				{
					aUsage.mImage = ((PrimeGlyphCacheTextureInfo*)aTextureInfo.mpTextureInfo->mTexture)->mImage;
					aUsage.mTriangleFirst = 0;
					aLastColor = mColor;
					aUsage.mIsVertexColorConstant = true;
					mTextures.push_back(aUsage);
				}
				else if (mTextures[aTextureCount - 1].mImage != ((PrimeGlyphCacheTextureInfo*)aTextureInfo.mpTextureInfo->mTexture)->mImage)
				{
					aLastColor = mColor;
					aUsage.mIsVertexColorConstant = true;
					aUsage.mImage = ((PrimeGlyphCacheTextureInfo*)aTextureInfo.mpTextureInfo->mTexture)->mImage;
					aUsage.mTriangleFirst = aTriangleCount;
					mTextures.push_back(aUsage);
				}

				uint32_t aVertexColor;
				if (mTextStyleColorEnabled)
				{
					uint32_t aCharIndex = mLineLayout->GetCharIndexFromGlyphIndex(glyphIndexBegin);
					aLastColor = mLineLayout->mAnalysisInfoArray[aCharIndex].mpTextStyle->mColor;
				}
				if (mColor == aLastColor)
					aVertexColor = mTextStyleColorEnabled ? aLastColor : 0;
				else
					aVertexColor = aLastColor;

				const float kEpsilon = 0.00001f;
				aU0 += kEpsilon;
				aV0 += kEpsilon;
				aU1 += kEpsilon;
				aV1 -= kEpsilon;

				SexyVertex2D* aTri0 = mTriangles[aTriangleCount];
				SexyVertex2D* aTri1 = mTriangles[aTriangleCount + 1];
				aTri0[0].x = aX1; aTri0[0].y = aY1; aTri0[0].color = aVertexColor; aTri0[0].u = aU0; aTri0[0].v = aV0;
				aTri0[1].x = aX1; aTri0[1].y = aY2; aTri0[1].color = aVertexColor; aTri0[1].u = aU0; aTri0[1].v = aV1;
				aTri0[2].x = aX2; aTri0[2].y = aY1; aTri0[2].color = aVertexColor; aTri0[2].u = aU1; aTri0[2].v = aV0;
				aTri1[0].x = aX1; aTri1[0].y = aY2; aTri1[0].color = aVertexColor; aTri1[0].u = aU0; aTri1[0].v = aV1;
				aTri1[1].x = aX2; aTri1[1].y = aY2; aTri1[1].color = aVertexColor; aTri1[1].u = aU1; aTri1[1].v = aV1;
				aTri1[2].x = aX2; aTri1[2].y = aY1; aTri1[2].color = aVertexColor; aTri1[2].u = aU1; aTri1[2].v = aV0;
				aTriangleCount += 2;
			}
		}
	}
	mTrianglesUsed = aTriangleCount;
	return aResult;
}

void PrimeGlyphMesh::SaveStates()
{
}

void PrimeGlyphMesh::RestoreStates()
{
}

/////////////// Drawing ///////////////

void PrimeGlyphMesh::BuildEnd()
{
	uint32_t aCount = mGlyphCache->GetTextureInfoCount();
	for (uint32_t i = 0; i < aCount; i++)
	{
		if (mGlyphCache->IsUpdating(mGlyphCache->GetTextureInfo(i)))
			mGlyphCache->EndUpdate(mGlyphCache->GetTextureInfo(i));
	}
}

void PrimeGlyphMesh::Draw(Graphics* g, uint32_t glyphIndexBegin, uint32_t glyphIndexEnd)
{
	size_t aTextureCount = mTextures.size();
	if (aTextureCount == 0)
		return;

	SaveStates();
	for (uint32_t i = 0; i < aTextureCount; i++)
		Draw_Characters(g, i, i == aTextureCount - 1);
	RestoreStates();
}

void PrimeGlyphMesh::Draw_Characters(Graphics* g, int32 textureIndex, bool isLastTexture)
{
	TextureUsageInfo& aInfo = mTextures[textureIndex];
	int aFirst = aInfo.mTriangleFirst;
	int aCount;
	if (isLastTexture)
		aCount = mTrianglesUsed - aFirst;
	else
		aCount = mTextures[textureIndex + 1].mTriangleFirst - aFirst;
	Draw_CharacterTriangles(g, aInfo.mImage, mTriangles + aFirst, aCount);
}

void PrimeGlyphMesh::Draw_DebugCharacterRects(Graphics* g, SexyVertex2D firstVertex[][3], int32 triangleCount)
{
	for (int i = 0; i < triangleCount / 2; i++)
	{
		SexyVertex2D* aVerts = firstVertex[i * 2];
		Rect aRect;
		aRect.mX = (int)aVerts[0].x;
		aRect.mY = (int)aVerts[0].y;
		aRect.mWidth = (int)(aVerts[2].x - (float)aRect.mX);
		aRect.mHeight = (int)(aVerts[1].y - (float)aRect.mY);
		g->DrawRect(aRect.mX, aRect.mY, aRect.mWidth, aRect.mHeight);
	}
}

void PrimeGlyphMesh::Draw_CharacterTriangles(Graphics* g, Image* image, SexyVertex2D firstVertex[][3], int32_t triangleCount)
{
	if (mColor == 0 && !mTextStyleColorEnabled)
		return;

	Graphics3D* a3D = g->Get3D();
	Color aColor = Color::FromInt(mColor);

	if (mIsUsedMVPFlag && mIsMVPDirty)
	{
		for (int i = 0; i < triangleCount; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				float aX = firstVertex[i][j].x;
				float aY = firstVertex[i][j].y;
				firstVertex[i][j].x = aX * mMVP[0] + aY * mMVP[1] + mMVP[2];
				firstVertex[i][j].y = aX * mMVP[3] + aY * mMVP[4] + mMVP[5];
			}
		}
		mIsMVPDirty = false;
	}

	g->SetColor(aColor);
	bool aColorize = g->GetColorizeImages();
	g->SetColorizeImages(true);
	if (mScaleToApply)
	{
		SexyMatrix3 aMatrix = CalculateScaleTransform(g->mTransX, g->mTransY);
		a3D->PushTransform(aMatrix, true);
		g->DrawTrianglesTex(image, firstVertex, triangleCount, aColor, 0, g->mTransX, g->mTransY, g->mLinearBlend, &g->mClipRect);
		a3D->PopTransform();
	}
	else
	{
		g->DrawTrianglesTex(image, firstVertex, triangleCount);
	}
	g->SetColorizeImages(aColorize);
}

SexyMatrix3 PrimeGlyphMesh::CalculateScaleTransform(float startOffsetX, float startOffsetY)
{
	SexyMatrix3 aMatrix;
	aMatrix.LoadIdentity();
	aMatrix.m00 = mScaleX;
	aMatrix.m11 = mScaleY;
	float aShiftX = (mScaleWidth * 0.5f) * (mScaleX + -1.0f);
	float aShiftY = (mScaleHeight * 0.5f) * (mScaleY + -1.0f);
	aMatrix.m02 = (startOffsetX + mScaleOriginX) * (1.0f - mScaleX) - aShiftX;
	aMatrix.m12 = (startOffsetY + mScaleOriginY) * (1.0f - mScaleY) - aShiftY;
	return aMatrix;
}
