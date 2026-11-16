//
//  TrialCardManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-02.
//

#include "SexyAppFramework/Common.h"

#include "PlantTrialCardManager.h"
#include "TodLib/TodStringFile.h"
#include "TodLib/TodCommon.h"
#include "LawnApp.h"
#include "Board.h"
#include "NewPVPUtils.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "NameMapperEnum.h"
#include "gameNetWork/PacketID.h"
#include "DNode/DNodeWidget.h"

namespace RiftUtils { bool IsPlayingRiftLevel(); }

/////////////// Lifecycle ///////////////

TrialCardManager::TrialCardManager()
{
}

TrialCardManager::~TrialCardManager()
{
}

/////////////// Accessors ///////////////

bool TrialCardManager::ContainsId(int i_id)
{
	return i_id >= 97001 && i_id <= 99000;
}

std::vector<TrialCardConfig> TrialCardManager::GetTrialCardConfigList()
{
	return SynchronizeData.TrialCardConfigList;
}

std::vector<PlayerTrialCardInfo> TrialCardManager::GetPlayerTrialCardList()
{
	return SynchronizeData.PlayerTrialCardList;
}

std::vector<PlayerTrialStatusInfo> TrialCardManager::GetPlayerTrialStatusList()
{
	return SynchronizeData.PlayerTrialStatusList;
}

SexyString TrialCardManager::GetTrialCardName(int i_id)
{
	TrialCardConfig config = GetTrialCardConfigByID(i_id);
	int level = config.PlantLevel;
	int days = config.DurationHours / 24;
	std::string plantName = PlantNameMapperServerID::GetInstance().GetNameForId(config.PlantID);
	SexyString time = TodReplaceNumberString(SexyString(_S("[TOTAL_LOGIN_DAYS]")), _S("{DAY_COUNT}"), days);
	SexyString name = TodStringTranslate(Sexy::ToWString("[" + Sexy::StringToUpper(plantName) + "]"));
	SexyString result = TodReplaceNumberString(SexyString(_S("[TEMPLATE_TRIAL_CARD_NAME]")), _S("{NUM}"), level);
	result = TodReplaceString(result, _S("{TIME}"), time);
	result = TodReplaceString(result, _S("{NAME}"), name);
	return result;
}

SexyString TrialCardManager::GetTrialCardUse(int i_id)
{
	TrialCardConfig config = GetTrialCardConfigByID(i_id);
	int level = config.PlantLevel;
	int days = config.DurationHours / 24;
	std::string plantName = PlantNameMapperServerID::GetInstance().GetNameForId(config.PlantID);
	SexyString time = TodReplaceNumberString(SexyString(_S("[TOTAL_LOGIN_DAYS]")), _S("{DAY_COUNT}"), days);
	SexyString name = TodStringTranslate(Sexy::ToWString("[" + Sexy::StringToUpper(plantName) + "]"));
	SexyString result = TodReplaceNumberString(SexyString(_S("[TEMPLATE_TRIAL_CARD_USE]")), _S("{NUM}"), level);
	result = TodReplaceString(result, _S("{TIME}"), time);
	result = TodReplaceString(result, _S("{NAME}"), name);
	return result;
}

SexyString TrialCardManager::GetTrialCardGetWay(int i_id)
{
	return TodStringTranslate(_S("[TEMPLATE_TRIAL_CARD_GET_WAY]"));
}

TrialCardConfig TrialCardManager::GetConfigForBestTrialStatus(int i_plantId)
{
	return GetTrialCardConfigByID(GetBestTrialStatus(i_plantId).ID);
}

bool TrialCardManager::HasConfig(int i_id)
{
	for (size_t i = 0; i < SynchronizeData.TrialCardConfigList.size(); i++)
	{
		if (SynchronizeData.TrialCardConfigList[i].ID == i_id)
			return true;
	}
	return false;
}

PlayerTrialCardInfo TrialCardManager::GetPlayerTrialCardByID(int i_cardId)
{
	for (size_t i = 0; i < SynchronizeData.PlayerTrialCardList.size(); i++)
	{
		if (SynchronizeData.PlayerTrialCardList[i].ID == i_cardId)
			return SynchronizeData.PlayerTrialCardList[i];
	}
	return PlayerTrialCardInfo();
}

PlayerTrialStatusInfo TrialCardManager::GetPlayerTrialStatusByID(int i_cardId)
{
	for (size_t i = 0; i < SynchronizeData.PlayerTrialStatusList.size(); i++)
	{
		if (SynchronizeData.PlayerTrialStatusList[i].ID == i_cardId)
			return SynchronizeData.PlayerTrialStatusList[i];
	}
	PlayerTrialStatusInfo info;
	return info;
}

TrialCardConfig TrialCardManager::GetTrialCardConfigByID(int i_cardId)
{
	for (size_t i = 0; i < SynchronizeData.TrialCardConfigList.size(); i++)
	{
		if (SynchronizeData.TrialCardConfigList[i].ID == i_cardId)
			return SynchronizeData.TrialCardConfigList[i];
	}
	TrialCardConfig config;
	return config;
}

bool TrialCardManager::CanUseOnCurrentLevel()
{
	if (NewPVPUtils::IsPlayingNewPVP() || (gLawnApp->m_board && gLawnApp->m_board->IsDangerRoom()) || (gLawnApp->m_board && gLawnApp->m_board->IsBattleZ()) || RiftUtils::IsPlayingRiftLevel())
		return false;
	return true;
}

std::vector<PlayerTrialStatusInfo> TrialCardManager::GetTrialStatusList(int i_plantId)
{
	std::vector<PlayerTrialStatusInfo> list;
	for (size_t i = 0; i < SynchronizeData.PlayerTrialStatusList.size(); i++)
	{
		TrialCardConfig config = GetTrialCardConfigByID(SynchronizeData.PlayerTrialStatusList[i].ID);
		if (config.PlantID == i_plantId)
			list.push_back(SynchronizeData.PlayerTrialStatusList[i]);
	}
	return list;
}

bool TrialCardManager::BestThenRight(PlayerTrialStatusInfo& i_left, PlayerTrialStatusInfo& i_right)
{
	bool result = false;
	if (i_left.ID != 0)
	{
		result = true;
		if (i_right.ID != 0)
		{
			TrialCardConfig leftConfig = GetTrialCardConfigByID(i_left.ID);
			TrialCardConfig rightConfig = GetTrialCardConfigByID(i_right.ID);
			result = false;
			if (leftConfig.PlantLevel > rightConfig.PlantLevel)
				result = true;
			else if (leftConfig.PlantLevel == rightConfig.PlantLevel)
				result = i_left.EndTime > i_right.EndTime;
		}
	}
	return result;
}

PlayerTrialStatusInfo TrialCardManager::GetBestTrialStatus(int i_plantId)
{
	PlayerTrialStatusInfo best;
	std::vector<PlayerTrialStatusInfo> list = GetTrialStatusList(i_plantId);
	for (size_t i = 0; i < list.size(); i++)
	{
		if (BestThenRight(list[i], best))
			best = list[i];
	}
	return best;
}

void TrialCardManager::AddTrialCard(int i_cardId, int i_amount)
{
	std::vector<PlayerTrialCardInfo>& list = SynchronizeData.PlayerTrialCardList;
	for (std::vector<PlayerTrialCardInfo>::iterator it = list.begin(), end = list.end(); it != end; ++it)
	{
		if (it->ID == i_cardId)
		{
			it->Number += i_amount;
			return;
		}
	}
	PlayerTrialCardInfo info;
	info.ID = i_cardId;
	info.Number = 1;
	list.push_back(info);
}

void TrialCardManager::SubTrialCard(int i_cardId)
{
	std::vector<PlayerTrialCardInfo>& list = SynchronizeData.PlayerTrialCardList;
	for (std::vector<PlayerTrialCardInfo>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (it->ID == i_cardId)
		{
			it->Number--;
			if (it->Number <= 0)
				list.erase(it);
			return;
		}
	}
}

void TrialCardManager::SynchronizeTrialData()
{
	std::map<std::string, std::string> params;
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_SYNCHORIZE_TRIAL_CARD, params, 30.0f, [this](const std::string& i_response)
	{
		SynchronizeData.Clear();
		if (SynchronizeData.SerializeJson(i_response))
			CheckTrial();
	}, true, true, "[NET_CONNECTING]", 0);
}

bool TrialCardManager::IsTrialingPlant(int i_plantId)
{
	bool result = CanUseOnCurrentLevel();
	if (result)
		goto trial;
done:
	return result;
trial:
	result = !GetTrialStatusList(i_plantId).empty();
	goto done;
}

void TrialCardManager::CheckTrial()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	time_t now = gLawnApp->GetRealServerTime();
	std::vector<int> seenIds;
	std::vector<PlayerTrialStatusInfo>::iterator it = SynchronizeData.PlayerTrialStatusList.begin();
	while (it != SynchronizeData.PlayerTrialStatusList.end())
	{
		bool keep = false;
		if (now < it->EndTime)
		{
			bool found = std::find(seenIds.begin(), seenIds.end(), it->ID) != seenIds.end();
			if (!found)
			{
				TrialCardConfig config = GetTrialCardConfigByID(it->ID);
				std::string plantName = PlantNameMapperServerID::GetInstance().GetNameForId(config.PlantID);
				keep = true;
				if (profile->GetIsPlantUnlocked(plantName))
				{
					profile->GetPlantStarLevel(plantName, found);
					keep = profile->GetPlantStarLevel(plantName, found) < config.PlantLevel;
				}
			}
		}
		if (!keep)
			it = SynchronizeData.PlayerTrialStatusList.erase(it);
		else
		{
			seenIds.push_back(it->ID);
			++it;
		}
	}
}
