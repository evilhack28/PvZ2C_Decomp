//
//  BaseResStreamsDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/resstreams/BaseResStreamsDriver.h"
#include "SexyAppFramework/ResStreamsFormat.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ResStreamsManager.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

BaseResStreamsDriver::BaseResStreamsDriver()
{
	mIsDecompressing = 0;
	mThreadInitted = false;
	mDecompressionReset = true;
	mDecompressionFullReset = true;
	mDecompressionQuit = false;
}

BaseResStreamsDriver::~BaseResStreamsDriver()
{
	mIsDecompressing = 0;
	mThreadInitted = false;
	mDecompressionQuit = true;
	mDecompressCondition.Notify();
	mDecompressShutdown.Wait(1000);

	for (TaskResourceList::iterator anItr = mReadBuffers.begin(); anItr != mReadBuffers.end(); ++anItr)
		delete *anItr;
	mReadBuffers.clear();

	for (TaskResourceList::iterator anItr = mDecompressBuffers.begin(); anItr != mDecompressBuffers.end(); ++anItr)
		delete *anItr;
	mReadBuffers.clear();

	delete mDecompressThreadResource;
	delete mDiskResource;
	delete mGPUResource;
}

/////////////// Accessors ///////////////

IResStreamsDriver::TaskResource* BaseResStreamsDriver::GetDiskResource()
{
	return mDiskResource;
}

IResStreamsDriver::TaskResource* BaseResStreamsDriver::GetGPUResource()
{
	return mGPUResource;
}

IResStreamsDriver::TaskResource* BaseResStreamsDriver::GetDecompressThreadResource()
{
	return mDecompressThreadResource;
}

uint32 BaseResStreamsDriver::GetDecompressedSize()
{
	return mDecompressedSize;
}

int32 BaseResStreamsDriver::IsDecompressionFullyComplete()
{
	return mFinishedDecompressing;
}

int32 BaseResStreamsDriver::IsDecompressionChunkComplete()
{
	return !mIsDecompressing;
}

void BaseResStreamsDriver::Align(uint32& theSize, int theBytes) const
{
	uint32 aRemainder = theSize % theBytes;
	theSize += aRemainder ? theBytes - aRemainder : 0;
}

/////////////// Decompression ///////////////

bool BaseResStreamsDriver::BeginDecompression(int theCompressionType)
{
	mDecompressionQuit = false;
	mDecompressionType = theCompressionType;
	if (!mThreadInitted)
	{
		mZlibStream.zalloc = Z_NULL;
		mZlibStream.zfree = Z_NULL;
		mZlibStream.opaque = Z_NULL;
		inflateInit(&mZlibStream);
		mZlibStream.next_in = Z_NULL;
		mThreadInitted = true;
		mZlibStream.avail_in = 0;
		LaunchThread(DecompressionThreadProc, this, STP_HIGHEST);
	}
	mDecompressionFullReset = true;
	return true;
}

bool BaseResStreamsDriver::ContinueDecompressStream(uint8* theOutBuffer, uint32 theOutBufferSize)
{
	mDecompressedBuffer = theOutBuffer;
	mIsDecompressing = 1;
	mDecompressedBufferSize = theOutBufferSize;
	mDecompressedSize = 0;
	mDecompressCondition.Notify();
	return true;
}

/////////////// Buffers ///////////////

IResStreamsDriver::TaskResource* BaseResStreamsDriver::CreateHoldoverBuffer(uint32& outSize)
{
	outSize = GetGPUTileSizeForTexture(NULL);
	return new BaseBufferResource(outSize);
}

/////////////// Decompression thread ///////////////

void BaseResStreamsDriver::DecompressionThreadProc(void* theArg)
{
	BaseResStreamsDriver* aDriver = (BaseResStreamsDriver*)theArg;
	while (!aDriver->mDecompressionQuit)
	{
		aDriver->mDecompressCondition.Wait(5000);
		if (!gSexyAppBase->mShutdown)
		{
			aDriver->RunDecompressProcess();
			gSexyAppBase->mResStreamsManager->Update();
		}
	}
	OutputDebugStrF("BaseResStreamsDriver::DecompressionThreadProc() exiting.\n");
	aDriver->mDecompressShutdown.Notify();
}

void BaseResStreamsDriver::RunDecompressProcess()
{
	if (mDecompressionFullReset)
	{
		inflateReset(&mZlibStream);
		mZlibStream.next_in = Z_NULL;
		mZlibStream.avail_in = 0;
		mDecompressionFullReset = false;
	}
	if (mDecompressionReset)
	{
		mZlibStream.next_in = Z_NULL;
		mZlibStream.avail_in = 0;
		mDecompressionReset = false;
	}
	if (mIsDecompressing)
	{
		if (mZlibStream.next_in == Z_NULL)
		{
			mZlibStream.next_in = mCompressedBuffer;
			mZlibStream.avail_in = mCompressedBufferSize;
		}
		mZlibStream.next_out = mDecompressedBuffer;
		mZlibStream.avail_out = mDecompressedBufferSize;
		int aResult = inflate(&mZlibStream, Z_SYNC_FLUSH);
		AtomicSet((int32*)&mDecompressedSize, mDecompressedBufferSize - mZlibStream.avail_out);
		AtomicSet(&mFinishedDecompressing, aResult == Z_OK ? mZlibStream.avail_in == 0 : aResult == Z_STREAM_END);
		AtomicSet(&mIsDecompressing, 0);
	}
}

/////////////// Texture sizes ///////////////

uint32 BaseResStreamsDriver::GetFileDataSizeForTexture(ResStreamTextureDescriptor* theTextureDesc) const
{
	switch (theTextureDesc->format)
	{
	case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_ALPHA_SPLIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT_ALPHA_SPLIT:
	case RSB_TEXTURE_FORMAT_COMPRESSED_RGBA_ALPHA_SPLIT:
	{
		int aWidth, aHeight, aSize;
		uint32 aGPUSize = GetGPUDataSizeForTexture(theTextureDesc);
		GetAttachedTextureSize(*theTextureDesc, aWidth, aHeight, aSize);
		return aGPUSize + aSize;
	}
	case RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_COMPRESS_ALPHA_SPLIT:
		return GetGPUDataSizeForTexture(theTextureDesc) * 2;
	}
	return GetGPUDataSizeForTexture(theTextureDesc);
}

/////////////// Buffers (free lookup) ///////////////

IResStreamsDriver::TaskResource* BaseResStreamsDriver::GetFreeReadBuffer()
{
	for (TaskResourceList::iterator anItr = mReadBuffers.begin(); anItr != mReadBuffers.end(); ++anItr)
	{
		TaskResource* aResource = *anItr;
		if (!aResource->IsLocked())
			return aResource;
	}
	return NULL;
}

IResStreamsDriver::TaskResource* BaseResStreamsDriver::GetFreeDecompressBuffer()
{
	if (AreReadAndDecompressBuffersUnified())
		return GetFreeReadBuffer();

	for (TaskResourceList::iterator anItr = mDecompressBuffers.begin(); anItr != mDecompressBuffers.end(); ++anItr)
	{
		TaskResource* aResource = *anItr;
		if (!aResource->IsLocked())
			return aResource;
	}
	return NULL;
}

IResStreamsDriver::TaskResource* BaseResStreamsDriver::GetFreeHoldoverBuffer()
{
	for (TaskResourceList::iterator anItr = mHoldoverBuffers.begin(); anItr != mHoldoverBuffers.end(); ++anItr)
	{
		TaskResource* aResource = *anItr;
		if (!aResource->IsLocked())
			return aResource;
	}

	uint32 aSize;
	mHoldoverBuffers.push_back(CreateHoldoverBuffer(aSize));
	return mHoldoverBuffers.back();
}

/////////////// Init ///////////////

bool BaseResStreamsDriver::InitWithApp(SexyAppBase* theAppBase)
{
	int aReadBufferCount = GetReadBufferCount();
	int aDecompressBufferCount = GetDecompressBufferCount();
	if (AreReadAndDecompressBuffersUnified())
	{
		aReadBufferCount += aDecompressBufferCount;
		aDecompressBufferCount = 0;
	}

	for (int i = 0; i < aReadBufferCount; i++)
		mReadBuffers.push_back(new BaseBufferResource(GetReadBufferSize()));

	for (int i = 0; i < aDecompressBufferCount; i++)
		mDecompressBuffers.push_back(new BaseBufferResource(GetDecompressBufferSize()));

	mDecompressThreadResource = new BaseDecompressThreadResource();
	mDiskResource = new BaseDiskResource();
	mGPUResource = new BaseGPUResource();
	return true;
}
