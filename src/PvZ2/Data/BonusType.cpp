//
//  BonusType.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "GameFeatureType.h"
#include "ReflectionBuilder.h"
#include "PVZDB.h"
#include "MD5.h"
#include "LawnApp.h"

/////////////// Logic ///////////////

std::string BonusType::AllBonusNumSign;

std::string BonusType::CalBonusNumSign()
{
	std::stringstream stream(std::ios_base::out | std::ios_base::in);
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_BONUSTYPES); it; ++it)
	{
		Sexy::RtWeakPtr<BonusType> bonus(*it);
		stream << bonus->BonusNum;
	}

	Sexy::OutputDebugStrF("*sign = %s", stream.str().c_str());
	return MD5(stream.str()).toString();
}

void BonusType::ResetBonusNumSign()
{
	AllBonusNumSign = CalBonusNumSign();
}

bool BonusType::CheckBonusNumSign()
{
	return CalBonusNumSign() == AllBonusNumSign;
}

BonusTypePtr BonusType::GetBonusTypeFromUnlockString(const std::string i_unlockString, bool i_doCheckSign)
{
	if (i_doCheckSign)
	{
		if (!CheckBonusNumSign())
		{
			gLawnApp->ShowDataErrorDialog();
			return NULL;
		}
	}

	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_BONUSTYPES); it; ++it)
	{
		BonusTypePtr bonus(*it);
		if (bonus->ToString() == i_unlockString)
			return bonus;
	}

	return NULL;
}

const char* BonusType::ToString() const
{
	switch (Bonus)
	{
	case BONUS_GOLD_1:
		return "bonus_gold_1";
	case BONUS_GOLD_2:
		return "bonus_gold_2";
	case BONUS_GOLD_3:
		return "bonus_gold_3";
	case BONUS_DIAMOND_1:
		return "bonus_diamond_1";
	case BONUS_DIAMOND_2:
		return "bonus_diamond_2";
	case BONUS_DIAMOND_3:
		return "bonus_diamond_3";
	case BONUS_GOLD_4:
		return "bonus_gold_4";
	case BONUS_CARD_GOLD_250:
		return "bonus_card_gold_250";
	case BONUS_CARD_GOLD_500:
		return "bonus_card_gold_500";
	case BONUS_CARD_GOLD_1000:
		return "bonus_card_gold_1000";
	case BONUS_CARD_GOLD_5000:
		return "bonus_card_gold_5000";
	case BONUS_CARD_KEY_EGYPT:
		return "bonus_card_key_egypt";
	case BONUS_CARD_DIAMOND_5:
		return "bonus_card_diamond_5";
	case BONUS_CARD_DIAMOND_10:
		return "bonus_card_diamond_10";
	case BONUS_CARD_DIAMOND_50:
		return "bonus_card_diamond_50";
	case BONUS_CARD_PIECE_SNOWPEA:
		return "bonus_card_piece_snowpea";
	case BONUS_CARD_PIECE_TORCHWOOD:
		return "bonus_card_piece_torchwood";
	case BONUS_CARD_PIECE_PEAPOD:
		return "bonus_card_piece_peapod";
	case BONUS_CARD_PIECE_KERNELPULT:
		return "bonus_card_piece_kernelpult";
	case BONUS_CARD_PIECE_LIGHTNINGREED:
		return "bonus_card_piece_lightningreed";
	case BONUS_CARD_PIECE_COCONUTCANNON:
		return "bonus_card_piece_coconutcannon";
	case BONUS_CARD_KEY_PIRATE:
		return "bonus_card_key_pirate";
	case BONUS_CARD_PIECE_MELONPULT:
		return "bonus_card_piece_melonpult";
	case BONUS_CARD_PIECE_IMITATER:
		return "bonus_card_piece_imitater";
	case BONUS_CARD_KEY_COWBOY:
		return "bonus_card_key_cowboy";
	case BONUS_CARD_PIECE_FIREGOURD:
		return "bonus_card_piece_firegourd";
	case BONUS_CARD_PIECE_PEACH:
		return "bonus_card_piece_peach";
	case BONUS_CARD_KEY_KONGFU:
		return "bonus_card_key_kongfu";
	case BONUS_CARD_PIECE_MAGNIFYINGGRASS:
		return "bonus_card_piece_magnifyinggrass";
	case BONUS_CARD_PIECE_STARFRUIT:
		return "bonus_card_piece_starfruit";
	case BONUS_CARD_KEY_FUTURE:
		return "bonus_card_key_future";
	case BONUS_GOLD_5:
		return "bonus_gold_5";
	case BONUS_DIAMOND_4:
		return "bonus_diamond_4";
	case BONUS_GOLD_6:
		return "bonus_gold_6";
	case BONUS_GOLD_7:
		return "bonus_gold_7";
	case BONUS_GOLD_8:
		return "bonus_gold_8";
	case BONUS_GOLD_9:
		return "bonus_gold_9";
	case BONUS_GOLD_10:
		return "bonus_gold_10";
	case BONUS_GOLD_11:
		return "bonus_gold_11";
	case BONUS_GOLD_12:
		return "bonus_gold_12";
	case BONUS_GOLD_13:
		return "bonus_gold_13";
	case BONUS_GOLD_14:
		return "bonus_gold_14";
	case BONUS_GOLD_15:
		return "bonus_gold_15";
	case BONUS_GOLD_16:
		return "bonus_gold_16";
	case BONUS_GOLD_17:
		return "bonus_gold_17";
	case BONUS_GOLD_18:
		return "bonus_gold_18";
	case BONUS_CARD_KEY_DARK:
		return "bonus_card_key_dark";
	case BONUS_CARD_KEY_BEACH:
		return "bonus_card_key_beach";
	case BONUS_CARD_KEY_ICEAGE:
		return "bonus_card_key_iceage";
	case BONUS_MAGIC_FERTILIZER:
		return "bonus_magic_fertilizer";
	case BONUS_MAGIC_DRUM:
		return "bonus_magic_drum";
	case BONUS_MAGIC_SNOWFLAKE:
		return "bonus_magic_snowflake";
	case BONUS_MAGIC_TORCH:
		return "bonus_magic_torch";
	case BONUS_MAGIC_REGENERATION:
		return "bonus_magic_regeneration";
	case BONUS_MAGIC_POLE:
		return "bonus_magic_pole";
	case BONUS_CARD_KEY_SKYCITY:
		return "bonus_card_key_skycity";
	case BONUS_MAGIC_FERTILIZER_2:
		return "bonus_magic_fertilizer_2";
	case BONUS_MAGIC_POLE_2:
		return "bonus_magic_pole_2";
	case BONUS_CARD_KEY_LOSTCITY:
		return "bonus_card_key_lostcity";
	}

	return NULL;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(BonusType);
