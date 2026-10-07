//
//  GemOfferMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GemOfferMgr.h"
#include "GameStateMgr.h"
#include "LawnApp.h"
#include "NetworkMgr.h"
#include "WorldMap.h"
#include "UniverseMap.h"
#include "WorldMapDefine.h"
#include "ActivityManager.h"
#include "NetworkMsgProcess.h"

GemOfferMgr::GemOfferMgr()
{
	m_hintRange = 0;
	m_activatedTips = 0;
}

GemOfferMgr::~GemOfferMgr()
{
}

void GemOfferMgr::ClearDatas()
{
	m_hintRange = 0;
	m_activatedTips = false;
	m_hintTimes.clear();
}

bool GemOfferMgr::CanShowHint()
{
	return gGameStateMgr->GetState() == GAME_WorldMap;
}

void GemOfferMgr::ShowHint()
{
	gLawnApp->ShowGemOfferHintUI();
}

void GemOfferMgr::RequestNetwork()
{
	INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
	std::vector<std::pair<int, int>> idList = { { Activity_Special_Gem_Offer, 1 } };
	process->RequestActivityList(idList, 0, true);
}

bool GemOfferMgr::NeedShowHint()
{
	time_t realTime = gLawnApp->GetRealBeijingTime();
	struct tm* now = gLawnApp->BeijingTime(&realTime);
	bool result;
	if (now->tm_min <= m_hintRange)
	{
		int hour = now->tm_hour;
		std::map<int, bool>::iterator it = m_hintTimes.find(hour);
		std::map<int, bool>::iterator last = m_hintTimes.end();
		result = it != last;
		if (__builtin_expect(result, 1))
		{
			if (__builtin_expect(!(*it).second, 0))
			{
				(*it).second = true;
				SetActivatedTips(true);
			}
			else
			{
				result = false;
			}
			return result;
		}
	}
	result = false;
	SetActivatedTips(false);
	return result;
}

void GemOfferMgr::ResetHintTimes()
{
	std::map<int, bool>::iterator it = m_hintTimes.begin();
	std::map<int, bool>::iterator last = m_hintTimes.end();
	while (it != last)
	{
		(*it).second = false;
		++it;
	}
}

void GemOfferMgr::RefreshActivity()
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_Special_Gem_Offer);
	if (item.m_bOpen)
	{
		GemOfferInfo info;
		if (item.GetDataSerialized(info) && info.hintTimes.size() != 0)
		{
			SyncActivityData(info);
		}
	}
}

void GemOfferMgr::SyncActivityData(const GemOfferInfo& i_data)
{
	for (size_t i = 0; i < i_data.hintTimes.size(); i++)
	{
		int hintTime = i_data.hintTimes[i];
		m_hintTimes.insert(std::make_pair(hintTime, false));
	}
	m_hintRange = i_data.timeRange;
}

void GemOfferMgr::InitTestData()
{
	gLawnApp->SetSpecialGemOffer(true);
	m_hintRange = 60;
	m_hintTimes.insert(std::make_pair(9, false));
	m_hintTimes.insert(std::make_pair(12, false));
	m_hintTimes.insert(std::make_pair(14, false));
	m_hintTimes.insert(std::make_pair(17, false));
	m_hintTimes.insert(std::make_pair(18, false));
	m_hintTimes.insert(std::make_pair(20, false));
}

void GemOfferMgr::Update()
{
	if (gLawnApp->HasSpecialGemOffer() && CanShowHint())
	{
		WorldMap* worldMap = gLawnApp->GetWorldMap();
		if (worldMap && !worldMap->IsActionQueued())
		{
			UniverseMap* universeMap = gLawnApp->GetWorldMap()->GetUniverseMap();
			if (universeMap && !universeMap->IsActived() && NeedShowHint())
			{
				ShowHint();
			}
		}
	}
}
