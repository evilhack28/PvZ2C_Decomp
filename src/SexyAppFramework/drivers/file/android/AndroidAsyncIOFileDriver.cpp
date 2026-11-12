//
//  AndroidAsyncIOFileDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-07.
//
//  The static helper TimeToFileTime has no name in the game; its name here is not real.
//

#include "SexyAppFramework/Common.h"
#include "drivers/file/android/AndroidAsyncIOFileDriver.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/SexyThread.h"
#include "SexyAppFramework/AutoCrit.h"
#include "drivers/app/android/AndroidAppDriver.h"
#include "drivers/app/android/JavaInterface.h"
#include <EAIO/EAFileUtil.h>
#include <errno.h>
#include <fnmatch.h>
#include <unistd.h>

using namespace Sexy;

char const * AndroidAsyncIOFileDriver::sAssetPrefix = "ASSET:";

/////////////// Helpers ///////////////

static FileTime TimeToFileTime(time_t inTime)
{
	return inTime;
}

/////////////// Lifecycle ///////////////

AndroidAsyncIOFileDriver::AndroidAsyncIOFileDriver()
{
	mbAsyncThreadRunning.store(false);
	mbAsyncThreadTimeToDie.store(false);
	mApp = NULL;
	mLoadDataFolder = "";
	mSaveDataFolder = "";
	mCacheDataFolder = "";
	mAppSupportDataFolder = "";
	CreateIOThread();
}

AndroidAsyncIOFileDriver::~AndroidAsyncIOFileDriver()
{
	DestroyIOThread();
}

bool AndroidAsyncIOFileDriver::InitFileDriver(SexyAppBase* app)
{
	mApp = app;
	mLoadDataFolder = sAssetPrefix;

	mSaveDataFolder = Android::Resources::GetUserDataFolder((AndroidAppDriver*)mApp->mAppDriver);
	if (*mSaveDataFolder.rbegin() != '/')
		mSaveDataFolder += '/';

	mCacheDataFolder = Android::Resources::GetCacheDataFolder((AndroidAppDriver*)mApp->mAppDriver);
	if (*mCacheDataFolder.rbegin() != '/')
		mCacheDataFolder += '/';

	mAppSupportDataFolder = Android::Resources::GetAppSupportDataFolder((AndroidAppDriver*)mApp->mAppDriver);
	if (*mAppSupportDataFolder.rbegin() != '/')
		mAppSupportDataFolder += '/';

	return true;
}

void AndroidAsyncIOFileDriver::InitSaveDataFolder()
{
}

/////////////// Paths ///////////////

std::string AndroidAsyncIOFileDriver::FixPath(const std::string& thePath)
{
	char aPath[4096];
	strcpy(aPath, thePath.c_str());
	for (char* p = aPath; *p; p++)
	{
		if (*p == '\\')
			*p = '/';
	}
	return aPath;
}

std::string AndroidAsyncIOFileDriver::GetCacheDataPath()
{
	return mSaveDataFolder;
}

std::string AndroidAsyncIOFileDriver::GetSaveDataPath()
{
	return mSaveDataFolder;
}

std::string AndroidAsyncIOFileDriver::GetCurPath()
{
	char aPath[4096];
	getcwd(aPath, sizeof(aPath));
	return aPath;
}

std::string AndroidAsyncIOFileDriver::GetLoadDataPath()
{
	return mLoadDataFolder;
}

std::string AndroidAsyncIOFileDriver::GetDataPath(IFileDriver::PathType inPathType)
{
	switch (inPathType)
	{
	case PathType_SaveData:
		return GetDataPathSaveData();
	case PathType_LoadData:
		return GetDataPathLoadData();
	case PathType_Cache:
		return GetDataPathCacheData();
	case PathType_NoBackup:
		return GetDataPathSupportDataNoBackup();
	case PathType_Backup:
		return GetDataPathSupportDataBackup();
	default:
		return "";
	}
}

std::string AndroidAsyncIOFileDriver::GetDataPathSaveData()
{
	return mSaveDataFolder;
}

std::string AndroidAsyncIOFileDriver::GetDataPathLoadData()
{
	return mLoadDataFolder;
}

std::string AndroidAsyncIOFileDriver::GetDataPathCacheData()
{
	return mCacheDataFolder;
}

std::string AndroidAsyncIOFileDriver::GetDataPathSupportDataNoBackup()
{
	return mAppSupportDataFolder + "No_Backup/";
}

std::string AndroidAsyncIOFileDriver::GetDataPathSupportDataBackup()
{
	return mAppSupportDataFolder + "Backup/";
}

bool AndroidAsyncIOFileDriver::IsDataPathValid(const std::string& inPath)
{
	std::string aDir = GetFileDir(RemoveTrailingSlash(GetLoadDataPath()), true);
	return inPath.find(aDir) != std::string::npos;
}

bool AndroidAsyncIOFileDriver::IsAssetFilename(std::string const & path)
{
	return strncmp(path.c_str(), sAssetPrefix, 6) == 0;
}

/////////////// Files ///////////////

IFile* AndroidAsyncIOFileDriver::CreateFile(const std::string& path)
{
	std::string aPath = FixPath(path);
	int aFileSize = -1;
	if (IsAssetFilename(path))
	{
		aFileSize = Android::Resources::GetAssetFileSize(path);
	}
	else
	{
		struct stat aStat;
		if (stat(aPath.c_str(), &aStat) == 0)
			aFileSize = aStat.st_size;
	}
	if (aFileSize != -1)
	{
		size_t aBufferSize = aFileSize + 2048 - aFileSize % 2048;
		uint8* aBuffer = (uint8*)malloc(aBufferSize);
		if (aBuffer)
			return CreateFileWithBufferAndAttrData(aPath, aBuffer, aBufferSize, aFileSize, true);
	}
	return NULL;
}

IFile* AndroidAsyncIOFileDriver::CreateFileDirect(const std::string& thePath)
{
	std::string aPath = FixPath(thePath);
	int aFileSize = -1;
	if (IsAssetFilename(thePath))
	{
		aFileSize = Android::Resources::GetAssetFileSize(thePath);
	}
	else
	{
		struct stat aStat;
		if (stat(aPath.c_str(), &aStat) == 0)
			aFileSize = aStat.st_size;
	}
	if (aFileSize != -1)
		return new AndroidAsyncIOFile(aPath, GetFileSize(thePath), this);
	return NULL;
}

IFile* AndroidAsyncIOFileDriver::CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size)
{
	std::string aPath = FixPath(path);
	int aFileSize = -1;
	if (IsAssetFilename(path))
	{
		aFileSize = Android::Resources::GetAssetFileSize(path);
	}
	else
	{
		struct stat aStat;
		if (stat(aPath.c_str(), &aStat) == 0)
			aFileSize = aStat.st_size;
	}
	if (aFileSize != -1 && (uint32)(aFileSize + 2048 - aFileSize % 2048) <= buffer_size)
		return CreateFileWithBufferAndAttrData(aPath, buffer, buffer_size, aFileSize, false);
	return NULL;
}

IFile* AndroidAsyncIOFileDriver::CreateFileWithBufferAndAttrData(const std::string& path, uint8* buffer, size_t buffer_size, size_t theFileSize, bool delete_buffer)
{
	return new AndroidAsyncIOFile(path, buffer, buffer_size, delete_buffer, theFileSize, this);
}

uint64 AndroidAsyncIOFileDriver::GetFileSize(const std::string& path)
{
	std::string aPath = FixPath(path);
	if (IsAssetFilename(path))
		return Android::Resources::GetAssetFileSize(path);
	struct stat aStat;
	if (stat(aPath.c_str(), &aStat) != 0)
		return 0;
	return aStat.st_size;
}

FileTime AndroidAsyncIOFileDriver::GetFileLastAccessTime(const std::string& path)
{
	FileTime aTime = 0;
	std::string aPath = FixPath(path);
	struct stat aStat;
	if (stat(aPath.c_str(), &aStat) == 0)
		aTime = TimeToFileTime(aStat.st_atime);
	return aTime;
}

FileTime AndroidAsyncIOFileDriver::GetFileTime(const std::string& path)
{
	FileTime aTime = 0;
	std::string aPath = FixPath(path);
	struct stat aStat;
	if (stat(aPath.c_str(), &aStat) == 0)
		aTime = TimeToFileTime(aStat.st_mtime);
	return aTime;
}

FileTime AndroidAsyncIOFileDriver::GetFileBirthTime(const std::string& path)
{
	return GetFileTime(path);
}

bool AndroidAsyncIOFileDriver::FileExists(const std::string& path, bool* isFolder)
{
	std::string aPath = FixPath(path);
	bool aExists = IsAssetFilename(path);
	if (aExists)
	{
		int aFileSize = Android::Resources::GetAssetFileSize(path);
		if (aFileSize < 0)
			aExists = false;
		else if (isFolder)
			*isFolder = false;
	}
	else
	{
		struct stat aStat;
		if (stat(aPath.c_str(), &aStat) != 0)
			return aExists;
		if (isFolder)
			*isFolder = S_ISDIR(aStat.st_mode);
		aExists = true;
	}
	return aExists;
}

bool AndroidAsyncIOFileDriver::MakeFolders(const std::string& folder)
{
	std::string aPath = FixPath(folder);
	std::string aDir = aPath;
	int aPos = 0;
	for (;;)
	{
		int aFound = aDir.find_first_of("\\/", aPos);
		if (aFound == std::string::npos)
			break;
		aPos = aFound + 1;
		mkdir(aDir.substr(0, aFound).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	mkdir(aDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	return true;
}

bool AndroidAsyncIOFileDriver::DeleteTree(const std::string& path)
{
	return EA::IO::Directory::Remove(path.c_str(), true);
}

bool AndroidAsyncIOFileDriver::DeleteFile(const std::string& path)
{
	std::string aPath = FixPath(path);
	return unlink(aPath.c_str()) == 0;
}

bool AndroidAsyncIOFileDriver::GetVolumeStatistics(const std::string &pathOnVolume, VolumeStatistics *stats)
{
	stats->block_count = Android::Resources::GetFileSystemBlockCount(pathOnVolume);
	stats->blocks_free = Android::Resources::GetFileSystemBlocksFree(pathOnVolume);
	stats->block_size = Android::Resources::GetFileSystemBlockSize(pathOnVolume);
	return stats->block_count != 0 && stats->block_size != 0;
}

/////////////// File search ///////////////

IFileSearch* AndroidAsyncIOFileDriver::FileSearchStart(const std::string& criteria, FileSearchInfo* info)
{
	std::string aPattern = criteria;
	std::string aPath = FixPath(GetFileDir(aPattern, true));
	aPattern = GetFileName(aPattern);
	if (aPattern == "*.*" || aPattern == "")
		aPattern = "*";
	DIR* aDir = opendir(aPath.c_str());
	if (!aDir)
		return NULL;
	AndroidFileSearch* aSearch = new AndroidFileSearch(aPattern, aPath, aDir);
	if (!FileSearchNext(aSearch, info))
	{
		delete aSearch;
		closedir(aDir);
		return NULL;
	}
	return aSearch;
}

bool AndroidAsyncIOFileDriver::FileSearchNext(IFileSearch* search, FileSearchInfo* info)
{
	AndroidFileSearch* aSearch = (AndroidFileSearch*)search;
	if (!aSearch || !aSearch->mDir)
		return false;
	dirent* anEntry;
	while ((anEntry = readdir(aSearch->mDir)) != NULL)
	{
		if (fnmatch(aSearch->mPattern.c_str(), anEntry->d_name, 0) == 0)
		{
			struct stat aStat;
			if (stat((aSearch->mPath + anEntry->d_name).c_str(), &aStat) == 0)
			{
				info->create_time = TimeToFileTime(aStat.st_ctime);
				info->last_access_time = TimeToFileTime(aStat.st_atime);
				info->last_write_time = TimeToFileTime(aStat.st_mtime);
				info->file_size = aStat.st_size;
				info->is_directory = S_ISDIR(aStat.st_mode);
				info->file_name = anEntry->d_name;
				return true;
			}
		}
	}
	return false;
}

bool AndroidAsyncIOFileDriver::FileSearchEnd(IFileSearch* search)
{
	if (!search)
		return false;
	AndroidFileSearch* aSearch = (AndroidFileSearch*)search;
	if (aSearch->mDir)
	{
		closedir(aSearch->mDir);
		delete aSearch;
		return true;
	}
	delete aSearch;
	return false;
}

/////////////// Async IO thread ///////////////

void AndroidAsyncIOFileDriver::CreateIOThread()
{
	mbAsyncThreadTimeToDie.store(false);
	mbAsyncThreadRunning.store(true);
	LaunchThread(StaticAsyncIOThreadMain, this, STP_LOW);
}

void AndroidAsyncIOFileDriver::DestroyIOThread()
{
	mbAsyncThreadTimeToDie.store(true);
	if (mbAsyncThreadRunning.load())
	{
		while (mbAsyncThreadTimeToDie.load())
			SexySleep(100);
	}
}

void AndroidAsyncIOFileDriver::StaticAsyncIOThreadMain(void * pParam)
{
	((AndroidAsyncIOFileDriver*)pParam)->AsyncIOThreadMain();
}

void AndroidAsyncIOFileDriver::AsyncIOThreadMain()
{
	mbAsyncThreadRunning.store(true);
	while (!mbAsyncThreadTimeToDie.load())
	{
		AndroidAIO::aiocb* aJob = GetAsyncReadJob();
		if (!aJob)
		{
			mAsyncWorkAvailable.Wait(100);
			continue;
		}
		ssize_t aResult = lseek(aJob->aio_fildes, aJob->aio_offset, SEEK_SET);
		if (aResult >= 0)
		{
			aResult = read(aJob->aio_fildes, aJob->aio_buf, aJob->aio_nbytes);
			if (aResult != aJob->aio_nbytes)
			{
				int anError = errno;
			}
		}
		__atomic_store_n(&aJob->return_code, aResult, __ATOMIC_RELEASE);
		__atomic_store_n(&aJob->error_code, 0, __ATOMIC_RELEASE);
	}
	mbAsyncThreadTimeToDie.store(false);
}

int AndroidAsyncIOFileDriver::SubmitAsyncRead(struct AndroidAIO::aiocb * pContext)
{
	AutoCrit aAutoCrit(mAsyncWorkCS);
	mAsyncIOJobs.push_back(pContext);
	mAsyncWorkAvailable.Notify();
	return 0;
}

struct AndroidAIO::aiocb * AndroidAsyncIOFileDriver::GetAsyncReadJob()
{
	AutoCrit aAutoCrit(mAsyncWorkCS);
	if (mAsyncIOJobs.empty())
		return NULL;
	AndroidAIO::aiocb* aJob = mAsyncIOJobs.front();
	mAsyncIOJobs.pop_front();
	return aJob;
}
