//
//  CardGameRewardMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "UICardGameReward.h"
#include "ActivityManager.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "gameNetWork/PacketID.h"
#include "DNode/DNodeWidget.h"
#include "UIDaveTreasure.h"
#include "TGALogMgr.h"
#include "GameCommon.h"

/////////////// Lifecycle ///////////////

CardGameRewardMgr::CardGameRewardMgr()
{
	m_currentPurchasedIndex = 0;
	m_requested = false;
	m_resultCreated = false;
	gMessageRouter->Subscribe(Message::NotifyCardGameRewardDetails, Sexy::MakeDelegate(*this, &CardGameRewardMgr::OnExchangeFinish));
}

CardGameRewardMgr::~CardGameRewardMgr()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Logic ///////////////

void CardGameRewardMgr::OnExchangeFinish(bool success, const New_S2C_BuyCardGameReward* pData)
{
	if (success)
	{
		std::stringstream stream;
		stream.str("");
		std::vector<S2C_BonusInfo> bonusList = pData->BonusList;
		int count = bonusList.size();
		std::vector<LotteryBonus> rewards;
		for (int i = 0; i < count; i++)
		{
			LotteryBonus bonus;
			bonus.Weight = 0;
			bonus.BonusId = bonusList[i].objectId;
			bonus.Quantity = bonusList[i].quantity;
			ProfileChangeItemAmount(bonus.BonusId, bonus.Quantity, false);
			stream << bonusList[i].objectId << "," << bonusList[i].quantity << ";";
			rewards.push_back(bonus);
		}
		gDaveTreasureDataManager->ShowBonus(rewards, std::vector<LotteryBonus>());
		UICardGameReward::GetSingletonPtr()->UpdateUI();
		TGACardGameData data;
		data._step = "6";
		data._star = DString(CardGameUtils::GetCurrentStarCount()).c_str();
		data._reward = stream.str();
		TGALogMgr::GetInstance().LogCardGame(data);
	}
}

void CardGameRewardMgr::Init()
{
	UICardGameReward::ShowDialog();
}

void CardGameRewardMgr::SyncActivityData(const NetworkCardGameReward& i_data)
{
}

void CardGameRewardMgr::RequestNetwork()
{
	gActivityManager->Request(Activity_Artifact_Present, true, 0);
	m_requested = true;
}

void CardGameRewardMgr::onResultClosed()
{
	if (m_resultCreated)
	{
		RequestNetwork();
		m_resultCreated = false;
	}
}

bool CardGameRewardMgr::Load()
{
	m_currentPurchasedIndex = 0;
	ActiveItem item = gActivityManager->GetActiveItem(Activity_Artifact_Present);
	bool loaded = item.IsValid();
	if (loaded)
	{
		loaded = item.m_bOpen;
		if (loaded)
		{
			NetworkCardGameReward data;
			loaded = item.GetDataSerialized(data);
			if (loaded)
				SyncActivityData(data);
		}
	}
	return loaded;
}

void CardGameRewardMgr::onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList)
{
	if (i_success && m_requested)
	{
		if (changeList.find(Activity_Artifact_Present) != changeList.end())
		{
			Init();
			m_requested = false;
		}
	}
}

void CardGameRewardMgr::RequestCardGameReward(const std::string& world, int index)
{
	std::map<std::string, std::string> params;
	params["world"] = world;
	params["index"] = DString(index).c_str();
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_CARD_GAME_ACHIEVEMENT_REWARD, params, 30.0f, [this](const std::string& i_response)
	{
	}, true, true, "[NET_CONNECTING]", 0);
}
