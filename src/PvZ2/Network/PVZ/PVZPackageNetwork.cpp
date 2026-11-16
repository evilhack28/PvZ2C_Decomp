//
//  PVZPackageNetwork.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-10.
//

#include "SexyAppFramework/Common.h"

#include "PVZPackageNetwork.h"
#include "PVZVersion.h"
#include "SexyAppFramework/JsonWriter.h"
#include "Board.h"
#include "PVZDB.h"
#include "LawnApp.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "PurchaseBroker.h"
#include "MagentoService.h"
#include "PresentType.h"
#include "PlantType.h"
#include "ZombieType.h"
#include "ObjectTypeDirectory.h"
#include "GamePropertySheet.h"
#include "DailyRewardConfig.h"

static void RequestWatchedTables(std::vector<WatchInfo>& io_watchInfos, const Sexy::Delegate2<int, const std::string&>& i_onFinished, int i_retries);

/////////////// Lifecycle ///////////////

PVZPackageNetworkManager::PVZPackageNetworkManager()
	: m_completedRequests(0)
{
	m_watchInfos.clear();
}

PVZPackageNetworkManager::~PVZPackageNetworkManager()
{
}

PVZLevelNetworkManager::PVZLevelNetworkManager()
{
}

PVZLevelNetworkManager::~PVZLevelNetworkManager()
{
}

/////////////// Accessors ///////////////

bool PVZPackageNetworkManager::NetworkRequestsCompleted()
{
	return (size_t)m_completedRequests == m_watchInfos.size();
}

/////////////// Requests ///////////////

void PVZPackageNetworkManager::Watch(const std::string& i_name, PVZDB::TableIndex i_tableIndex, bool i_versioned, bool i_encypted)
{
	WatchInfo info;
	info.watchName = i_name;
	info.watchTable = i_tableIndex;
	info.watchIsVersioned = i_versioned;
	info.watchIsEncypted = i_encypted;
	m_watchInfos.push_back(info);
	m_completedRequests = m_watchInfos.size();
}

void PVZPackageNetworkManager::onRequestFinished(int i_index, const std::string& i_json)
{
	m_indicesToApply.push_back((PVZDB::TableIndex)i_index);
	m_jsonToApply.push_back(i_json);
	m_completedRequests++;
	if (NetworkRequestsCompleted())
	{
		ApplyChanges();
	}
}

void PVZPackageNetworkManager::CheckForUpdates(int i_retries)
{
	m_indicesToApply.clear();
	m_jsonToApply.clear();
	m_completedRequests = 0;
	RequestWatchedTables(m_watchInfos, Sexy::MakeDelegate(*this, &PVZPackageNetworkManager::onRequestFinished), i_retries);
}

/////////////// Paths ///////////////

static std::string VersionedTableName(const WatchInfo& i_info)
{
	PVZVersion version = Version::App();
	return i_info.watchName + StrFormat(".%d.%d", version.major, version.minor);
}

std::string PVZPackageNetworkManager::getLocalPathForTable(PVZDB::TableIndex i_index)
{
	size_t i = 0;
	while (i < m_watchInfos.size())
	{
		WatchInfo& info = m_watchInfos[i];
		i++;
		if (info.watchTable == i_index)
		{
			return GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/" + (info.watchIsVersioned ? VersionedTableName(info) : info.watchName);
		}
	}
	return "";
}

/////////////// Apply ///////////////

void PVZPackageNetworkManager::ApplyChanges()
{
	for (size_t i = 0; i < m_indicesToApply.size(); i++)
	{
		std::string path = getLocalPathForTable(m_indicesToApply[i]);
		if (m_jsonToApply[i] != "" && PVZDB::GetInstance().LoadPackageForTableFromJson(m_indicesToApply[i], m_jsonToApply[i], false))
		{
			gSexyAppBase->EraseFile(path);
			PVZDB::GetInstance().SavePackageForTableToFile(m_indicesToApply[i], path, true, false);
		}
		else if (gLawnApp->FileExists(path))
		{
			PVZDB::GetInstance().LoadPackageForTableFromFile(m_indicesToApply[i], path, true, false);
		}
	}

	for (size_t i = 0; i < m_indicesToApply.size(); i++)
	{
		switch (m_indicesToApply[i])
		{
		case PVZDB::TABLE_PRESENTTYPES:
			ObjectTypeDirectory<PresentType>::GetInstancePtr()->Clear();
			ObjectTypeDirectory<PresentType>::GetInstancePtr()->Init(PVZDB::TABLE_PRESENTTYPES);
			break;
		case PVZDB::TABLE_PLANTTYPES:
			ObjectTypeDirectory<PlantType>::GetInstancePtr()->Clear();
			ObjectTypeDirectory<PlantType>::GetInstancePtr()->Init(PVZDB::TABLE_PLANTTYPES);
			break;
		case PVZDB::TABLE_ZOMBIETYPES:
			ObjectTypeDirectory<ZombieType>::GetInstancePtr()->Clear();
			ObjectTypeDirectory<ZombieType>::GetInstancePtr()->Init(PVZDB::TABLE_ZOMBIETYPES);
			break;
		case PVZDB::TABLE_DROP_ITEM_GROUPS:
			ProfileMgr::GetInstance().GetCurrentProfile()->forceRefreshYetiCount();
			break;
		default:
			break;
		}
	}

	RtId propsId = PVZDB::GetInstance().GetIdByAlias(PVZDB::TABLE_PROPERTYSHEETS, RtName(L"DefaultGameProps"));
	GamePropertySheet* gameProps = RtDb::GetDb()->GetObjectForId(propsId)->Cast<GamePropertySheet>();
	ObjectTypeDirectory<PlantType>::GetInstancePtr()->SortTypes(gameProps->PlantTypeOrder);
	m_indicesToApply.clear();
	m_jsonToApply.clear();
	m_completedRequests = 0;
	m_watchInfos.clear();
}

/////////////// Cache ///////////////

void PVZPackageNetworkManager::CleanPackageCache()
{
	if (!NetworkRequestsCompleted())
	return;

	std::string path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/ProjectileTypes.json";
	gSexyAppBase->EraseFile(path);
	path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/PropertySheets.json";
	gSexyAppBase->EraseFile(path);
	path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/DropItemGroups.json";
	gSexyAppBase->EraseFile(path);
	path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/DropItems.json";
	gSexyAppBase->EraseFile(path);
	path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/PresentTypes.json";
	gSexyAppBase->EraseFile(path);
	path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/PlantTypes.json";
	gSexyAppBase->EraseFile(path);
	path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/ZombieTypes.json";
	gSexyAppBase->EraseFile(path);
	path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/BoardGridMaps.json";
	gSexyAppBase->EraseFile(path);
	path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "packages/LevelMutatorTables.json";
	gSexyAppBase->EraseFile(path);
}

/////////////// Package loading ///////////////

void PVZPackageNetworkManager::LoadPackageFile(bool i_local)
{
	if (!NetworkRequestsCompleted())
		return;

	m_watchInfos.clear();
	Watch("ProjectileTypes.json", PVZDB::TABLE_PROJECTILETYPES, false, false);
	Watch("PropertySheets.json", PVZDB::TABLE_PROPERTYSHEETS, false, false);
	Watch("DropItemGroups.json", PVZDB::TABLE_DROP_ITEM_GROUPS, false, false);
	Watch("DropItems.json", PVZDB::TABLE_DROP_ITEMS, false, false);
	Watch("ChallengeDropItems.json", PVZDB::TABLE_CHALLENGE_DROP_ITEMS, false, false);
	Watch("PresentTypes.json", PVZDB::TABLE_PRESENTTYPES, false, false);
	Watch("PlantTypes.json", PVZDB::TABLE_PLANTTYPES, false, false);
	Watch("ZombieTypes.json", PVZDB::TABLE_ZOMBIETYPES, false, false);
	Watch("BoardGridMaps.json", PVZDB::TABLE_BOARDGRIDMAPS, false, false);
	Watch("LevelMutatorTables.json", PVZDB::TABLE_LEVELMUTATORTABLES, false, false);
	Watch("LevelMutatorModules.json", PVZDB::TABLE_LEVELMUTATORMODULES, false, false);
	size_t n = 0;
	if (!i_local)
	{
		CheckForUpdates(n);
		return;
	}

	while (++n <= m_watchInfos.size())
	{
		m_indicesToApply.push_back(m_watchInfos[n - 1].watchTable);
		m_jsonToApply.push_back(std::string(""));
	}
	ApplyChanges();
}

/////////////// Level loading ///////////////

void PVZLevelNetworkManager::LoadLevel(std::string i_levelName)
{
	m_levelName = i_levelName;
	std::string url = "http://sha-vjun-001internal.ditwan.cn:38025/pvz2_designer/pvz2_cheat/packages/";
	url += "levels/" + i_levelName + ".json";
	Sexy::StructuredData data;
	data.BeginObject();
	data.AddString("url", url);
	data.EndObject();
	Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&data, this, this);
}

std::string PVZLevelNetworkManager::GetLevelLocalPath(std::string i_levelName)
{
	return GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "levels/" + i_levelName + ".json";
}

/////////////// Service callbacks ///////////////

void PVZLevelNetworkManager::ServiceRequestFailed(const Sexy::StructuredData*, const void* i_context)
{
	const std::string& level = gLawnApp->m_board->GetLevel();
	if (gLawnApp->m_board->GetLevelIsHard() && m_levelName != level)
	{
		LoadLevel(level);
	}
}

void PVZLevelNetworkManager::ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context)
{
	if (i_context != this)
		return;

	long statusCode = i_response->IntegerForPath("$.statusCode", -1);
	if (!(statusCode == -1 || statusCode == 200))
	{
		ServiceRequestFailed(i_response, i_context);
		return;
	}

	Sexy::JsonWriter writer(Sexy::JsonWriter::COMPACT);
	std::stringstream stream(std::ios_base::out | std::ios_base::in);
	writer.Write(stream, i_response->Root(), true);
	if (stream.str().length() != 0)
	{
		gSexyAppBase->WriteBytesToFile(GetLevelLocalPath(m_levelName), stream.str().c_str(), stream.str().length());
		gLawnApp->m_board->RestartLevel();
		StrFormat("Load %s success!", m_levelName.c_str());
	}
}
