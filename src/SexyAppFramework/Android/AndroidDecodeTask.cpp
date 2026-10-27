//
//  AndroidDecodeTask.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-26.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/resstreams/android/AndroidDecodeTask.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGraphicsDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

static void RoundUpToTile(uint& theValue)
{
	uint remainder = theValue & 0x1f;
	theValue += remainder != 0 ? 0x20 - remainder : 0;
}

AndroidDecodeTask::AndroidDecodeTask(AndroidResStreamsDriver* theDriver, IResStreamsDriver::TaskResource* theInBuffer, uint32 theByteOffset,
	ResStreamTextureDescriptor* theTextureDesc, uint32 theTextureRef, uint32 theTextureRefMulti, uint32 theTileOffset, uint32 theNumTiles)
	: mDriver(theDriver)
	, mType(IResStreamsDriver::TASK_DECODE)
	, mIsExecuting(false)
	, mState(0)
	, mInBuffer(theInBuffer)
	, mData(NULL)
{
	if (theInBuffer != NULL)
	{
		theInBuffer->Lock();
		mData = (uint8*)mInBuffer->GetPtr() + theByteOffset;
		if ((uintptr_t)mData & 3)
			mInBuffer = theInBuffer;
	}

	mNumTiles = theNumTiles;
	mWidth = theTextureDesc->width;
	mByteOffset = theByteOffset;
	mTextureDesc = theTextureDesc;
	mTextureRef = theTextureRef;
	mTextureRefMulti = theTextureRefMulti;
	mTileOffset = theTileOffset;

	uint width = theTextureDesc->width;
	uint height = theTextureDesc->height;
	RoundUpToTile(width);
	RoundUpToTile(height);
	mTilesWide = width >> 5;
	mTilesHigh = height >> 5;
}

/////////////// Accessors ///////////////

bool AndroidDecodeTask::IsExecuting()
{
	return mIsExecuting;
}

IResStreamsDriver::TaskType AndroidDecodeTask::GetType()
{
	return mType;
}

bool AndroidDecodeTask::CanExecute()
{
	return true;
}

bool AndroidDecodeTask::IsDone()
{
	return mState != 0;
}

bool AndroidDecodeTask::HasError()
{
	return mState < 0;
}

/////////////// Logic ///////////////

void AndroidDecodeTask::Update()
{
}

bool AndroidDecodeTask::Finish()
{
	if (mInBuffer != NULL)
		mInBuffer->Unlock();
	return true;
}

bool AndroidDecodeTask::Execute()
{
	uint bytesPerPixel;
	uint glType;
	uint glFormat;
	bool tiled;
	mState = 1;
	int tileSize = mDriver->GetGPUTileSizeForTexture(mTextureDesc);
	uint gpuDataSize = mDriver->GetGPUDataSizeForTexture(mTextureDesc);
	uint texture = mTextureRef;
	uint textureMulti = mTextureRefMulti;

	switch (mTextureDesc->format)
	{
	case RSB_TEXTURE_FORMAT_A8R8G8B8:
		tiled = false;
		glFormat = 0x1908;
		glType = 0x1401;
		bytesPerPixel = 4;
		break;
	case RSB_TEXTURE_FORMAT_A4R4G4B4:
		tiled = false;
		glFormat = 0x1908;
		glType = 0x8033;
		bytesPerPixel = 2;
		break;
	case RSB_TEXTURE_FORMAT_R5G6B5:
		tiled = false;
		glFormat = 0x1907;
		glType = 0x8363;
		bytesPerPixel = 2;
		break;
	case RSB_TEXTURE_FORMAT_R5G5B5A1:
		tiled = false;
		glFormat = 0x1908;
		glType = 0x8034;
		bytesPerPixel = 2;
		break;
	case RSB_TEXTURE_FORMAT_A4R4G4B4_TILED:
		tiled = true;
		bytesPerPixel = 2;
		glFormat = 0x1908;
		glType = 0x8033;
		tileSize = 0x800;
		break;
	case RSB_TEXTURE_FORMAT_R5G6B5_TILED:
		tiled = true;
		bytesPerPixel = 2;
		glFormat = 0x1907;
		glType = 0x8363;
		tileSize = 0x800;
		break;
	case RSB_TEXTURE_FORMAT_R5G5B5A1_TILED:
		tiled = true;
		bytesPerPixel = 2;
		glFormat = 0x1908;
		glType = 0x8034;
		tileSize = 0x800;
		break;
	case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_2BIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1:
	case RSB_TEXTURE_FORMAT_COMPRESSED_DXT1_RGB:
	case RSB_TEXTURE_FORMAT_COMPRESSED_DXT3_RGBA:
	case RSB_TEXTURE_FORMAT_COMPRESSED_DXT5_RGBA:
	case RSB_TEXTURE_FORMAT_COMPRESSED_ATITC_RGB:
	case RSB_TEXTURE_FORMAT_COMPRESSED_ATITC_RGBA:
	case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_ALPHA_SPLIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT_ALPHA_SPLIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_RGBA_ALPHA_SPLIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_COMPRESS_ALPHA_SPLIT:
		{
			uint fileDataSize = mDriver->GetFileDataSizeForTexture(mTextureDesc);
			uint colorType = ConvertRSBToGLFormat(mTextureDesc->format);
			mDriver->DecodeCompressedTextureBlock(*mTextureDesc, colorType, texture, textureMulti,
				mData, tileSize * mNumTiles, gpuDataSize, fileDataSize);
		}
		return true;
	default:
		tiled = false;
		glFormat = 0x1908;
		glType = 0x8033;
		break;
	}

	mDriver->mGraphicsDriver->GetRenderDevice3D()->Flush(RenderDevice3D::FLUSHF_BufferedState);
	mDriver->mGraphicsDriver->GetRenderDevice3D()->SetTexture(0, NULL);

	if (tiled)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glBindTexture(GL_TEXTURE_2D, texture);

		uint tileY = mTileOffset / mTilesWide;
		uint tileX = mTileOffset - tileY * mTilesWide;
		uint rows = 32;
		if (mTextureDesc->height < (tileY + 1) * 32)
			rows = mTextureDesc->height - (tileY << 5);

		uint8* data = mData;
		for (uint i = 0; i < mNumTiles; i++)
		{
			uint x = (tileX + 1) * 32;
			if (mWidth < x)
			{
				uint partialWidth = mTextureDesc->width - (tileX << 5);
				uint8* row = data;
				for (uint r = 0; r < rows; r++)
				{
					glTexSubImage2D(GL_TEXTURE_2D, 0, x - 32, tileY * 32 + r, partialWidth, 1, glFormat, glType, row);
					row += bytesPerPixel * 32;
				}
			}
			else
			{
				glTexSubImage2D(GL_TEXTURE_2D, 0, x - 32, tileY * 32, 32, rows, glFormat, glType, data);
			}

			data += tileSize;
			tileX++;
			if (mTilesWide <= tileX)
			{
				tileY++;
				if ((tileY + 1) * 32 > mTextureDesc->height)
					rows = mTextureDesc->height - (tileY << 5);
				tileX = 0;
			}
		}
		return true;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture);

	ResStreamTextureDescriptor* desc = mTextureDesc;
	uint bytesLeft = tileSize * mNumTiles;
	int pitch = desc->pitch;
	uint8* data = mData;
	int pixelsPerRow = (int)pitch / tileSize;
	uint y = mTileOffset / pixelsPerRow;
	uint x = mTileOffset - y * pixelsPerRow;
	uint curX = x;
	if (x != 0 && y < desc->height)
	{
		uint rowBytes = bytesPerPixel * mWidth;
		rowBytes -= x * bytesPerPixel;
		uint minA = bytesLeft;
		uint minB = rowBytes;
		uint count = std::min(minA, minB);
		uint pixels = count / bytesPerPixel;
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, pixels, 1, glFormat, glType, data);
		data += count;
		bytesLeft -= count;
		curX = pixels + x;
		desc = mTextureDesc;
		if (desc->width <= curX)
		{
			y++;
			int gap = pitch - bytesPerPixel * mWidth;
			bytesLeft -= gap;
			data += gap;
			curX = 0;
		}
	}
	if ((int)bytesLeft < 1)
		return true;
	uint height = *(volatile uint*)&mTextureDesc->height;
	if (y >= height)
		return true;

	int rowCount;
	{
		int minC = (int)bytesLeft / (int)pitch;
		int minD = height - y;
		rowCount = std::min(minC, minD);
	}
	if (bytesPerPixel * mWidth == pitch)
	{
		bytesLeft -= (uint)rowCount * pitch;
		glTexSubImage2D(GL_TEXTURE_2D, 0, curX, y, (int)pitch / (int)bytesPerPixel, rowCount, glFormat, glType, data);
		data += (uint)rowCount * pitch;
		y += rowCount;
	}
	else
	{
		for (int r = 0; r < rowCount; r++)
		{
			glTexSubImage2D(GL_TEXTURE_2D, 0, curX, y, mWidth, 1, glFormat, glType, data);
			bytesLeft -= pitch;
			data += (int)pitch;
			y++;
		}
	}
	if ((int)bytesLeft < 1 || (desc = mTextureDesc)->height <= y)
		return true;
	if (curX < desc->width)
	{
		uint rowBytes = bytesPerPixel * mWidth;
		rowBytes -= curX * bytesPerPixel;
		uint minA = bytesLeft;
		uint minB = rowBytes;
		uint count = std::min(minA, minB);
		glTexSubImage2D(GL_TEXTURE_2D, 0, curX, y, count / bytesPerPixel, 1, glFormat, glType, data);
	}
	return true;
}

