//
//  AwardsGranter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//
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
	case 0x14: return "sprout";
	case 0x13: return "worldkey";
	case 0x12: return "giftbox";
	case 0x11: return "costume";
	case 0x10: return "costumegroup_lod";
	case 0xf: return "game_feature";
	case 0xe: return "key";
	case 0xd: return "powerupuse";
	case 0xc: return "gems";
	case 0xb: return "coins";
	case 9: return "note";
	case 8: return "firstkey";
	case 7: return "powerupgadget";
	case 6: return "mapgadget";
	case 5: return "upgrade";
	case 4: return "powerup";
	case 3: return "unlock_plant";
	case 2: return "collectible";
	case 1: return "present";
	case 0x15: return "plant_boost";
	default: return "none";
	}
}

/////////////// IsOwned ///////////////

bool AwardsGranter::IsOwned(AwardType awardType, std::string awardParam, bool i_checkGlobalSaveToo)
{
	switch (awardType)
	{
	case 5:
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		const CollectableType* c = (const CollectableType*)Identity(ObjectTypeDirectory<CollectableType>::GetInstancePtr()->GetTypeFromTypeName(awardParam).operator->());
		GameFeatureTypePtr feature = GameFeatureType::GetGameFeatureTypeFromUnlockString(*(const std::string*)((const char*)c + 0x98));
		bool r = profile->GameFeatureIsUnlocked(feature->Feature);
		return r;
	}
	case 0xf:
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		GameFeatureTypePtr feature = GameFeatureType::GetGameFeatureTypeFromUnlockString(awardParam);
		bool r = profile->GameFeatureIsUnlocked(feature->Feature);
		return r;
	}
	case 3:
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
			ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile((FunnelEvent)10);
		else if (i_awardParam == "wallnut")
			ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile((FunnelEvent)15);
		else if (i_awardParam == "potatomine")
			ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile((FunnelEvent)21);
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, i_awardParam.c_str(), i_awardCount);
		break;
	case AWARD_Upgrade:
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		const std::string* unlockString = (const std::string*)((const char*)Identity(ObjectTypeDirectory<CollectableType>::GetInstancePtr()->GetTypeFromTypeName(i_awardParam).operator->()) + 0x98);
		GameFeatureTypePtr feature = GameFeatureType::GetGameFeatureTypeFromUnlockString(*unlockString);
		profile->UnlockGameFeature(feature->Feature);
		gMessageRouter->Broadcast(Message::AwardGiven, i_awardContext, i_awardParam.c_str(), i_awardCount);
		break;
	}
	case AWARD_MapGadget:
		ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile((FunnelEvent)29);
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
