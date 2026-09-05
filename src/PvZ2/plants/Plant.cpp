//
//  Plant.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-03.
//

#include "Plant.h"

#include "Board.h"
#include "BoardTransforms.h"
#include "LawnApp.h"
#include "LevelModuleManager.h"
#include "ProtectThePlantChallenge.h"
#include "BoardPropertySheet.h"
#include "BoardConstants.h"
#include "StageModule.h"
#include "GameEventMgr.h"
#include "NameMapper.h"
#include "NewPVPUtils.h"
#include "PlantBoostMgr.h"
#include "PlantBoostPropertySheet.h"
#include "PlantFramework.h"
#include "PlantGeneEnhancement.h"
#include "PlantNewAvatar.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "PVZ1ModeUtils.h"
#include "ScaledApp.h"
#include "ReflectionBuilder.h"
#include "ResourceHelpers.h"
#include "SexyAppFramework/MTRand.h"
#include "TimeMgr.h"
#include "TodLib/TodStringFile.h"
#include "Zombie.h"
#include "ZombieType.h"

class PlantAvatarExchange
{
public:
	static int GetAvatarExchangeCost(int i_rare);
};

RT_CLASS_IMPLEMENT(Plant);
RT_CLASS_IMPLEMENT(PlantType);
RT_CLASS_IMPLEMENT(PlantPropertySheet);

void Plant::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RelocationEvent);
		REFLECTION_CLASSBUILDER_FIELD(float, m_relocateFromX);
		REFLECTION_CLASSBUILDER_FIELD(float, m_relocateFromY);
		REFLECTION_CLASSBUILDER_FIELD(float, m_relocateToX);
		REFLECTION_CLASSBUILDER_FIELD(float, m_relocateToY);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_relocateStartTime);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_relocateEndTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_whetherToMovePlant);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_relocationType);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, m_relocationOffsetFromDestination);
	REFLECTION_CLASSBUILDER_END(RelocationEvent);

	REFLECTION_CLASSBUILDER_BEGIN(UBoostInfo);
		REFLECTION_CLASSBUILDER_FIELD(float, m_uBoostDamagePerHit);
		REFLECTION_CLASSBUILDER_FIELD(float, m_uBoostDisabledTime);
		REFLECTION_CLASSBUILDER_FIELD(float, m_uBoostDamageTotal);
		REFLECTION_CLASSBUILDER_FIELD(float, m_uBoostDamageLimit);
		REFLECTION_CLASSBUILDER_FIELD(float, m_uBoostDamageDuration);
		REFLECTION_CLASSBUILDER_FIELD(float, m_uBoostDamageBySun);
		REFLECTION_CLASSBUILDER_FIELD(float, m_uBoostDamageGlobal);
	REFLECTION_CLASSBUILDER_END(UBoostInfo);

	REFLECTION_CLASSBUILDER_BEGIN(PlantConditionTracker);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<uint8_t>, m_conditionFlags);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<EntityCondition>, m_conditions);
	REFLECTION_CLASSBUILDER_END(PlantConditionTracker);

	REFLECTION_CLASSBUILDER_BEGIN(PlantConditionTracker);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<uint8_t>, m_conditionFlags);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<EntityCondition>, m_conditions);
	REFLECTION_CLASSBUILDER_END(PlantConditionTracker);

	REFLECTION_CLASSBUILDER_BEGIN(Plant);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(ValueRange, m_initialLaunchInterval);
		REFLECTION_CLASSBUILDER_FIELD(ValueRange, m_launchInterval);
		REFLECTION_CLASSBUILDER_FIELD(float, m_baseScale);
		REFLECTION_CLASSBUILDER_FIELD(uint, m_state);
		REFLECTION_CLASSBUILDER_FIELD(float, m_PlantHealth);
		REFLECTION_CLASSBUILDER_FIELD(float, m_PlantLastHealth);
		REFLECTION_CLASSBUILDER_FIELD(float, m_showHealthBarTime);
		REFLECTION_CLASSBUILDER_FIELD(float, m_PlantMaxHealth);
		REFLECTION_CLASSBUILDER_FIELD(float, m_speedModifier);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_lastDamageType);
		REFLECTION_CLASSBUILDER_FIELD(float, m_baseSpeedModifier);
		REFLECTION_CLASSBUILDER_FIELD(float, m_extraCurePercent);
		REFLECTION_CLASSBUILDER_FIELD(UBoostInfo, m_uBoostInfo);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_row);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_column);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isOnBoard);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isShooter);
		REFLECTION_CLASSBUILDER_FIELD(float, m_extraValue);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_disappearTime);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_doSpecialTime);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_stateEndTime);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_launchTime);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_plantFoodEndTime);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timeTillNextDamageFlash);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_fadeInDuration);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_fadeInEndTime);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_speedChangeTime);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_damageStates);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_currentDamageState);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_mirror);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_squish);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_canAttack);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_currentPlantActionIdx);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_type);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_animRig);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_animPotRig);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_plantFoodShine);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_starPlantFoodShine);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_protectedFromShovel);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isDuplicate);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isInPlantFoodState);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bIsInvincible);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_shouldUseStarPFEffect);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_InvincibleTime);
		REFLECTION_CLASSBUILDER_FIELD(MultiPlantGridLayer, m_multiPlantGridLayer);
		REFLECTION_CLASSBUILDER_FIELD(MultiPlantGridLayer, m_multiPlantDrawLayer);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_tAttackUpTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bIsAttackUp);
		REFLECTION_CLASSBUILDER_FIELD(float, m_iAppendAttackUpPercent);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_tAttackUpConstValueTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bIsAttackUpConstValue);
		REFLECTION_CLASSBUILDER_FIELD(float, m_iAppendAttackUpConstValue);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bIsTupleSpellPlantFood);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_tLossLifeTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bIsLossLife);
		REFLECTION_CLASSBUILDER_FIELD(float, m_iLossLifePerFrame);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_tCureLifeTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bIsCureLife);
		REFLECTION_CLASSBUILDER_FIELD(float, m_iCureLifePerFrame);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RelocationEvent>, m_relocationEvents);
		REFLECTION_CLASSBUILDER_FIELD(RelocationEvent, m_curRelocationEvent);
		REFLECTION_CLASSBUILDER_FIELD(float, m_xShakeOffset);
		REFLECTION_CLASSBUILDER_FIELD(float, m_yShakeOffset);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bAvatar);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bAvatarActive);
		REFLECTION_CLASSBUILDER_FIELD(int, m_iMiniLevel);
		REFLECTION_CLASSBUILDER_FIELD(int, m_starLevel);
		REFLECTION_CLASSBUILDER_FIELD(int, m_iMaxLevel);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bCheatSkill);
		REFLECTION_CLASSBUILDER_FIELD(int, m_skillProbability);
		REFLECTION_CLASSBUILDER_FIELD(int, m_skillProbIndex);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_show_upgrade);
		REFLECTION_CLASSBUILDER_FIELD(float, m_upgrade_percent);
		REFLECTION_CLASSBUILDER_FIELD(float, m_lastUpgradepercent);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_upgradeSetTime);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_BombProjectile);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlayedThreePeaterSound);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isSleepping);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_sleepingEndTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_inPvz1SleepAction);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_inPvz1Sleepping);
		REFLECTION_CLASSBUILDER_FIELD(int, m_pvz1SleepRate);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_pvz1SleepTimer);
		REFLECTION_CLASSBUILDER_FIELD(int, m_iAvatar);
		REFLECTION_CLASSBUILDER_FIELD(int, m_iLevel);
		REFLECTION_CLASSBUILDER_FIELD(int, m_avatarIndex);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bDead);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isThrownAway);
		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
		REFLECTION_CLASSBUILDER_FIELD(PlantConditionTracker, m_conditionTracker);
		REFLECTION_CLASSBUILDER_FIELD(AttachedEffectManager, m_attachedEffects);
		REFLECTION_CLASSBUILDER_FIELD(AttachedBoardEntityManager, m_attachedBoardEntities);
		REFLECTION_CLASSBUILDER_FIELD(float, m_extraNormalDamage);
		REFLECTION_CLASSBUILDER_FIELD(float, m_extraSpecialDamage);
		REFLECTION_CLASSBUILDER_FIELD(float, m_extraLevelDamage);
		REFLECTION_CLASSBUILDER_FIELD(float, m_extraHpRate);
		REFLECTION_CLASSBUILDER_FIELD(int, m_extraHp);
		REFLECTION_CLASSBUILDER_FIELD(float, m_extraAtkRate);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_plantOnWater);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<float> >, m_extraReg);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<pvztime_t>, m_lastRegenTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<float> >, m_extraSun);
		REFLECTION_CLASSBUILDER_FIELD(float, m_reducedCooldown);
		REFLECTION_CLASSBUILDER_FIELD(float, m_awakenDamage);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<float> >, m_sunRefund);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<float> >, m_invincible);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<pvztime_t>, m_invincibleLastTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, m_invincibleCurDamage);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<float> >, m_ghost);
		REFLECTION_CLASSBUILDER_FIELD(float, m_improvePoison);
		REFLECTION_CLASSBUILDER_FIELD(float, m_stunBoostCoolDown);
		REFLECTION_CLASSBUILDER_FIELD(float, m_stunBoostTimer);
		REFLECTION_CLASSBUILDER_FIELD(float, m_plantfoodRateOnKillZombie);
		REFLECTION_CLASSBUILDER_FIELD(float, m_plantfoodRateOnKillZombieTimer);
		REFLECTION_CLASSBUILDER_FIELD(float, m_sunmoneyRateOnKillZombie);
		REFLECTION_CLASSBUILDER_FIELD(float, m_coinRateOnKillZombie);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_enableDamageRecord);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_lastDamageRecord);
		REFLECTION_CLASSBUILDER_FIELD(float, m_damageRecordValue);
		REFLECTION_CLASSBUILDER_FIELD(float, m_damageReduceValue);
		REFLECTION_CLASSBUILDER_FIELD(float, m_perSlingShotDamage);
		REFLECTION_CLASSBUILDER_FIELD(float, m_slingShotTimer);
		REFLECTION_CLASSBUILDER_FIELD(float, m_slingShotCounter);
		REFLECTION_CLASSBUILDER_FIELD(float, m_geneSkillBoost);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_waterDurationEnd);
		REFLECTION_CLASSBUILDER_FIELD(std::set<std::string>, m_tags);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_consumeSun);
		REFLECTION_CLASSBUILDER_FIELD(int, m_actualCost);
		REFLECTION_CLASSBUILDER_FIELD(PlantPtr, m_holoPlant);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_holoShinny);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isCrossPlant);

		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onStandaloneEffectFinishedCallback, onStandaloneEffectFinishedCallback, StandaloneEffect*);
		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onAnimStoppedCallback, onAnimStoppedCallback, const std::string&);
		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_NOARGS(onPlantfoodStartedCallback, onPlantfoodStartedCallback);
		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_NOARGS(onPlantfoodLoopedCallback, onPlantfoodLoopedCallback);
		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_NOARGS(onPlantfoodEndedCallback, onPlantfoodEndedCallback);
		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(OnEventCall, OnEventCall, RealObject*);

	REFLECTION_CLASSBUILDER_END(Plant);
}

void PlantType::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(PlantAvatarType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, (PlantAvatarType)-1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(normal, (PlantAvatarType)0);
	REFLECTION_ENUMBUILDER_END(PlantAvatarType);

	REFLECTION_ENUMBUILDER_BEGIN(PlantAvatarRare);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(rare0, (PlantAvatarType)0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(rare1, (PlantAvatarType)1);
	REFLECTION_ENUMBUILDER_END(PlantAvatarRare);

	REFLECTION_ENUMBUILDER_BEGIN(PlantProfessions);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(invalid, (PlantProfessions)-1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(shooter, (PlantProfessions)0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(warrior, (PlantProfessions)1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(supporter, (PlantProfessions)2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(protector, (PlantProfessions)3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(sunmaker, (PlantProfessions)4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(specialist, (PlantProfessions)5);
	REFLECTION_ENUMBUILDER_END(PlantProfessions);

	REFLECTION_ENUMBUILDER_BEGIN(PlantAttributeType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(hp, (PlantAttributeType)0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(attack, (PlantAttributeType)1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(range, (PlantAttributeType)2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(plant, (PlantAttributeType)3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(support, (PlantAttributeType)4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(control, (PlantAttributeType)5);
	REFLECTION_ENUMBUILDER_END(PlantAttributeType);

	REFLECTION_ENUMBUILDER_BEGIN(PlantAttributeRank);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, (PlantAttributeRank)0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(D, (PlantAttributeRank)1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(C, (PlantAttributeRank)2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(B, (PlantAttributeRank)3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(A, (PlantAttributeRank)4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(S, (PlantAttributeRank)5);
	REFLECTION_ENUMBUILDER_END(PlantAttributeRank);

	REFLECTION_ENUMBUILDER_BEGIN(PlantTag);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(green, (PlantTag)0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(heal, (PlantTag)1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(support, (PlantTag)2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(debuff, (PlantTag)3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(sun_produce, (PlantTag)4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(red, (PlantTag)5);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pea, (PlantTag)6);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(dps, (PlantTag)7);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(aoe, (PlantTag)8);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(burn, (PlantTag)9);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(one_shot, (PlantTag)10);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(curve, (PlantTag)11);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(manual, (PlantTag)12);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(explode, (PlantTag)13);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(flame, (PlantTag)14);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(lightning, (PlantTag)27);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(cold, (PlantTag)17);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(magic, (PlantTag)37);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(poison, (PlantTag)35);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(shadow, (PlantTag)15);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(blue, (PlantTag)16);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(summon, (PlantTag)18);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(consume, (PlantTag)19);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(operate, (PlantTag)20);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(flying, (PlantTag)21);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(watering, (PlantTag)22);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(low, (PlantTag)23);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(high, (PlantTag)24);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(armor, (PlantTag)25);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(yellow, (PlantTag)26);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(defence, (PlantTag)28);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(slow, (PlantTag)29);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(teleport, (PlantTag)30);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(control, (PlantTag)31);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(physical, (PlantTag)33);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(grey, (PlantTag)32);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(purple, (PlantTag)34);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(pink, (PlantTag)36);
	REFLECTION_ENUMBUILDER_END(PlantTag);

	REFLECTION_ENUMBUILDER_BEGIN(PlantSpecialTag);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_red, (PlantSpecialTag)0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_grey, (PlantSpecialTag)2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_purple, (PlantSpecialTag)6);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_pink, (PlantSpecialTag)10);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_blue, (PlantSpecialTag)4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_yellow, (PlantSpecialTag)8);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_burned1, (PlantSpecialTag)1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_stuned1, (PlantSpecialTag)3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_freezed1, (PlantSpecialTag)5);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_poisoned1, (PlantSpecialTag)7);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_stucked1, (PlantSpecialTag)9);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(s_hypnotized1, (PlantSpecialTag)11);
	REFLECTION_ENUMBUILDER_END(PlantSpecialTag);

	REFLECTION_ENUMBUILDER_BEGIN(PlantAdditionType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, (PlantAdditionType)-1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(AdditionA, (PlantAdditionType)0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(AdditionB, (PlantAdditionType)1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(AdditionC, (PlantAdditionType)2);
	REFLECTION_ENUMBUILDER_END(PlantAdditionType);

	REFLECTION_CLASSBUILDER_BEGIN(PlantAvatar);
		REFLECTION_CLASSBUILDER_FIELD(PlantAvatarType, AvatarType);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, AvatarLayers);
		REFLECTION_CLASSBUILDER_FIELD(int, CostNum);
		REFLECTION_CLASSBUILDER_FIELD(float, PacketCooldownPercent);
	REFLECTION_CLASSBUILDER_END(PlantAvatar);

	REFLECTION_CLASSBUILDER_BEGIN(PlantAttributeInfo);
		REFLECTION_CLASSBUILDER_FIELD(PlantAttributeType, Type);
		REFLECTION_CLASSBUILDER_FIELD(PlantAttributeRank, Rank);
	REFLECTION_CLASSBUILDER_END(PlantAttributeInfo);

	REFLECTION_CLASSBUILDER_BEGIN(PlantSpecialTagInfo);
		REFLECTION_CLASSBUILDER_FIELD(PlantSpecialTag, Tag);
		REFLECTION_CLASSBUILDER_FIELD(int, MinLevel);
	REFLECTION_CLASSBUILDER_END(PlantSpecialTagInfo);

	REFLECTION_CLASSBUILDER_BEGIN(PlantAttribute);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantAttributeInfo>, Attributes);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantTag>, Tags);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantSpecialTagInfo>, SpecialTags);
	REFLECTION_CLASSBUILDER_END(PlantAttribute);

	REFLECTION_CLASSBUILDER_BEGIN(PlantType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantFramework);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<PlantPropertySheet>, Properties);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<HeroPlantPropertySheet>, HeroProperties);
		REFLECTION_CLASSBUILDER_FIELD(std::string, AnimRigClass);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(bool, Enabled);
		REFLECTION_CLASSBUILDER_FIELD(bool, PlantPieceEnabled);
		REFLECTION_CLASSBUILDER_FIELD(bool, AvatarEnabled);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PlantResourceGroups);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, AdventureFlags);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantAvatarRare>, SecondPopAnimRare);
		REFLECTION_CLASSBUILDER_FIELD(std::string, HomeWorld);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantPieceImageName);
		REFLECTION_CLASSBUILDER_FIELD(std::string, AvatarPieceImageName);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantAvatar>, Avatars);
		REFLECTION_CLASSBUILDER_FIELD(int32, Rare);
		REFLECTION_CLASSBUILDER_FIELD(int32, ExchangeAvatarCost);
		REFLECTION_CLASSBUILDER_FIELD(bool, ExchangeAvatarOpenFlag);
		REFLECTION_CLASSBUILDER_FIELD(PlantProfessions, Profession);
		REFLECTION_CLASSBUILDER_FIELD(PlantAttribute, Attribute);
		REFLECTION_CLASSBUILDER_FIELD(int, DisplayFamilyId);
	REFLECTION_CLASSBUILDER_END(PlantType);

}

const PlantPropertySheet* PlantType::GetProps() const
{
	return Properties.Get();
}

int PlantType::GetCost(int level) const
{
	return GetCost();
}

PlantPropsPtr PlantType::GetPropsPtr() const
{
	return Properties;
}

HeroPlantPropsPtr PlantType::GetHeroPropsPtr() const
{
	return HeroProperties;
}

const class HeroPlantPropertySheet* PlantType::GetHeroProps() const
{
	return HeroProperties.operator->();
}

bool PlantType::IsHeroPlant() const
{
	return HeroProperties.IsValid();
}

bool PlantType::GetExchangeAvatarOpenFlag() const
{
	return ExchangeAvatarOpenFlag;
}

int PlantType::GetExchangeAvatarCost() const
{
	if (ExchangeAvatarCost > 0)
		return ExchangeAvatarCost;
	return PlantAvatarExchange::GetAvatarExchangeCost(Rare);
}

bool PlantType::IsDoubleBoard() const
{
	return false;
}

bool PlantType::IsInHomeWorld() const
{
	if (gLawnApp != NULL && gLawnApp->m_board != NULL)
	{
		StageModule* stage = gLawnApp->m_board->GetStage();
		if (stage != NULL && stage->MatchWorld(HomeWorld))
			return true;
	}
	return false;
}

int PlantType::GetSaveCostInHomeWorld() const
{
	if (!IsInHomeWorld())
		return 0;
	return Properties->SaveCostInHomeWorld;
}

bool PlantType::IsInsideRestrictedArea(const Sexy::Point& i_gridPosition) const
{
	const Sexy::Rect& area = GetProps()->RestrictPlantingToGridArea;
	if (area.mWidth == 0 && area.mHeight == 0)
		return true;
	return area.Contains(i_gridPosition);
}

void PlantType::UpdateAvatar() const
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (profile)
		eCurAvatar = profile->GetPlantAvatar(TypeName, true);
	else
		eCurAvatar = E_AVATAR_NONE;
}

float PlantType::GetMaxHitpoints() const
{
	return GetProps()->Hitpoints;
}

int PlantType::GetBeghouledCost() const
{
	return GetProps()->BeghouledCost;
}

Color PlantType::GetRareColor() const
{
	switch (Rare)
	{
	case 1:  return Color(0xa4, 0xff, 0xa4);
	case 2:  return Color(0x00, 0x80, 0xff);
	case 3:  return Color(0xaf, 0x87, 0xff);
	case 4:  return Color(0xff, 0xcc, 0x00);
	default: return Color(0xff, 0xff, 0xcc);
	}
}

std::string PlantType::GetPlantProfessionName(PlantProfessions i_profession)
{
	switch (i_profession)
	{
	case PROFESSION_Shooter:    return "[PROFESSION_SHOOTER]";
	case PROFESSION_Warrior:    return "[PROFESSION_WARRIOR]";
	case PROFESSION_Supporter:  return "[PROFESSION_SUPPORTER]";
	case PROFESSION_Protector:  return "[PROFESSION_PROTECTOR]";
	case PROFESSION_Sunmaker:   return "[PROFESSION_SUNMAKER]";
	case PROFESSION_Specialist: return "[PROFESSION_SPECIALIST]";
	default:                    return "";
	}
}

std::string PlantType::GetPlantProfessionDescription(PlantProfessions i_profession)
{
	switch (i_profession)
	{
	case PROFESSION_Shooter:    return "[PROFESSION_SHOOTER_DESCRIPTION]";
	case PROFESSION_Warrior:    return "[PROFESSION_WARRIOR_DESCRIPTION]";
	case PROFESSION_Supporter:  return "[PROFESSION_SUPPORTER_DESCRIPTION]";
	case PROFESSION_Protector:  return "[PROFESSION_PROTECTOR_DESCRIPTION]";
	case PROFESSION_Sunmaker:   return "[PROFESSION_SUNMAKER_DESCRIPTION]";
	case PROFESSION_Specialist: return "[PROFESSION_SPECIALIST_DESCRIPTION]";
	default:                    return "";
	}
}

SkillPropertySheetPtr PlantType::GetCurrentLevelSkillType(int i_level, bool bIsProperty) const
{
	SkillPropertySheetPtr ret;
	const PlantLevelStat& stat = Properties->PlantLevelStats[i_level - 1];
	if (bIsProperty)
		ret = stat.PropertySkillType;
	else
		ret = stat.AdvancedSkillType;

	return ret;
}

bool PlantType::HasPlantAdventureFlag(std::string i_flag) const
{
	if (i_flag.length() > 5 && "level" == i_flag.substr(0, 5))
	{
		std::string idx = i_flag.substr(5, 1);
		int level = atoi(idx.c_str());
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		if (profile == NULL || profile->GetPlantStarLevel(TypeName) < level)
			return false;

		return true;
	}

	for (std::vector<std::string>::const_iterator it = AdventureFlags.begin(); it != AdventureFlags.end(); ++it)
	{
		if (*it == i_flag)
			return true;
	}

	return false;
}

int PlantType::GetCostOffset() const
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if ("jalapeno" != TypeName || PVZ1ModeUtils::IsPlayingPVZ1Level())
		return 0;

	int result = 0;
	if (profile->GetPlantStarLevel("jalapeno") == 3)
		result = -25;

	return result;
}

void PlantType::GetAvatarLayers(PlantAvatarType i_avatarType, std::vector<std::string>& i_avatarLayers) const
{
	for (size_t i = 0; i < Avatars.size(); i++)
	{
		if (Avatars[i].AvatarType == i_avatarType)
			i_avatarLayers = Avatars[i].AvatarLayers;
	}
}

int PlantType::GetNewAvatarRare() const
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	int avatarId = profile->GetEquipAvatarID(TypeName);
	if (profile->GetWhichAvatarType(avatarId) == NEW_AVATAR_TYPE)
	{
		PlantNewAvatarPtr info = NewAvatar::GetAvatarInfoByAvatarId(avatarId);
		if (info)
			return info->Rare;

		return -1;
	}

	return -1;
}

bool PlantType::IsNewAvatarNewRare() const
{
	bool result = false;
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	int avatarId = profile->GetEquipAvatarID(TypeName);
	if (profile->GetWhichAvatarType(avatarId) == NEW_AVATAR_TYPE)
	{
		PlantNewAvatarPtr info = NewAvatar::GetAvatarInfoByAvatarId(avatarId);
		if (info)
			result = 0 < info->Rare;
	}

	return result;
}

void PlantType::AddResourceRequirements(std::set<std::string>& io_resGroupNames) const
{
	if (TypeName == "hypnoshroom")
	{
		const ZombieType* garg = gLawnApp->m_board->GetStage()->GetGargantuarForStage();
		garg->AddInGameResourceRequirements(io_resGroupNames);
	}

	io_resGroupNames.insert(PlantResourceGroups.begin(), PlantResourceGroups.end());

	if (TypeName != "slingpea")
		io_resGroupNames.insert(PlantFramework);
}

bool PlantType::IsSunProducer() const
{
	if (TypeName == "powerlily" || TypeName == "marigold")
		return false;

	const PlantPropertySheet* props = GetProps();
	for (size_t i = 0; i < props->Actions.size(); i++)
	{
		if (props->Actions[i].Type == PLANT_ACTION_PRODUCE_SUN)
			return true;
	}

	return false;
}

bool PlantType::IsBlowProducer() const
{
	if (TypeName == "blover"
		|| TypeName == "hurrikale"
		|| TypeName == "bamboo"
		|| TypeName == "acorn"
		|| TypeName == "broccoli"
		|| TypeName == "citron"
		|| TypeName == "cracker"
		|| TypeName == "draftodil")
		return true;

	return false;
}

bool PlantType::GetCanBeUsedOnStage(const std::string& i_stage) const
{
	if (GetProps() != NULL && GetProps()->ValidStages.size() == 0)
		return true;

	for (size_t i = 0; i < GetProps()->ValidStages.size(); i++)
	{
		if (GetProps()->ValidStages[i] == i_stage)
			return true;
	}

	return false;
}

void PlantPropertySheet::StaticClassInit()
{
}

float PlantPropertySheet::GetPacketCoolDownTime(int iStarLv) const
{
	return PacketCooldown;
}

Sexy::Rect PlantPropertySheet::GetCollisionRect(Plant* plant) const
{
	return Sexy::Rect(
		(int)((HitRectAdjust.mX + plant->m_position.x) - (float)(plant->GetWidth() / 2)),
		(int)((plant->m_position.y + 10.0f + HitRectAdjust.mY) - (float)plant->GetHeight()),
		plant->GetWidth() + HitRectAdjust.mWidth,
		plant->GetHeight() + HitRectAdjust.mHeight);
}

/////////////// Plant -- accessors ///////////////

void Plant::registerForEvents()
{
}

void Plant::constructAndSetFrameworkFromType()
{
	m_plantFramework = Sexy::RtClass::StaticGetClassNamed(((const PlantType*)m_type)->PlantFramework.c_str())->New()->Cast<PlantFramework>();
	m_plantFramework->m_plant = this;
	m_plantFramework->registerForEvents();
}

void Plant::UpdateDamageStates()
{
	if (m_damageStates != 0)
	{
		int chunk = 0;
		if (m_damageStates + 1 != 0)
			chunk = (int)GetMaxHealth() / (m_damageStates + 1);

		int idx = 0;
		if (chunk != 0)
			idx = (int)m_PlantHealth / chunk;

		int target = eastl::min_alt(eastl::max_alt(m_damageStates - idx, 0), m_damageStates);

		if (target != m_currentDamageState && target <= m_damageStates)
		{
			m_currentDamageState = target;
			if (!m_plantFramework->HandleDamageStateChanged())
				m_pCachedPlantAnimRig->SetDamageStateIndex(m_currentDamageState);
		}
	}
}

void Plant::onPostLoad()
{
	BoardEntity::onPostLoad();

	m_pCachedPlantPropertySheet = (PlantPropertySheet*)m_type->GetProps();

	if (m_shouldUseStarPFEffect)
		m_pCachedEffectAnimRig_StarPlantFoodShine = m_starPlantFoodShine.Get();
	else
		m_pCachedEffectAnimRig_PlantFoodShine = m_plantFoodShine.Get();

	PlantAnimRig* rig = GetAnimRig();
	m_plantFramework->SetPopAnimDelegates(rig);
	m_plantFramework->onPostLoad();

	rig->SetIdleAnimationWeights(GetProps()->IdleAnimationWeights);
	m_pCachedPlantAnimRig = rig;
}

bool Plant::IsOnBoard()
{
	return m_isOnBoard;
}

float Plant::GetUBoostDamageTotal()
{
	return m_uBoostInfo.m_uBoostDamageTotal;
}

void Plant::SetHealth(const float i_health)
{
	m_PlantHealth = i_health;
}

void Plant::SetMaxHealth(float maxHealth)
{
	m_PlantMaxHealth = maxHealth;
}

void Plant::SetExtraLevelDamge(float ratio)
{
	m_extraLevelDamage = ratio;
}

float Plant::GetExtraLevelDamge() const
{
	return m_extraLevelDamage;
}

bool Plant::IsThrownAway()
{
	return m_isThrownAway;
}

void Plant::SetIsThrownAway(bool i_thrown)
{
	m_isThrownAway = i_thrown;
}

int Plant::GetHeight() const
{
	return BoardConstants::GRIDSQUARE_WIDTH();
}

void Plant::forceApplyConditionEffects()
{
	updateSpeed();
}

/////////////// Plant -- conditions ///////////////

PlantConditionTracker& Plant::GetConditionTracker()
{
	return m_conditionTracker;
}

bool Plant::HasCondition(PlantConditions i_condition) const
{
	return m_conditionTracker.HasCondition(i_condition);
}

float Plant::updateRelocationPositionAndRotation()
{
	float rotOffset = 0.0f;
	float ret = 0.0f;

	if (isRelocating())
	{
		float toX = m_curRelocationEvent.m_relocateToX;
		float toY = m_curRelocationEvent.m_relocateToY;
		float fromX = m_curRelocationEvent.m_relocateFromX;
		float fromY = m_curRelocationEvent.m_relocateFromY;
		float dx = toX - fromX;
		float dy = toY - fromY;
		RelocationEvent::RelocationType type = m_curRelocationEvent.m_relocationType;
		float t = (PVZ_T() - m_curRelocationEvent.m_relocateStartTime)
			/ (m_curRelocationEvent.m_relocateEndTime - m_curRelocationEvent.m_relocateStartTime);

		if (type == RelocationEvent::RELOCATION_ABSORBED)
		{
			float rot = Sexy::SexyMath::DegToRad(720.0f);
			m_curRelocationEvent.m_relocationOffsetFromDestination.y = t * dy;
			m_curRelocationEvent.m_relocationOffsetFromDestination.x = t * dx;
			return rot * t;
		}

		if (type != RelocationEvent::RELOCATION_SHAKE_FADE_IN && type != RelocationEvent::RELOCATION_SHAKE_FADE_OUT)
		{
			double s = sin((double)(Sexy::SexyMath::DegToRad(180.0f) * t));
			float apex = m_curRelocationEvent.m_relocateApexHeight;
			float d720 = Sexy::SexyMath::DegToRad(720.0f);

			if (type != RelocationEvent::RELOCATION_PUSHED)
			{
				ret = d720 * t;
				rotOffset = (float)(s * (double)apex);
			}

			m_curRelocationEvent.m_relocationOffsetFromDestination.x = (t - 1.0f) * dx;
			m_curRelocationEvent.m_relocationOffsetFromDestination.y = (t - 1.0f) * dy - rotOffset;
			return ret;
		}

		m_curRelocationEvent.m_relocationOffsetFromDestination.x = INV_S(m_xShakeOffset);
		m_curRelocationEvent.m_relocationOffsetFromDestination.y = INV_S(m_yShakeOffset);
	}

	return 0.0f;
}

void Plant::SetIsSleepping(bool i_isSleepping, float durationTime)
{
	m_isSleepping = i_isSleepping;
	m_sleepingEndTime = PVZ_EOT();

	if (m_animRig.IsValid())
		m_animRig.Get()->SetPaused(m_isSleepping);

	if (m_attachedEffects.Contains("sleepping"))
		m_attachedEffects.Remove("sleepping");

	bool notify = false;
	if (m_isSleepping)
	{
		if (!m_attachedEffects.Contains("sleepping"))
		{
			AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate("sleepping");
			effect.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_SLEEPPING_PLANT_EFFECT"));
			effect.PlayAnimLooped("animation");
			effect.Attach(this, SexyVector3(0.0f, 0.0f, 0.0f), 1);
		}

		notify = m_isSleepping;
		if (durationTime > 0.0f)
			m_sleepingEndTime = PVZ_T() + durationTime;
	}

	m_plantFramework->onSleeped(notify);
}

void Plant::GetFireOrigin(int& originX, int& originY)
{
	float scale = m_baseScale;
	originX = (int)(GetPosition().x + scale * m_pCachedPlantPropertySheet->Actions[m_currentPlantActionIdx].SpawnOffset.x);
	originY = (int)(GetPosition().y + m_pCachedPlantPropertySheet->Actions[m_currentPlantActionIdx].SpawnOffset.y * scale);
}

bool Plant::IsFrostImmune()
{
	const BoardPropertySheet* props = gLawnApp->m_board->GetBoardProperties();
	bool result = std::find(props->PlantFrostBlacklist.begin(), props->PlantFrostBlacklist.end(),
	                        GetType()->TypeName) != props->PlantFrostBlacklist.end();
	if (!result)
		result = HasCondition(PCONDITION_Icecubed);

	return result;
}

bool Plant::AbsorbsSmashAttack()
{
	const BoardPropertySheet* props = gLawnApp->m_board->GetBoardProperties();
	bool result = std::find(props->PlantSmashAttackBlacklist.begin(), props->PlantSmashAttackBlacklist.end(),
	                        GetType()->TypeName) != props->PlantSmashAttackBlacklist.end();
	if (!result)
		result = m_plantFramework->AbsorbsSmashAttack();

	return result;
}

EntityCondition& Plant::ApplyCondition(PlantConditions i_condition, pvztime_t i_duration, pvztime_t i_eventDelay)
{
	return m_conditionTracker.ApplyCondition(this, i_condition, i_duration, i_eventDelay);
}

void Plant::EndCondition(PlantConditions i_condition)
{
	m_conditionTracker.EndCondition(this, i_condition);
}

void Plant::SetDamageFlash(float i_duration)
{
	m_conditionTracker.ApplyCondition(this, PCONDITION_DamageFlash, i_duration, 0);
}

/////////////// Plant -- misc small ///////////////

float Plant::GetTotalDamageRate()
{
	float boostSum = m_uBoostInfo.m_uBoostDamageBySun + m_uBoostInfo.m_uBoostDamageGlobal + m_uBoostInfo.m_uBoostDamageTotal + m_extraNormalDamage;
	return boostSum * m_extraSpecialDamage * GetExtraDPSmodifier() * m_awakenDamage;
}

float Plant::GetDamageConstValue()
{
	return m_bIsAttackUpConstValue ? m_iAppendAttackUpConstValue : 0.0f;
}

float Plant::GetSlingShotExtraDamage()
{
	return m_slingShotCounter * m_perSlingShotDamage;
}

void Plant::SetSkillProbability(int i_probability)
{
	if (i_probability < 0)
		return;

	m_skillProbability = i_probability;
	m_skillProbIndex = 0;
	m_bCheatSkill = true;
}

void Plant::AddTag(const std::string& i_tag)
{
	m_tags.insert(i_tag);
}

PlantTypePtr Plant::GetType() const
{
	return m_type;
}

bool Plant::IsSlowed()
{
	return m_conditionTracker.GetSpeedModifier() < 1.0f;
}

float Plant::GetGeneSkillBoost()
{
	return m_geneSkillBoost;
}

void Plant::SetGeneSkillBoost(int i_skillBoost)
{
	m_geneSkillBoost = GeneEnhancement::GetGeneEnhancementSkillBoost((PlantSkillBoost)i_skillBoost);
}

void Plant::FullHealth()
{
	m_PlantLastHealth = m_PlantHealth;
	m_PlantHealth = GetMaxHealth();
}

void Plant::StartLossLife(pvztime_t duration, float percentOfMaxHealth)
{
	m_bIsLossLife = true;
	m_tLossLifeTime = PVZ_T() + duration;

	int maxHitpoints = GetMaxHitpoints();
	m_iLossLifePerFrame = PVZ_Dt() * percentOfMaxHealth * maxHitpoints;
}

void Plant::EndLossLife()
{
	m_bIsLossLife = false;
	m_tLossLifeTime = PVZ_EOT();
	m_iLossLifePerFrame = 0.0f;
}

void Plant::StartCureLife(pvztime_t duration, float percentOfMaxHealth)
{
	m_bIsCureLife = true;
	m_tCureLifeTime = PVZ_T() + duration;

	int maxHitpoints = GetMaxHitpoints();
	m_iCureLifePerFrame = PVZ_Dt() * percentOfMaxHealth * maxHitpoints;
}

void Plant::EndCureLife()
{
	m_bIsCureLife = false;
	m_tCureLifeTime = PVZ_EOT();
	m_iCureLifePerFrame = 0.0f;
}

/////////////// Plant -- PlantFramework forwarders ///////////////

int Plant::GetMaxHitpoints()
{
	return m_plantFramework->GetMaxHitpoints();
}

BoardEntityHeight Plant::GetEntityHeight() const
{
	return m_plantFramework->GetEntityHeight();
}

float Plant::getTideDepthHeightMaxPct()
{
	return m_plantFramework->GetTideDepthHeightMaxPct();
}

bool Plant::IsDelayDestroy()
{
	return m_plantFramework->IsDelayDestroy();
}

void Plant::NotifyDamagedEntity(BoardEntity* entity)
{
	m_plantFramework->NotifyDamagedEntity(entity);
}

void Plant::NotifyComponentOwner()
{
	m_plantFramework->NotifyComponentOwner();
}

void Plant::onAnimStoppedCallback(const std::string& i_animCommand)
{
	m_plantFramework->onAnimStoppedCallback(i_animCommand);
}

void Plant::onPlantfoodStartedCallback()
{
	m_plantFramework->onPlantfoodStarted();
}

void Plant::onPlantfoodLoopedCallback()
{
	m_plantFramework->onPlantfoodLooped();
}

void Plant::onPlantfoodEndedCallback()
{
	m_plantFramework->onPlantfoodEnded();
}

void Plant::unregisterForEvents()
{
	m_plantFramework->unregisterForEvents();
}

void Plant::onApplyCondition(PlantConditions i_condition)
{
	m_plantFramework->onApplyCondition(i_condition);
}

void Plant::bePushed()
{
	m_plantFramework->onBePushed();
}

void Plant::beThrown()
{
	m_plantFramework->onBeThrown();
}

void Plant::onStandaloneEffectFinishedCallback(StandaloneEffect* i_effect)
{
	m_plantFramework->onStandaloneEffectFinishedCallback(i_effect);
}

void Plant::OnEventCall(RealObject* pTarget)
{
	m_plantFramework->DoEventCall(pTarget);
}

bool Plant::CanBeConvertedByCondition()
{
	return m_plantFramework->CanBeConvertedByCondition();
}

bool Plant::ShouldClipWithWater() const
{
	return m_plantFramework->ShouldClipWithWater();
}

bool Plant::HasGravity()
{
	return m_plantFramework->HasGravity();
}

bool Plant::TryBlockPush()
{
	return m_plantFramework->TryBlockPush();
}

bool Plant::ReceiveHelp(PlantHelpType i_helpType)
{
	return m_plantFramework->onReceiveHelp(i_helpType);
}

bool Plant::BlockRailcartMovement() const
{
	return m_plantFramework->BlockRailcartMovement();
}

bool Plant::CanBeWatered()
{
	return m_plantFramework->CanBeWatered();
}

bool Plant::CanBeTargetedBy(const BoardEntity* i_entity)
{
	return m_plantFramework->CanBeTargetedBy(i_entity);
}

bool Plant::IsIgnoreControlAndDmg() const
{
	return m_plantFramework->IsIgnoreControlAndDmg();
}

bool Plant::TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction)
{
	return m_plantFramework->TryBlockPushOffBoard(i_srcZombie, i_direction);
}

bool Plant::TryApplyDamageToEntity(DamageInfo& damageInfo, BoardEntity* entity)
{
	return m_plantFramework->TryApplyDamageToEntity(damageInfo, entity);
}

/////////////// Plant -- targeting / invincibility ///////////////

bool Plant::CanBeShoveled()
{
	if (IsInPlantFoodState() || isRelocating() || IsHidden() || m_protectedFromShovel ||
		IsIceblocked() || HasCondition(PCONDITION_WrappedInWormHole))
		return false;

	return m_plantFramework->CanBeShoveled();
}

bool Plant::CanBeTargeted()
{
	if (isRelocating() || IsHidden() || IsSuspended())
		return false;

	return m_plantFramework->CanBeTargeted();
}

bool Plant::CanBeRangeTargeted()
{
	if (IsInPlantFoodState() || IsInvincible() || !CanBeTargeted() || IsSuspended())
		return false;

	return m_plantFramework->CanBeRangeTargeted();
}

bool Plant::IsInvincible(bool dontConsiderPlantfood) const
{
	if (m_plantFramework == NULL)
		return true;

	if (!HasCondition(PCONDITION_GroupSquidified))
	{
		if (!dontConsiderPlantfood)
		{
			if (IsInPlantFoodState())
				return true;
		}

		if (!m_plantFramework->IsInvincible())
			return m_bIsInvincible;
	}

	return true;
}

void Plant::onDestroy()
{
	m_plantFramework->onDestroy();

	m_bDead = true;
	m_groundEffect.Destroy();
	m_attachedEffects.Clear();
	m_attachedBoardEntities.Clear();

	if (IsBeingRemoved())
		return;

	gMessageRouter->Post(Message::PlantDestory, this);
}

int Plant::CalcRenderOrder() const
{
	if (HasCondition(PCONDITION_GroupSquidified))
	{
		if (m_holoPlant.IsValid())
			return m_holoPlant.Get()->CalcRenderOrder() - 2;
	}

	return m_plantFramework->CalcRenderOrder();
}

void Plant::SetPlantAvatarShowIndex(int index)
{
	m_avatarIndex = index;
	m_plantFramework->ShowPlantNewRareAvatarAnim(index);
}

float Plant::GetRelocationSpeedInGridSquaresPerSecond() const
{
	if (!isRelocating())
		return 0.0f;

	float dx = fabsf(m_curRelocationEvent.m_relocateToX - m_curRelocationEvent.m_relocateFromX) / (float)BoardConstants::GRIDSQUARE_WIDTH();
	float dy = fabsf(m_curRelocationEvent.m_relocateToY - m_curRelocationEvent.m_relocateFromY) / (float)BoardConstants::GRIDSQUARE_HEIGHT();

	float duration = fabsf(m_curRelocationEvent.m_relocateEndTime - m_curRelocationEvent.m_relocateStartTime);
	float dist = sqrtf(dx * dx + dy * dy);
	if (duration > 0.0f)
		return dist / duration;

	return FLT_MAX;
}

void Plant::ResetLaunchTimer(float i_forcedInterval)
{
	float spd = m_speedModifier;
	float delay = i_forcedInterval / (GetAdditionValue(PlantAddition::PAdditonRLS_SPD_Add) + spd);
	m_launchTime = delay * m_plantFramework->GetLaunchDelayMultiplier() + PVZ_T();
}

void Plant::ResetLaunchTimer(bool i_useInitialTiming)
{
	float interval;
	if (i_useInitialTiming)
	{
		if (NewPVPUtils::IsPlayingNewPVP())
			interval = m_initialLaunchInterval.Min;
		else
			interval = m_initialLaunchInterval.GetRandomValue();
	}
	else
	{
		if (NewPVPUtils::IsPlayingNewPVP())
			interval = m_launchInterval.Min;
		else
			interval = m_launchInterval.GetRandomValue();
	}

	float delay = (interval - m_plantFramework->GetReducedLaunchDelay()) /
		(GetAdditionValue(PlantAddition::PAdditonRLS_SPD_Add) + m_speedModifier);

	m_launchTime = m_plantFramework->GetLaunchDelayMultiplier() * delay + PVZ_T();
}

void Plant::updateSpeed()
{
	float speedModifier = m_conditionTracker.GetSpeedModifier();

	if (HasCondition(PCONDITION_SlowDown) || HasCondition(PCONDITION_MoreSlowDown) ||
		HasCondition(PCONDITION_DripWater))
	{
		m_speedModifier = speedModifier;
	}

	m_plantFramework->OnupdateSpeed(speedModifier);

	GetAnimRig()->SetAnimRateOverride(GetAdditionValue(PlantAddition::PAdditonRLS_SPD_Add) + speedModifier);
}

void Plant::onHiddenChanged(bool i_hidden, bool i_oldhidden)
{
	if (m_animRig.IsValid())
		m_animRig.Get()->SetPaused(i_hidden);

	m_plantFramework->NotifySetHidden(i_hidden, i_oldhidden);

	if (i_hidden && HasCondition(PCONDITION_GroupIcecubed))
	{
		if (m_holoPlant.IsValid())
		{
			m_holoPlant.Get()->KillPlant(true, false);
			m_holoPlant.ClearId();
		}
	}
}

bool Plant::CollidesWithType(CollisionTypeFlags i_collisionTypes) const
{
	BoardEntityHeight height = GetProps()->Height;
	if (height == ENTITYHEIGHT_ON_GROUND)
		return TestFlag(i_collisionTypes, COLLIDE_ON_GROUND_PLANTS);
	else if (height == ENTITYHEIGHT_LOW)
		return TestFlag(i_collisionTypes, COLLIDE_LOW_PLANTS);
	else if (height == ENTITYHEIGHT_NORMAL)
		return TestFlag(i_collisionTypes, COLLIDE_NORMAL_PLANTS);
	else if (height == ENTITYHEIGHT_TALL)
		return TestFlag(i_collisionTypes, COLLIDE_TALL_PLANTS);
	else
		return TestFlag(i_collisionTypes, COLLIDE_ALL_PLANTS);
}

void Plant::CheckUBoost()
{
	if (m_uBoostInfo.m_uBoostDamagePerHit > 0.0f)
	{
		m_uBoostInfo.m_uBoostDisabledTime = PVZ_T() + m_uBoostInfo.m_uBoostDamageDuration;
		float total = m_uBoostInfo.m_uBoostDamagePerHit + m_uBoostInfo.m_uBoostDamageTotal;
		m_uBoostInfo.m_uBoostDamageTotal = eastl::min_alt(total, m_uBoostInfo.m_uBoostDamageLimit);
	}
}

Sexy::SexyVector3 Plant::CalcProjectileTargetLocation(float i_inTime)
{
	const Sexy::Rect& rect = GetCollisionRect();
	const Sexy::SexyVector3& pos = GetPosition();
	float z = (pos.y - (float)rect.mY) - 0.333333f * (float)rect.mHeight;
	return Sexy::SexyVector3((float)rect.GetCenter().mX, pos.y, z);
}

void Plant::SetGridLocSilent(int i_gridX, int i_gridY)
{
	m_column = i_gridX;
	m_row = i_gridY;

	if (gLawnApp->m_board != NULL)
	{
		Sexy::Point p(i_gridX, i_gridY);
		Sexy::Point boardPos = BoardTransforms::GridToBoardSpaceUnbounded(p);
		SetPosition(Sexy::SexyVector3((float)boardPos.mX, (float)boardPos.mY - 10.0f, GetPosition().z));

		if (gLawnApp->m_board->m_roofStage)
		{
			Sexy::SexyVector3 pos = GetPosition();
			pos.z = gLawnApp->m_board->calculateRoofOffsetZ(pos.x);
			SetPosition(pos);
		}
	}
}

void Plant::TakeArrowCure(int value)
{
	float newHealth = __builtin_fminf((float)value + m_PlantHealth, m_PlantMaxHealth);

	m_PlantLastHealth = m_PlantHealth;
	m_PlantHealth = newHealth;

	AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate("cureup");
	effect.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_PEACH_CURE_UP"));
	effect.PlayAnimAndDestroy("peach_effect");
	effect.Attach(this, Sexy::SexyVector3(0.0f, 0.0f, 0.0f), 1);

	UpdateDamageStates();
}

void Plant::SetAvatarEnable(bool bAvatar)
{
	m_bAvatar = bAvatar;

	if (!bAvatar)
		m_avatarIndex = -1;

	if (GetAvatarEnable())
	{
		m_pCachedPlantAnimRig->SetAvatarIndex(m_avatarIndex);
		m_pCachedPlantAnimRig->ShowAvatarLayers(m_type, E_AVATAR_NORMAL);
	}
	else
	{
		m_pCachedPlantAnimRig->SetAvatarIndex(m_avatarIndex);
		m_pCachedPlantAnimRig->ShowAvatarLayers(m_type, E_AVATAR_NONE);
	}
}

void Plant::TakeSmashAttack(Sexy::RtWeakPtr<Zombie> i_srcZombie)
{
	m_plantFramework->TakeSmashAttack(i_srcZombie);

	if (IsDestroyed())
		gMessageRouter->Broadcast(Message::PlantSmashedToDeath, this);
}

void Plant::TakeGridItemSmashAttack(Sexy::RtWeakPtr<GridItem> i_srcGridItem)
{
	m_plantFramework->TakeGridItemSmashAttack(i_srcGridItem);

	if (IsDestroyed())
		gMessageRouter->Broadcast(Message::PlantSmashedToDeath, this);
}

bool Plant::IsInPlantDefence()
{
	if (!IsProtect())
		return false;

	ProtectThePlantChallengeModule* module = gLawnApp->m_board->m_levelModuleManager->GetModuleByClass<ProtectThePlantChallengeModule>();
	if (!module)
		return false;

	ProtectThePlantChallengeProperties* props = module->GetPropsPtr()->Cast<ProtectThePlantChallengeProperties>();
	return props->IsPlantDefenceMode;
}

void Plant::SetPlantAvatarValue(int iAvatar)
{
	if (m_iAvatar < -1 || m_iAvatar > 2)
		return;

	m_iAvatar = iAvatar;

	bool isOneOrTwo = (iAvatar == 1 || iAvatar == 2);
	if (isOneOrTwo || iAvatar == -1)
	{
		SetAvatarActive(true);
		if (isOneOrTwo)
			SetAvatarEnable(true);
	}
	else
	{
		SetAvatarActive(false);
	}
}

void Plant::SetBombProjectile(const Projectile* i_projectile)
{
	m_BombProjectile = i_projectile->GetPtr();
}

void Plant::IsImpactedByObject(Sexy::RtWeakPtr<Sexy::RtObject> i_object)
{
	m_plantFramework->IsImpactedByObject(i_object);
}

void Plant::HidePlantfoodAnimationEffect()
{
	if (m_plantFoodShine)
		m_plantFoodShine->CancelEffect();

	if (m_starPlantFoodShine)
		m_starPlantFoodShine->CancelEffect();
}

void Plant::DisablePlantfoodAnimation()
{
	gMessageRouter->Post(Message::PlantFoodEnd, this);
	m_isInPlantFoodState = false;
	m_pCachedPlantAnimRig->PlayPlantFoodEnd();

	if (m_shouldUseStarPFEffect)
		m_pCachedEffectAnimRig_StarPlantFoodShine->PlayPlantFoodShineEnd();
	else
		m_pCachedEffectAnimRig_PlantFoodShine->PlayPlantFoodShineEnd();

	ApplyCondition(PCONDITION_PlantfoodFlash, 0.75f, 0.0f);
	ResetLaunchTimer(true);
}

int Plant::Shovel()
{
	gMessageRouter->Broadcast(Message::PlantShoveled, this);
	int refund = (int)m_plantFramework->GetRefundSunAmountForShovel();

	bool isHappyLeek = GetType()->TypeName == "happyleek";
	if (isHappyLeek)
		m_plantFramework->ShovelKill();
	else
		KillPlant(false, isHappyLeek, (DamageTypeFlags)0x40000000000);

	return refund;
}

void Plant::ClearPvz1Sleep()
{
	m_inPvz1Sleepping = false;
	m_pvz1SleepRate = 0;
	m_pvz1SleepTimer = 0;

	if (m_attachedEffects.Contains("sleepping_pvz1"))
		m_attachedEffects.Remove("sleepping_pvz1");

	if (m_animRig.IsValid())
		m_animRig.Get()->SetPaused(m_inPvz1Sleepping);
}

bool Plant::CanApplyPlantfood()
{
	if (!IsHidden() && !isRelocating() && m_state != STATE_BEINGREMOVED &&
		!IsSuspended() && !m_inPvz1Sleepping)
	{
		if (!IsInPlantFoodState() && !HasCondition(PCONDITION_Ghost) &&
			!HasCondition(PCONDITION_Swapping))
		{
			if (HasCondition(PCONDITION_NotFiring))
				return false;

			if (HasCondition(PCONDITION_Smoke))
				return false;

			if (IsInPlantDefence())
				return false;

			return m_plantFramework->CanApplyPlantfood();
		}
	}

	return false;
}

void Plant::KillPlant(bool bSelfKill, bool bInstantKill, DamageTypeFlags i_lastDamageType)
{
	if (IsDestroyed())
		return;

	m_lastDamageType = i_lastDamageType;
	m_PlantHealth = 0;
	m_plantFramework->onKilled(bInstantKill);

	if (HasCondition(PCONDITION_GroupIcecubed) && m_holoPlant.IsValid())
	{
		m_holoPlant.Get()->KillPlant(true, false);
		m_holoPlant.ClearId();
	}

	m_conditionTracker.ClearConditions(this);

	if (IsDelayDestroy())
		return;

	PostDeadMessage(bSelfKill);
	Destroy();
}

void Plant::SetInvincible(bool is_invincible, bool is_needEffect, pvztime_t i_time)
{
	m_bIsInvincible = is_invincible;

	if (is_invincible)
	{
		m_InvincibleTime = PVZ_T() + i_time;

		if (is_needEffect)
		{
			AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate("cureshield");
			effect.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_PEACH_SHIELD"));
			effect.PlayAnimLooped("peach_shield");
			effect.Attach(this, SexyVector3(0.0f, 0.0f, 0.0f), 1);
		}
	}
}

/////////////// Plant -- misc small (2) ///////////////

void Plant::FadeIn(pvztime_t i_duration)
{
	m_fadeInDuration = i_duration;
	m_fadeInEndTime = PVZ_T() + i_duration;
}

bool Plant::IsSkillActivate()
{
	if (m_skillProbability == 0)
		return false;

	m_skillProbIndex = (m_skillProbIndex + 1) % m_skillProbability;
	return m_skillProbIndex == m_skillProbability - 1;
}

int Plant::Rand()
{
	if (NewPVPUtils::IsPlayingNewPVP() && m_randomObject)
		return m_randomObject->Next();

	return Sexy::Rand();
}

int Plant::Rand(int range)
{
	if (NewPVPUtils::IsPlayingNewPVP() && m_randomObject)
		return m_randomObject->Next((unsigned long)range);

	return Sexy::Rand(range);
}

float Plant::Rand(float range)
{
	if (NewPVPUtils::IsPlayingNewPVP() && m_randomObject)
		return m_randomObject->Next(range);

	return Sexy::Rand(range);
}

void Plant::resetSlingShot()
{
	if (m_perSlingShotDamage != 0.0f)
	{
		m_slingShotTimer = PVZ_T() + 5.0f;
		m_slingShotCounter = 0.0f;
	}
}

void Plant::SetHighlighted(bool i_highlighted)
{
	if (i_highlighted)
		ApplyCondition(PCONDITION_Highlighted, PVZ_EOT(), 0);
	else
		EndCondition(PCONDITION_Highlighted);
}

void Plant::SetUpgradePercent(float i_upgrade_percent)
{
	m_upgrade_percent = i_upgrade_percent;
	if (m_lastUpgradepercent < 0.5f)
		m_lastUpgradepercent = i_upgrade_percent;
	m_upgradeSetTime = PVZ_T();
}

void Plant::Heal()
{
	m_PlantLastHealth = m_PlantHealth;
	m_PlantHealth = GetMaxHealth();
	UpdateDamageStates();
	m_plantFramework->onHealed();
}

bool Plant::HasTag(const std::string& i_tag)
{
	return m_tags.find(i_tag) != m_tags.end();
}

bool Plant::IsInHomeWorld()
{
	return GetType()->IsInHomeWorld();
}

void Plant::onEndCondition(PlantConditions i_condition)
{
	switch (i_condition)
	{
	case PCONDITION_MoreSlowDown:
		m_speedModifier = m_conditionTracker.GetSpeedModifier();
		break;
	case PCONDITION_DripWater:
		m_speedModifier = m_baseSpeedModifier;
		break;
	default:
		break;
	}

	m_plantFramework->onEndCondition(i_condition);
}

/////////////// Plant -- more accessors ///////////////

void Plant::SetIsControlled(bool i_controlled)
{
	m_isControlled = i_controlled;
}

bool Plant::IsControlled()
{
	return m_isControlled;
}

float Plant::GetPoisonBoost()
{
	return m_improvePoison;
}

void Plant::SetShowUpgrade(bool i_show_upgrade)
{
	m_show_upgrade = i_show_upgrade;
}

void Plant::SetAvatarActive(bool bActive)
{
	m_bAvatarActive = bActive;
}

void Plant::setShowShadowBoost(bool isShowShadowBoost)
{
	m_bIsShowShadowBoost = isShowShadowBoost;
}

void Plant::SetTupleSpellPlantFood(bool bTupleSpell)
{
	m_bIsTupleSpellPlantFood = bTupleSpell;
}

bool Plant::IsSkillCheat()
{
	return m_bCheatSkill;
}

void Plant::DelTag(const std::string& i_tag)
{
	m_tags.erase(i_tag);
}

void Plant::ClearTag()
{
	m_tags.clear();
}

bool Plant::IsSwapping()
{
	return m_conditionTracker.HasCondition(PCONDITION_Swapping);
}

bool Plant::IsIceblocked()
{
	return m_conditionTracker.HasCondition(PCONDITION_Icecubed);
}

void Plant::ClearConditions()
{
	m_conditionTracker.ClearConditions(this);
}

void Plant::OnUseSpecialAnimCommand(pvztime_t i_timeStamp)
{
	if (m_row == -1)
		return;
	if (m_column == -1)
		return;

	DoSpecial();
}

bool Plant::TryBlockZombossRush(Zombie* i_zomboss)
{
	return m_plantFramework->TryBlockZombossRush(i_zomboss);
}

void Plant::SetAttackUpValue(bool bAttackUp, pvztime_t tAttackUpTime, float iAppendPercent)
{
	m_bIsAttackUp = bAttackUp;
	m_iAppendAttackUpPercent = iAppendPercent;

	if (bAttackUp)
		m_tAttackUpTime = PVZ_T() + tAttackUpTime;
	else
		m_tAttackUpTime = PVZ_EOT();
}

void Plant::SetAttackUpConstValue(bool bAttackUp, pvztime_t tAttackUpTime, float iAppendConstValue)
{
	m_bIsAttackUpConstValue = bAttackUp;
	m_iAppendAttackUpConstValue = iAppendConstValue;

	if (!bAttackUp)
		tAttackUpTime = PVZ_EOT();
	m_tAttackUpConstValueTime = tAttackUpTime;
}

bool Plant::CanLevelUp(int i_targetLevel)
{
	return m_type->GetProps()->MaxLevel >= i_targetLevel;
}

void Plant::addRelocationEvent(const RelocationEvent& i_event)
{
	m_relocationEvents.push_back(i_event);
}

Sexy::Rect Plant::GetPlantAttackRect(PlantWeapon i_plantWeapon)
{
	return m_plantFramework->GetPlantAttackRect(i_plantWeapon);
}

AttachedEffect& Plant::AddAttachedEffect(const char* iEffectName, const char* iPanAnimName,
                                         const char* iAnimName, const SexyVector3& iOffset,
                                         int iRenderLayerOffset, bool playOnce)
{
	AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate(iEffectName);
	effect.InitializeWithAnimation(GetPAMByName(iPanAnimName));

	if (!playOnce)
		effect.PlayAnimLooped(iAnimName);
	else
		effect.PlayAnimAndDestroy(iAnimName);

	effect.Attach(this, iOffset, iRenderLayerOffset);

	return effect;
}

void Plant::PlayAttackUpEffect()
{
	AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate("attackup");
	effect.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_PEACH_ATTACK_UP"));
	effect.PlayAnimAndDestroy("attack_up");
	effect.Attach(this, SexyVector3(0.0f, 0.0f, 0.0f), 1);
}

void Plant::PlaySongEffect(int level)
{
	AttachedEffect& up = (AttachedEffect&)m_attachedEffects.FindOrCreate("song_effect_up");
	up.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_BIRTHSUNFLOWER_TX"));
	std::string anim = level < 2 ? "attack2" : "attack4";
	up.PlayAnimAndDestroy(anim);
	up.Attach(this, SexyVector3(0.0f, -15.0f, 0.0f), 1);

	AttachedEffect& down = (AttachedEffect&)m_attachedEffects.FindOrCreate("song_effect_down");
	down.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_BIRTHSUNFLOWER_TX"));
	anim = level < 2 ? "attack1" : "attack3";
	down.PlayAnimAndDestroy(anim);
	down.Attach(this, SexyVector3(0.0f, -15.0f, 0.0f), -1);
}

SexyString Plant::GetFormattedNameString(PlantTypePtr i_seedType)
{
	std::string formatted = StrFormat("[%s]", StringToUpper(i_seedType->TypeName).c_str());
	return TodStringTranslate(StringToWString(formatted));
}

SexyString Plant::GetFormattedToolTip(PlantTypePtr i_seedType)
{
	std::string formatted = StrFormat("[%s_TOOLTIP]", StringToUpper(i_seedType->TypeName).c_str());
	return TodStringTranslate(StringToWString(formatted));
}

SexyString Plant::GetFormattedDescription(PlantTypePtr i_seedType)
{
	std::string formatted = StrFormat("[%s_DESCRIPTION]", StringToUpper(i_seedType->TypeName).c_str());
	return TodStringTranslate(StringToWString(formatted));
}

SexyString Plant::GetFormattedDescriptionHeader(PlantTypePtr i_seedType)
{
	std::string formatted = StrFormat("[%s_DESCRIPTION_HEADER]", StringToUpper(i_seedType->TypeName).c_str());
	return TodStringTranslate(StringToWString(formatted));
}

int Plant::GetWidth() const
{
	return BoardConstants::GRIDSQUARE_WIDTH() * 0.8f;
}

Sexy::SexyVector3 Plant::GetStunnedEffectOffset() const
{
	return Sexy::SexyVector3(0.0f, 0.0f, 35.0f);
}

bool Plant::IsVine() const
{
	return m_plantFramework && m_plantFramework->IsVine();
}

void Plant::SetInPvz1SleepAction()
{
	m_inPvz1SleepAction = true;
	m_pvz1SleepRate = 3;
	m_pvz1SleepTimer = 0.0f;
}

void Plant::StartExternalRemoval()
{
	m_state = STATE_BEINGREMOVED;
	gMessageRouter->Broadcast(Message::PlantDestory, this);
	m_isOnBoard = false;
	m_row = -1;
}

void Plant::SetGridLoc(int i_gridX, int i_gridY)
{
	SetGridLocSilent(i_gridX, i_gridY);
	gMessageRouter->Broadcast(Message::PlantPlaced, this);
}

void Plant::NotifyConditionEvent(PlantConditions i_condition)
{
	switch (i_condition)
	{
	case PCONDITION_Squidified:
		SetHidden(true);
		break;
	case PCONDITION_GroupSquidified:
		m_holoShinny = true;
		break;
	default:
		break;
	}
}

RelocationEvent Plant::GetRelocating() const
{
	return m_curRelocationEvent;
}

Sexy::SexyVector3 Plant::GetRelocationPosition() const
{
	return Sexy::SexyVector3(
		m_curRelocationEvent.m_relocationOffsetFromDestination.x + m_curRelocationEvent.m_relocateToX,
		m_curRelocationEvent.m_relocationOffsetFromDestination.y + m_curRelocationEvent.m_relocateToY,
		0.0f);
}

bool Plant::IsWatering()
{
	return m_pCachedPlantAnimRig->GetState() == PLANTANIM_WATER;
}

SexyVector2 Plant::GetRelocationBoardSpaceOffsetFromDestination()
{
	updateRelocationPositionAndRotation();
	return m_curRelocationEvent.m_relocationOffsetFromDestination;
}

bool Plant::IsOnBoardGrid()
{
	if (!m_isOnBoard)
		return false;
	if (m_row < 0)
		return false;
	if (m_row >= BoardConstants::NUMBER_OF_ROWS())
		return false;
	if (m_column < 0)
		return false;

	return m_column < BoardConstants::NUMBER_OF_COLUMNS();
}

void Plant::DoProjectileCombo()
{
	m_plantFramework->DoProjectileCombo();
}

void Plant::UpdateRelocationPositionAndRotation()
{
	updateRelocationPositionAndRotation();
}

void Plant::SetPlantfoodShineColor(const Color& i_color)
{
	if (m_shouldUseStarPFEffect)
		m_pCachedEffectAnimRig_StarPlantFoodShine->SetPAMColor(i_color);
	else
		m_pCachedEffectAnimRig_PlantFoodShine->SetPAMColor(i_color);
}

bool PlantType::CanPlantOnPlant(Plant* i_plant) const
{
	return canGiveFirstAidToPlant(i_plant);
}

void Plant::SetIsDuplicatePlant(bool i_duplicate)
{
	m_isDuplicate = i_duplicate;
	m_plantFramework->onSetDuplicate(i_duplicate);
}

void Plant::OnApplyZombieCondition(Zombie* i_zombie, ZombieConditionsStruct& i_conditionsStruct)
{
	i_conditionsStruct.Duration *= GetZombieConditionExtendRate(i_conditionsStruct.Condition);
}

void Plant::ClearFrost()
{
	m_frostInfo.Clear();
	EndCondition(PCONDITION_FrostStage1);
	EndCondition(PCONDITION_FrostStage2);
}

Sexy::Point Plant::GetCenterPt()
{
	const Sexy::Rect& rect = GetCollisionRect();
	return Sexy::Point(rect.mX + rect.mWidth / 2, rect.mY + rect.mHeight / 2);
}

void Plant::SetPosition(const Sexy::SexyVector3& i_newPosition)
{
	if (m_plantFramework)
		m_plantFramework->OnSetPosition(m_position, i_newPosition);

	BoardEntity::SetPosition(i_newPosition);
}

void Plant::SetSpeedModifier(float i_modifier)
{
	m_speedModifier = i_modifier;
	GetAnimRig()->SetAnimRateOverride(m_speedModifier + GetAdditionValue(PlantAddition::PAdditonRLS_SPD_Add));
}

void Plant::SetIsPreviewPlant()
{
	m_pCachedPlantAnimRig->SetPaused(false);
}

void Plant::PlayAttackAnimation()
{
	m_pCachedPlantAnimRig->PlayAttack();
}

void Plant::ChangeSpeedModifier(float i_modifier, float i_time)
{
	if (m_speedChangeTime < 0.0f)
		SetSpeedModifier(i_modifier);

	m_speedChangeTime = PVZ_T() + i_time;
}

void Plant::updateUBoost()
{
	if (m_uBoostInfo.m_uBoostDamagePerHit > 0.0f && PVZ_T() >= m_uBoostInfo.m_uBoostDisabledTime)
	{
		m_uBoostInfo.m_uBoostDamageTotal = 0.0f;
		m_uBoostInfo.m_uBoostDisabledTime = PVZ_EOT();
	}
}

void Plant::RecoverFastCoolDownRatio()
{
	int id = PlantNameMapper::GetInstance().GetIdForType(m_type);
	float boost = PlantBoostMgr::GetInstance().GetPlantBoostValue(id, FAST_COOLDOWN);
	m_reducedCooldown = 1.0f / (1.0f + boost);
}

void Plant::SetFastCoolDownRatio(float ratio)
{
	int id = PlantNameMapper::GetInstance().GetIdForType(m_type);
	float boost = PlantBoostMgr::GetInstance().GetPlantBoostValue(id, FAST_COOLDOWN);
	m_reducedCooldown = 1.0f / (ratio + 1.0f + boost);
}

void Plant::UpdateShooter()
{
	if (PVZ_T() > m_launchTime)
	{
		ResetLaunchTimer(false);
		m_plantFramework->FindTargetAndFire((PlantWeapon)0);
	}
}

void Plant::onLevelUp(int i_targetLevel)
{
	Heal();
	CreateLevelEffect();

	if (i_targetLevel == 4)
		m_plantFramework->TriggerBoost();
}

void Plant::onLevelUpFailed(int i_targetLevel)
{
	if (m_type->GetProps()->MaxLevel < i_targetLevel)
		m_plantFramework->TriggerBoost();
}

void Plant::SetCurrentLevel(int i_level)
{
	if (m_type->GetProps()->MaxLevel < i_level)
	{
		BoardEntity::SetCurrentLevel(m_type->GetProps()->MaxLevel);
		return;
	}

	if (i_level < m_type->GetProps()->MinLevel)
	{
		BoardEntity::SetCurrentLevel(m_type->GetProps()->MinLevel);
		return;
	}

	BoardEntity::SetCurrentLevel(i_level);
}

int Plant::GetMaxAffectZombieLevel()
{
	int idx = GetCurrentLevel() - 1;
	if (idx >= 0 && (size_t)idx < GetProps()->PlantLevelStats.size())
		return GetProps()->PlantLevelStats[idx].MaxAffectZombieLevel;

	return 1;
}

float Plant::GetExtraHitPointsmodifier() const
{
	int idx = GetCurrentLevel() - 1;
	if (idx >= 0 && (size_t)idx < GetProps()->PlantLevelStats.size())
		return GetProps()->PlantLevelStats[idx].HitPointsLevel;

	return 1.0f;
}

bool Plant::WasKilledByZombies()
{
	bool result = false;
	if (!TestFlag(m_lastDamageType, DAMAGE_NON_ZOMBIE))
		result = !(GetType()->TypeName == "magicbeans");

	return result;
}

void Plant::TakeNoMsgDied()
{
	AddTag("NoDiedMsg");
	gMessageRouter->Post(Message::PlantChallengeDied, this);
	KillPlant(false, false, DAMAGE_NONE);
}

void Plant::RemoveAttachedEffect(const char* iEffectName)
{
	m_attachedEffects.Remove(iEffectName);
}

float Plant::GetAdditionValue(PlantAddition::PAdditonRLS i_rule) const
{
	float total = 0.0f;
	for (size_t i = 0; i < m_addtions.size(); i++)
	{
		const PlantAddition& addition = m_addtions[i];
		if (addition.rls == i_rule)
			total += addition.value;
	}

	if (i_rule == PlantAddition::PAdditonRLS_ATK_Muti)
		return total + 1.0f;

	return total;
}

void Plant::TakeFatalDamage(const DamageInfo& i_damage)
{
	if (m_PlantHealth > 0.0f)
	{
		DamageInfo damage(i_damage);
		damage.Amount = m_PlantHealth;
		damage.Flags |= DAMAGE_FATAL;
		TakeDamage(damage);

		if (m_PlantHealth == 0.0f)
			KillPlant(false, false, DAMAGE_NONE);
	}
}

PlantPropsPtr Plant::GetProps() const
{
	return m_type->Properties;
}

Sexy::Point Plant::GetGridExtents() const
{
	return GetProps()->GridExtents;
}

Sexy::Rect Plant::CalcGridFootprint() const
{
	Sexy::Point pos = CalcGridPosition();
	Sexy::Point ext = GetGridExtents();

	if (ext.mX == 3 && ext.mY == 3)
		return Sexy::Rect(pos.mX - 1, pos.mY - 1, 3, 3);

	return Sexy::Rect(pos.mX, 1 - ext.mY + pos.mY, ext.mX, ext.mY);
}

void Plant::OnAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp,
                          const std::string& i_animCommand, const std::string& i_animCommandParam)
{
	if (m_row != -1 && m_column != -1)
		m_plantFramework->OnAnimCommand(i_animCommand, i_animCommandParam);
}

DamageInfo Plant::calcDamageInfoFromPlantAction(const PlantAction& i_action)
{
	DamageInfo damage;
	float dmg = (float)i_action.Damage;
	damage.Amount = GetTotalDamageRate() * dmg + GetDamageConstValue();
	damage.Instigator = this;

	if (i_action.Burns)
	{
		damage.Flags = DAMAGE_HITS_SHIELD_AND_BODY | DAMAGE_HAS_FIRE | DAMAGE_ASH_ON_DEATH;
	}
	else
	{
		if (i_action.ChillDuration != 0.0f)
			damage.AddCondition(ZCONDITION_Chilled, i_action.ChillDuration);

		if (i_action.FreezeDuration != 0.0f)
			damage.AddCondition(ZCONDITION_Frozen, i_action.FreezeDuration);
	}

	m_plantFramework->CustomizePlantActionDamage(i_action, damage);

	return damage;
}

void Plant::onDraw(Sexy::Graphics* i_g)
{
	m_plantFramework->Draw(i_g);
}

void Plant::UpdateAnimRig()
{
	if (m_pCachedPlantAnimRig)
	{
		m_plantFramework->UpdateAnimRig();
		m_pCachedPlantAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
}

void Plant::AddToRenderQueue(RenderQueue* i_queue)
{
	RealObject::AddToRenderQueue(i_queue);

	if (!IsHidden())
		m_plantFramework->AddToRenderQueue(i_queue);
}

bool Plant::ShouldDrawShadow() const
{
	if (!RealObject::ShouldDrawShadow())
		return false;
	if (!m_plantFramework->HasShadow())
		return false;
	if (m_state == 3)
		return false;

	return !IsHidden();
}

bool Plant::IsSuspended()
{
	return m_conditionTracker.TestModifierFlag(CMODIFIER_Suspended) || IsHidden();
}

bool Plant::CanFindTarget(PlantWeapon i_plantWeapon)
{
	return FindTarget(i_plantWeapon).IsValid();
}

bool Plant::CanFindTargetInRow(int i_row, PlantWeapon i_plantWeapon)
{
	return FindTargetInRow(i_row, i_plantWeapon).IsValid();
}

int Plant::GetActualCost()
{
	return m_actualCost;
}

void Plant::SetHoloPlant(Sexy::RtWeakPtr<Plant> i_holoPlant)
{
	m_holoPlant = i_holoPlant;
}

bool Plant::GetAvatarEnable()
{
	return m_bAvatarActive && m_bAvatar && m_avatarIndex >= 0;
}

bool Plant::IsConvertedByCondition()
{
	return HasCondition(PCONDITION_Sheeped)
		|| HasCondition(PCONDITION_Squidified)
		|| HasCondition(PCONDITION_Icecubed)
		|| HasCondition(PCONDITION_GroupSauced)
		|| HasCondition(PCONDITION_GroupTrappedInNet)
		|| HasCondition(PCONDITION_GroupSheeped)
		|| HasCondition(PCONDITION_Sauced)
		|| HasCondition(PCONDITION_GroupPlantfooded);
}
