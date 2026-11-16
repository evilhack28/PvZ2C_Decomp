//
//  AwardsGranter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//
#include "PvZ/CollectableUpgrade.h"
#include "PvZ/AwardsGranter.h"
#include "PvZ/CollectableType.h"
#include "PvZ/GameFeatureType.h"
#include "PvZ/ObjectTypeDirectory.h"
#include "PvZ/PlayerInfo.h"
#include "PvZ/ProfileMgr.h"
#include "PvZ/ProfileUtils.h"
#include "PvZ/GameEventMgr.h"

const char* AwardContextToString(AWARD_Context i_context);

static const void* Identity(const void* p) { return p; }

/////////////// AwardTypeToString ///////////////

const char* AwardsGranter::AwardTypeToString(AwardType i_awardType)
{
	switch (i_awardType)
	{
	case AWARD_Sprout: return "sprout";
	case AWARD_WorldKey: return "worldkey";
	case AWARD_GiftBox: return "giftbox";
	case AWARD_Costume: return "costume";
	case AWARD_CostumeGroupLOD: return "costumegroup_lod";
	case AWARD_GameFeature: return "game_feature";
	case AWARD_Key: return "key";
	case AWARD_PowerupUse: return "powerupuse";
	case AWARD_Gems: return "gems";
	case AWARD_Coins: return "coins";
	case AWARD_Note: return "note";
	case AWARD_FirstKey: return "firstkey";
	case AWARD_PowerupGadget: return "powerupgadget";
	case AWARD_MapGadget: return "mapgadget";
	case AWARD_Upgrade: return "upgrade";
	case AWARD_Powerup: return "powerup";
	case AWARD_UnlockPlant: return "unlock_plant";
	case AWARD_Collectable: return "collectible";
	case AWARD_Present: return "present";
	case AWARD_PlantBoost: return "plant_boost";
	default: return "none";
	}
}

/////////////// IsOwned ///////////////

bool AwardsGranter::IsOwned(AwardType awardType, std::string awardParam, bool i_checkGlobalSaveToo)
{
	switch (awardType)
	{
	case AWARD_Upgrade:
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		const CollectableUpgradeType* c = (const CollectableUpgradeType*)Identity(ObjectTypeDirectory<CollectableType>::GetInstancePtr()->GetTypeFromTypeName(awardParam).operator->());
		GameFeatureTypePtr feature = GameFeatureType::GetGameFeatureTypeFromUnlockString(c->Upgrade);
		bool r = profile->GameFeatureIsUnlocked(feature->Feature);
		return r;
	}
	case AWARD_GameFeature:
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		GameFeatureTypePtr feature = GameFeatureType::GetGameFeatureTypeFromUnlockString(awardParam);
		bool r = profile->GameFeatureIsUnlocked(feature->Feature);
		return r;
	}
	case AWARD_UnlockPlant:
		return ProfileMgr::GetInstance().GetCurrentProfile()->GetIsPlantUnlocked(awardParam);
	default:
		return false;
	}
}

/////////////// GiveAward ///////////////

void AwardsGranter::GiveAward(AwardType i_awardType, std::string i_awardParam, int i_awardCount, AWARD_Context i_awardContext, bool i_applyToGlobalSaveDataToo)
{
	GiveAward(i_awardType, i_awardParam, i_awardCount, i_awardContext, i_applyToGlobalSaveDataToo, "award", AwardContextToString(i_awardContext));
}

void AwardsGranter::GiveAward(AwardType i_awardType, std::string i_awardParam, int i_awardCount, AWARD_Context i_awardContext, bool i_applyToGlobalSaveDataToo, std::string i_metricsSource, std::string i_metricsSubtype)
{
	switch (i_awardType)
	{
	case AWARD_UnlockPlant:
		ProfileMgr::GetInstance().GetCurrentProfile()->UnlockPlant(i_awardParam);
		if (i_awardParam == "sunflower")
			ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile(FUNNEL_PickupSunflower);
		else if (i_awardParam == "wallnut")
			ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile(FUNNEL_PickupWallnut);
		else if (i_awardParam == "potatomine")
			ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile(FUNNEL_PickupPotatoMine);
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, i_awardParam.c_str(), i_awardCount);
		break;
	case AWARD_Upgrade:
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		const std::string* unlockString = &((const CollectableUpgradeType*)Identity(ObjectTypeDirectory<CollectableType>::GetInstancePtr()->GetTypeFromTypeName(i_awardParam).operator->()))->Upgrade;
		GameFeatureTypePtr feature = GameFeatureType::GetGameFeatureTypeFromUnlockString(*unlockString);
		profile->UnlockGameFeature(feature->Feature);
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, i_awardParam.c_str(), i_awardCount);
		break;
	}
	case AWARD_MapGadget:
		ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile(FUNNEL_PickupMap);
		break;
	case AWARD_Coins:
	{
		ProfileMgr::GetInstance().GetCurrentProfile()->AddCoins(i_awardCount);
		std::string text = Sexy::StrFormat("coins %d", i_awardCount);
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, text.c_str(), i_awardCount);
		break;
	}
	case AWARD_Gems:
	{
		ProfileMgr::GetInstance().GetCurrentProfile()->AddGems(i_awardCount, true);
		std::string text = Sexy::StrFormat("gems %d", i_awardCount);
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, text.c_str(), i_awardCount);
		break;
	}
	case AWARD_PowerupUse:
		ProfileMgr::GetInstance().GetCurrentProfile()->ModifyPowerupUses(i_awardParam, i_awardCount);
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, i_awardParam.c_str(), i_awardCount);
		break;
	case AWARD_Key:
		ProfileMgr::GetInstance().GetCurrentProfile()->AddKeys(i_awardParam, i_awardCount);
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, i_awardParam.c_str(), i_awardCount);
		break;
	case AWARD_GameFeature:
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		GameFeatureTypePtr feature = GameFeatureType::GetGameFeatureTypeFromUnlockString(i_awardParam);
		profile->UnlockGameFeature(feature->Feature);
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, i_awardParam.c_str(), i_awardCount);
		break;
	}
	case AWARD_Costume:
	{
		int costumeId = -1;
		Sexy::StringToInt(i_awardParam.c_str(), &costumeId);
		break;
	}
	case AWARD_WorldKey:
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, "WorldKey", i_awardCount);
		break;
	default:
		break;
	}

	if (i_awardContext == AWARDCONTEXT_EpicQuest)
	{
		EpicQuestRewardInfo info;
		info.uniqueID = i_metricsSubtype;
		info.type = AwardTypeToString(i_awardType);
		info.subtype = i_awardParam;
		info.amount = i_awardCount;
		gMessageRouter->Broadcast(Message::EpicQuestRewarded, &info);
	}
}
