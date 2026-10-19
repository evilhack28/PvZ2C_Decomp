//
//  PrimeGlyphCache.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-20.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PrimeText/PrimeGlyphCache.h"
#include "SexyAppFramework/PrimeText/PrimeText.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/DeviceImage.h"
#include "SexyAppFramework/IGraphicsDriver.h"
#include "SexyAppFramework/RenderDevice.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PrimeGlyphCache::PrimeGlyphCache(EA::Allocator::ICoreAllocator* allocator, Sexy::SexyAppBase* appPointer, int textureSize)
	: EA::Text::GlyphCache(allocator)
{
	miInternalGlyphCount = 0;
	miInternalOffset = 0;
	mbFullCopyOnNextUpdate = false;
	mbIsCachingInternaly = true;
	mCurrentTextureInfo = NULL;
	mAppPointer = appPointer;
	mnTextureSizeDefault = textureSize;
}

PrimeGlyphCache::~PrimeGlyphCache()
{
}

/////////////// Texture ///////////////

uintptr_t PrimeGlyphCache::CreateTexture(EA::Text::TextureInfo* textureInfo)
{
	textureInfo->mFormat = EA::Text::kTextureFormatABGR;
	DeviceImage* image = new DeviceImage();
	image->SetImageMode(true, true);
	image->Create(textureInfo->mnSize, textureInfo->mnSize);
	PrimeGlyphCacheTextureInfo* info = (PrimeGlyphCacheTextureInfo*)mpCoreAllocator->Alloc(sizeof(PrimeGlyphCacheTextureInfo), "EAText::Cache::TextureStruct", 1);
	info->mImage = image;
	info->mpTextureData = (uint32_t*)mpCoreAllocator->Alloc(textureInfo->mnSize * textureInfo->mnSize * 4, "EAText::Cache::Texture", 1);
	return (uintptr_t)info;
}

bool PrimeGlyphCache::DestroyTexture(EA::Text::TextureInfo* textureInfo)
{
	PrimeGlyphCacheTextureInfo* info = (PrimeGlyphCacheTextureInfo*)textureInfo->mTexture;
	if (info)
	{
		if (info->mImage)
			delete info->mImage;
		info->mImage = NULL;
		mpCoreAllocator->Free(info->mpTextureData);
		mpCoreAllocator->Free(info);
	}
	return true;
}

bool PrimeGlyphCache::BeginUpdate(EA::Text::TextureInfo* textureInfo)
{
	EA::Thread::AutoFutex lock(mMutex);
	bool result = false;
	if (!textureInfo->mpData)
	{
		result = true;
		textureInfo->mpData = (uint8_t*)((PrimeGlyphCacheTextureInfo*)textureInfo->mTexture)->mpTextureData;
		textureInfo->mnStride = textureInfo->mnSize * 4;
		miInternalGlyphCount = 0;
		miInternalOffset = 0;
		mbIsCachingInternaly = true;
		mCurrentTextureInfo = textureInfo;
		mMutex.Lock();
	}
	return result;
}

bool PrimeGlyphCache::EndUpdate(EA::Text::TextureInfo* textureInfo)
{
	EA::Thread::AutoFutex lock(mMutex);
	if (!textureInfo->mpData)
		return false;
	PrimeGlyphCacheTextureInfo* info = (PrimeGlyphCacheTextureInfo*)textureInfo->mTexture;
	if (miInternalGlyphCount)
	{
		DeviceImage* image = info->mImage;
		if (!image->GetRenderData())
			mAppPointer->mGraphicsDriver->GetRenderDevice()->Get3D()->CreateImageRenderData(image);
		uint32_t* data = info->mpTextureData;
		if (!mbIsCachingInternaly || mbFullCopyOnNextUpdate)
		{
			mAppPointer->mGraphicsDriver->GetRenderDevice()->CopyIntoImage(image, 0, 0, textureInfo->mnSize, textureInfo->mnSize, data);
			mbFullCopyOnNextUpdate = false;
		}
		else
		{
			for (int i = 0; i < (int)miInternalGlyphCount; i++)
			{
				InternalGlyphInfo& glyph = mInternalGlyphInfo[i];
				if (glyph.miSizeX && glyph.miSizeY)
					mAppPointer->mGraphicsDriver->GetRenderDevice()->CopyIntoImage(image, glyph.miDestX, glyph.miDestY, glyph.miSizeX, glyph.miSizeY, &mpInternalCache[glyph.miOffset]);
			}
			mbFullCopyOnNextUpdate = false;
		}
	}
	textureInfo->mpData = NULL;
	mCurrentTextureInfo = NULL;
	mMutex.Unlock();
	return true;
}

bool PrimeGlyphCache::WriteTextureArea(EA::Text::TextureInfo* pTextureInfo, uint32_t nDestPositionX, uint32_t nDestPositionY,
                                       const void* pSourceData, uint32_t nSourceSizeX, uint32_t nSourceSizeY,
                                       uint32_t sourceStride, uint32_t nSourceFormat)
{
	EA::Text::GlyphCache::WriteTextureArea(pTextureInfo, nDestPositionX, nDestPositionY, pSourceData, nSourceSizeX, nSourceSizeY, sourceStride, nSourceFormat);
	if (!mbIsCachingInternaly)
		return true;
	uint32_t size = nSourceSizeY * 4 * nSourceSizeX;
	if ((uint32_t)(miInternalOffset + size) >= EAMTEXT_INTERNAL_CACHE_SIZE || miInternalGlyphCount >= EAMTEXT_INTERNAL_CACHED_GLYPH_COUNT_MAX)
	{
		mbIsCachingInternaly = false;
		return true;
	}
	WriteTextureArea(&mpInternalCache[miInternalOffset], 0, 0, nSourceSizeX << 2, pTextureInfo->mFormat, pSourceData, nSourceSizeX, nSourceSizeY, sourceStride, nSourceFormat);
	InternalGlyphInfo& glyph = mInternalGlyphInfo[miInternalGlyphCount];
	glyph.miDestX = nDestPositionX;
	glyph.miDestY = nDestPositionY;
	glyph.miSizeX = nSourceSizeX;
	glyph.miSizeY = nSourceSizeY;
	glyph.miOffset = miInternalOffset;
	miInternalGlyphCount++;
	miInternalOffset += size;
	return true;
}

void PrimeGlyphCache::WriteTextureArea(void* pDest, uint32_t nDestPositionX, uint32_t nDestPositionY,
                                       uint32_t nDestStride, uint32_t nDestFormat,
                                       const void* pSourceData, uint32_t nSourceSizeX, uint32_t nSourceSizeY,
                                       uint32_t nSourceStride, uint32_t nSourceFormat)
{
	EA::Text::GlyphCache::WriteTextureArea(pDest, nDestPositionX, nDestPositionY, nDestStride, nDestFormat, pSourceData, nSourceSizeX, nSourceSizeY, nSourceStride, nSourceFormat);
}

void PrimeGlyphCache::Clear()
{
	ClearTexture(mTextureInfoArray.front());
	mbFullCopyOnNextUpdate = true;
}

/////////////// Glyph image ///////////////

DeviceImage* PrimeGlyphCache::GetGlyphImage(EA::Text::TextureInfo* textureInfo)
{
	return ((PrimeGlyphCacheTextureInfo*)textureInfo->mTexture)->mImage;
}

DeviceImage* PrimeGlyphCache::PrepareGlyphImage(EA::Text::TextureInfo* textureInfo)
{
	DeviceImage* image = GetGlyphImage(textureInfo);
	if (!image->GetRenderData())
		mAppPointer->mGraphicsDriver->GetRenderDevice()->Get3D()->CreateImageRenderData(image);
	return image;
}

void PrimeGlyphCache::CopyEntireGlyphImage(EA::Text::TextureInfo* textureInfo)
{
	if (textureInfo && textureInfo->mTexture)
	{
		PrimeGlyphCacheTextureInfo* info = (PrimeGlyphCacheTextureInfo*)textureInfo->mTexture;
		uint32_t* data = info->mpTextureData;
		if (data)
		{
			DeviceImage* image = info->mImage;
			if (image)
				mAppPointer->mGraphicsDriver->GetRenderDevice()->CopyIntoImage(image, 0, 0, textureInfo->mnSize, textureInfo->mnSize, data);
		}
	}
}

void PrimeGlyphCache::DebugDrawCache(Sexy::Graphics* g, int x, int y)
{
	g->DrawImage(GetGlyphImage(mTextureInfoArray.front()), x, y);
}
