//
//  AndroidAsyncIOFile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-26.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/file/android/AndroidAsyncIOFileDriver.h"
#include <errno.h>
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

AndroidAsyncIOFile::AndroidAsyncIOFile(const std::string& theFilename, uint32 theFileSize, AndroidAsyncIOFileDriver* pDriver)
{
	mDeleteBuffer = false;
	mBuffer = NULL;
	mBufferSize = 0;
	mSize = 0;
	mIsLoaded = false;
	mHasError = false;
	mAsyncDriver = pDriver;
	mIsDirect = true;
	mReadPos = 0;
	mReadSize = 0;
	mbIsAndroidArchive = false;
	mArchiveOffset = 0;
	if (!InitRead(theFilename, theFileSize))
		mHasError = true;
}

AndroidAsyncIOFile::AndroidAsyncIOFile(const std::string& theFilename, uint8* buffer, uint32 buffer_size, bool delete_buffer, uint32 theFileSize, AndroidAsyncIOFileDriver* pDriver)
{
	mDeleteBuffer = delete_buffer;
	mBuffer = buffer;
	mBufferSize = buffer_size;
	mSize = 0;
	mIsLoaded = false;
	mHasError = false;
	mAsyncDriver = pDriver;
	mIsDirect = false;
	mReadPos = 0;
	mReadSize = 0;
	mbIsAndroidArchive = false;
	mArchiveOffset = 0;
	if (!InitRead(theFilename, theFileSize))
		mHasError = true;
}

AndroidAsyncIOFile::~AndroidAsyncIOFile()
{
	if (mDeleteBuffer)
		free(mBuffer);
	Close();
}

/////////////// Accessors ///////////////

uint8* AndroidAsyncIOFile::GetBuffer()
{
	return mBuffer;
}

uint32 AndroidAsyncIOFile::GetSize()
{
	return mSize;
}

uint64 AndroidAsyncIOFile::DirectReadBlockSize()
{
	return 2048;
}

bool AndroidAsyncIOFile::IsLoaded()
{
	if (!mIsLoaded && !mHasError)
		AsyncLoad();
	return mIsLoaded;
}

bool AndroidAsyncIOFile::HasError()
{
	if (!mIsLoaded && !mHasError)
	{
		AsyncLoad();
		return mHasError;
	}
	return mIsLoaded;
}

/////////////// Loading ///////////////

bool AndroidAsyncIOFile::InitRead(const std::string& filename, uint32 theFileSize)
{
	memset(&mAIO, 0, sizeof(mAIO));
	mAIO.aio_fildes = -1;
	mSize = theFileSize;

	long offset = 0;
	long size = 0;
	std::string archive;
	if (Android::Resources::GetAssetFileInfo(filename, archive, offset, size))
	{
		mArchiveOffset = offset;
		mbIsAndroidArchive = true;
		mAIO.aio_fildes = open(archive.c_str(), O_RDONLY);
		if (mAIO.aio_fildes != -1)
			lseek(mAIO.aio_fildes, mArchiveOffset, SEEK_SET);
	}
	if (mAIO.aio_fildes == -1)
	{
		mAIO.aio_fildes = open(filename.c_str(), O_RDONLY);
		if (mAIO.aio_fildes == -1)
		{
			mHasError = true;
			return false;
		}
	}
	if (!mIsDirect)
	{
		mAIO.pAsyncDriver = mAsyncDriver;
		mAIO.aio_nbytes = theFileSize;
		mAIO.aio_offset = mArchiveOffset;
		mAIO.aio_buf = GetBuffer();
		AndroidAIO::aio_read(&mAIO);
	}
	return true;
}

void AndroidAsyncIOFile::AsyncLoad()
{
	if (mIsLoaded || mHasError)
		return;
	int32 error = __atomic_load_n(&mAIO.error_code, __ATOMIC_ACQUIRE);
	if (error == EINPROGRESS)
		return;
	if (error == 0)
		mIsLoaded = true;
	else
		mHasError = true;
}

bool AndroidAsyncIOFile::ForceLoad()
{
	while (!mIsLoaded && !mHasError)
		AsyncLoad();
	return !mHasError;
}

void AndroidAsyncIOFile::Close()
{
	if (mAIO.aio_fildes != -1)
	{
		close(mAIO.aio_fildes);
		mAIO.aio_fildes = -1;
	}
}

/////////////// Direct reads ///////////////

void AndroidAsyncIOFile::DirectSeek(uint64 theSeekPoint)
{
	if (DirectReadStatus() != READ_PENDING)
		mReadPos = theSeekPoint;
}

bool AndroidAsyncIOFile::DirectRead(uint8* theBuffer, uint64 theReadSize)
{
	if (DirectReadStatus() == READ_PENDING)
		return false;
	mHasError = false;
	mReadSize = theReadSize;
	mAIO.aio_nbytes = theReadSize;
	mAIO.aio_offset = mArchiveOffset + mReadPos;
	mAIO.aio_buf = theBuffer;
	mAIO.pAsyncDriver = mAsyncDriver;
	if (AndroidAIO::aio_read(&mAIO) == 0)
	{
		mReadPos += theReadSize;
		return true;
	}
	mHasError = true;
	return false;
}

IFile::Status AndroidAsyncIOFile::DirectReadStatus()
{
	if (mReadSize == 0)
		return READ_COMPLETE;
	if (mHasError)
		return READ_ERROR;
	int32 error = __atomic_load_n(&mAIO.error_code, __ATOMIC_ACQUIRE);
	if (error == EINPROGRESS)
		return READ_PENDING;
	if (error != 0)
	{
		mHasError = true;
		return READ_ERROR;
	}
	mReadSize = 0;
	return READ_COMPLETE;
}
