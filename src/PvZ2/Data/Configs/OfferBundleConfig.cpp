//
//  OfferBundleConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "OfferBundleConfig.h"
#include "LawnApp.h"
#include "PVZDB.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(OfferBundleConfig);


/////////////// Reflection ///////////////

void OfferBundleConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BundleInfo);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::string, sku_id, Sku);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, gem_amount, Gems);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::string, display_img, DisplayImage);
	REFLECTION_CLASSBUILDER_END(BundleInfo);

	REFLECTION_CLASSBUILDER_BEGIN(rewardItem);
		REFLECTION_CLASSBUILDER_FIELD(int, id);
		REFLECTION_CLASSBUILDER_FIELD(int, count);
	REFLECTION_CLASSBUILDER_END(rewardItem);

	REFLECTION_CLASSBUILDER_BEGIN(OppoNewerDailyReward);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<rewardItem>, items);
	REFLECTION_CLASSBUILDER_END(OppoNewerDailyReward);

	REFLECTION_CLASSBUILDER_BEGIN(OfferBundleConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<BundleInfo>, m_bundleInfoList, BundleInfoList);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<OppoNewerDailyReward>, m_loginReward, loginReward);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<int>, m_rechargeReward, rechargeReward);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<int>, m_rechargeLevel, rechargeLevel);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<int>, m_rechargeRewardPlantPiecesBlue, rechargeRewardPlantPiecesBlue);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<int>, m_rechargeRewardPlantPiecesGreen, rechargeRewardPlantPiecesGreen);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, m_rechargeRewardAvatarPieces, rechargeRewardAvatarPicecs);
	REFLECTION_CLASSBUILDER_END(OfferBundleConfig);

}


/////////////// Accessors ///////////////

const std::vector<OppoNewerDailyReward>& OfferBundleConfig::GetDailyReward() const
{
	return m_loginReward;
}

int OfferBundleConfig::GetAvatarPiecesRewardCount()
{
	return m_rechargeRewardAvatarPieces;
}

int OfferBundleConfig::GetBundleOfferGemAmount(const std::string& i_sku)
{
	for (std::vector<BundleInfo>::iterator it = m_bundleInfoList.begin(), end = m_bundleInfoList.end(); it != end; ++it)
	{
		if ((*it).sku_id == i_sku)
			return (*it).gem_amount;
	}
	return 0;
}

const std::string& OfferBundleConfig::GetBundleDisplayImageName(const std::string& i_sku)
{
	for (std::vector<BundleInfo>::iterator it = m_bundleInfoList.begin(), end = m_bundleInfoList.end(); it != end; ++it)
	{
		if ((*it).sku_id == i_sku)
			return (*it).display_img;
	}
	return m_invalidDisplayImageName;
}


/////////////// Recharge ///////////////

int OfferBundleConfig::GetRechargeLevel(int recharge)
{
	size_t n = m_rechargeLevel.size();
	size_t i = 0;
	int j = 0;
	while (j = i, i != n)
	{
		if (m_rechargeLevel[i++] > recharge)
			return j;
	}
	return i;
}

int OfferBundleConfig::GetRechargeValue(int levelIndex)
{
	if (levelIndex < 0 || (size_t)levelIndex >= m_rechargeLevel.size())
		return 0;
	return m_rechargeLevel[levelIndex];
}

int OfferBundleConfig::GetPlantPiecesRewardCount(int plantRare, int rechargeLevelIndex)
{
	if (plantRare == 2)
	{
		if (rechargeLevelIndex >= 0 && (size_t)rechargeLevelIndex < m_rechargeRewardPlantPiecesBlue.size())
			return m_rechargeRewardPlantPiecesBlue[rechargeLevelIndex];
	}
	else if (plantRare == 1)
	{
		if (rechargeLevelIndex >= 0 && (size_t)rechargeLevelIndex < m_rechargeRewardPlantPiecesGreen.size())
			return m_rechargeRewardPlantPiecesGreen[rechargeLevelIndex];
	}
	return 0;
}

bool OfferBundleConfig::ShouldGetAvatarPieces(int rechargeLevel)
{
	return m_rechargeLevel.size() - 1 == (size_t)rechargeLevel;
}

int OfferBundleConfig::GetPlantIDByCreatedTime(time_t createdTime)
{
	time_t now = gLawnApp->GetRealBeijingTime();
	if (now == 0)
		return m_rechargeReward[now];
	int days = (int)(difftime(now, createdTime) * (1.0 / 86400));
	if (__builtin_expect(!!(days > 0), 1))
	{
		if ((size_t)days < m_rechargeReward.size())
			return m_rechargeReward[days];
		return m_rechargeReward[m_rechargeReward.size() - 1];
	}
	return m_rechargeReward[0];
}


/////////////// Refresh ///////////////

void OfferBundleConfig::Refresh()
{
	Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_OFFER_BUNDLE_CONFIG);
	for (; it; it++)
	{
		Sexy::RtWeakPtr<Sexy::RtObject> config = *it;
		OfferBundleConfig* other = NULL;
		if (config)
			other = config->Cast<OfferBundleConfig>();
		if (other)
		{
			m_bundleInfoList = other->m_bundleInfoList;
			m_loginReward = other->m_loginReward;
			m_rechargeReward = other->m_rechargeReward;
			m_rechargeLevel = other->m_rechargeLevel;
			m_rechargeRewardPlantPiecesBlue = other->m_rechargeRewardPlantPiecesBlue;
			m_rechargeRewardPlantPiecesGreen = other->m_rechargeRewardPlantPiecesGreen;
			m_rechargeRewardAvatarPieces = other->m_rechargeRewardAvatarPieces;
		}
	}
}
