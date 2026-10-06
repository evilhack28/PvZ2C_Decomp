//
//  DebugLog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

#include "DebugLog.h"
#include "FileUtil.h"
#include "LawnApp.h"

/////////////// DebugLog ///////////////

DebugLog::DebugLog()
{
	m_Flags = DebugLogFlags_None;
	m_pathLogCat = "";

	SetFlag(m_Flags, DebugLog_Error, true);
	SetFlag(m_Flags, DebugLog_NetMessage, true);
	SetFlag(m_Flags, DebugLog_BIData, true);
	SetFlag(m_Flags, DebugLog_LoadGroup, true);
}

DebugLog::~DebugLog()
{
}

void DebugLog::SendLog(const std::string& i_log, DebugLogFlags i_flag, DebugPathType i_type, const std::string& i_tag)
{
}

std::string DebugLog::GetExternalFolder()
{
	return Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)gLawnApp) + "Debug/";
}

bool DebugLog::LogFile(const std::string& i_file, const std::string& i_mode, const std::string& i_log)
{
	std::string folder = GetExternalFolder();
	std::string path = folder + i_file;

	gLawnApp->mFileDriver->MakeFolders(folder);

	std::shared_ptr<FILE> file = FileUtil::openFile(path, i_mode);
	bool result = (bool)file;
	if (result)
	{
		FileUtil::writeFile(file, i_log);
	}

	return result;
}

bool DebugLog::ReadFile(const std::string& i_file, const std::string& i_mode, std::string& i_content)
{
	std::string folder = GetExternalFolder();
	std::string path = folder + i_file;

	std::shared_ptr<FILE> file = FileUtil::openFile(path, i_mode);
	return FileUtil::readFile(file, i_content);
}
