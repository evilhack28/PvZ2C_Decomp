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

/////////////// Tasks ///////////////

class BaseTask : public IResStreamsDriver::Task
{
public:
	BaseTask(BaseResStreamsDriver* theDriver, IResStreamsDriver::TaskType theType);

	virtual bool						IsExecuting() { return mIsExecuting; }
	virtual IResStreamsDriver::TaskType	GetType() { return mType; }
	virtual bool						IsDone() { return mState != 0; }
	virtual bool						HasError() { return mState < 0; }

protected:
	BaseResStreamsDriver*				mDriver;
	IResStreamsDriver::TaskType			mType;
	bool								mIsExecuting;
	int									mState;
};

BaseTask::BaseTask(BaseResStreamsDriver* theDriver, IResStreamsDriver::TaskType theType)
{
	mDriver = theDriver;
	mType = theType;
	mIsExecuting = false;
	mState = 0;
}

class BaseReadIntoBufferTask : public BaseTask
{
public:
	BaseReadIntoBufferTask(BaseResStreamsDriver* theDriver, IFile* theFile, uint32 theReadLength);

	virtual void						Update();
	virtual bool						CanExecute();
	virtual bool						Execute();
	virtual bool						Finish();
	virtual IResStreamsDriver::TaskResource*	GetOutBuffer() { return mOutBuffer; }
	virtual uint32						GetNumBytesRead() { return mReadLength; }
	virtual bool						CanExecuteOffMainThread() { return true; }

	static SimpleMemPool msPool;

	void* operator new(size_t size)
	{
		return msPool.GetMemory(static_cast<uint32_t>(size));
	}

	void operator delete(void* addr)
	{
		msPool.ReturnMemory((uint8*)addr);
	}

private:
	uint32								mReadLength;
	IResStreamsDriver::TaskResource*	mDiskResource;
	BaseBufferResource*					mOutBuffer;
	IFile*								mFile;
};

SimpleMemPool BaseReadIntoBufferTask::msPool(sizeof(BaseReadIntoBufferTask), 12);

BaseReadIntoBufferTask::BaseReadIntoBufferTask(BaseResStreamsDriver* theDriver, IFile* theFile, uint32 theReadLength)
	: BaseTask(theDriver, IResStreamsDriver::TASK_READDISK)
{
	mReadLength = std::min(theReadLength, theDriver->GetReadBufferSize());
	mDiskResource = theDriver->GetDiskResource();
	mOutBuffer = NULL;
	mFile = theFile;
}

void BaseReadIntoBufferTask::Update()
{
	if (mState == 0)
	{
		switch (mFile->DirectReadStatus())
		{
		case IFile::READ_COMPLETE:
			mState = 1;
			break;
		case IFile::READ_ERROR:
			mState = -1;
			break;
		}
	}
}

bool BaseReadIntoBufferTask::CanExecute()
{
	if (mDiskResource->IsLocked())
		return false;
	mOutBuffer = (BaseBufferResource*)mDriver->GetFreeReadBuffer();
	return mOutBuffer != NULL;
}

bool BaseReadIntoBufferTask::Execute()
{
	mOutBuffer->Lock();
	mDiskResource->Lock();
	mState = 0;
	mFile->DirectRead(mOutBuffer->GetBuffer(), mReadLength);
	return true;
}

bool BaseReadIntoBufferTask::Finish()
{
	mOutBuffer->Unlock();
	mDiskResource->Unlock();
	return true;
}

class BaseReadWithoutBufferTask : public BaseTask
{
public:
	BaseReadWithoutBufferTask(BaseResStreamsDriver* theDriver, IFile* theFile, uint8* theDst, uint32 theReadLength, uint32 theFileLocation);

	virtual void						Update();
	virtual bool						CanExecute();
	virtual bool						Execute();
	virtual bool						Finish();
	virtual uint32						GetNumBytesRead() { return mReadLength; }
	virtual bool						CanExecuteOffMainThread() { return true; }

	static SimpleMemPool msPool;

	void* operator new(size_t size)
	{
		return msPool.GetMemory(static_cast<uint32_t>(size));
	}

	void operator delete(void* addr)
	{
		msPool.ReturnMemory((uint8*)addr);
	}

private:
	uint32								mReadLength;
	IResStreamsDriver::TaskResource*	mDiskResource;
	uint8*								mDst;
	IFile*								mFile;
	uint32								mFileLocation;
};

SimpleMemPool BaseReadWithoutBufferTask::msPool(sizeof(BaseReadWithoutBufferTask), 12);

BaseReadWithoutBufferTask::BaseReadWithoutBufferTask(BaseResStreamsDriver* theDriver, IFile* theFile, uint8* theDst, uint32 theReadLength, uint32 theFileLocation)
	: BaseTask(theDriver, IResStreamsDriver::TASK_READDISK)
{
	mDst = theDst;
	mReadLength = theReadLength;
	mDiskResource = theDriver->GetDiskResource();
	mFile = theFile;
	mFileLocation = theFileLocation;
}

void BaseReadWithoutBufferTask::Update()
{
	if (mState == 0)
	{
		switch (mFile->DirectReadStatus())
		{
		case IFile::READ_COMPLETE:
			mState = 1;
			break;
		case IFile::READ_ERROR:
			mState = -1;
			break;
		}
	}
}

bool BaseReadWithoutBufferTask::CanExecute()
{
	return !mDiskResource->IsLocked();
}

bool BaseReadWithoutBufferTask::Execute()
{
	mDiskResource->Lock();
	mState = 0;
	mFile->DirectSeek(mFileLocation);
	mFile->DirectRead(mDst, mReadLength);
	return true;
}

bool BaseReadWithoutBufferTask::Finish()
{
	mDiskResource->Unlock();
	return true;
}

class BaseDecompressionTask : public BaseTask
{
public:
	BaseDecompressionTask(BaseResStreamsDriver* theDriver, BaseDecompressionTask* thePrevDecompress, BaseBufferResource* theInBuffer, uint32 theSize, bool isFullReset);

	virtual void						Update();
	virtual bool						CanExecute();
	virtual bool						Execute();
	virtual bool						Finish();
	virtual IResStreamsDriver::TaskResource*	GetInBuffer() { return mInBuffer; }
	virtual IResStreamsDriver::TaskResource*	GetOutBuffer() { return mOutBuffer; }
	virtual bool						DidFinishDecompression() { return mDriver->IsDecompressionFullyComplete() != 0; }
	virtual uint32						GetNumBytesRead() { return mDriver->GetDecompressedSize(); }
	virtual bool						CanExecuteOffMainThread() { return true; }

	static SimpleMemPool msPool;

	void* operator new(size_t size)
	{
		return msPool.GetMemory(static_cast<uint32_t>(size));
	}

	void operator delete(void* addr)
	{
		msPool.ReturnMemory((uint8*)addr);
	}

private:
	uint32								mSize;
	IResStreamsDriver::TaskResource*	mDecompressThreadResource;
	BaseBufferResource*					mInBuffer;
	BaseBufferResource*					mOutBuffer;
	uint64								mUnused;
	bool								mIsNewStream;
	bool								mIsFullReset;
};

SimpleMemPool BaseDecompressionTask::msPool(sizeof(BaseDecompressionTask), 24);

BaseDecompressionTask::BaseDecompressionTask(BaseResStreamsDriver* theDriver, BaseDecompressionTask* thePrevDecompress, BaseBufferResource* theInBuffer, uint32 theSize, bool isFullReset)
	: BaseTask(theDriver, IResStreamsDriver::TASK_DECOMPRESS)
{
	mOutBuffer = NULL;
	mInBuffer = theInBuffer;
	mSize = theSize;
	mInBuffer->Lock();
	mDecompressThreadResource = theDriver->GetDecompressThreadResource();
	mIsFullReset = isFullReset;
	if (thePrevDecompress == NULL)
	{
		mIsNewStream = true;
	}
	else
	{
		mIsNewStream = false;
		mDecompressThreadResource->Lock();
	}
}

void BaseDecompressionTask::Update()
{
	if (mState == 0 && mDriver->IsDecompressionChunkComplete())
		mState = 1;
}

bool BaseDecompressionTask::CanExecute()
{
	if (mIsNewStream && mDecompressThreadResource->IsLocked())
		return false;
	mOutBuffer = (BaseBufferResource*)mDriver->GetFreeDecompressBuffer();
	return mOutBuffer != NULL;
}

bool BaseDecompressionTask::Execute()
{
	mOutBuffer->Lock();
	mState = 0;
	if (mIsNewStream)
	{
		mDecompressThreadResource->Lock();
		if (mIsFullReset)
			mDriver->BeginDecompression(1);
		mDriver->DecompressStream(mInBuffer->GetBuffer(), mSize, mOutBuffer->GetBuffer(), mOutBuffer->GetSize());
	}
	else
	{
		mDriver->ContinueDecompressStream(mOutBuffer->GetBuffer(), mOutBuffer->GetSize());
	}
	return true;
}

bool BaseDecompressionTask::Finish()
{
	mDecompressThreadResource->Unlock();
	mOutBuffer->Unlock();
	mInBuffer->Unlock();
	return true;
}

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

bool BaseResStreamsDriver::DecompressStream(uint8* theCompressedBuffer, uint32 theCompressedBufferSize,
											uint8* theOutBuffer, uint32 theOutBufferSize)
{
	mCompressedBuffer = theCompressedBuffer;
	mCompressedBufferSize = theCompressedBufferSize;
	mDecompressedBuffer = theOutBuffer;
	mDecompressedBufferSize = theOutBufferSize;
	mDecompressionReset = true;
	mIsDecompressing = 1;
	mDecompressedSize = 0;
	mDecompressCondition.Notify();
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

/////////////// Task creation ///////////////

IResStreamsDriver::Task* BaseResStreamsDriver::CreateReadTask(IFile* theFile, uint32 theReadLength)
{
	return new BaseReadIntoBufferTask(this, theFile, theReadLength);
}

IResStreamsDriver::Task* BaseResStreamsDriver::CreateReadTaskWithoutBuffer(IFile* theFile, uint8* theDst, uint32 theReadLength, uint32 theFileLocation)
{
	return new BaseReadWithoutBufferTask(this, theFile, theDst, theReadLength, theFileLocation);
}

IResStreamsDriver::Task* BaseResStreamsDriver::CreateDecompressTask(TaskResource* theReadBuffer, Task* thePrevDecompress)
{
	return new BaseDecompressionTask(this, (BaseDecompressionTask*)thePrevDecompress, (BaseBufferResource*)theReadBuffer, thePrevDecompress->GetRemainingBytesToDecompress(), false);
}

IResStreamsDriver::Task* BaseResStreamsDriver::CreateDecompressTask(TaskResource* theReadBuffer, uint32 theSize, bool isFullReset)
{
	return new BaseDecompressionTask(this, NULL, (BaseBufferResource*)theReadBuffer, theSize, isFullReset);
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
