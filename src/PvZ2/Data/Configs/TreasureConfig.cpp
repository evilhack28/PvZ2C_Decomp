//
//  TreasureConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "TreasureConfig.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

TreasureConfig::TreasureConfig()
{
}

TreasureConfig::~TreasureConfig()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(TreasureConfig);

void TreasureConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TreasureReward);
	REFLECTION_CLASSBUILDER_END(TreasureReward);

	REFLECTION_CLASSBUILDER_BEGIN(TreasurePool);
	REFLECTION_CLASSBUILDER_END(TreasurePool);

	REFLECTION_CLASSBUILDER_BEGIN(TreasureConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<TreasureReward>, TreasureRewardList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TreasurePool>, TreasurePools);
	REFLECTION_CLASSBUILDER_END(TreasureConfig);
}

/////////////// Accessors ///////////////

TreasureReward* TreasureConfig::GetTreasureRewardBySku(std::string strSku)
{
	std::vector<TreasureReward>::iterator it = std::find(TreasureRewardList.begin(), TreasureRewardList.end(), strSku);
	if (it != TreasureRewardList.end())
		return &*it;
	return NULL;
}

/////////////// Logic ///////////////

TreasurePool* TreasureConfig::GetTreasurePool(std::string& strMapname)
{
	for (int i = 0; i < TreasurePools.size();)
	{
		const size_t index = i;
		std::string upperName = Sexy::StringToUpper(strMapname);
		std::string upperPool = Sexy::StringToUpper(TreasurePools[i++].mapName);
		if (upperName == upperPool)
			return &TreasurePools[index];
	}
	return NULL;
}

static bool operator==(const TreasureReward& reward, const std::string& sku)
{
	return reward.strSku == sku;
}

TreasureConfig::VECTREASURES* TreasureConfig::GetTreasureRewardsByWorld(const std::string& strWorld)
{
	if (m_mapTreasureReward.empty())
	{
		for (int i = 0; i < TreasureRewardList.size();)
		{
			const size_t index = i;
			i++;
			m_mapTreasureReward[Sexy::StringToUpper(TreasureRewardList[index].mapName)].push_back(TreasureRewardList[index]);
		}
	}
	std::map<std::string, VECTREASURES>::iterator it = m_mapTreasureReward.find(strWorld);
	if (it == m_mapTreasureReward.end())
		return NULL;
	return &it->second;
}
