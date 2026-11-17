//
//  PlantWarsNetworkMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//

#include "SexyAppFramework/Common.h"

#include "PlantWars.h"
#include "NetworkMgr.h"
#include "LawnApp.h"
#include "Board.h"
#include "ActivityManager.h"
#include "RiftThemeMgr.h"
#include "PVZ2UIDialog.h"

namespace PlantWarsUtils { int CalcNodeType(std::string i_plant); }

/////////////// Lifecycle ///////////////

PlantWarsNetworkMgr::PlantWarsNetworkMgr()
{
	m_flag08 = false;
	m_intF8 = 0;
	m_currentLevel = "";
	m_flag118 = false;
	m_int11C = 0;
	gMessageRouter->Subscribe(&Message::NotifyRefreshActivityList, Sexy::MakeDelegate(*this, &PlantWarsNetworkMgr::onNotifyRefreshActivityList));
}

PlantWarsNetworkMgr::~PlantWarsNetworkMgr()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Accessors ///////////////

PlantWarsMainEntryData& PlantWarsNetworkMgr::GetMainEntryData()
{
	return m_mainEntryData;
}

PlantWarsEndOfPlayData& PlantWarsNetworkMgr::GetEndPlayData()
{
	return m_endOfPlayData;
}

std::string& PlantWarsNetworkMgr::GetPrefixWorld()
{
	return m_mainEntryData.cw;
}

bool PlantWarsNetworkMgr::IsOffSeason()
{
	return m_mainEntryData.offseason;
}

void PlantWarsNetworkMgr::SetCurrentLevel(std::string i_level)
{
	m_currentLevel = i_level;
}

std::string PlantWarsNetworkMgr::GetCurrentLevel() const
{
	return m_currentLevel;
}

int PlantWarsNetworkMgr::GetCurrentWorldId()
{
	return GetCurrentWorldData().id;
}

std::vector<PlantWarsLevelData>& PlantWarsNetworkMgr::GetCurrentLevelInfo()
{
	return GetCurrentWorldData().levels;
}

/////////////// Level data ///////////////

PlantWarsWorldData& PlantWarsNetworkMgr::GetCurrentWorldData()
{
	PlantWarsWorldData world;
	std::vector<PlantWarsWorldData>& worlds = m_mainEntryData.worldInfo;
	for (size_t i = 0; i < worlds.size(); i++)
	{
		if (worlds[i].pw == GetPrefixWorld())
			return worlds[i];
	}
	return world;
}

PlantWarsLevelData PlantWarsNetworkMgr::GetCurrentLevelData()
{
	PlantWarsLevelData data;
	for (size_t i = 0; i < m_mainEntryData.worldInfo.size(); i++)
	{
		if (m_mainEntryData.worldInfo[i].pw == GetPrefixWorld())
		{
			if ((size_t)GetCurrentLevelIndex() < m_mainEntryData.worldInfo[i].levels.size())
				return m_mainEntryData.worldInfo[i].levels[GetCurrentLevelIndex()];
		}
	}
	return data;
}

void PlantWarsNetworkMgr::GetCurrentLevelScoreList(std::vector<int>& o_scoreList)
{
	int level = GetCurrentLevelIndex();
	if (m_levelTempData.size() > level)
	{
		o_scoreList.push_back(m_levelTempData[level].m_nodes[0].curScore);
		o_scoreList.push_back(m_levelTempData[level].m_nodes[1].curScore);
	}
}

WorldMapEventStatus PlantWarsNetworkMgr::GetLevelStatus(const std::string& i_worldPrefix, int i_level)
{
	int status = 0;
	for (size_t i = 0; i < m_mainEntryData.worldInfo.size(); i++)
	{
		if (m_mainEntryData.worldInfo[i].pw == i_worldPrefix)
		{
			if (i_level >= 0 && (size_t)i_level < m_mainEntryData.worldInfo[i].levels.size())
				status = m_mainEntryData.worldInfo[i].levels[i_level].ls;
		}
	}
	return status == 1 ? EVENTSTATUS_UNLOCKED : status == 2 ? EVENTSTATUS_CLEARED : EVENTSTATUS_LOCKED;
}

void PlantWarsNetworkMgr::SetCurrentLevelNodeScore(int i_score)
{
	int level = GetCurrentLevelIndex();
	if (m_levelTempData.size() > level)
	{
		std::string levelName = gLawnApp->m_board->GetLevel();
		int node = PlantWarsUtils::CalcNodeType(levelName);
		m_levelTempData[level].m_nodes[node].curScore = i_score;
	}
}

int PlantWarsNetworkMgr::GetLeaderBoardBonusCurrentIndex(std::string i_worldPrefix)
{
	for (size_t i = 0; i < m_mainEntryData.worldInfo.size(); i++)
	{
		if (m_mainEntryData.worldInfo[i].pw == i_worldPrefix)
			return m_mainEntryData.worldInfo[i].lbb.ci;
	}
	return -1;
}

int PlantWarsNetworkMgr::GetLevelScore(int i_level, int i_node)
{
	return GetCurrentLevelInfo()[i_level].nodes[i_node].curScore;
}

int PlantWarsNetworkMgr::GetLevelTotalScore(int i_level)
{
	return GetLevelScore(i_level, 0) + GetLevelScore(i_level, 1);
}

int PlantWarsNetworkMgr::GetLevelTargetScore(int i_level, int i_node)
{
	return GetCurrentLevelInfo()[i_level].nodes[i_node].score;
}

int PlantWarsNetworkMgr::GetLevelTargetStarInfoScore(int i_level, int i_index)
{
	return GetCurrentLevelInfo()[i_level].starsTarget[i_index].score;
}

bool PlantWarsNetworkMgr::GetLevelTargetStarInfoStatus(int i_level, int i_index)
{
	return GetCurrentLevelInfo()[i_level].starsTarget[i_index].isCompleted;
}

bool PlantWarsNetworkMgr::GetLevelTargetStatus(int i_level)
{
	return GetCurrentLevelInfo()[i_level].passTarget.isCompleted;
}

int PlantWarsNetworkMgr::GetLevelTargetTotalScore(int i_level)
{
	return GetCurrentLevelInfo()[i_level].passTarget.score;
}

/////////////// Level temp data ///////////////

float PlantWarsNetworkMgr::GetLevelTime(int i_level)
{
	float time = m_levelTempData[i_level].GetLevelTime(0);
	return time + m_levelTempData[i_level].GetLevelTime(1);
}

float PlantWarsNetworkMgr::GetLevelTime(int i_level, int i_node)
{
	return m_levelTempData[i_level].GetLevelTime(i_node);
}

void PlantWarsNetworkMgr::SetLevelTime(int i_level, int i_node, float i_time)
{
	m_levelTempData[i_level].SetLevelTime(i_node, i_time);
}

void PlantWarsNetworkMgr::ClearNode(int i_level, int i_node)
{
	m_levelTempData[i_level].ClearNode(i_node);
}

std::vector<std::string> PlantWarsNetworkMgr::GetNodePlantPackets(int i_level, int i_node)
{
	return m_levelTempData[i_level].GetNodePlantPackets(i_node);
}

std::string PlantWarsNetworkMgr::GetNodePlantPacket(int i_level, int i_node, int i_index)
{
	return m_levelTempData[i_level].GetNodePlantPacket(i_node, i_index);
}

void PlantWarsNetworkMgr::AddNodePlant(int i_level, int i_node, std::string i_plant)
{
	m_levelTempData[i_level].AddNode(i_node, i_plant);
}

void PlantWarsNetworkMgr::DeleteNodePlant(int i_level, int i_node, std::string i_plant)
{
	m_levelTempData[i_level].DeleteNode(i_node, i_plant);
}

int PlantWarsNetworkMgr::CalcNodeType(std::string i_plant)
{
	if (i_plant.find("_a") != std::string::npos)
		return 0;
	return i_plant.find("_b") != std::string::npos ? 1 : -1;
}

/////////////// Rewards ///////////////

void PlantWarsNetworkMgr::ObtainStarReward(int i_worldId, int i_rewardId)
{
	for (size_t i = 0; i < m_mainEntryData.worldInfo.size(); i++)
	{
		if (m_mainEntryData.worldInfo[i].id == i_worldId)
		{
			for (size_t j = 0; j < m_mainEntryData.worldInfo[i].reward.size(); j++)
			{
				if (m_mainEntryData.worldInfo[i].reward[j].id == i_rewardId)
				{
					m_mainEntryData.worldInfo[i].reward[j].status = true;
					return;
				}
			}
		}
	}
}

void PlantWarsNetworkMgr::ObtainLeaderBoardBonus(int i_worldId, int i_rewardId)
{
	for (size_t i = 0; i < m_mainEntryData.worldInfo.size(); i++)
	{
		if (m_mainEntryData.worldInfo[i].id == i_worldId)
		{
			for (size_t j = 0; j < m_mainEntryData.worldInfo[i].reward.size(); j++)
			{
				if (m_mainEntryData.worldInfo[i].reward[j].id == i_rewardId)
				{
					m_mainEntryData.worldInfo[i].reward[j].status = true;
					return;
				}
			}
		}
	}
}

/////////////// Sync ///////////////

void PlantWarsNetworkMgr::syncMainEntryInfo()
{
	ActiveItem item = gActivityManager->GetActiveItem(10888);
	if (item.m_bOpen)
	{
		PlantWarsMainEntryData data;
		if (item.GetDataSerialized(data))
		{
			RiftThemeMgr::GetInstance().SyncTheme(data.ct);
			m_mainEntryData = data;
			syncWorldMapInfo(data);
		}
		else
		{
			PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(L"", L"[WECHAT_ACTIVITY_DATA_ERROR]");
			dialog->AddButton(L"[BUTTON_OK]", Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
		}
	}
}

void PlantWarsNetworkMgr::syncWorldMapInfo(const PlantWarsMainEntryData& i_data)
{
	m_levelTempData.clear();
	for (size_t i = 0; i < m_mainEntryData.worldInfo.size(); i++)
	{
		if (m_mainEntryData.worldInfo[i].pw == GetPrefixWorld())
		{
			for (size_t j = 0; j < m_mainEntryData.worldInfo[i].levels.size(); j++)
			{
				PlantWarsLevelTempData tempData;
				tempData.Assign(0, m_mainEntryData.worldInfo[i].levels[j].nodes[0].battleArray);
				tempData.Assign(1, m_mainEntryData.worldInfo[i].levels[j].nodes[1].battleArray);
				m_levelTempData.push_back(tempData);
			}
		}
	}
}

/////////////// Network ///////////////

void PlantWarsNetworkMgr::RequestNetwork()
{
	INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
	std::vector<std::pair<int, int>> idList = { { 10888, 0 } };
	process->RequestActivityList(idList, 0, true);
}

void PlantWarsNetworkMgr::onNotifyRefreshActivityList(bool i_success, const std::set<int>& i_ids)
{
	if (i_success && m_flag08)
	{
		if (i_ids.find(10888) != i_ids.end())
		{
			syncMainEntryInfo();
			m_flag08 = false;
			if (m_callback)
				m_callback();
		}
	}
}

void PlantWarsNetworkMgr::RequestMainEntryData(std::function<void()> i_callback)
{
	if (!m_flag08)
	{
		{
			INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
			std::vector<std::pair<int, int>> idList = { { 10888, 1 } };
			process->RequestActivityList(idList, 0, true);
		}
		m_flag08 = true;
		m_callback = i_callback;
	}
}

void PlantWarsNetworkMgr::RequestStartPlayData(PlantWarsStartPlayParamData i_data)
{
}

void PlantWarsNetworkMgr::RequestTransferPlayData(PlantWarsTransferPlayParamData i_data)
{
}
