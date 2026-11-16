//
//  LostNetActivityConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LostNetActivityConfig.h"
#include "PVZDB.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include <time.h>

time_t CalcTimeStamp(const std::string& date, const std::string& format);

LostNetActivityConfig::LostNetActivityConfig()
{
}

LostNetActivityConfig::~LostNetActivityConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LostNetActivityConfig);

void LostNetActivityConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LostNetActivityConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_inited);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, RewardPool);

	REFLECTION_CLASSBUILDER_END(LostNetActivityConfig);
}

/////////////// Activity ///////////////

void LostNetActivityConfig::Refresh()
{
	Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_LOSTNET_ACTIVITY_CONFIG);
	for (; it; it++)
	{
		Sexy::RtWeakPtr<Sexy::RtObject> config = *it;
		LostNetActivityConfig* other = NULL;
		if (config)
			other = config->Cast<LostNetActivityConfig>();
		if (other)
		{
			OrgPrice = other->OrgPrice;
			Price = other->Price;
			Coins = other->Coins;
			Gems = other->Gems;
			TargetLevel = other->TargetLevel;
			LimitLevel = other->LimitLevel;
			StartDate = other->StartDate;
			EndDate = other->EndDate;
			RewardPool = other->RewardPool;
			m_inited = true;
			break;
		}
	}
}

bool LostNetActivityConfig::IsActivity()
{
	if (!m_inited)
		Refresh();
	time_t start = CalcTimeStamp(Sexy::StrFormat("%d", StartDate), std::string("%Y%m%d"));
	time_t end = CalcTimeStamp(Sexy::StrFormat("%d", EndDate), std::string("%Y%m%d"));
	time_t now = time(NULL);
	localtime(&now);
	return end >= now && start <= now;
}

int LostNetActivityConfig::GetCurrentBonus()
{
	if (!m_inited)
		Refresh();
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	if (profile)
		return profile->GetTodayLostNetActivityBonus();
	return 0;
}

time_t LostNetActivityConfig::GetTodaySec()
{
	if (!m_inited)
		Refresh();
	time_t now = time(NULL);
	localtime(&now);
	return 86400 - (now + 115200) % 86400;
}
