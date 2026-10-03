//
//  SexyIOHookBlocking.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//
/////////////// SexyIOHookBlocking ///////////////

#include "SexyAppFramework/drivers/audio/wwise/SexyIOHookBlocking.h"
#include "SexyAppFramework/drivers/audio/wwise/POSIX/AkFileHelpers.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/IFileDriver.h"
#include <sys/stat.h>

SexyIOHookBlocking::SexyIOHookBlocking()
	: mRSBOffset(0)
	, mbDataIsInAPK(false)
{
}

SexyIOHookBlocking::~SexyIOHookBlocking()
{
}

AKRESULT SexyIOHookBlocking::Read(AkFileDesc& in_fileDesc, const AkIoHeuristics& in_heuristics, void* out_pBuffer, AkIOTransferInfo& io_transferInfo)
{
	AkUInt32 uSizeTransferred;
	AKRESULT eResult = CAkFileHelpers::ReadBlocking(in_fileDesc.hFile, out_pBuffer, io_transferInfo.uFilePosition, io_transferInfo.uRequestedSize, uSizeTransferred);
	if (eResult == AK_Success)
		return (io_transferInfo.uRequestedSize == uSizeTransferred) ? AK_Success : AK_Fail;
	return eResult;
}

AKRESULT SexyIOHookBlocking::Write(AkFileDesc& in_fileDesc, const AkIoHeuristics& in_heuristics, void* in_pData, AkIOTransferInfo& io_transferInfo)
{
	return AK_Fail;
}

AKRESULT SexyIOHookBlocking::Close(AkFileDesc& in_fileDesc)
{
	return CAkFileHelpers::CloseFile(in_fileDesc.hFile);
}

AKRESULT SexyIOHookBlocking::Open(const AkOSChar* in_pszFileName, AkOpenMode in_eOpenMode, AkFileSystemFlags* in_pFlags, bool& io_bSyncOpen, AkFileDesc& out_fileDesc)
{
	std::string aPath = in_pszFileName;
	io_bSyncOpen = true;
	return Open_Aux(aPath, in_eOpenMode, in_pFlags, io_bSyncOpen, out_fileDesc);
}

AKRESULT SexyIOHookBlocking::Open_Aux(std::string thePathName, AkOpenMode in_eOpenMode, AkFileSystemFlags* in_pFlags, bool& io_bSyncOpen, AkFileDesc& out_fileDesc)
{
	AkFileHandle aFile = 0;
	AKRESULT eResult;
	if (Sexy::gSexyAppBase->mResStreamsManager != NULL)
	{
		if (__builtin_expect(Sexy::gSexyAppBase->mResStreamsManager->IsInitialized("dynamic.rsb"), 1))
		{
			uint32 aGroupId = Sexy::gSexyAppBase->mResStreamsManager->GetGroupForFile(thePathName, false, false);
			if (aGroupId != 0xFFFFFFFF)
			{
				if (!Sexy::gSexyAppBase->mResStreamsManager->IsGroupLoaded(aGroupId))
				{
				std::string aRSBPath = Sexy::gSexyAppBase->mResStreamsManager->GetRSBPath(aGroupId);
					const char* aRSBFile = aRSBPath.c_str();
					if (aFile != 0 || CAkFileHelpers::OpenFile(aRSBFile, in_eOpenMode, false, false, aFile) == AK_Success)
					{
						out_fileDesc.hFile = aFile;
						eResult = AK_Fail;
						Sexy::gSexyAppBase->mResStreamsManager->LoadGroupFileIndex(aGroupId);
						uint32 aIndex;
						uint32 aSize;
						if (Sexy::gSexyAppBase->mResStreamsManager->GetFileLocation(aGroupId, thePathName, &aIndex, &aSize))
						{
							eResult = AK_Success;
							out_fileDesc.iFileSize = aSize;
							out_fileDesc.uSector = aIndex + mRSBOffset;
							out_fileDesc.deviceID = m_deviceID;
							out_fileDesc.pCustomParam = NULL;
							out_fileDesc.uCustomParamSize = 0;
						}
						goto done;
					}
				}
			}
		}
	}
	{
		std::string aFullPath = Sexy::gSexyAppBase->mFileDriver->GetLoadDataPath() + thePathName;
		const char* aFullFile = aFullPath.c_str();
		eResult = AK_Fail;
		if (__builtin_expect(aFile != 0 || (eResult = CAkFileHelpers::OpenFile(aFullFile, in_eOpenMode, false, false, aFile)) == AK_Success, 1))
		{
			out_fileDesc.hFile = aFile;
			eResult = AK_Fail;
			struct stat aStat;
			if (__builtin_expect(stat(aFullFile, &aStat) == 0, 0))
			{
				eResult = AK_Success;
				out_fileDesc.iFileSize = 0;
				out_fileDesc.uSector = 0;
				out_fileDesc.deviceID = m_deviceID;
				out_fileDesc.pCustomParam = NULL;
				out_fileDesc.uCustomParamSize = 0;
			}
		}
	}
done:
	return eResult;
}

AKRESULT SexyIOHookBlocking::Open(AkFileID in_fileID, AkOpenMode in_eOpenMode, AkFileSystemFlags* in_pFlags, bool& io_bSyncOpen, AkFileDesc& out_fileDesc)
{
	char aPath[100] = {0};
	char aIdStr[50] = {0};
	AKRESULT eResult = AK_Fail;
	sprintf(aIdStr, "%u", in_fileID);
	int aLen = sprintf(aPath, "%s/%s.wem", mFileIdToPathMap[std::string(aIdStr)].c_str(), aIdStr);
	if (aLen > 0)
	{
		io_bSyncOpen = true;
		eResult = Open_Aux(std::string(aPath), in_eOpenMode, in_pFlags, io_bSyncOpen, out_fileDesc);
	}
	return eResult;
}
