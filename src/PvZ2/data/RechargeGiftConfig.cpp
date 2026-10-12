//
//  RechargeGiftConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RechargeGiftConfig.h"
#include "LawnApp.h"
#include "PVZDB.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RechargeGiftConfig::RechargeGiftConfig()
{
}

RechargeGiftConfig::~RechargeGiftConfig()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(RechargeGiftConfig);

void RechargeGiftConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RechargeGiftConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_END(RechargeGiftConfig);
}

/////////////// Accessors ///////////////

const std::string& RechargeGiftConfig::GetSku() const
{
	return m_strPaySku;
}

const std::string& RechargeGiftConfig::GetTitle() const
{
	return m_strTitle;
}

const std::vector<std::string>& RechargeGiftConfig::GetPlants() const
{
	return m_vecPlants;
}

/////////////// Logic ///////////////

RechargeGiftConfig* RechargeGiftConfig::GetConfig(const std::string& packageName)
{
	int today = 0;
	if (packageName.empty())
	{
		time_t realTime = gLawnApp->GetRealBeijingTime();
		if (realTime <= 0)
			return nullptr;
		struct tm* now = gLawnApp->BeijingTime(&realTime);
		today = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_RECHARGE_GIFT_CONFIG); it; ++it)
	{
		RechargeGiftConfig* config = Sexy::RtWeakPtr<Sexy::RtObject>(*it)->Cast<RechargeGiftConfig>();
		if (config != nullptr)
		{
			if (packageName.empty())
			{
				if (today >= config->GetStartDate() && today <= config->GetEndDate())
					return config;
			}
			else if (config->m_strPackageName == packageName)
				return config;
		}
	}
	return nullptr;
}
