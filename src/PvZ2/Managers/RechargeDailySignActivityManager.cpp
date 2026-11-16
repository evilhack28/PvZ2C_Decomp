//
//  RechargeDailySignActivityManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "RechargeDailySignActivity.h"
#include "ActivityManager.h"
#include "NetworkMgr.h"
#include "NetworkMsgProcess.h"

/////////////// Lifecycle ///////////////

RechargeDailySignActivityManager::RechargeDailySignActivityManager()
{
}

RechargeDailySignActivityManager::~RechargeDailySignActivityManager()
{
}

/////////////// Data ///////////////

void RechargeDailySignActivityManager::Init(ActiveItem item)
{
	if (item.IsValid() && item.m_bOpen)
	{
		item.GetDataSerialized(_data);
		_activityEndTime = item.m_endDate;
		Sexy::OutputDebugStrF("RechargeDailySignActivityManager::Init");
		Sexy::OutputDebugStrF("data._rechargeCurrency : %d", _data._rechargeCurrency);
		Sexy::OutputDebugStrF("data._advanceSignDayNum : %d", _data._advanceSignDayNum);
		Sexy::OutputDebugStrF("data._normalDaySignNum : %d", _data._normalDaySignNum);
		for (int i = 0; i < _data._dayDataList.size(); i++)
		{
			for (int j = 0; j < _data._dayDataList[i].size(); j++)
			{
				Sexy::OutputDebugStrF("data[%d].[%d].ObjectID : %d", i, j, _data._dayDataList[i][j].ObjectID);
				Sexy::OutputDebugStrF("data[%d].[%d].Quantity : %d", i, j, _data._dayDataList[i][j].Quantity);
				Sexy::OutputDebugStrF("data[%d].[%d].BtnStatus : %d", i, j, _data._dayDataList[i][j].BtnStatus);
			}
		}
	}
}

RechargeDailySignBonusBtnStatus RechargeDailySignActivityManager::GetBtnStatus(int day, RechargeDailySignBonusType bonusType)
{
	int normalDays = _data._normalDaySignNum;
	int advanceDays = _data._advanceSignDayNum;
	std::vector<RechargeDailySignDayReward> dayData = _data._dayDataList[day];
	int status = dayData[bonusType].BtnStatus;
	int normalStatus = dayData[DailySignBonusNormal].BtnStatus;
	int dayNum = day + 1;
	if (bonusType == DailySignBonusNormal)
	{
		if (normalDays < dayNum)
			return BtnStatus_Disable;
		if (status == 0)
			return BtnStatus_ShowBtn;
		if (status == 1)
			return BtnStatus_HideBtn;
		return BtnStatus_Invalid;
	}
	if (bonusType == DailySignBonusAdvance)
	{
		if (advanceDays < dayNum)
		{
			if (normalStatus == 0)
				return BtnStatus_HideBtn;
			if (normalStatus == 1)
				return BtnStatus_Disable;
			return BtnStatus_Invalid;
		}
		if (normalStatus == 0)
			return BtnStatus_HideBtn;
		if (normalStatus == 1)
		{
			if (status == 0)
				return BtnStatus_ShowBtn;
			if (status == 1)
				return BtnStatus_HideBtn;
		}
	}
	return BtnStatus_Invalid;
}

int RechargeDailySignActivityManager::CurrentCanGotItemIndex()
{
	for (int i = 0; i < _data._dayDataList.size(); i++)
	{
		RechargeDailySignBonusBtnStatus normalStatus = GetBtnStatus(i, DailySignBonusNormal);
		RechargeDailySignBonusBtnStatus advanceStatus = GetBtnStatus(i, DailySignBonusAdvance);
		if (normalStatus != BtnStatus_HideBtn || advanceStatus != BtnStatus_HideBtn)
			return i;
	}
	return 0;
}

/////////////// Network ///////////////

void RechargeDailySignActivityManager::RequestNetwork()
{
	std::vector<std::pair<int, int>> idList;
	idList.push_back(std::pair<int, int>(Activity_RechargeDailySignActivity, 1));
	NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestActivityList(idList, 0, true);
}
