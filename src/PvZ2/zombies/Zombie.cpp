//
//  Zombie.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-03.
//

#include "Zombie.h"

#include "TimeMgr.h"

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
