//
//  PVZCachedNetworkTable.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-10.
//

#include "SexyAppFramework/Common.h"

#include "PVZCachedNetworkTable.h"
#include "PVZVersion.h"
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

PVZCachedNetworkTableManager::PVZCachedNetworkTableManager()
	: m_completedRequests(0)
{
	m_watchInfos.clear();
}

PVZCachedNetworkTableManager::~PVZCachedNetworkTableManager()
{
}

PVZCachedNetworkTableManager& PVZCachedNetworkTableManager::operator=(const PVZCachedNetworkTableManager& i_other)
{
	m_watchInfos = i_other.m_watchInfos;
	m_indicesToApply = i_other.m_indicesToApply;
	m_jsonToApply = i_other.m_jsonToApply;
	m_completedRequests = i_other.m_completedRequests;
	return *this;
}

/////////////// Accessors ///////////////

bool PVZCachedNetworkTableManager::NetworkRequestsCompleted()
{
	Sexy::OutputDebugStrF("DailyRewardConfig, NetworkRequestsCompleted m_completedRequests : %d", m_completedRequests);
	return m_completedRequests == 0;
}

/////////////// Requests ///////////////

void PVZCachedNetworkTableManager::CheckForUpdates(int i_retries)
{
	RequestWatchedTables(m_watchInfos, Sexy::MakeDelegate(*this, &PVZCachedNetworkTableManager::onRequestFinished), i_retries);
}

void PVZCachedNetworkTableManager::Watch(const std::string& i_name, PVZDB::TableIndex i_tableIndex, bool i_versioned, bool i_encypted)
{
	WatchInfo info;
	info.watchName = i_name;
	info.watchTable = i_tableIndex;
	info.watchIsVersioned = i_versioned;
	info.watchIsEncypted = i_encypted;
	info.isFetching = false;
	m_watchInfos.push_back(info);
	m_completedRequests++;
}

void PVZCachedNetworkTableManager::onRequestFinished(int i_index, const std::string& i_json)
{
	m_indicesToApply.push_back((PVZDB::TableIndex)i_index);
	m_jsonToApply.push_back(i_json);
	Sexy::OutputDebugStrF("DailyRewardConfig, onRequestFinished : %d", i_index);
	m_completedRequests--;
}

/////////////// Paths ///////////////

static std::string VersionedTableName(const WatchInfo& i_info)
{
	PVZVersion version = Version::App();
	return i_info.watchName + StrFormat(".%d.%d", version.major, version.minor);
}

std::string PVZCachedNetworkTableManager::getLocalPathForTable(PVZDB::TableIndex i_index)
{
	size_t i = 0;
	while (i < m_watchInfos.size())
	{
		WatchInfo& info = m_watchInfos[i];
		i++;
		if (info.watchTable == i_index)
		{
			return GetFolder(Sexy::IFileDriver::PathType_NoBackup) + (info.watchIsVersioned ? VersionedTableName(info) : info.watchName);
		}
	}
	return "";
}

/////////////// Apply ///////////////

void PVZCachedNetworkTableManager::ApplyChanges()
{
	bool purchaseConfigChanged = false;
	Sexy::OutputDebugStrF("DailyRewardConfig, PVZCachedNetworkTableManager::ApplyChanges, m_indicesToApply.size() : %d", m_indicesToApply.size());
	for (size_t i = 0; i < m_indicesToApply.size(); i++)
	{
		std::string path = getLocalPathForTable(m_indicesToApply[i]);
		if (m_jsonToApply[i] != "" && PVZDB::GetInstance().LoadPackageForTableFromJson(m_indicesToApply[i], m_jsonToApply[i], false))
		{
			if (m_indicesToApply[i] == PVZDB::TABLE_MAGENTO)
			{
				Sexy::OutputDebugStrF("Magento, get config json : %s", m_jsonToApply[i].c_str());
				Magento::InitMagentoDataSign();
			}
			else if (m_indicesToApply[i] == PVZDB::TABLE_PURCHASE_CONFIG)
			{
				purchaseConfigChanged = true;
			}
			gSexyAppBase->EraseFile(path);
			if (!PVZDB::GetInstance().SavePackageFromNetJsonStringToFile(m_indicesToApply[i], m_jsonToApply[i], path, false, true))
			{
				Sexy::OutputDebugStrF("DailyRewardConfig, save json error");
			}
			if (m_indicesToApply[i] == PVZDB::TABLE_DAILY_REWARD_CONFIG)
			{
				Sexy::OutputDebugStrF("DailyRewardConfig, drc9 is existed : %d", gLawnApp->FileExists(path));
			}
		}
		else
		{
			if (gLawnApp->FileExists(path))
			{
				PVZDB::GetInstance().LoadPackageForTableFromFile(m_indicesToApply[i], path, false, true);
				if (m_indicesToApply[i] == PVZDB::TABLE_MAGENTO)
				{
					Magento::InitMagentoDataSign();
				}
				else if (m_indicesToApply[i] == PVZDB::TABLE_PURCHASE_CONFIG)
				{
					purchaseConfigChanged = true;
					goto next;
				}
			}
			if (m_indicesToApply[i] == PVZDB::TABLE_DAILY_REWARD_CONFIG)
			{
				if (m_jsonToApply[i] == "")
				{
					Sexy::OutputDebugStrF("DailyRewardConfig, drc9 load from server failed : empty json");
				}
				else
				{
					Sexy::OutputDebugStrF("DailyRewardConfig, drc9 load from server failed : parse failed");
				}
			}
		}
		next:;
	}

	if (purchaseConfigChanged)
	{
		ProfileMgr::GetInstance().GetPurchaseBroker()->ResetPurchaseAdapter();
	}

	if (NetworkRequestsCompleted())
	{
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
			case PVZDB::TABLE_DAILY_REWARD_CONFIG:
			{
				struct tm startTime = {};
				startTime.tm_year = gLawnApp->GetDailyRewardConfig()->GetStartYear() - 1900;
				startTime.tm_mon = gLawnApp->GetDailyRewardConfig()->GetStartMonth() - 1;
				startTime.tm_mday = gLawnApp->GetDailyRewardConfig()->GetStartDay();
				startTime.tm_hour = 0;
				startTime.tm_min = 0;
				startTime.tm_sec = 0;
				time_t signTimeStamp = GetTimegm(&startTime) - GetBJTimeOffset();
				ProfileMgr::GetInstance().GetCurrentProfile()->SetLastRequestSignTimeStamp(signTimeStamp);
				break;
			}
			default:
				break;
			}
		}

		RtId propsId = PVZDB::GetInstance().GetIdByAlias(PVZDB::TABLE_PROPERTYSHEETS, RtName(L"DefaultGameProps"));
		GamePropertySheet* gameProps = RtDb::GetDb()->GetObjectForId(propsId)->Cast<GamePropertySheet>();
		ObjectTypeDirectory<PlantType>::GetInstancePtr()->SortTypes(gameProps->PlantTypeOrder);
		m_watchInfos.clear();
	}
	m_indicesToApply.clear();
	m_jsonToApply.clear();
}
