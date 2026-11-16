//
//  MonthlyCardSpecialManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-02.
//

#include "SexyAppFramework/Common.h"

#include "MonthlyCardSpecial.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "GameEventMgr.h"
#include "ActivityManager.h"
#include "RtDelegate.h"

/////////////// Lifecycle ///////////////

MonthlyCardSpecialManager::MonthlyCardSpecialManager()
{
	_activityEndTime = PVZ_EOT();
	gMessageRouter->Subscribe(Message::NotifyRefreshActivityList, Sexy::MakeDelegate(*this, &MonthlyCardSpecialManager::OnNotifyRefreshActivityList));
}

MonthlyCardSpecialManager::~MonthlyCardSpecialManager()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Accessors ///////////////

void MonthlyCardSpecialManager::LoadData(const MonthlyCardSpecialData& data)
{
	_data = data;
}

MonthlyCardSpecialData& MonthlyCardSpecialManager::GetData()
{
	return _data;
}

/////////////// Logic ///////////////

void MonthlyCardSpecialManager::RequestNetwork()
{
	Sexy::LazySingleton<ActivityManager>::GetInstancePtr()->Request(Activity_MonthlyCardSpecial);
}

void MonthlyCardSpecialManager::OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList)
{
	if (i_success)
	{
		const int id = Activity_MonthlyCardSpecial;
		if (changeList.find(id) != changeList.end())
		{
			ActiveItem item = Sexy::LazySingleton<ActivityManager>::GetInstancePtr()->GetActiveItem(id);
			MonthlyCardSpecialData data;
			if (item.GetDataSerialized(data))
				_data = data;
		}
	}
}

void MonthlyCardSpecialManager::TestInitData()
{
	MonthlyCardSpecialItemData item;
	item.TrailDay = 1;
	item.BuyTimes = 1;
	for (int i = 0; i < 4; i++)
		_data.ItemDataList.push_back(item);
}
