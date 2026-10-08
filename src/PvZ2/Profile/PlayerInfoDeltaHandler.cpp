//
//  PlayerInfoDeltaHandler.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-08.
//

#include "SexyAppFramework/Common.h"

#include "LawnApp.h"
#include "PlayerInfo.h"
#include "PlayerInfoDeltaHandler.h"

static const char* const gSnapshotFilenames[] = { "snapshot1.dat", "snapshot2.dat" };
static int sSnapshotIndx;

/////////////// Lifecycle ///////////////

PlayerInfoDeltaHandler::PlayerInfoDeltaHandler()
	: OfflineDataPersistor("/dev/null", PVZDB::TABLE_PLAYER_INFO_DELTA)
{
	m_offlineFilenameIndx = gSexyAppBase->RegistryReadInteger("CurrSnapshotIndx", &sSnapshotIndx);
}

PlayerInfoDeltaHandler::~PlayerInfoDeltaHandler()
{
}

/////////////// Accessors ///////////////

int PlayerInfoDeltaHandler::getOtherIndex() const
{
	return (m_offlineFilenameIndx + 1) % 2;
}

std::string PlayerInfoDeltaHandler::getOfflineFilename()
{
	return GetFolder(Sexy::IFileDriver::PathType_NoBackup) + gSnapshotFilenames[m_offlineFilenameIndx];
}

void PlayerInfoDeltaHandler::UpdateFileIndex()
{
	m_offlineFilenameIndx = getOtherIndex();
	gSexyAppBase->RegistryWriteInteger("CurrSnapshotIndx", m_offlineFilenameIndx);
}

/////////////// Delta ///////////////

void PlayerInfoDeltaHandler::FillCurrentMap(IndexToPlayerInfoMap& currentMap)
{
	currentMap.clear();

	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLAYER_PROFILES); it; ++it)
	{
		PlayerInfoPtr playerInfo(*it);
		if (playerInfo.IsValid())
		{
			currentMap[playerInfo->GetProfileIndex()] = playerInfo;
		}
	}
}

bool PlayerInfoDeltaHandler::CreateDelta()
{
	IndexToPlayerInfoMap currentMap;
	FillCurrentMap(currentMap);

	{
		OfflineDataPersistor snapshotPersistor(gSnapshotFilenames[getOtherIndex()], PVZDB::TABLE_PLAYER_PROFILES);
		snapshotPersistor.Save();
	}

	bool result;
	std::string filename = getOfflineFilename();
	if (gLawnApp->FileExists(filename))
	{
		loadTableFromFile(filename);

		IndexToPlayerInfoMap snapshotMap;
		SnapshotToDelta(currentMap, snapshotMap);
		result = saveTableToFile(m_filename);
	}
	else
	{
		result = PVZDB::GetInstance().SavePackageForTableToFile(PVZDB::TABLE_PLAYER_PROFILES, m_filename, false, false);
	}

	return result;
}

void PlayerInfoDeltaHandler::SnapshotToDelta(IndexToPlayerInfoMap& currentMap, IndexToPlayerInfoMap& snapshotMap)
{
	snapshotMap.clear();

	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(m_tableIndex); it; ++it)
	{
		PlayerInfoPtr deltaInfo(*it);
		if (deltaInfo.IsValid())
		{
			long index = deltaInfo->GetProfileIndex();
			snapshotMap[index] = deltaInfo;

			IndexToPlayerInfoMapConstIter found = currentMap.find(index);
			if (found != currentMap.end())
			{
				deltaInfo->UpdateForDelta(*found->second);
			}
			else
			{
				deltaInfo->MarkForDelete();
			}
		}
	}

	for (IndexToPlayerInfoMapConstIter it = currentMap.begin(); it != currentMap.end(); ++it)
	{
		long index = it->second->GetProfileIndex();
		if (snapshotMap.find(index) == snapshotMap.end())
		{
			PVZDB::GetInstance().GetTable(m_tableIndex)->AllocId(it->second, Sexy::RtDbTable::ODM_Never, true, NULL);
		}
	}
}
