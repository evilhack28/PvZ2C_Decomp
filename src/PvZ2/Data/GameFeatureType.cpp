//
//  GameFeatureType.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GameFeatureType.h"

#include "ReflectionBuilder.h"
#include "PVZDB.h"
#include "Toggles.h"
#include "WorldMapUtils.h"
#include "WorldData.h"
#include "ResourceHelpers.h"

RT_CLASS_IMPLEMENT(GameFeatureType);

/////////////// Reflection ///////////////

void GameFeatureType::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(GameFeature);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_shovel, FEATURE_SHOVEL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_almanac, FEATURE_ALMANAC);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_coins, FEATURE_COINS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_gems, FEATURE_GEMS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_buy_sun, FEATURE_BUY_SUN);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_keys, FEATURE_KEYS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_worldmap, FEATURE_WORLDMAP);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_plantfood, FEATURE_PLANTFOOD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_plantfood_purchase, FEATURE_PLANTFOOD_PURCHASE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_has_played_dangerroom, FEATURE_HAS_PLAYED_DANGERROOM);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_has_failed_dangerroom, FEATURE_HAS_FAILED_DANGERROOM);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_has_won_dangerroom, FEATURE_HAS_WON_DANGERROOM);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_treasure_yeti, FEATURE_TREASURE_YETI);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_powerup_wizardfinger, FEATURE_POWERUP_WIZARDFINGER);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_powerup_flick_zombie, FEATURE_POWERUP_FLICKZOMBIE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_powerup_pinch, FEATURE_POWERUP_PINCH);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_powerup_tacticalcuke, FEATURE_POWERUP_TACTICALCUKE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_cannon_1, FEATURE_CANNON_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_shield_1, FEATURE_SHIELD_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_cannon_intro, FEATURE_CANNON_INTRO);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_shield_intro, FEATURE_SHIELD_INTRO);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_christmas_protect_intro, FEATURE_CHRISTMAS_PROTECT_INTRO);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_1, FEATURE_UPGRADE_LAWNMOWER_TYPE_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_2, FEATURE_UPGRADE_LAWNMOWER_TYPE_2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_3, FEATURE_UPGRADE_LAWNMOWER_TYPE_3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_4, FEATURE_UPGRADE_LAWNMOWER_TYPE_4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_5, FEATURE_UPGRADE_LAWNMOWER_TYPE_5);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_6, FEATURE_UPGRADE_LAWNMOWER_TYPE_6);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_7, FEATURE_UPGRADE_LAWNMOWER_TYPE_7);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_8, FEATURE_UPGRADE_LAWNMOWER_TYPE_8);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_9, FEATURE_UPGRADE_LAWNMOWER_TYPE_9);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_10, FEATURE_UPGRADE_LAWNMOWER_TYPE_10);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_11, FEATURE_UPGRADE_LAWNMOWER_TYPE_11);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_12, FEATURE_UPGRADE_LAWNMOWER_TYPE_12);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_13, FEATURE_UPGRADE_LAWNMOWER_TYPE_13);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_14, FEATURE_UPGRADE_LAWNMOWER_TYPE_14);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_15, FEATURE_UPGRADE_LAWNMOWER_TYPE_15);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_mower_type_16, FEATURE_UPGRADE_LAWNMOWER_TYPE_16);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(6_slots, FEATURE_UPGRADE_6_SLOTS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(7_slots, FEATURE_UPGRADE_7_SLOTS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(sunshovel_lvl1, FEATURE_UPGRADE_SHOVEL_LVL1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(kongfu_coming_soon, FEATURE_CARD_KONGFU_COMING_SOON);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_festival_entrance, FEATURE_FESTIVAL_ENTRANCE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_festivalgame_crazyyeti_legend, FEATURE_FESTIVALGAME_CRAZYYETI_LEGEND);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_festivalgame_gargantuarcrisis_legend, FEATURE_FESTIVALGAME_GARGANTUARCRISIS_LEGEND);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_festivalgame_devilinvade_legend, FEATURE_FESTIVALGAME_DEVILINVADE_LEGEND);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_festivalgame_wealthgod_legend, FEATURE_FESTIVALGAME_DEVILINVADE_LEGEND);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_tip_freezingwind, FEATURE_TIP_FREEZINGWIND);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_tip_shield, FEATURE_TIP_SHIELD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_air_missile_guide, FEATURE_AIR_MISSILE_GUIDE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(sunshovel_lvl2, FEATURE_UPGRADE_SHOVEL_LVL2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pf_refresh, FEATURE_UPGRADE_PF_REFRESH);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(wallnut_firstaid, FEATURE_UPGRADE_WALLNUT_FIRSTAID);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pf_slots_lvl1, FEATURE_UPGRADE_PF_SLOTS_LVL1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(starting_sun_lvl1, FEATURE_UPGRADE_STARTING_SUN_LVL1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(sunshovel3, FEATURE_UPGRADE_SHOVEL_LVL3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(sunshovel_lvl4, FEATURE_UPGRADE_SHOVEL_LVL4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pf_slots_lvl2, FEATURE_UPGRADE_PF_SLOTS_LVL2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(startingsun2, FEATURE_UPGRADE_STARTING_SUN_LVL2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(startingsun3, FEATURE_UPGRADE_STARTING_SUN_LVL3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(startingsun4, FEATURE_UPGRADE_STARTING_SUN_LVL4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(seedslot2, FEATURE_UPGRADE_8_SLOTS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pf_slots_lvl3, FEATURE_UPGRADE_PF_SLOTS_LVL3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(manual_mowers_1, FEATURE_UPGRADE_MANUAL_MOWERS_1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(manual_mowers_2, FEATURE_UPGRADE_MANUAL_MOWERS_2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(manual_mowers_3, FEATURE_UPGRADE_MANUAL_MOWERS_3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(manual_mowers_4, FEATURE_UPGRADE_MANUAL_MOWERS_4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(manual_mowers_5, FEATURE_UPGRADE_MANUAL_MOWERS_5);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_battle_array, FEATURE_BATTLE_ARRAY);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_unlock_hardlevel, FEATURE_UNLOCK_HARDLEVEL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_get_easylevel_star, FEATURE_GET_EASYLEVEL_STAR);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_powerup_vasebreaker_move, FEATURE_POWERUP_VASEBREAKER_MOVE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_powerup_vasebreaker_reveal, FEATURE_POWERUP_VASEBREAKER_REVEAL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_powerup_vasebreaker_butter, FEATURE_POWERUP_VASEBREAKER_BUTTER);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_powerup_vasebreaker_color, FEATURE_POWERUP_VASEBREAKER_COLOR);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(feature_has_seen_rift_how_to_play, FEATURE_HAS_SEEN_RIFT_HOW_TO_PLAY);
	REFLECTION_ENUMBUILDER_END(GameFeature);

	REFLECTION_CLASSBUILDER_BEGIN(GameFeatureType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

		REFLECTION_CLASSBUILDER_FIELD(std::string, LocalizedName);
		REFLECTION_CLASSBUILDER_FIELD(std::string, LocalizedInfo);
		REFLECTION_CLASSBUILDER_FIELD(std::string, UpgradeImage);
		REFLECTION_CLASSBUILDER_FIELD(std::string, HomeWorld);
		REFLECTION_CLASSBUILDER_FIELD(GameFeature, Feature);
		REFLECTION_CLASSBUILDER_FIELD(bool, IsAPowerup);
	REFLECTION_CLASSBUILDER_END(GameFeatureType);

}

/////////////// Lookup ///////////////

GameFeatureTypePtr GameFeatureType::GetGameFeatureTypeFromEnum(const GameFeature i_feature)
{
	return GetGameFeatureTypeFromUnlockString(GetGameFeatureInternalStringFromEnum(i_feature));
}

GameFeatureTypePtr GameFeatureType::GetGameFeatureTypeFromUnlockString(const std::string i_unlockString)
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_GAMEFEATURES); it; ++it)
	{
		GameFeatureTypePtr type = *it;
		if (type->ToString() == i_unlockString)
			return type;
	}
	return GameFeatureTypePtr();
}

/////////////// Queries ///////////////

Sexy::ImagePtr GameFeatureType::GetUpgradeImage() const
{
	Sexy::ImagePtr image;
	if (IsAPowerup)
		image = GetUIResource<Sexy::Image>(UpgradeImage);
	else
		image = GetImageByName(UpgradeImage);
	return image;
}

bool GameFeatureType::IsFeatureEnabled() const
{
	switch (Feature)
	{
	case FEATURE_CARD_KONGFU_COMING_SOON:
		return false;
	case FEATURE_POWERUP_PINCH:
		if (Toggles::GetInstance().IsEnabled("PowerupSnowball"))
			return false;
	}
	if (__builtin_expect(!!(HomeWorld.size() == 0), 1))
		return true;
	return WorldMapUtils::GetWorldMapList()->IsWorldEnabled(HomeWorld);
}

/////////////// Names ///////////////

const char* GameFeatureType::GetGameFeatureInternalStringFromEnum(const GameFeature i_feature)
{
	switch (i_feature)
	{
	case FEATURE_SHOVEL:
		return "feature_shovel";
	case FEATURE_ALMANAC:
		return "feature_almanac";
	case FEATURE_COINS:
		return "feature_coins";
	case FEATURE_GEMS:
		return "feature_gems";
	case FEATURE_BUY_SUN:
		return "feature_buy_sun";
	case FEATURE_KEYS:
		return "feature_keys";
	case FEATURE_WORLDMAP:
		return "feature_worldmap";
	case FEATURE_PLANTFOOD:
		return "feature_plantfood";
	case FEATURE_PLANTFOOD_PURCHASE:
		return "feature_plantfood_purchase";
	case FEATURE_HAS_PLAYED_DANGERROOM:
		return "feature_has_played_dangerroom";
	case FEATURE_HAS_FAILED_DANGERROOM:
		return "feature_has_failed_dangerroom";
	case FEATURE_HAS_WON_DANGERROOM:
		return "feature_has_won_dangerroom";
	case FEATURE_TREASURE_YETI:
		return "feature_treasure_yeti";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_1:
		return "feature_mower_type_1";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_2:
		return "feature_mower_type_2";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_3:
		return "feature_mower_type_3";
	case FEATURE_UPGRADE_6_SLOTS:
		return "6_slots";
	case FEATURE_UPGRADE_7_SLOTS:
		return "7_slots";
	case FEATURE_UPGRADE_8_SLOTS:
		return "seedslot2";
	case FEATURE_UPGRADE_SHOVEL_LVL1:
		return "sunshovel_lvl1";
	case FEATURE_UPGRADE_SHOVEL_LVL2:
		return "sunshovel_lvl2";
	case FEATURE_UPGRADE_SHOVEL_LVL3:
		return "sunshovel3";
	case FEATURE_UPGRADE_PF_REFRESH:
		return "pf_refresh";
	case FEATURE_UPGRADE_WALLNUT_FIRSTAID:
		return "wallnut_firstaid";
	case FEATURE_UPGRADE_PF_SLOTS_LVL1:
		return "pf_slots_lvl1";
	case FEATURE_UPGRADE_PF_SLOTS_LVL2:
		return "pf_slots_lvl2";
	case FEATURE_UPGRADE_PF_SLOTS_LVL3:
		return "pf_slots_lvl3";
	case FEATURE_UPGRADE_STARTING_SUN_LVL1:
		return "starting_sun_lvl1";
	case FEATURE_UPGRADE_STARTING_SUN_LVL2:
		return "startingsun2";
	case FEATURE_UPGRADE_STARTING_SUN_LVL3:
		return "startingsun3";
	case FEATURE_POWERUP_WIZARDFINGER:
		return "feature_powerup_wizardfinger";
	case FEATURE_POWERUP_FLICKZOMBIE:
		return "feature_powerup_flick_zombie";
	case FEATURE_POWERUP_PINCH:
		return "feature_powerup_pinch";
	case FEATURE_POWERUP_TACTICALCUKE:
		return "feature_powerup_tacticalcuke";
	case FEATURE_CARD_KONGFU_COMING_SOON:
		return "kongfu_coming_soon";
	case FEATURE_UPGRADE_SHOVEL_LVL4:
		return "sunshovel_lvl4";
	case FEATURE_UPGRADE_STARTING_SUN_LVL4:
		return "startingsun4";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_4:
		return "feature_mower_type_4";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_5:
		return "feature_mower_type_5";
	case FEATURE_FESTIVAL_ENTRANCE:
		return "feature_festival_entrance";
	case FEATURE_FESTIVALGAME_CRAZYYETI_LEGEND:
		return "feature_festivalgame_crazyyeti_legend";
	case FEATURE_FESTIVALGAME_GARGANTUARCRISIS_LEGEND:
		return "feature_festivalgame_gargantuarcrisis_legend";
	case FEATURE_FESTIVALGAME_DEVILINVADE_LEGEND:
		return "feature_festivalgame_devilinvade_legend";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_6:
		return "feature_mower_type_6";
	case FEATURE_UPGRADE_MANUAL_MOWERS_1:
		return "manual_mowers_1";
	case FEATURE_UPGRADE_MANUAL_MOWERS_2:
		return "manual_mowers_2";
	case FEATURE_UPGRADE_MANUAL_MOWERS_3:
		return "manual_mowers_3";
	case FEATURE_UPGRADE_MANUAL_MOWERS_4:
		return "manual_mowers_4";
	case FEATURE_UPGRADE_MANUAL_MOWERS_5:
		return "manual_mowers_5";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_7:
		return "feature_mower_type_7";
	case FEATURE_FESTIVALGAME_WEALTHGOD_LEGEND:
		return "feature_festivalgame_wealthgod_legend";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_8:
		return "feature_mower_type_8";
	case FEATURE_TIP_FREEZINGWIND:
		return "feature_tip_freezingwind";
	case FEATURE_TIP_SHIELD:
		return "feature_tip_shield";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_9:
		return "feature_mower_type_9";
	case FEATURE_AIR_MISSILE_GUIDE:
		return "feature_air_missile_guide";
	case FEATURE_CANNON_1:
		return "feature_cannon_1";
	case FEATURE_SHIELD_1:
		return "feature_shield_1";
	case FEATURE_CANNON_INTRO:
		return "feature_cannon_intro";
	case FEATURE_SHIELD_INTRO:
		return "feature_shield_intro";
	case FEATURE_BATTLE_ARRAY:
		return "feature_battle_array";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_10:
		return "feature_mower_type_10";
	case FEATURE_CHRISTMAS_PROTECT_INTRO:
		return "feature_christmas_protect_intro";
	case FEATURE_UNLOCK_HARDLEVEL:
		return "feature_unlock_hardlevel";
	case FEATURE_GET_EASYLEVEL_STAR:
		return "feature_get_easylevel_star";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_11:
		return "feature_mower_type_11";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_12:
		return "feature_mower_type_12";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_13:
		return "feature_mower_type_13";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_14:
		return "feature_mower_type_14";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_15:
		return "feature_mower_type_15";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_16:
		return "feature_mower_type_16";
	case FEATURE_POWERUP_VASEBREAKER_MOVE:
		return "feature_powerup_vasebreaker_move";
	case FEATURE_POWERUP_VASEBREAKER_REVEAL:
		return "feature_powerup_vasebreaker_reveal";
	case FEATURE_POWERUP_VASEBREAKER_COLOR:
		return "feature_powerup_vasebreaker_color";
	case FEATURE_POWERUP_VASEBREAKER_BUTTER:
		return "feature_powerup_vasebreaker_butter";
	case FEATURE_HAS_SEEN_RIFT_HOW_TO_PLAY:
		return "feature_has_seen_rift_how_to_play";
	default:
		return "feature_gems";
	}
}

const char* GameFeatureType::ToString() const
{
	switch (Feature)
	{
	case FEATURE_SHOVEL:
		return "feature_shovel";
	case FEATURE_ALMANAC:
		return "feature_almanac";
	case FEATURE_COINS:
		return "feature_coins";
	case FEATURE_GEMS:
		return "feature_gems";
	case FEATURE_BUY_SUN:
		return "feature_buy_sun";
	case FEATURE_KEYS:
		return "feature_keys";
	case FEATURE_WORLDMAP:
		return "feature_worldmap";
	case FEATURE_PLANTFOOD:
		return "feature_plantfood";
	case FEATURE_PLANTFOOD_PURCHASE:
		return "feature_plantfood_purchase";
	case FEATURE_HAS_PLAYED_DANGERROOM:
		return "feature_has_played_dangerroom";
	case FEATURE_HAS_FAILED_DANGERROOM:
		return "feature_has_failed_dangerroom";
	case FEATURE_HAS_WON_DANGERROOM:
		return "feature_has_won_dangerroom";
	case FEATURE_TREASURE_YETI:
		return "feature_treasure_yeti";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_1:
		return "feature_mower_type_1";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_2:
		return "feature_mower_type_2";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_3:
		return "feature_mower_type_3";
	case FEATURE_UPGRADE_6_SLOTS:
		return "6_slots";
	case FEATURE_UPGRADE_7_SLOTS:
		return "7_slots";
	case FEATURE_UPGRADE_8_SLOTS:
		return "seedslot2";
	case FEATURE_UPGRADE_SHOVEL_LVL1:
		return "sunshovel_lvl1";
	case FEATURE_UPGRADE_SHOVEL_LVL2:
		return "sunshovel_lvl2";
	case FEATURE_UPGRADE_SHOVEL_LVL3:
		return "sunshovel3";
	case FEATURE_UPGRADE_PF_REFRESH:
		return "pf_refresh";
	case FEATURE_UPGRADE_WALLNUT_FIRSTAID:
		return "wallnut_firstaid";
	case FEATURE_UPGRADE_PF_SLOTS_LVL1:
		return "pf_slots_lvl1";
	case FEATURE_UPGRADE_PF_SLOTS_LVL2:
		return "pf_slots_lvl2";
	case FEATURE_UPGRADE_PF_SLOTS_LVL3:
		return "pf_slots_lvl3";
	case FEATURE_UPGRADE_STARTING_SUN_LVL1:
		return "starting_sun_lvl1";
	case FEATURE_UPGRADE_STARTING_SUN_LVL2:
		return "startingsun2";
	case FEATURE_UPGRADE_STARTING_SUN_LVL3:
		return "startingsun3";
	case FEATURE_POWERUP_WIZARDFINGER:
		return "feature_powerup_wizardfinger";
	case FEATURE_POWERUP_FLICKZOMBIE:
		return "feature_powerup_flick_zombie";
	case FEATURE_POWERUP_PINCH:
		return "feature_powerup_pinch";
	case FEATURE_POWERUP_TACTICALCUKE:
		return "feature_powerup_tacticalcuke";
	case FEATURE_CARD_KONGFU_COMING_SOON:
		return "kongfu_coming_soon";
	case FEATURE_UPGRADE_SHOVEL_LVL4:
		return "sunshovel_lvl4";
	case FEATURE_UPGRADE_STARTING_SUN_LVL4:
		return "startingsun4";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_4:
		return "feature_mower_type_4";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_5:
		return "feature_mower_type_5";
	case FEATURE_FESTIVAL_ENTRANCE:
		return "feature_festival_entrance";
	case FEATURE_FESTIVALGAME_CRAZYYETI_LEGEND:
		return "feature_festivalgame_crazyyeti_legend";
	case FEATURE_FESTIVALGAME_GARGANTUARCRISIS_LEGEND:
		return "feature_festivalgame_gargantuarcrisis_legend";
	case FEATURE_FESTIVALGAME_DEVILINVADE_LEGEND:
		return "feature_festivalgame_devilinvade_legend";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_6:
		return "feature_mower_type_6";
	case FEATURE_UPGRADE_MANUAL_MOWERS_1:
		return "manual_mowers_1";
	case FEATURE_UPGRADE_MANUAL_MOWERS_2:
		return "manual_mowers_2";
	case FEATURE_UPGRADE_MANUAL_MOWERS_3:
		return "manual_mowers_3";
	case FEATURE_UPGRADE_MANUAL_MOWERS_4:
		return "manual_mowers_4";
	case FEATURE_UPGRADE_MANUAL_MOWERS_5:
		return "manual_mowers_5";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_7:
		return "feature_mower_type_7";
	case FEATURE_FESTIVALGAME_WEALTHGOD_LEGEND:
		return "feature_festivalgame_wealthgod_legend";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_8:
		return "feature_mower_type_8";
	case FEATURE_TIP_FREEZINGWIND:
		return "feature_tip_freezingwind";
	case FEATURE_TIP_SHIELD:
		return "feature_tip_shield";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_9:
		return "feature_mower_type_9";
	case FEATURE_AIR_MISSILE_GUIDE:
		return "feature_air_missile_guide";
	case FEATURE_CANNON_1:
		return "feature_cannon_1";
	case FEATURE_SHIELD_1:
		return "feature_shield_1";
	case FEATURE_CANNON_INTRO:
		return "feature_cannon_intro";
	case FEATURE_SHIELD_INTRO:
		return "feature_shield_intro";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_10:
		return "feature_mower_type_10";
	case FEATURE_CHRISTMAS_PROTECT_INTRO:
		return "feature_christmas_protect_intro";
	case FEATURE_UNLOCK_HARDLEVEL:
		return "feature_unlock_hardlevel";
	case FEATURE_GET_EASYLEVEL_STAR:
		return "feature_get_easylevel_star";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_11:
		return "feature_mower_type_11";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_12:
		return "feature_mower_type_12";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_13:
		return "feature_mower_type_13";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_14:
		return "feature_mower_type_14";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_15:
		return "feature_mower_type_15";
	case FEATURE_UPGRADE_LAWNMOWER_TYPE_16:
		return "feature_mower_type_16";
	case FEATURE_POWERUP_VASEBREAKER_MOVE:
		return "feature_powerup_vasebreaker_move";
	case FEATURE_POWERUP_VASEBREAKER_REVEAL:
		return "feature_powerup_vasebreaker_reveal";
	case FEATURE_POWERUP_VASEBREAKER_COLOR:
		return "feature_powerup_vasebreaker_color";
	case FEATURE_POWERUP_VASEBREAKER_BUTTER:
		return "feature_powerup_vasebreaker_butter";
	case FEATURE_HAS_SEEN_RIFT_HOW_TO_PLAY:
		return "feature_has_seen_rift_how_to_play";
	default:
		return NULL;
	}
}
