//
//  OfflineDataPersistor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "AuthMgr.h"
#include "GameEventMgr.h"
#include "LawnApp.h"
#include "SexyAppFramework/IFileDriver.h"
#include "OfflineDataPersistor.h"

/////////////// OfflineDataPersistor ///////////////

OfflineDataPersistor::OfflineDataPersistor(const char* i_filename, PVZDB::TableIndex tableIndex)
	: m_filename(i_filename)
	, m_tableIndex(tableIndex)
{
}

void OfflineDataPersistor::notifyDataLoaded()
{
	gMessageRouter->Post(Message::PersistorLoadComplete);
}

void OfflineDataPersistor::LoadWithNotify()
{
	Load();
	notifyDataLoaded();
}

std::string OfflineDataPersistor::getOfflineFilename()
{
	return GetFolder(Sexy::IFileDriver::PathType_NoBackup) + m_filename;
}

bool OfflineDataPersistor::saveTableToFile(const std::string& i_filename)
{
	return PVZDB::GetInstance().SavePackageForTableToFile(m_tableIndex, i_filename, false, true);
}

void OfflineDataPersistor::loadTableFromFile(const std::string& i_filename)
{
	PVZDB::GetInstance().LoadPackageForTableFromFile(m_tableIndex, i_filename, false, true);
}

bool OfflineDataPersistor::IsFileExist()
{
	bool result = false;

	if (!m_filename.empty())
	{
		std::string filename = getOfflineFilename();

		bool exist = gLawnApp->FileExists(filename);
		if (exist)
		{
			result = gLawnApp->mFileDriver->GetFileSize(filename) == 0 ? false : exist;
		}
	}

	return result;
}

void OfflineDataPersistor::Load()
{
	std::string filename = getOfflineFilename();
	std::string backupFilename = filename + ".bak";

	if (gLawnApp->FileExists(filename) && gLawnApp->mFileDriver->GetFileSize(filename) != 0)
	{
		loadTableFromFile(filename);
	}
	else if (gLawnApp->FileExists(backupFilename) && gLawnApp->mFileDriver->GetFileSize(backupFilename) != 0)
	{
		loadTableFromFile(backupFilename);
	}

	notifyDataLoaded();
}

bool OfflineDataPersistor::Save()
{
	bool result = AuthMgr::GetInstance().HasNoAuth();

	if (!result)
	{
		if (m_filename == "pp.dat")
		{
			std::string tempFilename = getOfflineFilename() + "_.bak";
			std::string backupFilename = getOfflineFilename() + ".bak";

			result = saveTableToFile(backupFilename);
			if (result)
			{
				gSexyAppBase->EraseFile(tempFilename);
				gSexyAppBase->RenameFile(getOfflineFilename(), tempFilename);
				gSexyAppBase->RenameFile(backupFilename, getOfflineFilename());
				gSexyAppBase->RenameFile(tempFilename, backupFilename);
			}
		}
		else
		{
			result = saveTableToFile(getOfflineFilename());
		}
	}

	return result;
}
