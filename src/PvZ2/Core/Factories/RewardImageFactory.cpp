// Reconstructed by EvilHack28 on 2026-09-05
#include "RewardImageFactory.h"

namespace
{
	class AwardEntry
	{
	public:
		AwardEntry(AwardType i_awardType, const std::string& i_awardParam, int i_quantity, int i_id);

	private:
		std::string m_key;
	};

	class AwardStackImageResolver
	{
	public:
		static ImagePtr GetCurrencyImageFor(const AwardEntry& i_entry);
		static ImagePtr GetPinataGemsImageForTier(int i_tier);
	};

	ImagePtr GetRewardImage(AwardType i_awardType, const std::string& i_awardParam, int i_quantity, int i_id)
	{
		if (i_awardType == AWARD_Gems)
		{
			int tier;
			if (i_quantity <= RewardImageFactory::k_GemsSmall)
				tier = 1;
			else if (i_quantity < RewardImageFactory::k_GemsMedium + 1)
				tier = 2;
			else
				tier = 3;
			return AwardStackImageResolver::GetPinataGemsImageForTier(tier);
		}

		AwardEntry entry(i_awardType, i_awardParam, i_quantity, i_id);
		return AwardStackImageResolver::GetCurrencyImageFor(entry);
	}
}

ImagePtr RewardImageFactory::GetImageForReward(const LevelOfTheDay_RewardItemType& i_reward)
{
	return GetImageForReward(i_reward.Award, i_reward.AwardParam, i_reward.AwardQuantity, i_reward.AwardId);
}

ImagePtr RewardImageFactory::GetImageForReward(AwardType i_awardType, const std::string& i_awardParam, int i_quantity, int i_id)
{
	return GetRewardImage(i_awardType, i_awardParam, i_quantity, i_id);
}

ImagePtr RewardImageFactory::GetImageForReward(AwardType i_awardType, int i_id)
{
	return GetRewardImage(i_awardType, "", 0, i_id);
}
