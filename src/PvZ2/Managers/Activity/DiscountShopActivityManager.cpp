//
//  DiscountShopActivityManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "DiscountShopActivity.h"
#include "ActivityManager.h"
#include "NetworkMgr.h"
#include "NetworkMsgProcess.h"

/////////////// Lifecycle ///////////////

DiscountShopActivityManager::DiscountShopActivityManager()
{
}

DiscountShopActivityManager::~DiscountShopActivityManager()
{
}

/////////////// Data ///////////////

void DiscountShopActivityManager::Init(ActiveItem item)
{
	if (item.IsValid() && item.m_bOpen)
	{
		item.GetDataSerialized(_data);
		_activityEndTime = item.m_endDate;
		Sexy::OutputDebugStrF("DiscountShopActivityManager::Init");
		Sexy::OutputDebugStrF("data._rechargeCurrencyToday : %d", _data._rechargeCurrencyToday);
		for (int i = 0; i < _data._itemList.size(); i++)
		{
			Sexy::OutputDebugStrF("data.item[%d].ObjectId : %d", i, _data._itemList[i].ObjectId);
			Sexy::OutputDebugStrF("data.item[%d].Quantity : %d", i, _data._itemList[i].Quantity);
			Sexy::OutputDebugStrF("data.item[%d].CostGem : %d", i, _data._itemList[i].CostGem);
			Sexy::OutputDebugStrF("data.item[%d].Discount : %d", i, _data._itemList[i].Discount);
			Sexy::OutputDebugStrF("data.item[%d].BtnStatus : %d", i, _data._itemList[i].BtnStatus);
			Sexy::OutputDebugStrF("data.item[%d].CurrencyID : %d", i, _data._itemList[i].CurrencyID);
		}
	}
}

/////////////// Network ///////////////

void DiscountShopActivityManager::RequestNetwork()
{
	std::vector<std::pair<int, int>> idList;
	idList.push_back(std::pair<int, int>(Activity_DiscountShopActivity, 1));
	NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestActivityList(idList, 0, true);
}
