//
//  Zombie.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-03.
//

#include "StateMachineTableBuilder.h"
#include "Zombie.h"

#include "TimeMgr.h"
#include "PlantGroup.h"
#include "Board.h"
#include "BoardTransforms.h"
#include "GridItemArmrack.h"
#include "GridItemFlame.h"
#include "Plant_StreetLamp.h"
#include "BoardPropertySheet.h"
#include "LawnApp.h"
#include "DangerRoomModule.h"
#include "DangerRoomManager.h"
#include "NewPVPUtils.h"
#include "Zomboss.h"
#include "ZombieZombossMech.h"
#include "TodLib/TodStringFile.h"

// classes: Zombie, ZombiePropertySheet, ZombieType
// 543 function(s), 152704 B to reconstruct. Drop a TODO line as its function matches.
//
// TODO  17712 B  Zombie::NotifyApplyCondition                         _ZN6Zombie20NotifyApplyConditionE16ZombieConditions
// TODO   6680 B  Zombie::StaticClassInit                              _ZN6Zombie15StaticClassInitEv
// TODO   5292 B  Zombie::NotifyEndCondition                           _ZN6Zombie18NotifyEndConditionE16ZombieConditions
// TODO   4464 B  Zombie::onUpdate                                     _ZN6Zombie8onUpdateEv
// TODO   3592 B  Zombie::TakeDamage                                   _ZN6Zombie10TakeDamageERK10DamageInfo
// TODO   3516 B  Zombie::onDraw                                       _ZN6Zombie6onDrawEPN4Sexy8GraphicsE
// TODO   3472 B  ZombiePropertySheet::StaticClassInit                 _ZN19ZombiePropertySheet15StaticClassInitEv
// TODO   1808 B  Zombie::ApplyCondition                               _ZN6Zombie14ApplyConditionE16ZombieConditionsffb
// TODO   1608 B  Zombie::DoSpecial                                    _ZN6Zombie9DoSpecialEv
// TODO   1448 B  Zombie::updateResilienceBar                          _ZN6Zombie19updateResilienceBarEv
// TODO   1364 B  Zombie::takeBodyDamage                               _ZN6Zombie14takeBodyDamageERK10DamageInfo
// TODO   1332 B  Zombie::initResilienceBar                            _ZN6Zombie17initResilienceBarEv
// TODO   1316 B  Zombie::ZombieInitialize                             _ZN6Zombie16ZombieInitializeEN4Sexy9RtWeakPtrIK10ZombieTypeEEiiijRKSt6vectorISsSaISsEE
// TODO   1212 B  Zombie::findEatTarget                                _ZN6Zombie13findEatTargetEiN4Sexy5TRectIiEE
// TODO   1188 B  Zombie::onEnterState_RiseFromStorm                   _ZN6Zombie26onEnterState_RiseFromStormE11ZombieState
// TODO   1188 B  Zombie::onExitState_StormEntrance                    _ZN6Zombie25onExitState_StormEntranceE11ZombieState
// TODO   1152 B  Zombie::onEnterState_StormEntrance                   _ZN6Zombie26onEnterState_StormEntranceE11ZombieState
// TODO   1124 B  Zombie::onStreetLampChanged                          _ZN6Zombie19onStreetLampChangedEP14PlantFrameworki
// TODO   1108 B  Zombie::Zombie                                       _ZN6ZombieC2Ev
// TODO   1108 B  Zombie::Zombie                                       _ZN6ZombieC1Ev
// TODO   1012 B  Zombie::DrawHealthBarAndResilienceBar                _ZN6Zombie29DrawHealthBarAndResilienceBarEPN4Sexy8GraphicsE
// TODO    976 B  Zombie::CreateZombieLevelEffect                      _ZN6Zombie23CreateZombieLevelEffectEb
// TODO    964 B  Zombie::CheckSpeedUpTileTurnToDirection              _ZN6Zombie31CheckSpeedUpTileTurnToDirectionEv
// TODO    960 B  Zombie::processCardGameMoveToEnemy                   _ZN6Zombie26processCardGameMoveToEnemyEv
// TODO    936 B  Zombie::OverrideProjectileCollision                  _ZN6Zombie27OverrideProjectileCollisionEP10Projectile
// TODO    936 B  Zombie::updateState_Walk                             _ZN6Zombie16updateState_WalkEv
// TODO    924 B  Zombie::UpdateLeaderCondition                        _ZN6Zombie21UpdateLeaderConditionEv
// TODO    912 B  Zombie::UpdatePosition                               _ZN6Zombie14UpdatePositionEv
// TODO    884 B  Zombie::DropHead                                     _ZN6Zombie8DropHeadEv
// TODO    836 B  Zombie::UpdateDripWaterConditionDamage               _ZN6Zombie30UpdateDripWaterConditionDamageERK10DamageInfo
// TODO    824 B  Zombie::FlickOff                                     _ZN6Zombie8FlickOffERKN4Sexy11SexyVector3Eff
// TODO    796 B  Zombie::eatPlantGroup                                _ZN6Zombie13eatPlantGroupEP10PlantGroup
// TODO    776 B  ZombiePropertySheet::ZombiePropertySheet             _ZN19ZombiePropertySheetC2Ev
// TODO    776 B  ZombiePropertySheet::ZombiePropertySheet             _ZN19ZombiePropertySheetC1Ev
// TODO    748 B  Zombie::buildProjectileSets                          _ZN6Zombie19buildProjectileSetsEv
// TODO    736 B  Zombie::updateState_Besiege                          _ZN6Zombie19updateState_BesiegeEv
// TODO    728 B  Zombie::DrawTitles                                   _ZN6Zombie10DrawTitlesEPN4Sexy8GraphicsE
// TODO    724 B  Zombie::FlickOff                                     _ZN6Zombie8FlickOffERKN4Sexy11SexyVector3E
// TODO    712 B  Zombie::setNewPAM                                    _ZN6Zombie9setNewPAMESs
// TODO    712 B  Zombie::spreadBadSmell                               _ZN6Zombie14spreadBadSmellEv
// TODO    708 B  Zombie::findAttackTargets                            _ZN6Zombie17findAttackTargetsEv
// TODO    700 B  Zombie::updateOverlayEffects                         _ZN6Zombie20updateOverlayEffectsEv
// TODO    692 B  Zombie::DropArm                                      _ZN6Zombie7DropArmEv
// TODO    684 B  Zombie::onEnterState_ResilienceEnterBreak            _ZN6Zombie33onEnterState_ResilienceEnterBreakE11ZombieState
// TODO    680 B  Zombie::FindRangedTarget                             _ZN6Zombie16FindRangedTargetESt6vectorIN4Sexy9RtWeakPtrI11BoardEntityEESaIS4_EE
// TODO    680 B  Zombie::eatZombie                                    _ZN6Zombie9eatZombieEPS_
// TODO    680 B  Zombie::initializeAnimRigForType                     _ZN6Zombie24initializeAnimRigForTypeEN4Sexy9RtWeakPtrIK10ZombieTypeEE
// TODO    672 B  Zombie::DrawHealthBar                                _ZN6Zombie13DrawHealthBarEPN4Sexy8GraphicsE
// TODO    672 B  Zombie::doSpreadChemistPoison                        _ZN6Zombie21doSpreadChemistPoisonEii
// TODO    664 B  Zombie::eatPlant                                     _ZN6Zombie8eatPlantEP5Plant
// TODO    656 B  Zombie::onDrawShadow                                 _ZN6Zombie12onDrawShadowEPN4Sexy8GraphicsE
// TODO    640 B  Zombie::SetIsSleepping                               _ZN6Zombie14SetIsSleeppingEbf
// TODO    640 B  Zombie::TriggerTitleIconEffect                       _ZN6Zombie22TriggerTitleIconEffectEi
// TODO    636 B  Zombie::onPopAnimCommand                             _ZN6Zombie16onPopAnimCommandERKSsfS1_S1_
// TODO    624 B  Zombie::CalcExtraHpFactor                            _ZN6Zombie17CalcExtraHpFactorEv
// TODO    620 B  Zombie::eatTarget                                    _ZN6Zombie9eatTargetEP11BoardEntity
// TODO    612 B  Zombie::Gum                                          _ZN6Zombie3GumESsfP11BoardEntity
// TODO    608 B  Zombie::SetHasPlantFood                              _ZN6Zombie15SetHasPlantFoodEb
// TODO    580 B  Zombie::onEnterState_TakeWeapon                      _ZN6Zombie23onEnterState_TakeWeaponE11ZombieState
// TODO    580 B  Zombie::AddAttachedEffect                            _ZN6Zombie17AddAttachedEffectEPKcS1_S1_RKN4Sexy11SexyVector3Eib
// TODO    568 B  ZombieType::StaticClassInit                          _ZN10ZombieType15StaticClassInitEv
// TODO    564 B  Zombie::findArmrackTarget                            _ZN6Zombie17findArmrackTargetEv
// TODO    560 B  Zombie::onEnterState_IntroOnBoard                    _ZN6Zombie25onEnterState_IntroOnBoardE11ZombieState
// TODO    560 B  Zombie::spawnTransitionAnimation                     _ZN6Zombie24spawnTransitionAnimationEv
// TODO    556 B  Zombie::onElectrocuted                               _ZN6Zombie14onElectrocutedEv
// TODO    556 B  Zombie::onTurnedToAsh                                _ZN6Zombie13onTurnedToAshEv
// TODO    552 B  Zombie::CheckWarningRequest                          _ZN6Zombie19CheckWarningRequestEv
// TODO    544 B  Zombie::DropHelm                                     _ZN6Zombie8DropHelmEv
// TODO    540 B  Zombie::updateState_DropIntoIceHole                  _ZN6Zombie27updateState_DropIntoIceHoleEv
// TODO    540 B  Zombie::UpdateMinifyState                            _ZN6Zombie17UpdateMinifyStateEv
// TODO    532 B  Zombie::SetHasLeader                                 _ZN6Zombie12SetHasLeaderEbf
// TODO    532 B  Zombie::CheckAllStreetLamp                           _ZN6Zombie18CheckAllStreetLampEv
// TODO    528 B  Zombie::NotifyConditionEvent                         _ZN6Zombie20NotifyConditionEventE16ZombieConditions
// TODO    524 B  Zombie::onResilienceRecovered                        _ZN6Zombie21onResilienceRecoveredEv
// TODO    488 B  Zombie::updateState_StormEntrance                    _ZN6Zombie25updateState_StormEntranceEv
// TODO    488 B  Zombie::onLeaderConditionEnd                         _ZN6Zombie20onLeaderConditionEndEv
// TODO    488 B  Zombie::CheckResilience                              _ZN6Zombie15CheckResilienceERK10DamageInfo
// TODO    484 B  Zombie::updateState_StuckIntoGround                  _ZN6Zombie27updateState_StuckIntoGroundEv
// TODO    480 B  Zombie::CalcZombieAttackRect                         _ZN6Zombie20CalcZombieAttackRectEv
// TODO    476 B  Zombie::attackGridItem                               _ZN6Zombie14attackGridItemEN4Sexy9RtWeakPtrI8GridItemEE
// ... and 463 more (units.json)


void Zombie::EndLossLife()
{
	m_bIsLossLife = false;
	m_tLossLifeTime = PVZ_EOT();
	m_iLossLifePerFrame = 0;
}

ZombieConditionTracker& Zombie::GetConditionTracker()
{
	return m_conditionTracker;
}

void Zombie::ClearTargetHistory()
{
	m_targetHistory.clear();
}

void Zombie::DelTag(const std::string& i_tag)
{
	m_tags.erase(i_tag);
}

bool Zombie::IsSuspended()
{
	return m_conditionTracker.TestModifierFlag(CMODIFIER_Suspended);
}

bool Zombie::HasGravity()
{
	return true;
}

void Zombie::onLostHead()
{
}

void Zombie::onMowedDown()
{
}

class GameSubSystem* Zombie::GetSubSystem()
{
	return NULL;
}

void Zombie::playEatSound()
{
}

bool Zombie::CanBePulledHelm()
{
	return true;
}

void Zombie::onZombiePostLoad()
{
}

bool Zombie::CanApplyVenomStack()
{
	return true;
}

bool Zombie::hasArmParticle() const
{
	return true;
}

bool Zombie::hasHeadParticle() const
{
	return true;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Zombie);

bool Zombie::CanLevelUp(int i_targetLevel)
{
	return true;
}

ZombieParticle* Zombie::onHelmDropped(HelmType i_helmType, int i_helmHitpoints)
{
	return NULL;
}

void Zombie::SetIsFlagZombie(bool i_hasFlag)
{
}

bool Zombie::onCanTargetPlant(Plant* i_plant)
{
	return true;
}

void Zombie::onTakeBodyDamage(const DamageInfo& i_damageReceived)
{
}

void Zombie::onTakeHelmDamage(const DamageInfo& i_damageReceived)
{
}

Sexy::SexyVector3 Zombie::GetStunnedEffectOffset() const
{
	return Sexy::SexyVector3(0.0f, 0.0f, 35.0f);
}


void Zombie::onExitState_Ash(ZombieState i_arg)
{
}

void Zombie::onExitState_Attack(ZombieState i_arg)
{
}

void Zombie::onExitState_Besiege(ZombieState i_arg)
{
}

void Zombie::onExitState_BleedingOut(ZombieState i_arg)
{
}

void Zombie::onExitState_Die(ZombieState i_arg)
{
}

void Zombie::onExitState_DropIntoIceHole(ZombieState i_arg)
{
}

void Zombie::onExitState_Eat(ZombieState i_arg)
{
}

void Zombie::onExitState_Electrocute(ZombieState i_arg)
{
}

void Zombie::onExitState_FlickedOff(ZombieState i_arg)
{
}

void Zombie::onExitState_Glide(ZombieState i_arg)
{
}

void Zombie::onExitState_Grabbed(ZombieState i_arg)
{
}

void Zombie::onExitState_Idle(ZombieState i_arg)
{
}

void Zombie::onExitState_MowedDown(ZombieState i_arg)
{
}

void Zombie::onExitState_Plantify(ZombieState i_arg)
{
}

void Zombie::onExitState_ResilienceBreak(ZombieState i_arg)
{
}

void Zombie::onExitState_ResilienceEnterBreak(ZombieState i_arg)
{
}

void Zombie::onExitState_TakeWeapon(ZombieState i_arg)
{
}

void Zombie::onExitState_TargetRise(ZombieState i_arg)
{
}

void Zombie::onExitState_Winning(ZombieState i_arg)
{
}

void Zombie::onEnterState_Glide(ZombieState i_arg)
{
}

void Zombie::onEnterState_TargetRise(ZombieState i_arg)
{
}

void Zombie::updateState_Attack()
{
}

void Zombie::updateState_BleedingOut()
{
}

void Zombie::updateState_Grabbed()
{
}

void Zombie::updateState_IntroOnBoard()
{
}

void Zombie::updateState_ResilienceEnterBreak()
{
}

void Zombie::updateState_ResilienceRecover()
{
}

void Zombie::updateState_TakeWeapon()
{
}

void Zombie::updateState_TargetRise()
{
}


void Zombie::SetBesieged(bool i_besieged)
{
	m_isBesieged = i_besieged;
}

void Zombie::SetSizeType(ZombieSizeType i_sizeType)
{
	m_ZombieSizeType = i_sizeType;
}

void Zombie::SetHitpoints(float i_hitpoints)
{
	m_hitpoints = i_hitpoints;
}

void Zombie::SetStormType(StormType i_stormType)
{
	m_stormType = i_stormType;
}

void Zombie::SetBaseEatDPS(float i_dps)
{
	m_baseEatDPS = i_dps;
}

void Zombie::SetMergeLevel(int i_mergeLevel)
{
	m_mergeLevel = i_mergeLevel;
}

void Zombie::SetZombieScale(float i_scale)
{
	m_scale = i_scale;
}

void Zombie::SetDamageScale(float i_damageScale)
{
	m_damageScale = i_damageScale;
}

void Zombie::SetExtraEatDPS(float i_dps)
{
	m_extraEatDPS = i_dps;
}

void Zombie::SetPacketLevel(int i_packetLevel)
{
	m_packetLevel = i_packetLevel;
}

void Zombie::setHelmHitpoints(float i_helmHitpoints)
{
	m_helmHitpoints = i_helmHitpoints;
}

void Zombie::setStateMachineTimeScale(float i_scale)
{
	m_stateMachineTimeScale = i_scale;
}

float Zombie::GetZombieScale()
{
	return m_scale;
}

float Zombie::getStuckIntoGroundHeight()
{
	return m_stuckIntoGroundHeight;
}


void Zombie::SetSpeedScale(float i_speedScale)
{
	m_speedScale = i_speedScale;
	updateSpeed();
}

float Zombie::GetSpeedScale()
{
	return m_speedScale;
}

void Zombie::SetDpsScale(float i_dpsScale)
{
	m_dpsScale = i_dpsScale;
}

float Zombie::GetDpsScale() const
{
	return m_dpsScale;
}

float Zombie::GetMaxResilienceValue()
{
	return m_currentResilience.m_maxResilience;
}

void Zombie::SetIsFlying(bool i_flying)
{
	SetFlag(m_zombieFlags, ZFLAG_IsFlying, i_flying);
}

void Zombie::SetIsJumping(bool i_jumping)
{
	SetFlag(m_zombieFlags, ZFLAG_IsJumping, i_jumping);
}

void Zombie::SetSuppressDeath(bool i_suppressDeath)
{
	SetFlag(m_zombieFlags, ZFLAG_SuppressDeath, i_suppressDeath);
}

void Zombie::SetHasDroppedLoot(bool i_hasDroppedLoot)
{
	SetFlag(m_zombieFlags, ZFLAG_HasDroppedLoot, i_hasDroppedLoot);
}

void Zombie::SetIsFriendZombie(bool i_isFriendZombie)
{
	SetFlag(m_zombieFlags, ZFLAG_FriendZombie, i_isFriendZombie);
}

void Zombie::SetIgnoreFindTarget(bool i_isIgnore)
{
	SetFlag(m_zombieFlags, ZFLAG_IgnoreFindTarget, i_isIgnore);
}

void Zombie::SetIgnoresAllDamage(bool i_ignoreDamage)
{
	SetFlag(m_zombieFlags, ZFLAG_IgnoreAllDamage, i_ignoreDamage);
}

void Zombie::SetIgnoresCollisions(bool i_ignoresCollisions)
{
	SetFlag(m_zombieFlags, ZFLAG_IgnoresCollisions, i_ignoresCollisions);
}

void Zombie::SetIsParkourJumping(bool i_parkourJumping)
{
	SetFlag(m_zombieFlags, ZFLAG_IsParkourJumping, i_parkourJumping);
}

void Zombie::SetIsPulledByBeachZomboss(bool i_pulled)
{
	SetFlag(m_zombieFlags, ZFLAG_IsPulledByBeachZomboss, i_pulled);
}

void Zombie::SetIsBeingPulledByOlivePit(bool i_pulled)
{
	SetFlag(m_zombieFlags, ZFLAG_BeingSuckedIntoEndlessPitOfDespair, i_pulled);
}

void Zombie::SetAnimIgnoreConditionColors(bool i_ignoresColors)
{
	SetFlag(m_zombieFlags, ZFLAG_AnimIgnoreConditionColors, i_ignoresColors);
}

void Zombie::setIsTorchBurningFlag(bool i_isBurning)
{
	SetFlag(m_zombieFlags, ZFLAG_IsTorchBurning, i_isBurning);
}

bool Zombie::IsControlled() const
{
	return TestFlag(m_zombieFlags, ZFLAG_Controlled);
}

bool Zombie::HasTorch() const
{
	return TestFlag(m_zombieFlags, ZFLAG_HasTorch);
}

bool Zombie::DoesIgnoresCollisions() const
{
	return TestFlag(m_zombieFlags, ZFLAG_IgnoresCollisions);
}

bool Zombie::GetHasDroppedLoot() const
{
	return TestFlag(m_zombieFlags, ZFLAG_HasDroppedLoot);
}

bool Zombie::IsFlying() const
{
	return TestFlag(m_zombieFlags, ZFLAG_IsFlying);
}

bool Zombie::IsFriendZombie() const
{
	return TestFlag(m_zombieFlags, ZFLAG_FriendZombie);
}

bool Zombie::IsIgnoreFindTarget() const
{
	return TestFlag(m_zombieFlags, ZFLAG_IgnoreFindTarget);
}

bool Zombie::IsIgnoringAllDamage() const
{
	return TestFlag(m_zombieFlags, ZFLAG_IgnoreAllDamage);
}

bool Zombie::IsJumping() const
{
	return TestFlag(m_zombieFlags, ZFLAG_IsJumping);
}

bool Zombie::IsMowDownByMower() const
{
	return TestFlag(m_zombieFlags, ZFLAG_MowDownByMower);
}

bool Zombie::IsNotTargetableFlagSet() const
{
	return TestFlag(m_zombieFlags, ZFLAG_NotTargetable);
}

bool Zombie::IsParkourJumping() const
{
	return TestFlag(m_zombieFlags, ZFLAG_IsParkourJumping);
}

bool Zombie::IsSuppressingDeath() const
{
	return TestFlag(m_zombieFlags, ZFLAG_SuppressDeath);
}

bool Zombie::IsTorchBurning() const
{
	return TestFlag(m_zombieFlags, ZFLAG_IsTorchBurning);
}

bool Zombie::IsWinningZombie() const
{
	return TestFlag(m_zombieFlags, ZFLAG_WinningZombie);
}

void Zombie::SetIdleState()
{
	setZombieState(ZS_Idle, false);
}

void Zombie::SetWalkingState()
{
	setZombieState(ZS_Walk, false);
}

void Zombie::SetBesiegeHit(int i_hit)
{
	if (i_hit > 0)
		m_besiegeHit = i_hit;
}

void Zombie::AddBarrageXItem(int i_gridX, int i_por)
{
	m_GlideXWeights.AddItem(i_gridX, i_por);
}

void Zombie::AddBarrageYItem(int i_gridY, int i_por)
{
	m_GlideYWeights.AddItem(i_gridY, i_por);
}

bool Zombie::IsInZombieFoodState()
{
	return m_isInZombieFood;
}

void Zombie::StartPerformingSkills()
{
	m_canPerformSkill = true;
}

void Zombie::StopPerformingSkills()
{
	m_canPerformSkill = false;
}

bool Zombie::canTargetEntityHeight(BoardEntityHeight i_entityHeight)
{
	return i_entityHeight > 0;
}

Loot Zombie::GetLoot()
{
	return m_loot;
}

void Zombie::SetLoot(Loot i_loot)
{
	m_loot = i_loot;
}

void Zombie::SetMaxResilienceValue(float i_value)
{
	m_currentResilience.m_maxResilience = i_value;
}

void Zombie::SetTranslationMultiplier(float i_newMultiplier)
{
	m_translationMultiplier = i_newMultiplier;
}

void Zombie::BreakResilience()
{
	setZombieState(ZS_ResilienceEnterBreak, false);
}

void Zombie::SetGrabbedState()
{
	setZombieState(ZS_Grabbed, false);
}

void Zombie::onStartBleeding()
{
	setZombieState(ZS_BleedingOut, false);
}

void Zombie::onResilienceBreakAnimStopped(const std::string& i_animLabel)
{
	setZombieState(ZS_ResilienceBreak, false);
}

void Zombie::ClearTag()
{
	m_tags.clear();
}

AttachedBoardEntityNode* Zombie::GetOrCreateAttachedBoardEntity(const std::string& i_entityName)
{
	return static_cast<AttachedBoardEntityNode*>(&m_attachedBoardEntities.FindOrCreate(i_entityName));
}

void Zombie::ApplyNumb(pvztime_t i_time)
{
	ApplyCondition(ZCONDITION_Numb, i_time, 0.0f, true);
}

void Zombie::ApplyStun(pvztime_t i_time)
{
	ApplyCondition(ZCONDITION_Stunned, i_time, 0.0f, true);
}

void Zombie::endRushOnScreen()
{
	m_conditionTracker.EndCondition(this, ZCONDITION_RushOnscreen);
}

EEliminateType Zombie::GetEliminateColor()
{
	return m_eliminateColor;
}

ZombieResistenceType Zombie::GetCurrentResilienceWeakType()
{
	return m_currentResilience.m_weakType;
}

void Zombie::AddToRenderQueue(RenderQueue* i_queue)
{
	RealObject::AddToRenderQueue(i_queue);
}

ZombieSizeType Zombie::GetSizeType() const
{
	return m_ZombieSizeType;
}

bool Zombie::HasCondition(ZombieConditions i_condition) const
{
	return m_conditionTracker.HasCondition(i_condition);
}

bool Zombie::IsFlickedOff() const
{
	return isInState(ZS_FlickedOff);
}

bool Zombie::IsBleedingOut() const
{
	return isInState(ZS_BleedingOut);
}

bool Zombie::IsDropingIntoHole() const
{
	return isInState(ZS_DropIntoIceHole);
}

bool Zombie::IsRisingFromGround() const
{
	return isInState(ZS_RiseFromGround);
}

bool Zombie::IsEliteZombie() const
{
	return m_isEliteZombie;
}

InvisibleState Zombie::GetInvisibleState() const
{
	return m_invisibleState;
}

float Zombie::getStateMachineTimeScale() const
{
	return m_stateMachineTimeScale;
}

float Zombie::GetTranslationMultiplier() const
{
	return m_translationMultiplier;
}

bool Zombie::CanEliteScaleByZombie() const
{
	return m_enableEliteScale;
}

bool Zombie::CanShowHealthBarByDamage() const
{
	return m_enableShowHealthBarByDamage;
}

bool Zombie::CanNoInvincibleTakeDamage() const
{
	return m_enableNoInvincibleTakeDamage;
}

bool Zombie::CanEliteImmunittiesByZombie() const
{
	return m_enableEliteImmunities;
}

void Zombie::EndCondition(ZombieConditions i_condition)
{
	m_conditionTracker.EndCondition(this, i_condition);
}

void Zombie::SetDamageFlash(float i_duration)
{
	m_conditionTracker.ApplyCondition(this, ZCONDITION_DamageFlash, i_duration, 0.0f);
}

void Zombie::SetIsTargetable(bool i_isTargetable)
{
	SetFlag(m_zombieFlags, ZFLAG_NotTargetable, !i_isTargetable);
}

void Zombie::RefreshLastHealth()
{
	m_ZombieLastHealth = m_helmHitpoints + m_hitpoints;
}

MATH_TYPE Zombie::GetFacingMultiplier() const
{
	return m_facing == ZFACING_Left ? 1.0f : -1.0f;
}

bool Zombie::HasReachMaxResilienceValue()
{
	return m_currentResilience.m_currentResilience >= m_currentResilience.m_maxResilience;
}

void Zombie::StartRushOnScreen()
{
	m_conditionTracker.ApplyCondition(this, ZCONDITION_RushOnscreen, FLT_MAX, 0.0f);
}

void Zombie::AddTag(const std::string& i_tag)
{
	m_tags.insert(i_tag);
}

bool Zombie::GetHasLeader() const
{
	return m_conditionTracker.HasCondition(ZCONDITION_Leader);
}

bool Zombie::GetHasPlantFood() const
{
	return m_conditionTracker.HasCondition(ZCONDITION_HasPlantfood);
}

pvztime_t Zombie::getTimeInState() const
{
	return m_elapsedTimeInState;
}

void Zombie::SetBesiegeRate(float i_rate)
{
	if (i_rate >= 0.001f)
		m_besiegeRate = i_rate;
}

bool Zombie::HasArm() const
{
	return !TestFlag(m_zombieFlags, ZFLAG_LostArm);
}

bool Zombie::HasHead() const
{
	return !TestFlag(m_zombieFlags, ZFLAG_LostHead);
}

bool Zombie::IsInvisible() const
{
	return m_invisibleState == Invisible_Not_Detected && !m_canBeTargetedWhenInvisible;
}

GroundEffectType Zombie::GetTideEffect() const
{
	return TestFlag(m_zombieFlags, ZFLAG_IsPulledByBeachZomboss) ? (GroundEffectType)5 : (GroundEffectType)0;
}

bool Zombie::IsSlowed()
{
	return m_conditionTracker.GetSpeedModifier() < 1.0f;
}

bool Zombie::isInState(uint32 i_state) const
{
	return getState() == i_state;
}

bool Zombie::IsInSandStorm() const
{
	return (unsigned)(getState() - ZS_RiseFromStorm) <= 1;
}

bool Zombie::CanEliteImmuneCondition() const
{
	return GetEliteZombieType() != 1;
}

bool Zombie::HasReachResilienceDamageThreshold()
{
	return m_currentResilience.m_currentDamageAccumulation >= GetDamageThreshold();
}

void Zombie::reenterZombieState()
{
	m_stateMachine.ReenterState();
	m_elapsedTimeInState = 0.0;
}

void Zombie::onInitialized()
{
	BoardEntity::onInitialized();
	m_accumulatedTime = 0.0f;
}

void Zombie::AddStuckTime(float extendedTime)
{
	if (m_isStuckedUnderGround)
	{
		m_stuckUnderGroundTime += extendedTime;
		m_stuckIntoGroundTime += extendedTime;
	}
}

float Zombie::GetAmberScale()
{
	return (unsigned)GetSizeType() <= 1 ? 0.7f : 1.0f;
}

bool Zombie::CanDropArm() const
{
	return HasArm() && getArmDropFraction() >= 0.0f;
}

bool Zombie::CanDropHead() const
{
	return HasHead() && getHeadDropFraction() >= 0.0f;
}

bool Zombie::CanSurrender() const
{
	return GetProps()->CanSurrender;
}

bool Zombie::ExplodesWhenMowed() const
{
	return GetProps()->ExplodesWhenMowed;
}

bool Zombie::NormalDeathWhenMowed() const
{
	return GetProps()->NormalDeathWhenMowed;
}

int Zombie::GetLimitDamage() const
{
	return GetProps()->HurtDamageLimit;
}

bool Zombie::CanInvokeInvisible()
{
	return GetProps()->CanInvokeInvisible;
}

float Zombie::getArmDropFraction() const
{
	return GetProps()->ArmDropFraction;
}

float Zombie::getHeadDropFraction() const
{
	return GetProps()->HeadDropFraction;
}

void Zombie::SetMarkedForDeath()
{
	SetFlag(m_zombieFlags, ZFLAG_MarkedForDeath, true);
}

void Zombie::RemoveMarkedForDeath()
{
	SetFlag(m_zombieFlags, ZFLAG_MarkedForDeath, false);
}

void Zombie::SetTargetPosition(const SexyVector3& i_position)
{
	m_TargetPosition = i_position;
}

const SexyVector3& Zombie::GetTargetPosition()
{
	return m_TargetPosition;
}

void Zombie::ResetTargetPostion()
{
	m_TargetPosition.x = 0.0f;
	m_TargetPosition.y = 0.0f;
	m_TargetPosition.z = 0.0f;
}

void Zombie::SetZombieFlag(ZombieFlags i_flag, bool i_value)
{
	SetFlag(m_zombieFlags, i_flag, i_value);
}

ZombieFlags& Zombie::GetFlag()
{
	return m_zombieFlags;
}

AttachedEffectManager& Zombie::GetAttachedEffects()
{
	return m_attachedEffects;
}

AttachedEffectManager& Zombie::GetAttachedEffectManager()
{
	return m_attachedEffects;
}

AttachedBoardEntityManager& Zombie::GetAttachedBoardEntityManager()
{
	return m_attachedBoardEntities;
}

PlaybackController& Zombie::GetPlaybackController()
{
	return m_playbackController;
}

void Zombie::SetOriginalZombie(ZombiePtr i_zombie)
{
	m_originalZombie = i_zombie;
}

const std::vector<BoardEntityPtr>& Zombie::GetTargetHistory()
{
	return m_targetHistory;
}

const std::vector<BoardEntityPtr>& Zombie::GetTargetbyMaybee()
{
	return m_beTargetbyMaybee;
}

void Zombie::SetConditionTracker(ZombieConditions i_condition, float i_additionalValue)
{
	m_conditionTracker.SetAdditionalValue(i_condition, i_additionalValue);
}

void Zombie::SetExtraConditionTracker(ZombieConditions i_condition, float i_additionalValue)
{
	m_conditionTracker.SetExtraAdditionalValue(i_condition, i_additionalValue);
}

void Zombie::SetExtraConditionTracker2(ZombieConditions i_condition, float i_additionalValue)
{
	m_conditionTracker.SetExtraAdditionalValue2(i_condition, i_additionalValue);
}

void Zombie::SetElectrocuteColor(const std::string& i_color)
{
	m_electrocuteColor = i_color;
}

void Zombie::setBlinkOnDamage(bool i_blinkOnDamage)
{
	SetFlag(m_zombieFlags, ZFLAG_NoBlinkOnDamage, !i_blinkOnDamage);
}

void Zombie::setUseAnimTranslation(bool i_useAnimTranslation)
{
	SetFlag(m_zombieFlags, ZFLAG_UseAnimTranslation, i_useAnimTranslation);
}

const ZombieTypePtr& Zombie::GetType() const
{
	return m_type;
}

float Zombie::GetHitpoints() const
{
	return m_hitpoints;
}

ZombieFacing Zombie::GetFacing() const
{
	return m_facing;
}

float Zombie::GetCurrentResilienceValue()
{
	return m_currentResilience.m_currentResilience;
}

float Zombie::GetExtraDPSmodifier() const
{
	return m_extraDps;
}

float Zombie::GetMinifyTime()
{
	return 0.5f;
}

void Zombie::AddToTargetHistory(BoardEntityPtr i_entity)
{
	m_targetHistory.push_back(i_entity);
}

void Zombie::AddToTargetbyMaybee(BoardEntityPtr i_entity)
{
	m_beTargetbyMaybee.push_back(i_entity);
}

BoardEntity* Zombie::GetForcedTarget() const
{
	return m_forcedTarget;
}

ZombieState Zombie::getState() const
{
	return m_stateMachine.GetState();
}

float Zombie::GetExtraHitPointsmodifier() const
{
	return m_extraHP;
}

float Zombie::GetSpeedUpTileOffset()
{
	return 6.0f;
}

bool Zombie::HasHypnotized()
{
	return m_hasHypnotized;
}

void Zombie::SetHasHypnotized(bool i_value)
{
	m_hasHypnotized = i_value;
}

bool Zombie::IsSilenced()
{
	return m_isSilenced;
}

void Zombie::Silence(bool i_value)
{
	m_isSilenced = i_value;
}

void Zombie::SetCurrentResilienceValue(float i_value)
{
	m_currentResilience.m_currentResilience = i_value;
}

int32 Zombie::getZombieStateSerialization()
{
	return m_stateMachine.GetState();
}

void Zombie::SetIsUsingAnimTranslation(bool i_hasAnimTranslation)
{
	SetFlag(m_zombieFlags, ZFLAG_UseAnimTranslation, i_hasAnimTranslation);
}

void Zombie::onExitState_Walk(ZombieState i_arg)
{
	SetFlag(m_zombieFlags, ZFLAG_UseAnimTranslation, false);
}

void Zombie::onExitState_SpeedUpTileLeft(ZombieState i_arg)
{
	EndCondition((ZombieConditions)0x92);
}

void Zombie::onExitState_SpeedUpTileRight(ZombieState i_arg)
{
	EndCondition((ZombieConditions)0x92);
}

void Zombie::onExitState_SpeedUpTileUp(ZombieState i_arg)
{
	EndCondition((ZombieConditions)0x92);
}

void Zombie::onExitState_SpeedUpTileDown(ZombieState i_arg)
{
	EndCondition((ZombieConditions)0x92);
}

bool Zombie::IsValidRangedTarget(Plant* plant)
{
	return plant && plant->CanBeRangeTargeted();
}

bool Zombie::IsValidRangedTarget(PlantGroup* plant)
{
	return plant && plant->CanBeRangeTargeted();
}

ZombieResistenceRank Zombie::GetResistenceRank(ZombieResistenceType i_type)
{
	return GetResistenceRank(GetResistenceValue(i_type));
}

void Zombie::SetEliminateColor(int i_color)
{
	SetEliminateColor((EEliminateType)i_color);
}

void Zombie::SetEliminateColor(EEliminateType i_color)
{
	if ((unsigned)i_color >= 8)
		i_color = (EEliminateType)8;
	m_eliminateColor = i_color;
	m_conditionTracker.SetEliminateColor(i_color);
}

bool Zombie::CanIgnoreTitle(const DamageInfo& i_damage)
{
	return TestFlag(i_damage.Flags, (DamageTypeFlags)(1LL << 50));
}

void Zombie::applyButterGraphicalEffects()
{
	GetAnimRig()->SetButterVisibility(true);
}

void Zombie::onResilienceRecoverAnimStopped(const std::string& i_animLabel)
{
	SetWalkingState();
}

bool Zombie::canAttack()
{
	return GetZombieProps()->DoAttack;
}

void Zombie::SetFacing(ZombieFacing i_facing)
{
	m_facing = i_facing;
	m_pCachedZombieAnimRig->SetMirrorX(i_facing == ZFACING_Right);
}

bool Zombie::IsAffectedBySliderTiles() const
{
	return GetProps()->AffectedBySliders;
}

const std::string& Zombie::GetTypeName()
{
	return m_type->TypeName;
}

EliteZombie_Type Zombie::GetEliteZombieType() const
{
	return GetProps()->EliteZombieType;
}

const float Zombie::GetCriticalPos()
{
	return GetZombieProps()->CriticalPos;
}

bool Zombie::GetCanTriggerWin() const
{
	return GetZombieProps()->CanTriggerZombieWin;
}

int Zombie::GetArmorCount() const
{
	return (int)m_armor.size();
}

void Zombie::SetOwnerPlant(RtWeakPtr<Plant> i_ownerPlant)
{
	m_ownerPlant = i_ownerPlant;
}

RtWeakPtr<Plant> Zombie::GetOwnerPlant() const
{
	return m_ownerPlant;
}

ZombiePtr Zombie::GetOriginalZombie()
{
	return m_originalZombie;
}

EntityComponent_GroundEffect Zombie::GetGroundEffect()
{
	return m_groundEffect;
}

std::string Zombie::GetElectrocuteColor() const
{
	return m_electrocuteColor;
}

void Zombie::onZombieInitialize()
{
	if (gLawnApp->m_board && gLawnApp->m_board->m_juggledData.IsActivated)
		buildProjectileSets();
}

void Zombie::onTakeFatalDamage(const DamageInfo& i_lastDamageReceived)
{
	if (gLawnApp->m_board && gLawnApp->m_board->m_juggledData.IsActivated)
		dropAllProjectiles();
}

DamageInfo Zombie::modifyBodyDamage(const DamageInfo& i_incomingDamage)
{
	return i_incomingDamage;
}

float Zombie::GetDamageThreshold()
{
	return GetZombieProps()->Resilience->DamageThresholdPerSecond;
}

float Zombie::GetResilienceBaseDamageThreshold()
{
	return GetZombieProps()->Resilience->ResilienceBaseDamageThreshold;
}

float Zombie::GetResilienceExtraDamageThreshold()
{
	return GetZombieProps()->Resilience->ResilienceExtraDamageThreshold;
}

void Zombie::SetCurrentResistenceValue(ZombieResistenceType i_type, float i_value)
{
	m_currentResistence[i_type] = i_value;
}

float Zombie::GetResistenceValue(const DamageInfo& i_damage)
{
	return GetResistenceValue(ConvertToResistenceType(i_damage));
}

float Zombie::GetCurrentResistenceValue(const DamageInfo& i_damage)
{
	return GetCurrentResistenceValue(ConvertToResistenceType(i_damage));
}

bool Zombie::IsInmmuneFireDamage()
{
	return GetProps()->FireDamageMultiplier < EPSILON;
}

float Zombie::GetBaseWalkSpeed()
{
	const ZombiePropertySheet* props = GetProps().operator->();
	float speed = props->Speed;
	float variance = props->SpeedVariance;
	return RandRangeFloat(speed - variance * speed, speed + variance * speed);
}

bool Zombie::canPerformSkill()
{
	return m_canPerformSkill && isInPerformingSkillState();
}

bool Zombie::IsIZombie()
{
	return GetTypeName().find("izombie_") != std::string::npos;
}

bool Zombie::HasFullHitpoints() const
{
	return m_maxHitpoints == m_hitpoints && m_maxHelmHitpoints == m_helmHitpoints;
}

SexyVector2 Zombie::GetShadowScaling() const
{
	return GetZombieProps()->ShadowScaling;
}

SexyVector3 Zombie::GetFlickOffStartPositon()
{
	return m_flickOffStartPosition;
}

void Zombie::PutZombieWillPath(std::vector<Point>& vp, bool bGridPath)
{
	m_vWillPath = vp;
	m_bGridPath = bGridPath;
}

void Zombie::TriggerPlaybackParams(int i_type)
{
	if (i_type == 1)
		ApplyZombieFood();
}

void Zombie::onExitState_RiseFromPod(ZombieState i_state)
{
	m_groundEffect.ClearGroundEffect(this);
	SetIsControlled(false);
}

float Zombie::getLeftHitPer(bool includeHelm)
{
	float hp = m_hitpoints;
	float maxHp = m_maxHitpoints;
	if (includeHelm && m_helm)
	{
		hp += m_helmHitpoints;
		maxHp += m_maxHelmHitpoints;
	}
	return hp / maxHp;
}

void Zombie::SetHasLeader(bool i_hasLeader)
{
	SetHasLeader(i_hasLeader, DangerRoomModule::GetDangerRoomPropertySheet()->LeaderStrengthenRate);
}

bool Zombie::IsHelmTypeMetallic(HelmType i_helmType)
{
	switch (i_helmType)
	{
	case HELMTYPE_BUCKET:
	case HELMTYPE_HELMET:
	case HELMTYPE_METALPLATE:
	case HELMTYPE_CROWN:
	case HELMTYPE_MINING_TOOL:
	case HELMTYPE_BOX:
		return true;
	default:
		return false;
	}
}

bool Zombie::CanbeCorroded(HelmType i_helmType)
{
	switch (i_helmType)
	{
	case HELMTYPE_CONE:
	case HELMTYPE_BUCKET:
	case HELMTYPE_HELMET:
	case HELMTYPE_METALPLATE:
	case HELMTYPE_CROWN:
	case HELMTYPE_SHELL:
		return true;
	default:
		return false;
	}
}

bool Zombie::IsBoss()
{
	return IsA<Zomboss>() || IsA<ZombieZombossMech>();
}

bool Zombie::IsValidPinchTarget() const
{
	return IsOnTeam(TEAM_ZOMBIES) && GetZombieProps()->IsValidPinchTarget;
}

std::string Zombie::GetClassType() const
{
	return m_type->ZombieClass;
}

void Zombie::onEnterState_Winning(ZombieState i_state)
{
	m_pCachedZombieAnimRig->PlayEat();
	m_nextChewSoundTime = PVZ_T();
}

void Zombie::onEnterState_Eat(ZombieState i_state)
{
	m_pCachedZombieAnimRig->PlayEat();
	m_nextChewSoundTime = PVZ_T();
}

void Zombie::onEnterState_Ash(ZombieState i_state)
{
	GetAnimRig()->SetDisabled(true);
	onTurnedToAsh();
}

RtWeakPtr<PopAnim> Zombie::GetHeadParticlePopAnim()
{
	return GetPAMByName(GetType()->GetPopAnimName());
}

void Zombie::RiseFromStorm(const SexyVector3& i_position)
{
	SetPosition(i_position);
	setZombieState(ZS_RiseFromStorm);
}

void Zombie::onEnterState_Die(ZombieState i_state)
{
	if (HasCondition(ZCONDITION_Binded))
		EndCondition(ZCONDITION_Binded);
	m_pCachedZombieAnimRig->SetNeedsToDie();
}

void Zombie::updateState_MowedDown()
{
	if (PVZ_T() >= m_mowedStartTime + 0.33f)
		Destroy();
}

float Zombie::getTideDepthHeightMaxPct()
{
	float pct = GetProps()->MaxTideLoweredPercent;
	if (pct == 0.f)
		return gLawnApp->m_board->GetBoardProperties()->ZombieTideMaxHeightPct;
	return pct;
}

void Zombie::onExitState_RiseFromGround(ZombieState i_state)
{
	m_groundEffect.ClearGroundEffect(this);
	SetIsControlled(false);
	SetDisableSnapToGround(false);
}

void Zombie::onExitState_StuckIntoGround(ZombieState i_state)
{
	m_groundEffect.ClearGroundEffect(this);
	SetDisableSnapToGround(false);
	m_stuckIntoGroundTime = PVZ_EOT();
}

void Zombie::onLevelUp(int i_level)
{
	RefreshStats();
	CreateZombieLevelEffect(false);
}

bool Zombie::IsHelmMetallic()
{
	switch (GetHelmType())
	{
	case HELMTYPE_METALPLATE:
	case HELMTYPE_CROWN:
	case HELMTYPE_BUCKET:
		return true;
	default:
		return false;
	}
}

int Zombie::Rand()
{
	if (NewPVPUtils::IsPlayingNewPVP() && m_randomObject)
		return m_randomObject->Next();
	return Sexy::Rand();
}

int Zombie::Rand(int range)
{
	if (NewPVPUtils::IsPlayingNewPVP() && m_randomObject)
		return m_randomObject->Next((size_t)range);
	return Sexy::Rand(range);
}

float Zombie::Rand(float range)
{
	if (NewPVPUtils::IsPlayingNewPVP() && m_randomObject)
		return m_randomObject->Next(range);
	return Sexy::Rand(range);
}

float Zombie::RandWithOriginal(float i_original)
{
	if (NewPVPUtils::IsPlayingNewPVP() && m_randomObject)
		return m_randomObject->Next();
	return i_original;
}

float Zombie::RandWithOriginal(int range, float i_original)
{
	if (NewPVPUtils::IsPlayingNewPVP())
	{
		if (m_randomObject)
			return m_randomObject->Next((size_t)range);
	}
	return i_original;
}

float Zombie::RandWithOriginal(float range, float i_original)
{
	if (NewPVPUtils::IsPlayingNewPVP())
	{
		if (m_randomObject)
			return m_randomObject->Next(range);
	}
	return i_original;
}

void Zombie::applyPoisonGraphicalEffects()
{
	if (HasHead())
		GetAnimRig()->SetInkVisibility(true);
}

bool Zombie::HasFogImmune() const
{
	return HasCondition((ZombieConditions)107) || HasCondition((ZombieConditions)108);
}

int Zombie::CalcHelmDamageIndex() const
{
	return calcDamageIndex(GetHelmHitpoints(), m_maxHelmHitpoints, GetZombieProps()->HelmDamageLayerIndices);
}

float Zombie::GetLastDistanceWalked() const
{
	float track = m_animRig->GetGroundTrackTranslation();
	return GetFacingMultiplier() * track;
}

float Zombie::GetHitpointsUntilBleedout() const
{
	float drop = GetHeadDropHitPoints();
	return __builtin_fmaxf(GetHitpoints() - drop, 0.f);
}

void Zombie::OnIntroOnBoardEffectComplete(StandaloneEffect* i_effect)
{
	SetHidden(false);
	SetIsControlled(false);
	setZombieState(ZS_Walk, false);
}

float Zombie::GetTotalHitpoints() const
{
	float hp = GetHitpoints();
	float total = GetHelmHitpoints() + hp;
	float armor = GetArmorHitpoints();
	return total + armor;
}

bool Zombie::ShouldClipWithWater() const
{
	return !GetProps()->IgnoreWaterLine && !HasCondition(ZCONDITION_Tossed);
}

bool Zombie::IsInWater() const
{
	if (!IsOnGround())
		return false;
	return IsOnWaterTile(GetPosition());
}

void Zombie::RiseFromPod(const SexyVector3& i_boardPosition)
{
	SetPosition(i_boardPosition);
	SetFlag(m_zombieFlags, ZFLAG_WalkAfterRise, true);
	setZombieState(ZS_RiseFromPod, false);
}

void Zombie::setHasTorch(bool i_hasTorch)
{
	SetFlag(m_zombieFlags, ZFLAG_HasTorch, i_hasTorch);
	if (i_hasTorch)
		setIsTorchBurningFlag(i_hasTorch);
}

float Zombie::GetRandomValue(const ValueRange& i_range)
{
	if (NewPVPUtils::IsPlayingNewPVP() && m_randomObject)
		return i_range.GetRandomValue(m_randomObject);
	return i_range.GetRandomValue();
}

AttachedEffect* Zombie::GetAttachedEffect(const std::string i_entityName)
{
	if (m_attachedEffects.Contains(i_entityName))
		return (AttachedEffect*)&m_attachedEffects.FindOrCreate(i_entityName);
	return NULL;
}

AttachedBoardEntityNode* Zombie::GetAttachedBoardEntity(const std::string i_entityName)
{
	if (m_attachedBoardEntities.Contains(i_entityName))
		return (AttachedBoardEntityNode*)&m_attachedBoardEntities.FindOrCreate(i_entityName);
	return NULL;
}

void Zombie::onEnterState_Plantify(ZombieState i_state)
{
	if (CanDropHead())
		DropHead();
	m_animRig->SetNeedsToDie();
}

void Zombie::onEnterState_FlickedOff(ZombieState i_state)
{
	m_pCachedZombieAnimRig->SetPaused(true);
	m_flickedStartTime = PVZ_T();
	m_rotation = 0.f;
	m_flickOffStartPosition = GetPosition();
}

void Zombie::updateState_ResilienceBreak()
{
	RecoverResilience();
	if (HasReachMaxResilienceValue())
		setZombieState(ZS_ResilienceRecover, false);
}

void Zombie::StartWarpIn(float ofDuration)
{
	m_conditionTracker.ApplyCondition(this, ZCONDITION_WarpingIn, ofDuration, 0.f);
	SetFlag(m_zombieFlags, ZFLAG_IgnoresCollisions, true);
	SetFlag(m_zombieFlags, ZFLAG_NotTargetable, true);
}

void Zombie::StartWarpOut(float ofDuration)
{
	m_conditionTracker.ApplyCondition(this, (ZombieConditions)63, ofDuration, 0.f);
	SetFlag(m_zombieFlags, ZFLAG_IgnoresCollisions, true);
	SetFlag(m_zombieFlags, ZFLAG_NotTargetable, true);
}

void Zombie::updateSpeed()
{
	float speed = m_conditionTracker.GetSpeedModifier() * m_speedScale;
	GetAnimRig()->SetAnimRateModifier(speed);
	setStateMachineTimeScale(speed);
}

void Zombie::PlaceOnStreet(SexyVector3 i_position)
{
	SetPosition(i_position);
	m_zombieRenderLayerOffset = ZOMBIE_LAYER_OFFSET_BENEATH_ALL;
	onPlaceOnStreet();
}

void Zombie::onPlaceOnStreet()
{
	updateGroundEffect();
	setZombieState(ZS_Idle, false);
	m_pCachedZombieAnimRig->RandomizeCurrentAnimFrame();
	CreateZombieLevelEffect(true);
}

int Zombie::GetSummonZombieLevel()
{
	if (gLawnApp->m_board && gLawnApp->m_board->IsDangerRoom())
		return gDangerRoomMgr->PickupZombieLevelForCurrentLevel();
	return m_currentLevel;
}

void Zombie::onEnterState_Grabbed(ZombieState i_state)
{
	SetIsFlying(true);
	SetIgnoresCollisions(true);
	SetIgnoresAllDamage(true);
	SetIsControlled(true);
	SetIsTargetable(false);
}

void Zombie::EndInvokeInvisibleEffect()
{
	if (GetInvisibleState() == Invoke_Invisible)
		SetInvisibleState(CheckAllStreetLamp() ? Invisible_Detected : Invisible_Not_Detected);
}

void Zombie::ChangeCurrentResistenceValue(ZombieResistenceType i_type, float i_delta, bool i_add)
{
	float current = GetCurrentResistenceValue(i_type);
	SetCurrentResistenceValue(i_type, i_add ? current + i_delta : current - i_delta);
}

int Zombie::CalcProgressMeterHitpoints() const
{
	if (!IsOnTeam(TEAM_ZOMBIES))
		return 0;
	float hp = GetHitpoints();
	return (int)(GetHelmHitpoints() + hp);
}

void Zombie::updateState_Idle()
{
	if (HasCondition((ZombieConditions)85))
	{
		if (FindEatTarget())
			setZombieState(ZS_Eat, false);
	}
}

void Zombie::updateRushCondition()
{
	if (m_conditionTracker.HasCondition((ZombieConditions)7))
	{
		if (GetPosition().x <= 792.f)
			endRushOnScreen();
	}
}

void Zombie::UpdateCloneableState()
{
	if (CalcColumnPosition() > 7 && !IsClonedZombie() && !IsCloneable())
		SetIsCloneable(true);
}

bool Zombie::IsResilienceBreak() const
{
	return isInState(ZS_ResilienceEnterBreak) || isInState(ZS_ResilienceBreak) || isInState(ZS_ResilienceRecover);
}

void Zombie::spreadChemistPoison()
{
	if (HasCondition((ZombieConditions)78))
		doSpreadChemistPoison(CalcColumnPosition(), CalcRowPosition());
}

float Zombie::GetCurrentResilienceDamageReduced()
{
	if (GetCurrentResilienceValue() > 0.f)
	{
		if (IsResilienceBreak())
			return 0.f;
		if (HasReachResilienceDamageThreshold())
			return 1.f;
	}
	return 1.f;
}

void Zombie::StartLossLife(float i_duration, float i_scale)
{
	m_bIsLossLife = true;
	m_tLossLifeTime = PVZ_T() + i_duration;
	m_iLossLifePerFrame = GetMaxHitpoints() * PVZ_Dt() * i_scale;
}

Sexy::Point Zombie::GetGridExtents() const
{
	return GetProps()->GridExtents;
}
static float PassThrough(float v)
{
	return v;
}

float Zombie::GetBaseEatDPS()
{
	const ZombiePropertySheet* props = GetZombieProps();
	float ratio = props->EatDPSRatio;
	if (ratio > 0.0f)
		return PassThrough(m_maxHitpoints) * ratio;
	if (m_extraEatDPS > 0.0f)
		return m_extraEatDPS;
	if (m_baseEatDPS > 0.0f)
		return m_baseEatDPS;
	return props->EatDPS;
}

bool Zombie::HasTag(const std::string& i_tag)
{
	return m_tags.find(i_tag) != m_tags.end();
}

template <class T> static T* DownCast(Zombie* z)
{
	return static_cast<T*>(z);
}

int Zombie::GetBossStage()
{
	if (IsA<Zomboss>())
	{
		Zomboss* z = DownCast<Zomboss>(this);
		return z->GetStageIndex();
	}
	if (IsA<ZombieZombossMech>())
	{
		ZombieZombossMech* z = DownCast<ZombieZombossMech>(this);
		return z->GetStageIndex();
	}
	return 0;
}
bool Zombie::IsOnBoardOrClose(int i_maxGridDistFromRight) const
{
	Sexy::Point p = CalcGridPosition();
	return (p.mX >= 0) & (p.mX < BoardConstants::NUMBER_OF_COLUMNS() + i_maxGridDistFromRight);
}

bool Zombie::IsOnBoard() const
{
	Sexy::Point p = CalcGridPosition();
	return (p.mX >= 0) & (p.mX < BoardConstants::NUMBER_OF_COLUMNS());
}

void Zombie::SetIsWinningZombie()
{
	SetFlag(m_zombieFlags, ZFLAG_WinningZombie, true);
	setZombieState(ZS_Winning, false);
	if (IsInvisible() || m_canBeTargetedWhenInvisible)
		SetInvisibleState(Not_Invisible);
}

static bool IsHiddenFlag(RealObjectFlags f)
{
	return TestFlag(f, ROFLAG_Hidden);
}

bool Zombie::ShouldDrawShadow() const
{
	if (!RealObject::ShouldDrawShadow() || IsInWater() || IsHiddenFlag(m_realObjectFlags) || IsInvisible())
		return false;
	return !m_canBeTargetedWhenInvisible;
}

bool Zombie::isInPerformingSkillState()
{
	return (isInState(ZS_Idle) || isInState(ZS_Walk) || isInState(ZS_Attack)) && !IsSuspended();
}

void Zombie::TurnToAsh()
{
	if (allowAshState())
	{
		if (!isInState(ZS_Ash))
			setZombieState(ZS_Ash, false);
	}
	else
		setZombieState(ZS_Die, false);
}

void Zombie::onEnterState_MowedDown(ZombieState i_arg)
{
	m_pCachedZombieAnimRig->SetPaused(true);
	onMowedDown();
	m_mowedStartTime = PVZ_T();
	if (CanDropHead())
		DropHead();
}

void Zombie::UpdateLevelEffect()
{
	if (m_beginPlayLevelEffect)
	{
		int col = CalcColumnPosition();
		if (col > 0 && col < BoardConstants::NUMBER_OF_COLUMNS())
		{
			CreateZombieLevelEffect(false);
			m_beginPlayLevelEffect = false;
		}
	}
}

Sexy::SexyVector3 Zombie::GetNumbEffectOffset() const
{
	return Sexy::SexyVector3(0.0f, 0.0f, 25.0f);
}

Sexy::SexyVector3 Zombie::GetResilienceActivatedEffectOffset() const
{
	return Sexy::SexyVector3(0.0f, -50.0f, 0.0f);
}

void Zombie::initializeAnimRig()
{
	initializeAnimRigForType(m_type);
}

void Zombie::ClearConditions()
{
	bool shrinking = HasCondition(ZCONDITION_Shrunken);
	m_conditionTracker.ClearConditions(this);
	if (shrinking && !willDieToShrinking())
		ApplyCondition(ZCONDITION_Shrunken, PVZ_EOT(), 0.0f, true);
}

bool Zombie::willDieToShrinking()
{
	return false;
}

void Zombie::BindImageToSprite(const std::string& i_spriteName, Sexy::Image* i_image)
{
	m_spriteBind.push_back(std::pair<std::string, Sexy::Image*>(i_spriteName, i_image));
}

void Zombie::onApplyCondition(ZombieConditions i_condition)
{
	if (gLawnApp->m_board && gLawnApp->m_board->m_juggledData.IsActivated)
	{
		if (IsBleedingOut() || IsSuspended())
			dropAllProjectiles();
	}
}

float Zombie::GetResistenceValue(ZombieResistenceType i_type)
{
	if (i_type != -1 && (size_t)i_type < m_type->Resistences.size())
		return m_type->Resistences[i_type];
	return 0.0f;
}

float Zombie::GetResistenceValue(ZombieResistenceType i_type, ZombieTypePtr i_zombieType)
{
	if (i_type != -1 && (size_t)i_type < i_zombieType->Resistences.size())
		return i_zombieType->Resistences[i_type];
	return 0.0f;
}

void Zombie::RecoverResilience()
{
	float cur = GetCurrentResilienceValue();
	float rate = m_currentResilience.m_recoverValue;
	float value = cur + rate * PVZ_Dt();
	SetCurrentResilienceValue(std::min(value, m_currentResilience.m_maxResilience));
}

bool Zombie::IsBerserk() const
{
	if (HasCondition(ZCONDITION_Berserk) || HasCondition(ZCONDITION_New_PVP_Upgrade_Berserk) || HasCondition(ZCONDITION_Merged) || HasCondition(ZCONDITION_ImmuneControl))
		return true;
	return IsResilienceBreak();
}

Sexy::SexyVector3 Zombie::getGumPosition()
{
	const Sexy::SexyVector3& pos = GetPosition();
	return Sexy::SexyVector3(pos.x - 15.0f, pos.y, pos.z);
}

float Zombie::GetHeadDropHitPoints() const
{
	if (gLawnApp->IsInModule(Module_Pooyan | Module_Fishing | Module_Besiege))
		return 0.0f;
	float fraction = getHeadDropFraction();
	return PassThrough(m_maxHitpoints) * fraction;
}

void Zombie::RemoveAttachedEffect(const char* iEffectName)
{
	m_attachedEffects.Remove(std::string(iEffectName));
}

void Zombie::DetachAttachedEffect(const char* i_entityName)
{
	AttachedEffect* effect = GetAttachedEffect(std::string(i_entityName));
	if (effect->IsValid())
		effect->Detach();
}

void Zombie::onEnterState_DropIntoIceHole(ZombieState i_arg)
{
	GetAnimRig()->PlayStreetIdle();
}

void Zombie::UpdateInvisibleState()
{
	if (CalcColumnPosition() != m_previousCol && (unsigned)(m_invisibleState - Invisible_Not_Detected) < 2)
	{
		m_previousCol = CalcColumnPosition();
		if (CheckAllStreetLamp())
			SetInvisibleState(Invisible_Detected);
		else
			SetInvisibleState(Invisible_Not_Detected);
	}
}

void Zombie::RegrowArm()
{
	if (TestFlag(m_zombieFlags, ZFLAG_LostArm))
	{
		SetFlag(m_zombieFlags, ZFLAG_LostArm, false);
		GetAnimRig()->ShowArm();
		onRegrowArm();
	}
}

void Zombie::Heal()
{
	SetHitpoints(m_maxHitpoints);
	RegrowArm();
	onTakeBodyDamage(DamageInfo());
}

void Zombie::HealHelm()
{
	if (m_helm)
	{
		m_helmHitpoints = m_maxHelmHitpoints;
		onTakeHelmDamage(DamageInfo());
	}
}

void Zombie::HealByPercent(float healPercent)
{
	float max = m_maxHitpoints;
	SetHitpoints(std::min(m_hitpoints + healPercent * max, m_maxHitpoints));
	onTakeBodyDamage(DamageInfo());
}

void Zombie::HealByAmount(float amount)
{
	float cur = m_hitpoints;
	SetHitpoints(std::min(amount + cur, m_maxHitpoints));
	onTakeBodyDamage(DamageInfo());
}

void Zombie::CancelZombieFood()
{
	m_isInZombieFood = false;
	m_attachedEffects.Remove(std::string("zombiefood"));
}

bool Zombie::WillTargetPlant(Plant* i_plant)
{
	return IsOnOpposingTeam(i_plant) && i_plant->CanBeTargeted() && i_plant->CanBeTargetedBy(this) && canTargetEntityHeight(i_plant->GetEntityHeight());
}

bool Zombie::CheckSpeedUpTileIsTurnToUp()
{
	const Sexy::SexyVector3& pos = GetPosition();
	int x = BoardTransforms::BoardSpaceToGridX(pos.x);
	int y = BoardTransforms::BoardSpaceToGridY(pos.y);
	if (y + 1U <= 1 || x == -1)
		return false;
	return gLawnApp->m_board->GetGridSquareType(x, y - 1) == GRIDSQUARE_TD_ROAD;
}

bool Zombie::CheckSpeedUpTileIsTurnToDown()
{
	const Sexy::SexyVector3& pos = GetPosition();
	int x = BoardTransforms::BoardSpaceToGridX(pos.x);
	int y = BoardTransforms::BoardSpaceToGridY(pos.y);
	if (x == -1 || y == -1 || y == BoardConstants::NUMBER_OF_ROWS() - 1)
		return false;
	return gLawnApp->m_board->GetGridSquareType(x, y + 1) == GRIDSQUARE_TD_ROAD;
}

void Zombie::onEnterState_Idle(ZombieState i_arg)
{
	if (i_arg != ZS_RiseFromGround && i_arg != ZS_DropIntoIceHole)
		m_pCachedZombieAnimRig->PlayStreetIdle();
}

void Zombie::AddResilienceDamageAccumulation(float i_damage)
{
	if (GetCurrentResilienceValue() > 0.0f)
	{
		float value = i_damage;
		value += m_currentResilience.m_currentDamageAccumulation;
		float threshold = GetDamageThreshold();
		m_currentResilience.m_currentDamageAccumulation = std::min(value, threshold);
	}
}

bool Zombie::IsTargetable() const
{
	return !(TestFlag(m_zombieFlags, ZFLAG_NotTargetable) || HasCondition(ZCONDITION_Icecubed) || HasCondition(ZCONDITION_StoneBlocked) || HasCondition(ZCONDITION_PresentBoxed)) && !HasCondition(ZCONDITION_StoneBlocked);
}

void Zombie::GetNextGlideTarget()
{
	float now = PVZ_T();
	m_isGliding = true;
	m_lastGlideTime = now;
	m_startGlidePosition = GetPosition();
	int gridX = m_GlideXWeights.PickItem();
	int gridY = m_GlideYWeights.PickItem();
	m_nextGlidePosition.x = (float)BoardTransforms::GridToBoardSpaceXUnbounded(gridX);
	m_nextGlidePosition.y = (float)BoardTransforms::GridToBoardSpaceYUnbounded(gridY);
	m_nextGlidePosition.z = 0.0f;
}

void Zombie::TakeFatalDamage(BoardEntity* i_instigator)
{
	DamageInfo info(GetHitpoints(), DAMAGE_FATAL, i_instigator);
	TakeDamage(info);
}

void Zombie::TakeFatalDamage(const DamageInfo& i_damage)
{
	DamageInfo info(i_damage);
	info.Amount = GetHitpoints();
	info.Flags |= DAMAGE_FATAL;
	TakeDamage(info);
}

void Zombie::broadcastZombieDied(const DamageInfo* i_deathBlow)
{
	if (TestFlag(m_zombieFlags, ZFLAG_HasBroadcastedDeath))
		return;
	gMessageRouter->Broadcast(Message::ZombieDied, this, i_deathBlow);
	SetFlag(m_zombieFlags, ZFLAG_HasBroadcastedDeath, true);
}

void Zombie::onDestroy()
{
	m_isBeingDestroyed = true;
	DropAllLoot();
	ClearConditions();
	gMessageRouter->Post(Message::ZombieDestroyed, this);
	m_attachedEffects.Clear();
	m_groundEffect.Destroy();
}

void Zombie::registerForEvents()
{
	gMessageRouter->Subscribe(Message::NotifyWhenChanged, Sexy::MakeDelegate(*this, &Zombie::onStreetLampChanged));
}

void Zombie::onExitState_RiseFromStorm(ZombieState i_arg)
{
	SetUseGroundClipRect(false);
	SetIsControlled(false);
	SetDisableSnapToGround(false);
	gMessageRouter->Post(Message::ZombieExitSandstorm, this);
}

void Zombie::updateState_RiseFromPod()
{
	if (!GetAnimRig()->IsPlayingAnything())
	{
		if (TestFlag(m_zombieFlags, ZFLAG_WalkAfterRise))
			SetWalkingState();
		else
			SetIdleState();
	}
}

void Zombie::initializeResistences()
{
	for (int i = 0; i < ZombieResistenceType_Count; ++i)
		m_currentResistence.push_back(GetResistenceValue((ZombieResistenceType)i));
}

void Zombie::setState(const StateDefinition<ZombieState>& i_newState, bool i_reenterIfAlreadyInState)
{
	bool changed;
	if (i_reenterIfAlreadyInState && m_stateMachine.GetState() == i_newState.State)
		changed = m_stateMachine.ReenterState();
	else
		changed = m_stateMachine.SetState(i_newState);
	if (changed)
	{
		m_elapsedTimeInState = 0.0f;
		if (i_newState.State != ZS_Walk)
			EndCondition(ZCONDITION_Terrified);
	}
}

void Zombie::playDeathAnimation()
{
	DropAllLoot();
	ClearConditions();
	m_playingAnim = m_pCachedZombieAnimRig->PlayDie();
	if (m_playingAnim != -1)
	{
		SetFlag(m_zombieFlags, ZFLAG_UseAnimTranslation, false);
		SetFlag(m_zombieFlags, ZFLAG_PlayedDeathAnim, true);
	}
	else
		Destroy();
}

void Zombie::RiseFromGround(const SexyVector3& i_boardPosition, bool i_walkAfterRise)
{
	m_beginPlayLevelEffect = true;
	SetPosition(i_boardPosition);
	SetFlag(m_zombieFlags, ZFLAG_WalkAfterRise, i_walkAfterRise);
	gMessageRouter->Post(Message::ZombieRiseFromGround, this);
	setZombieState(ZS_RiseFromGround, false);
	gMessageRouter->Broadcast(Message::ZombieAddedToBoard, this);
}

void Zombie::MowDown()
{
	SetFlag(m_zombieFlags, ZFLAG_MowDownByMower, true);
	DamageInfo info;
	info.Flags |= DAMAGE_FROM_MOWER;
	TakeFatalDamage(info);
}

bool Zombie::IsInTargetHistory(BoardEntityPtr i_entity)
{
	return std::find(m_targetHistory.begin(), m_targetHistory.end(), i_entity) != m_targetHistory.end();
}

bool Zombie::CanNormalDamagePlantGroup(PlantGroup* i_plantGroup, bool i_arg)
{
	return IsOnOpposingTeam(i_plantGroup) && i_plantGroup->CanBeTargetedBy(this, i_arg) && canTargetEntityHeight(i_plantGroup->GetEntityHeight());
}

int Zombie::calcDamageIndex(float i_currentHitPoints, float i_maxHitpoints, int i_damageStates) const
{
	if (i_maxHitpoints <= 0.0f)
		return 0;
	int index = (i_damageStates - 1) - (int)(i_currentHitPoints / (i_maxHitpoints / (float)i_damageStates));
	return std::min(std::max(index, 0), i_damageStates - 1);
}

void Zombie::InvokeInvisible(bool invoke, bool i_fadeIn, bool i_canBeTargeted)
{
	if (CanInvokeInvisible())
	{
		if (invoke)
		{
			if (m_invisibleState == Not_Invisible)
			{
				m_canBeTargetedWhenInvisible = i_canBeTargeted;
				SetInvisibleState(Invisible_Not_Detected);
				if (i_fadeIn)
					m_InvisibleFadeInStartTime = PVZ_T();
			}
		}
		else
		{
			SetInvisibleState(Not_Invisible);
			if (i_fadeIn)
				m_InvisibleFadeInStartTime = PVZ_EOT();
		}
	}
}

void Zombie::OnInvisibleStateChanged(InvisibleState oldState, InvisibleState newState)
{
	int alpha;
	switch (newState)
	{
	case Invisible_Not_Detected: alpha = 0x7f; break;
	case Invisible_Detected: alpha = 0xb2; break;
	default: alpha = 0xff; break;
	}
	Color color(Color::White);
	color.mAlpha = alpha;
	GetAnimRig()->SetPAMColor(color);
}

bool Zombie::IsDying() const
{
	return isInState(ZS_Die) || isInState(ZS_Electrocute) || isInState(ZS_Ash) || isInState(ZS_MowedDown) || isInState(ZS_FlickedOff) || isInState(ZS_Plantify);
}

bool Zombie::IsOnGround() const
{
	Board* board = gLawnApp->m_board;
	if (board->m_roofStage)
	{
		const Sexy::SexyVector3& pos = GetPosition();
		if (!(board->calculateRoofOffsetZ(pos.x) >= pos.z))
			return false;
	}
	else if (GetPosition().z > 0.0f)
		return false;
	if (IsFlying())
		return false;
	return !IsJumping();
}

bool Zombie::canTargetPlant(Plant* i_plant)
{
	if (GetZombieProps()->DoSmashAttack)
		return true;
	return i_plant->CanBeTargeted() && canTargetEntityHeight(i_plant->GetEntityHeight()) && onCanTargetPlant(i_plant);
}

void Zombie::updateState_Eat()
{
	BoardEntity* target = findTarget();
	if (!target || target->IsA<GridItemArmrack>())
	{
		if (!IsSuspended())
			setZombieState(ZS_Walk, false);
	}
	else if (!target->IsA<GridItemFlame>())
		eatTarget(target);
}

bool Zombie::CanBeNumb()
{
	bool result = false;
	std::allocator<char> alloc;
	std::string name("numb", alloc);
	if (!m_attachedEffects.Contains(name))
		result = !HasCondition(ZCONDITION_Numb);
	return result;
}

void Zombie::SetIsControlled(bool i_controlled)
{
	if (i_controlled)
	{
		onExternalControlEvent();
		if (HasCondition(ZCONDITION_Invincible))
			EndCondition(ZCONDITION_Invincible);
		if (HasCondition(ZCONDITION_CureShield))
			EndCondition(ZCONDITION_CureShield);
		if (HasCondition(ZCONDITION_FogShieldLvl1))
			EndCondition(ZCONDITION_FogShieldLvl1);
	}
	SetFlag(m_zombieFlags, ZFLAG_Controlled, i_controlled);
}

bool Zombie::CanBeFlickedOff() const
{
	return (HasFogImmune() || IsBerserk() || m_unknown760 || HasCondition(ZCONDITION_Amber) || IsEliteZombie() || CanEliteImmunittiesByZombie() || !IsOnTeam(TEAM_ZOMBIES)) ? false : GetProps()->CanBeFlickedOff;
}

bool Zombie::CannotStunnedByStreetLamp() const
{
	if (!isInState(ZS_Die) && !isInState(ZS_Electrocute) && !isInState(ZS_Ash) && !isInState(ZS_MowedDown) && !isInState(ZS_FlickedOff) && !IsDropingIntoHole() && !IsControlled() && !IsOnOpposingTeam(TEAM_ZOMBIES) && !IsA<Zomboss>())
		return IsA<ZombieZombossMech>();
	return true;
}

bool Zombie::HasArmor(ArmorTypeFlags i_armorFlags) const
{
	for (std::vector<ArmorPtr>::const_iterator it = m_armor.begin(); it != m_armor.end(); ++it)
	{
		if (i_armorFlags == ARMOR_None || TestFlag((*it)->GetArmorFlags(), i_armorFlags))
			return true;
	}
	return false;
}

float Zombie::GetMaxArmorHitpoints() const
{
	float total = 0;
	for (const ArmorPtr& a : m_armor)
	{
		ArmorPtr armor = a;
		total += PassThrough(armor->GetMaxHealth());
	}
	return total;
}

float Zombie::GetArmorHitpoints() const
{
	float total = 0;
	for (const ArmorPtr& a : m_armor)
	{
		ArmorPtr armor = a;
		if (!armor->IsDecorativePassthrough())
			total += PassThrough(armor->GetHealth());
	}
	return total;
}

bool Zombie::HasMetallicArmor()
{
	for (const ArmorPtr& a : m_armor)
	{
		ArmorPtr armor = a;
		if (TestFlag(armor->GetArmorFlags(), ARMOR_METALLIC) && !armor->IsDestroyed())
			return true;
	}
	return false;
}

void Zombie::SetDamageBalancer(ZombieConditions i_conditions, float i_value)
{
	for (size_t i = 0; i < m_damageBalancer.size(); i++)
	{
		if (m_damageBalancer[i].TargetConditions == i_conditions)
		{
			m_damageBalancer[i].BalanceValue = i_value;
			return;
		}
	}
	m_damageBalancer.push_back(DamageBalancer(i_conditions, i_value));
}

void Zombie::SetDamageBalancer(DamageTypeFlags i_flags, float i_value)
{
	for (size_t i = 0; i < m_damageBalancer.size(); i++)
	{
		if (m_damageBalancer[i].TargetFlags == i_flags)
		{
			m_damageBalancer[i].BalanceValue = i_value;
			return;
		}
	}
	m_damageBalancer.push_back(DamageBalancer(i_flags, i_value));
}

void Zombie::DestroySpeedUpEffect()
{
	if (m_attachedEffects.Contains(std::string("speedup")))
		m_attachedEffects.Remove(std::string("speedup"));
}

void Zombie::ClearTargetbyMaybee(BoardEntityPtr i_entity)
{
	std::vector<BoardEntityPtr>::iterator it = std::find(m_beTargetbyMaybee.begin(), m_beTargetbyMaybee.end(), i_entity);
	if (it != m_beTargetbyMaybee.end())
		m_beTargetbyMaybee.erase(it);
}

BoardEntity* Zombie::findTarget()
{
	if (IsSuspended() || IsIgnoreFindTarget())
		return NULL;
	Rect attackRect = CalcZombieAttackRect();
	return findEatTarget(CalcRowPosition(), attackRect);
}

BoardEntity* Zombie::FindEatTarget()
{
	if (IsSuspended())
		return NULL;
	Rect attackRect = CalcZombieAttackRect();
	return findEatTarget(CalcRowPosition(), attackRect);
}

void Zombie::setHelm(HelmType i_helmType, float i_helmHitpoints)
{
	m_helm = i_helmType;
	float hp = (1.0f - m_unknown758) * i_helmHitpoints;
	m_maxHelmHitpoints = i_helmHitpoints;
	m_helmHitpoints = hp;
	m_helmHitpoints = std::max(0.0f, m_helmHitpoints);
	m_maxHelmHitpoints = std::max(0.0f, m_maxHelmHitpoints = hp);
	onSetHelm();
}

bool Zombie::canThrowProjectile(Projectile* i_projectile)
{
	const ProjectilePropertySheet* props = i_projectile->GetProps();
	return canJuggleProjectile(i_projectile) && m_unthrowableProjectiles.find(props) == m_unthrowableProjectiles.end();
}

SexyString Zombie::GetFormattedNameString(ZombieTypePtr i_zombieType)
{
	std::string formatted = StrFormat("[ZOMBIE_%s]", StringToUpper(i_zombieType->TypeName).c_str());
	return TodStringTranslate(StringToWString(formatted));
}

SexyString Zombie::GetFormattedToolTip(ZombieTypePtr i_zombieType)
{
	std::string formatted = StrFormat("[ZOMBIE_%s_TOOLTIP]", StringToUpper(i_zombieType->TypeName).c_str());
	return TodStringTranslate(StringToWString(formatted));
}

SexyString Zombie::GetFormattedDescription(ZombieTypePtr i_zombieType)
{
	std::string formatted = StrFormat("[ZOMBIE_%s_DESCRIPTION]", StringToUpper(i_zombieType->TypeName).c_str());
	return TodStringTranslate(StringToWString(formatted));
}

SexyString Zombie::GetFormattedDescriptionHeader(ZombieTypePtr i_zombieType)
{
	std::string formatted = StrFormat("[ZOMBIE_%s_DESCRIPTION_HEADER]", StringToUpper(i_zombieType->TypeName).c_str());
	return TodStringTranslate(StringToWString(formatted));
}

void Zombie::updateState_Ash()
{
	bool hasAsh;
	{
		std::allocator<char> alloc;
		std::string name("ash", alloc);
		hasAsh = m_attachedEffects.Contains(name);
	}
	if (!hasAsh)
		Destroy();
}

void Zombie::updateState_Electrocute()
{
	bool hasElectrocute;
	{
		std::allocator<char> alloc;
		std::string name("electrocute", alloc);
		hasElectrocute = m_attachedEffects.Contains(name);
	}
	if (!hasElectrocute)
		TurnToAsh();
}

void Zombie::updateState_Die()
{
	if (!TestFlag(m_zombieFlags, ZFLAG_PlayedDeathAnim))
	{
		if (m_pCachedZombieAnimRig->IsReadyToDie())
			playDeathAnimation();
		return;
	}
	if (m_pCachedZombieAnimRig->IsAnimFinished(m_playingAnim))
	{
		if (m_elapsedTimeInState < 10000.0)
		{
			m_elapsedTimeInState = 10000.0;
			return;
		}
		if (m_elapsedTimeInState >= 10000.5)
		{
			onExitState_Die(getState());
			Destroy();
		}
	}
}

void Zombie::onEnterState_Electrocute(ZombieState i_state)
{
	GetAnimRig()->SetDisabled(true);
	onElectrocuted();
	PlayPositionalSound(std::string("Play_LightningReed_Electrocute_PF"), 0.0f);
}

float Zombie::GetCurrentResistenceValue(ZombieResistenceType i_type)
{
	if (i_type == -1)
		return 0.0f;
	if (i_type == 6 && HasCondition((ZombieConditions)0x8a))
	{
		float base = m_currentResistence[6];
		return base + GetConditionTracker().GetCondition((ZombieConditions)0x8a).m_additionalDataValue;
	}
	return m_currentResistence[i_type];
}

float Zombie::GetResilienceDamage(const DamageInfo& i_damage)
{
	if (i_damage.ResilienceDamage.ExtraDamage > 0.0f && m_currentResilience.m_currentResilienceExtraDmgAccumulation < GetResilienceExtraDamageThreshold())
		return i_damage.ResilienceDamage.ExtraDamage;
	if (i_damage.ResilienceDamage.BaseDamage > 0.0f && m_currentResilience.m_currentResilienceBaseDmgAccumulation < GetResilienceBaseDamageThreshold())
		return i_damage.ResilienceDamage.BaseDamage;
	return 0.0f;
}

void Zombie::updateResilienceDamageThreshold()
{
	if (GetCurrentResilienceValue() > 0.0f)
	{
		if (PVZ_T() > m_currentResilience.m_nextDamageThresholdResetTime)
		{
			m_currentResilience.m_currentDamageAccumulation = 0.0f;
			m_currentResilience.m_nextDamageThresholdResetTime = PVZ_T() + 3.0f;
		}
		if (PVZ_T() > m_currentResilience.m_nextResilienceDamageThresholdResetTime)
		{
			m_currentResilience.m_currentResilienceBaseDmgAccumulation = 0.0f;
			m_currentResilience.m_currentResilienceExtraDmgAccumulation = 0.0f;
			m_currentResilience.m_nextResilienceDamageThresholdResetTime = PVZ_T() + 1.0f;
		}
	}
}

void Zombie::forceApplyConditionEffects()
{
	if (HasCondition((ZombieConditions)3))
		applyButterGraphicalEffects();
	if (HasCondition((ZombieConditions)0x30) || HasCondition((ZombieConditions)0x31) || HasCondition((ZombieConditions)0x8d))
		applyPoisonGraphicalEffects();
	updateSpeed();
}

void Zombie::updateStateMachine()
{
	if (m_stateMachineTimeScale != 0.0f)
	{
		m_stateMachine.UpdateState();
		float scale = m_stateMachineTimeScale;
		m_elapsedTimeInState += PVZ_Dt() * scale;
	}
	else if (HasCondition((ZombieConditions)0x92))
	{
		m_stateMachine.UpdateState();
		m_elapsedTimeInState += PVZ_Dt() * 0.0001f;
	}
}

void Zombie::EndConditions(std::vector<ZombieConditions> i_condition)
{
	for (std::vector<ZombieConditions>::iterator it = i_condition.begin(); it != i_condition.end(); ++it)
		m_conditionTracker.EndCondition(this, *it);
}

void Zombie::ApplyCondition(const ZombieConditionsStruct& i_conditionsStruct)
{
	ZombieConditionsStruct conditions(i_conditionsStruct);
	if (conditions.Instigator)
	{
		Plant* plant = conditions.Instigator->Cast<Plant>();
		if (plant)
			plant->OnApplyZombieCondition(this, conditions);
	}
	ApplyCondition(conditions.Condition, conditions.Duration, conditions.EventDelay, true);
}

void Zombie::setZombieState(ZombieState i_newState, bool i_reenterIfAlreadyInState)
{
	StateDefinition<ZombieState> newState =
		StateMachineTableBuilder::GetInstancePtr()->GetTable<ZombieState>(GetClass())->GetStateDefinition(i_newState);
	newState.SetContext(this);
	setState(newState, i_reenterIfAlreadyInState);
}

void Zombie::setZombieStateSerialization(int32 i_state)
{
	StateDefinition<ZombieState> newState =
		StateMachineTableBuilder::GetInstancePtr()->GetTable<ZombieState>(GetClass())->GetStateDefinition((ZombieState)i_state);
	newState.SetContext(this);
	m_stateMachine.SetStateNoTransition(newState);
}

void Zombie::choosePostStormState()
{
	gMessageRouter->Post(Message::SandstormDestroyed, this);
	if (!HasHead())
		chooseDeathState(DamageInfo());
	else
		SetWalkingState();
}

void Zombie::SetForcedTarget(BoardEntity* i_forcedTarget)
{
	RtWeakPtr<BoardEntity>& dst = m_forcedTarget;
	if (!i_forcedTarget)
	{
		dst = RtWeakPtr<BoardEntity>();
		return;
	}
	RtWeakPtr<GameObject> ptr = i_forcedTarget->GetPtr();
	dst = RtWeakPtr<BoardEntity>(ptr);
}

void Zombie::onEnterState_BleedingOut(ZombieState i_arg)
{
	gMessageRouter->Post(Message::ZombieBleedingOut, this, nullptr);
	SetFlag(m_zombieFlags, ZFLAG_UseAnimTranslation, true);
	if (!m_pCachedZombieAnimRig->IsPlaying(ZOMBIEANIM_WALK))
		m_pCachedZombieAnimRig->PlayWalk();
}

void Zombie::DropAllLoot()
{
	bool dropped = GetHasDroppedLoot();
	if (!dropped)
	{
		gMessageRouter->Post(Message::ZombieDropLoot, this);
		SetHasDroppedLoot(true);
		const SexyVector3& pos = GetPosition();
		LootHelpers::Drop(m_loot, pos);
		if (m_sunDrop > 0)
			gLawnApp->m_board->FanOutSun(pos, m_sunDrop, dropped, dropped, true, dropped, dropped);
	}
}

void Zombie::UpdatePVP()
{
	if (!IsDying())
	{
		float health = m_helmHitpoints + m_hitpoints;
		if (!FloatApproxEqual(m_ZombieLastHealth, health))
		{
			m_ZombieLastHealth = health;
			m_showHealthBarTime = 2.0f;
			SetShowHealthBar(true);
		}
		if (!m_bShowHealthBar || !(m_showHealthBarTime > 0.0f))
			return;
		m_showHealthBarTime -= PVZ_Dt();
		if (!(m_showHealthBarTime <= 0.0f))
			return;
	}
	SetShowHealthBar(false);
}

void Zombie::DoDropIntoIceHole(const SexyVector3& i_boardPosition, bool bSpecial)
{
	m_bSpecialSplitRect = bSpecial;
	SetTargetPosition(i_boardPosition);
	setZombieState(ZS_DropIntoIceHole);
	EndCondition((ZombieConditions)1);
	EndCondition((ZombieConditions)0x27);
	EndCondition((ZombieConditions)0x65);
	EndCondition((ZombieConditions)0x2c);
	EndCondition((ZombieConditions)0x18);
	EndCondition((ZombieConditions)2);
	EndCondition((ZombieConditions)0x38);
	EndCondition((ZombieConditions)0x29);
	EndCondition((ZombieConditions)3);
	EndCondition((ZombieConditions)4);
	EndCondition((ZombieConditions)0x39);
}

Sexy::SexyVector3 Zombie::LayerToWorld(const std::string& i_layerName)
{
	SexyVector2 offset;
	GetAnimRig()->CalcLayerTranslation(i_layerName, offset);
	offset -= GetZombieProps()->ArtCenter;
	offset *= GetConditionTracker().GetDrawScale();
	Sexy::SexyVector3 r = GetPosition();
	r.x += offset.x;
	r.y += offset.y;
	return r;
}

std::string Zombie::getElectrocutePAMName() const
{
	std::string name = "POPANIM_EFFECTS_ZOMBIE_SHOCK";
	if (!m_electrocuteColor.empty())
	{
		name += "_";
		name += Sexy::Upper(m_electrocuteColor);
	}
	return name;
}

void Zombie::onEnterState_Besiege(ZombieState i_arg)
{
	if (m_besiegeRate < 0.001f)
		m_besiegeRate = 3.0f;
	GetAnimRig()->PlayAndContinue("walk");
	GetNextBesiegeTarget();
}

void Zombie::PlayAidEffect()
{
	if (!GetAttachedEffect("pvpskill_aid"))
		AddAttachedEffect("pvpskill_aid", "POPANIM_ZOMBIE_ZOMBIE_PVPSKILL_AID", "f", Sexy::SexyVector3(0.0f, -40.0f, 0.0f), 1, true);
}

void Zombie::RemoveArmor(std::string i_armorFlags)
{
	for (std::vector<ArmorPtr>::iterator it = m_armor.begin(); it != m_armor.end(); ++it)
	{
		if ((*it)->GetArmorType() == i_armorFlags)
			(*it)->DestroyArmor();
	}
}

void Zombie::onEnterState_Attack(ZombieState i_arg)
{
	m_pCachedZombieAnimRig->PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate(GetPtr(), "onAttackAnimStopped"));
}

void Zombie::dropAllProjectiles()
{
	std::vector<RiftProjectileTimer>::iterator it = m_juggledProjectiles.begin();
	std::vector<RiftProjectileTimer>::iterator end = m_juggledProjectiles.end();
	for (; it != end; ++it)
	{
		RiftProjectileTimer timer = *it;
		if (timer.JuggledProjectile)
			timer.JuggledProjectile->Destroy();
	}
	m_juggledProjectiles.clear();
}

void Zombie::StuckIntoGround(const SexyVector3& i_boardPosition, pvztime_t i_stuckTime, pvztime_t i_underTime, float i_stuckHeight, pvztime_t i_intoGroundTime, bool hasStuckEffect)
{
	m_stuckTargetPos = i_boardPosition;
	m_stuckGoDownGroundSpeed = i_intoGroundTime == 0.0f ? 1.0f : 0.0f;
	m_stuckGoDownGroundTime = PVZ_T() + i_intoGroundTime;
	m_stuckIntoGroundTime = PVZ_T() + i_stuckTime;
	if (i_underTime > 0.0f)
	{
		m_isStuckedUnderGround = true;
		m_stuckUnderGroundTime = PVZ_T() + i_underTime;
		m_stuckIntoGroundTime += i_underTime;
	}
	m_hasStuckEffect = hasStuckEffect;
	m_stuckIntoGroundHeight = i_stuckHeight;
	gMessageRouter->Post(Message::ZombieStuckIntoGround, this);
	SetIgnoresAllDamage(true);
	SetIgnoreFindTarget(true);
	setZombieState(ZS_StuckInGround);
}

void Zombie::StuckIntoGround_2(const SexyVector3& i_boardPosition, pvztime_t i_stuckTime, pvztime_t i_underTime, float i_stuckHeight, pvztime_t i_intoGroundTime, bool hasStuckEffect)
{
	m_stuckTargetPos = i_boardPosition;
	m_stuckGoDownGroundSpeed = i_intoGroundTime == 0.0f ? 1.0f : 0.0f;
	m_stuckGoDownGroundTime = PVZ_T() + i_intoGroundTime;
	m_stuckIntoGroundTime = PVZ_T() + i_stuckTime;
	if (i_underTime > 0.0f)
	{
		m_isStuckedUnderGround = true;
		m_stuckUnderGroundTime = PVZ_T() + i_underTime;
		m_stuckIntoGroundTime += i_underTime;
	}
	m_hasStuckEffect = hasStuckEffect;
	m_stuckIntoGroundHeight = i_stuckHeight;
	gMessageRouter->Post(Message::ZombieStuckIntoGround, this);
	SetIgnoresAllDamage(false);
	SetIgnoreFindTarget(false);
	setZombieState(ZS_StuckInGround);
}

void Zombie::StormEntrance(int i_gridX, int i_gridY)
{
	Sexy::Point p = BoardTransforms::GridToBoardSpacePos(i_gridX, i_gridY);
	m_stormTargetLocation = SexyVector2((float)p.mX, (float)p.mY);
	SexyVector3 target = SexyVector3(m_stormTargetLocation.x, m_stormTargetLocation.y, 0.0f);
	SexyVector3 pos = target + SexyVector3(600.0f, 0.0f, 0.0f);
	SetPosition(pos);
	setZombieState(ZS_StormEntrance);
}

void Zombie::SetInvisibleState(InvisibleState state)
{
	InvisibleState oldState = m_invisibleState;
	if (oldState != state)
	{
		m_invisibleState = state;
		int alpha;
		if (state == Invisible_Not_Detected)
			alpha = 0x33;
		else
			alpha = state == Invisible_Detected ? 0xb2 : 0xff;
		Color color(Color::White);
		color.mAlpha = alpha;
		GetAnimRig()->SetPAMColor(color);
		SetIgnoresCollisions(m_invisibleState == Invisible_Not_Detected ? !m_canBeTargetedWhenInvisible : false);
		OnInvisibleStateChanged(oldState, m_invisibleState);
	}
}

void Zombie::DropAndHiddenAllZombieParticle()
{
	ZombieParticle* particle = DropArm();
	if (particle)
		particle->SetHidden(true);
	particle = DropHead();
	if (particle)
		particle->SetHidden(true);
	particle = DropHelm();
	if (particle)
		particle->SetHidden(true);
	for (size_t i = 0; i < m_armor.size(); i++)
	{
		particle = m_armor[i]->DropArmor((DamageTypeFlags)2);
		if (particle)
			particle->SetHidden(true);
	}
}

void Zombie::setupSkills(const std::vector<ZombieSkillData>& i_zombieSkillData, pvztime_t i_skillInterval)
{
	m_zombieSkills.clear();
	std::vector<ZombieSkillData>::const_iterator it = i_zombieSkillData.begin();
	std::vector<ZombieSkillData>::const_iterator end = i_zombieSkillData.end();
	for (; it != end; ++it)
	{
		ZombieSkill skill(*it);
		skill.ResetSkillTime();
		m_zombieSkills.push_back(skill);
	}
	m_delayTimeToPerformSkill = m_skillInterval = i_skillInterval;
}

void Zombie::onPostLoad()
{
	BoardEntity::onPostLoad();
	m_pCachedZombieAnimRig = m_animRig->CastChecked<ZombieAnimRig>();
	m_pCachedZombiePropertySheet = const_cast<ZombiePropertySheet*>(m_type->CastChecked<ZombieType>()->GetProps());
	m_pCachedZombieAnimRig->SetPopAnimCommandDelegate(Sexy::MakeDelegate(*this, &Zombie::onPopAnimCommand));
	if (gLawnApp->m_board && gLawnApp->m_board->m_juggledData.IsActivated)
		buildProjectileSets();
	onZombiePostLoad();
}

void Zombie::onEnterState_RiseFromPod(ZombieState i_arg)
{
	GetAnimRig()->PlayAndStop(spawnFromPodAnimationName, SELECT_EXACT, PopAnimRig::AnimStoppedDelegate());
	if (IsOnWaterTile(GetPosition()))
		m_groundEffect.SetGroundEffect(this, GetTideEffect(), true);
	else
		m_groundEffect.SetGroundEffect(this, (GroundEffectType)3, true);
	SetIsControlled(true);
}

void Zombie::updateState_RiseFromStorm()
{
	float t = std::min(getTimeInState(), 1.0f);
	float z = CurveLerp<float>(0.0f, 1.0f, t, -120.0f, 0.0f, CURVE_EASE_OUT);
	SexyVector3 pos = GetPosition();
	pos.z = z;
	SetPosition(pos);
	if (t >= 1.0f)
		SetWalkingState();
}

void Zombie::storeProjectileInJuggleLimbo(Projectile* i_projectile)
{
	ZombieJuggledData juggledData = gLawnApp->m_board->m_juggledData;
	i_projectile->SetHidden(true);
	i_projectile->SetPaused(true);
	RiftProjectileTimer timer;
	timer.JuggledProjectile = i_projectile->GetPtr();
	timer.ReturnTime = juggledData.JuggleLaunchDelay + m_accumulatedTime;
	m_juggledProjectiles.push_back(timer);
}

void Zombie::onEnterState_Walk(ZombieState i_arg)
{
	if (HasCondition((ZombieConditions)0x55) && HasCondition((ZombieConditions)0x8c))
		return;
	if (HasCondition((ZombieConditions)0x37))
	{
		m_pCachedZombieAnimRig->PlayEat();
		return;
	}
	m_pCachedZombieAnimRig->PlayWalk();
	SetFlag(m_zombieFlags, ZFLAG_UseAnimTranslation, true);
}

SexyVector3 Zombie::CalcPositionInTime(pvztime_t i_time)
{
	if (isInState(ZS_Walk) || isInState(ZS_BleedingOut) || IsFlying())
	{
		float walkSpeed = m_walkSpeed;
		float speed = m_conditionTracker.GetSpeedModifier();
		int width = BoardConstants::GRIDSQUARE_WIDTH();
		SexyVector3 r = GetPosition();
		r.x = r.x - i_time * walkSpeed * speed * GetFacingMultiplier() * (float)width;
		return r;
	}
	return GetPosition();
}

ZombieResistenceRank Zombie::GetResistenceRank(ZombieResistenceType i_type, ZombieTypePtr i_zombieType)
{
	float value = GetResistenceValue(i_type, i_zombieType);
	return GetResistenceRank(value);
}

ZombieResistenceRank Zombie::GetResistenceRank(float i_value)
{
	const ZombieResistenceConfig* config = ZombieResistenceConfig::GetConfig();
	ZombieResistenceRank rank = ZombieResistenceRank_D;
	if (config)
	{
		std::vector<ZombieResistenceConfig::ResistenceValueInfo>::const_iterator it = std::find_if(config->ResistenceValueInfos.begin(), config->ResistenceValueInfos.end(),
			[i_value](const ZombieResistenceConfig::ResistenceValueInfo& i_info) { return i_info.MinValue <= i_value && i_value < i_info.MaxValue; });
		if (it != config->ResistenceValueInfos.end())
			rank = (ZombieResistenceRank)std::distance(config->ResistenceValueInfos.begin(), it);
	}
	return rank;
}
