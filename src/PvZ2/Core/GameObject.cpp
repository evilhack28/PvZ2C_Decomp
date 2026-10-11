//
//  GameObject.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/ReflectionBuilder.h"

#include "GameObject.h"
#include "RtReflectionDelegate.h"
#include "GameEventMgr.h"

#include "AnimateArtifactMowerHolo.h"
#include "AnimateArtifactMowerSoulBell.h"
#include "AnimateArtifactMowerSwarm.h"
#include "AnimateArtifactMowerWithCalabash.h"
#include "AnimationControllerHelpers.h"
#include "AnimationMgr.h"
#include "ArmorflameClusterBomb.h"
#include "Artifact.h"
#include "ArtifactBoost.h"
#include "ArtifactGuitarTools.h"
#include "ArtifactPrismTowerTools.h"
#include "ArtifactSkateBoard.h"
#include "ArtifactSubsystem.h"
#include "ArtifactUFOTools.h"
#include "Barbarian.h"
#include "BladeKee.h"
#include "Board.h"
#include "BoardArtifactButton.h"
#include "BoardSaveState.h"
#include "Bomb.h"
#include "BonusChallengeModuleProperties.h"
#include "BossAircraft.h"
#include "CannonRocket.h"
#include "CardEffect.h"
#include "CardEffectSummonZombieWithPtero.h"
#include "CoinShowerSequence.h"
#include "ComponentBase.h"
#include "ComponentConditionRadius.h"
#include "ComponentDamageRadius.h"
#include "ComponentLightingDamageRadius.h"
#include "ComponentLinearBurst.h"
#include "ComponentObjectImpactor.h"
#include "ComponentOnDeath.h"
#include "ComponentPlantLauncher.h"
#include "ComponentProjectileConverter.h"
#include "ComponentPropagatedBurst.h"
#include "ComponentVisualStretcher.h"
#include "ComponentWarmingRadius.h"
#include "ComponentZombieMovement.h"
#include "ComponentZombieWhackTouch.h"
#include "CthulhuSubSystem.h"
#include "DandelionBomb.h"
#include "Effect_BouncingArrow.h"
#include "Effect_FloatingText.h"
#include "Effect_PopAnim.h"
#include "Effect_ScreenFade.h"
#include "Effect_StaticImage.h"
#include "EliminateColor.h"
#include "EliminateItem.h"
#include "FloatingIce.h"
#include "FlyingFireball.h"
#include "Fuse.h"
#include "GridItemPlacementChallengeModuleProps.h"
#include "GridSquareAlarmSagittifoliaFencePiece.h"
#include "GridSquareCoveringFlame.h"
#include "GridSquareCoveringPoison.h"
#include "GridSquareElectricCurrantFencePiece.h"
#include "GridSquareLaser.h"
#include "GridSquareMoonFlowerGlow.h"
#include "HeianStage.h"
#include "HighTideSign.h"
#include "HorsebeanPlane.h"
#include "HydraFlyingFireball.h"
#include "IntroWorldCup.h"
#include "JamStageMechanic.h"
#include "LawnMower.h"
#include "LevelModule.h"
#include "LightningBolt.h"
#include "LightningBoltToGround.h"
#include "LightningCloud.h"
#include "MoldColonyChallenge.h"
#include "MowerRemover.h"
#include "NewLightningBolt.h"
#include "NewRayEntity.h"
#include "Plant.h"
#include "Plant_AlarmSagittifolia.h"
#include "Plant_Armorflame.h"
#include "Plant_CarrotLauncher.h"
#include "Plant_ColdSnapdragon.h"
#include "Plant_CrownFlower.h"
#include "Plant_DevilsFlower.h"
#include "Plant_Egretflower.h"
#include "Plant_Elaeocarpus.h"
#include "Plant_ElectricBlueberry.h"
#include "Plant_ElectricCurrant.h"
#include "Plant_IcyCurrant.h"
#include "Plant_MagicShroom.h"
#include "Plant_Maybee.h"
#include "Plant_Olive.h"
#include "Plant_Snapdragon.h"
#include "FlyingObject.h"
#include "Plant_ThunderSnapdragon.h"
#include "PlantGroup.h"
#include "PooyanShooter.h"
#include "PVP/ZombiePVPSkill_Bomb.h"
#include "PVZ2UILotteryResult.h"
#include "RayEntity.h"
#include "RichManSquash.h"
#include "RiverCrossingDodoRider.h"
#include "RunningSubway.h"
#include "ScoreEffect.h"
#include "SharkMinion.h"
#include "Shield.h"
#include "SkatingGuacodile.h"
#include "Snake.h"
#include "SoccerGameModule.h"
#include "StarChallengeModule.h"
#include "StarLightningCloud.h"
#include "StarvingChomper.h"
#include "TutorialEffectMgr.h"
#include "TwinsAssistPerson.h"
#include "UISpacetimeEnergy.h"
#include "WhackAMoleModule.h"
#include "ZombieAction.h"
#include "ZombieCarnieMagician.h"
#include "ZombieGeneralActions.h"
#include "ZombieMirrorQueen.h"
#include "ZombieRomanHealerHealActionHandler.h"
#include "ZombieRomanMedusa.h"
#include "ZombieSkyCityElectric.h"
#include "ZombieSkyCityElectricElite.h"
#include "ZombieWithPushingAction.h"
#include "ZombieZombossMech_Beach.h"
#include "ZombieZombossMech_Dark.h"
#include "ZombieZombossMech_Dino.h"
#include "ZombieZombossMech_Eighties.h"
#include "ZombieZombossMech_IceAge.h"
#include "ZombieZombossMech_LostCity.h"
#include "ZombieZombossMech_Pirate.h"
#include "ZombieZombossMech_PVZ1_Robot.h"
#include "ZombieZombossMech_SkyCity.h"
#include "ZombieZombossMech_Steam.h"
#include "ZombossActions.h"
#include "ZombossCrosshair.h"
#include "ZombossHydraLobFireballsActionHandler.h"
#include "ZombossHydraPullActionHandler.h"
#include "ZombossHydraSpawnActionHandler.h"
#include "ZombossHydraSprayActionHandler.h"
#include "ZombossHydraWalkActionHandler.h"
#include "ZombossRocket.h"

/////////////// GameObject ///////////////

RT_CLASS_IMPLEMENT(GameObject);

void GameObject::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RtReflectionDelegateBase);
		REFLECTION_CLASSBUILDER_FIELD(RtId, m_objectId);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_methodName);
	REFLECTION_CLASSBUILDER_END(RtReflectionDelegateBase);

	REFLECTION_CLASSBUILDER_BEGIN(GameObject);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_thisPtr);
	REFLECTION_CLASSBUILDER_END(GameObject);
}

GameObject::GameObject(const GameObject& i_other)
	: RtObject(i_other)
	, m_thisPtr(i_other.m_thisPtr)
{
}

GameObject& GameObject::operator=(const GameObject& i_other)
{
	m_thisPtr = i_other.m_thisPtr;
	return *this;
}

GameObject::~GameObject()
{
}

RtWeakPtr<GameObject> GameObject::GetPtr() const
{
	return m_thisPtr;
}

bool GameObject::IsDestroyed() const
{
	return !m_thisPtr.IsValid();
}

void GameObject::registerForEvents()
{
}

void GameObject::onInitialized()
{
}

void GameObject::unregisterForEvents()
{
}

void GameObject::onPostLoad()
{
}

void GameObject::onDestroy()
{
}

void GameObject::initialize(RtId i_id)
{
	m_thisPtr = i_id;
	registerForEvents();
	onInitialized();
}

void GameObject::CallInitialize(RtId i_id)
{
	m_thisPtr = i_id;
}

void GameObject::Destroy()
{
	if (m_thisPtr.IsValid())
	{
		onDestroy();
		gMessageRouter->Unsubscribe(this);
		unregisterForEvents();

		RtWeakPtr<GameObject> thisPtr = m_thisPtr;
		m_thisPtr.ClearId();
		RtDb::GetDb()->ReleaseId(thisPtr);
	}
}

void GameObject::PostLoad()
{
	RtDb::GetDb()->SetObjectDeletionMode(m_thisPtr, RtDbTable::ODM_Deferred);
	registerForEvents();
	onPostLoad();
}

GameObject* GameObject::Create(RtClass* i_class, PVZDB::TableIndex i_inTable)
{
	GameObject* newObject = i_class->New()->CastChecked<GameObject>();

	RtId id;
	if (i_inTable != PVZDB::TABLE_INVALID)
	{
		id = PVZDB::GetInstance().GetTable(i_inTable)->AllocId(newObject, RtDbTable::ODM_Deferred, true, NULL);
	}

	newObject->initialize(id);
	return newObject;
}

bool GameObject::Serialize(const RtSerializeContext& inContext)
{
	{
		RtSerialRtonSync* sync = inContext.GetSync();
		RtSerialRtonKey key("objdata");
		RtSerializeContext objContext(sync, key);
		RtObject::Serialize(objContext);
	}

	if (inContext.GetSync()->IsReading())
	{
		gMessageRouter->Broadcast(Message::GameObjectSerializedIn, this);
	}

	return true;
}

/////////////// Template instances ///////////////

template AircraftLine* GameObject::Create<AircraftLine>(PVZDB::TableIndex);
template AlarmSagittifoliaFence* GameObject::Create<AlarmSagittifoliaFence>(PVZDB::TableIndex);
template AnimateArtifactMower* GameObject::Create<AnimateArtifactMower>(PVZDB::TableIndex);
template AnimateArtifactMowerGuitar* GameObject::Create<AnimateArtifactMowerGuitar>(PVZDB::TableIndex);
template AnimateArtifactMowerHolo* GameObject::Create<AnimateArtifactMowerHolo>(PVZDB::TableIndex);
template AnimateArtifactMowerSoulBell* GameObject::Create<AnimateArtifactMowerSoulBell>(PVZDB::TableIndex);
template AnimateArtifactMowerSwarm* GameObject::Create<AnimateArtifactMowerSwarm>(PVZDB::TableIndex);
template AnimateArtifactMowerWithCalabash* GameObject::Create<AnimateArtifactMowerWithCalabash>(PVZDB::TableIndex);
template AnimateArtifactMowerWithPrismTower* GameObject::Create<AnimateArtifactMowerWithPrismTower>(PVZDB::TableIndex);
template AnimateBombs* GameObject::Create<AnimateBombs>(PVZDB::TableIndex);
template AnimateLawnMowers* GameObject::Create<AnimateLawnMowers>(PVZDB::TableIndex);
template AnimationMgr* GameObject::Create<AnimationMgr>(PVZDB::TableIndex);
template AnimMgrSendAudioEvent* GameObject::Create<AnimMgrSendAudioEvent>(PVZDB::TableIndex);
template ArmorflameClusterBomb* GameObject::Create<ArmorflameClusterBomb>(PVZDB::TableIndex);
template ArtifactBeeEntity* GameObject::Create<ArtifactBeeEntity>(PVZDB::TableIndex);
template ArtifactBoostPropertySheet* GameObject::Create<ArtifactBoostPropertySheet>(PVZDB::TableIndex);
template Barbarian* GameObject::Create<Barbarian>(PVZDB::TableIndex);
template BladeKee* GameObject::Create<BladeKee>(PVZDB::TableIndex);
template BlueberryZapCloud* GameObject::Create<BlueberryZapCloud>(PVZDB::TableIndex);
template BoardEntity_Football* GameObject::Create<BoardEntity_Football>(PVZDB::TableIndex);
template BoardSaveState* GameObject::Create<BoardSaveState>(PVZDB::TableIndex);
template Bomb* GameObject::Create<Bomb>(PVZDB::TableIndex);
template BonusChallengeModuleProperties* GameObject::Create<BonusChallengeModuleProperties>(PVZDB::TableIndex);
template BouncingArrow* GameObject::Create<BouncingArrow>(PVZDB::TableIndex);
template CannonRocket* GameObject::Create<CannonRocket>(PVZDB::TableIndex);
template CardEffectProcessor* GameObject::Create<CardEffectProcessor>(PVZDB::TableIndex);
template CarrotMissile* GameObject::Create<CarrotMissile>(PVZDB::TableIndex);
template CoinShowerSequence* GameObject::Create<CoinShowerSequence>(PVZDB::TableIndex);
template ColdSnapdragonFlyDragon* GameObject::Create<ColdSnapdragonFlyDragon>(PVZDB::TableIndex);
template ComponentConditionRadius* GameObject::Create<ComponentConditionRadius>(PVZDB::TableIndex);
template ComponentDamageRadius* GameObject::Create<ComponentDamageRadius>(PVZDB::TableIndex);
template ComponentDamageTossRadius* GameObject::Create<ComponentDamageTossRadius>(PVZDB::TableIndex);
template ComponentLightingDamageRadius* GameObject::Create<ComponentLightingDamageRadius>(PVZDB::TableIndex);
template ComponentLinearBurst* GameObject::Create<ComponentLinearBurst>(PVZDB::TableIndex);
template ComponentObjectImpactor* GameObject::Create<ComponentObjectImpactor>(PVZDB::TableIndex);
template ComponentOnDeath_SpawnZombie* GameObject::Create<ComponentOnDeath_SpawnZombie>(PVZDB::TableIndex);
template ComponentPlantLauncher* GameObject::Create<ComponentPlantLauncher>(PVZDB::TableIndex);
template ComponentProjectileConverter* GameObject::Create<ComponentProjectileConverter>(PVZDB::TableIndex);
template ComponentPropagatedBurst* GameObject::Create<ComponentPropagatedBurst>(PVZDB::TableIndex);
template ComponentRunner* GameObject::Create<ComponentRunner>(PVZDB::TableIndex);
template ComponentVisualStretcher* GameObject::Create<ComponentVisualStretcher>(PVZDB::TableIndex);
template ComponentWarmingRadius* GameObject::Create<ComponentWarmingRadius>(PVZDB::TableIndex);
template ComponentWarmingRadiusForHeroPlant* GameObject::Create<ComponentWarmingRadiusForHeroPlant>(PVZDB::TableIndex);
template ComponentZombieMovement* GameObject::Create<ComponentZombieMovement>(PVZDB::TableIndex);
template ComponentZombieWhackTouch* GameObject::Create<ComponentZombieWhackTouch>(PVZDB::TableIndex);
template CthulhuEyeballEasyButton* GameObject::Create<CthulhuEyeballEasyButton>(PVZDB::TableIndex);
template DandelionBomb* GameObject::Create<DandelionBomb>(PVZDB::TableIndex);
template DevilsParasiteEntity* GameObject::Create<DevilsParasiteEntity>(PVZDB::TableIndex);
template DrawMessage* GameObject::Create<DrawMessage>(PVZDB::TableIndex);
template Effect_BouncingArrow* GameObject::Create<Effect_BouncingArrow>(PVZDB::TableIndex);
template Effect_FloatingText* GameObject::Create<Effect_FloatingText>(PVZDB::TableIndex);
template Effect_HammerEffect* GameObject::Create<Effect_HammerEffect>(PVZDB::TableIndex);
template Effect_PopAnim* GameObject::Create<Effect_PopAnim>(PVZDB::TableIndex);
template Effect_ScreenFade* GameObject::Create<Effect_ScreenFade>(PVZDB::TableIndex);
template Effect_StaticImage* GameObject::Create<Effect_StaticImage>(PVZDB::TableIndex);
template EgretflowerPlane* GameObject::Create<EgretflowerPlane>(PVZDB::TableIndex);
template ElaeocarpusWind* GameObject::Create<ElaeocarpusWind>(PVZDB::TableIndex);
template ElectricArcStream* GameObject::Create<ElectricArcStream>(PVZDB::TableIndex);
template ElectricCurrantFence* GameObject::Create<ElectricCurrantFence>(PVZDB::TableIndex);
template EliminateColor* GameObject::Create<EliminateColor>(PVZDB::TableIndex);
template EliminateItem* GameObject::Create<EliminateItem>(PVZDB::TableIndex);
template ExplosionShakeBoard* GameObject::Create<ExplosionShakeBoard>(PVZDB::TableIndex);
template FloatingIce* GameObject::Create<FloatingIce>(PVZDB::TableIndex);
template FlyingFireball* GameObject::Create<FlyingFireball>(PVZDB::TableIndex);
template Fuse* GameObject::Create<Fuse>(PVZDB::TableIndex);
template GridItemPlacementChallengeModuleProps* GameObject::Create<GridItemPlacementChallengeModuleProps>(PVZDB::TableIndex);
template GridSquareAlarmSagittifoliaFencePiece* GameObject::Create<GridSquareAlarmSagittifoliaFencePiece>(PVZDB::TableIndex);
template GridSquareCoveringFlame* GameObject::Create<GridSquareCoveringFlame>(PVZDB::TableIndex);
template GridSquareCoveringPoison* GameObject::Create<GridSquareCoveringPoison>(PVZDB::TableIndex);
template GridSquareElectricCurrantFencePiece* GameObject::Create<GridSquareElectricCurrantFencePiece>(PVZDB::TableIndex);
template GridSquareElectricCurrantGlowPiece* GameObject::Create<GridSquareElectricCurrantGlowPiece>(PVZDB::TableIndex);
template GridSquareLaser* GameObject::Create<GridSquareLaser>(PVZDB::TableIndex);
template GridSquareMoonFlowerGlow* GameObject::Create<GridSquareMoonFlowerGlow>(PVZDB::TableIndex);
template HeianSmokeBomb* GameObject::Create<HeianSmokeBomb>(PVZDB::TableIndex);
template HighTideSign* GameObject::Create<HighTideSign>(PVZDB::TableIndex);
template HorsebeanPlane* GameObject::Create<HorsebeanPlane>(PVZDB::TableIndex);
template HydraFlyingFireball* GameObject::Create<HydraFlyingFireball>(PVZDB::TableIndex);
template IcyCurrantFence* GameObject::Create<IcyCurrantFence>(PVZDB::TableIndex);
template IntroBoardDispatch* GameObject::Create<IntroBoardDispatch>(PVZDB::TableIndex);
template IntroWorldCupIconWidget* GameObject::Create<IntroWorldCupIconWidget>(PVZDB::TableIndex);
template JamStageMechanic* GameObject::Create<JamStageMechanic>(PVZDB::TableIndex);
template LawnMower* GameObject::Create<LawnMower>(PVZDB::TableIndex);
template LevelModuleDifficultyUIProps* GameObject::Create<LevelModuleDifficultyUIProps>(PVZDB::TableIndex);
template LightningBolt* GameObject::Create<LightningBolt>(PVZDB::TableIndex);
template LightningBoltToGround* GameObject::Create<LightningBoltToGround>(PVZDB::TableIndex);
template LightningCloud* GameObject::Create<LightningCloud>(PVZDB::TableIndex);
template LotteryResultIconWidget* GameObject::Create<LotteryResultIconWidget>(PVZDB::TableIndex);
template MagicCard* GameObject::Create<MagicCard>(PVZDB::TableIndex);
template MaybeeBee* GameObject::Create<MaybeeBee>(PVZDB::TableIndex);
template MoldColonyChallengeProps* GameObject::Create<MoldColonyChallengeProps>(PVZDB::TableIndex);
template MoveBoard* GameObject::Create<MoveBoard>(PVZDB::TableIndex);
template MowerRemover* GameObject::Create<MowerRemover>(PVZDB::TableIndex);
template NewLightningBolt* GameObject::Create<NewLightningBolt>(PVZDB::TableIndex);
template NewRayEntity* GameObject::Create<NewRayEntity>(PVZDB::TableIndex);
template OliveOilUnit* GameObject::Create<OliveOilUnit>(PVZDB::TableIndex);
template PenetratingRayEntity* GameObject::Create<PenetratingRayEntity>(PVZDB::TableIndex);
template Plant* GameObject::Create<Plant>(PVZDB::TableIndex);
template PlantGroup* GameObject::Create<PlantGroup>(PVZDB::TableIndex);
template PooyanShooter* GameObject::Create<PooyanShooter>(PVZDB::TableIndex);
template PteroFlyWithZombieEntity* GameObject::Create<PteroFlyWithZombieEntity>(PVZDB::TableIndex);
template PVPSkillBombRocket* GameObject::Create<PVPSkillBombRocket>(PVZDB::TableIndex);
template RayEntity* GameObject::Create<RayEntity>(PVZDB::TableIndex);
template RichManSquash* GameObject::Create<RichManSquash>(PVZDB::TableIndex);
template RiverCrossingDodoRider* GameObject::Create<RiverCrossingDodoRider>(PVZDB::TableIndex);
template RunningPlayer* GameObject::Create<RunningPlayer>(PVZDB::TableIndex);
template ScoreEffect* GameObject::Create<ScoreEffect>(PVZDB::TableIndex);
template ShakeBoard* GameObject::Create<ShakeBoard>(PVZDB::TableIndex);
template SharkMinion* GameObject::Create<SharkMinion>(PVZDB::TableIndex);
template Shield* GameObject::Create<Shield>(PVZDB::TableIndex);
template ShowAdvice* GameObject::Create<ShowAdvice>(PVZDB::TableIndex);
template SilverkeyTentacleShadow* GameObject::Create<SilverkeyTentacleShadow>(PVZDB::TableIndex);
template SkateBoardMower* GameObject::Create<SkateBoardMower>(PVZDB::TableIndex);
template SkatingGuacodile* GameObject::Create<SkatingGuacodile>(PVZDB::TableIndex);
template SnakeNode* GameObject::Create<SnakeNode>(PVZDB::TableIndex);
template SnapdragonFlyDragon* GameObject::Create<SnapdragonFlyDragon>(PVZDB::TableIndex);
template StarChallengeModuleProperties* GameObject::Create<StarChallengeModuleProperties>(PVZDB::TableIndex);
template StarLightningCloud* GameObject::Create<StarLightningCloud>(PVZDB::TableIndex);
template StarvingChomper* GameObject::Create<StarvingChomper>(PVZDB::TableIndex);
template ThunderSnapdragonFlyDragon* GameObject::Create<ThunderSnapdragonFlyDragon>(PVZDB::TableIndex);
template TimeEnergyAnimation* GameObject::Create<TimeEnergyAnimation>(PVZDB::TableIndex);
template TimeEvent* GameObject::Create<TimeEvent>(PVZDB::TableIndex);
template TutorialIconEffect* GameObject::Create<TutorialIconEffect>(PVZDB::TableIndex);
template TwinsAssistPerson* GameObject::Create<TwinsAssistPerson>(PVZDB::TableIndex);
template UFO* GameObject::Create<UFO>(PVZDB::TableIndex);
template WatergunBeamEntity* GameObject::Create<WatergunBeamEntity>(PVZDB::TableIndex);
template ZombieDropZombiesOnBoardActionHandler* GameObject::Create<ZombieDropZombiesOnBoardActionHandler>(PVZDB::TableIndex);
template ZombieElectricProjectileActionHandler* GameObject::Create<ZombieElectricProjectileActionHandler>(PVZDB::TableIndex);
template ZombieEliteElectricProjectileActionHandler* GameObject::Create<ZombieEliteElectricProjectileActionHandler>(PVZDB::TableIndex);
template ZombieIdleActionHandler* GameObject::Create<ZombieIdleActionHandler>(PVZDB::TableIndex);
template ZombieInstantTargetAttackActionHandler* GameObject::Create<ZombieInstantTargetAttackActionHandler>(PVZDB::TableIndex);
template ZombieMirrorQueenIdleActionHandler* GameObject::Create<ZombieMirrorQueenIdleActionHandler>(PVZDB::TableIndex);
template ZombieMirrorQueenMirrorMagicActionHandler* GameObject::Create<ZombieMirrorQueenMirrorMagicActionHandler>(PVZDB::TableIndex);
template ZombieMirrorQueenSummonActionHandler* GameObject::Create<ZombieMirrorQueenSummonActionHandler>(PVZDB::TableIndex);
template ZombiePlayAnimationActionHandler* GameObject::Create<ZombiePlayAnimationActionHandler>(PVZDB::TableIndex);
template ZombieProjectileActionHandler* GameObject::Create<ZombieProjectileActionHandler>(PVZDB::TableIndex);
template ZombieProjectileEliteActionHandler* GameObject::Create<ZombieProjectileEliteActionHandler>(PVZDB::TableIndex);
template ZombieProjectileLaunchActionHandler* GameObject::Create<ZombieProjectileLaunchActionHandler>(PVZDB::TableIndex);
template ZombiePushGriditemActionHandler* GameObject::Create<ZombiePushGriditemActionHandler>(PVZDB::TableIndex);
template ZombieRomanHealerHealActionHandler* GameObject::Create<ZombieRomanHealerHealActionHandler>(PVZDB::TableIndex);
template ZombieRomanMedusaPetrifyActionHandler* GameObject::Create<ZombieRomanMedusaPetrifyActionHandler>(PVZDB::TableIndex);
template ZombieSpawnActionHandler* GameObject::Create<ZombieSpawnActionHandler>(PVZDB::TableIndex);
template ZombieSpawnArtifactDoveActionHandler* GameObject::Create<ZombieSpawnArtifactDoveActionHandler>(PVZDB::TableIndex);
template ZombieStunActionHandler* GameObject::Create<ZombieStunActionHandler>(PVZDB::TableIndex);
template ZombieTeleportActionHandler* GameObject::Create<ZombieTeleportActionHandler>(PVZDB::TableIndex);
template ZombieTimedActionHandler* GameObject::Create<ZombieTimedActionHandler>(PVZDB::TableIndex);
template ZombieWalkActionHandler* GameObject::Create<ZombieWalkActionHandler>(PVZDB::TableIndex);
template ZombossBeachDiveActionHandler* GameObject::Create<ZombossBeachDiveActionHandler>(PVZDB::TableIndex);
template ZombossCoverUpActionHandler* GameObject::Create<ZombossCoverUpActionHandler>(PVZDB::TableIndex);
template ZombossCrosshair* GameObject::Create<ZombossCrosshair>(PVZDB::TableIndex);
template ZombossDarkFireBreathActionHandler* GameObject::Create<ZombossDarkFireBreathActionHandler>(PVZDB::TableIndex);
template ZombossDarkLobFireballsActionHandler* GameObject::Create<ZombossDarkLobFireballsActionHandler>(PVZDB::TableIndex);
template ZombossDarkSpawnActionHandler* GameObject::Create<ZombossDarkSpawnActionHandler>(PVZDB::TableIndex);
template ZombossDarkWalkActionHandler* GameObject::Create<ZombossDarkWalkActionHandler>(PVZDB::TableIndex);
template ZombossDinoLaserActionHandler* GameObject::Create<ZombossDinoLaserActionHandler>(PVZDB::TableIndex);
template ZombossDinoWalkActionHandler* GameObject::Create<ZombossDinoWalkActionHandler>(PVZDB::TableIndex);
template ZombossDropSandbagActionHandler* GameObject::Create<ZombossDropSandbagActionHandler>(PVZDB::TableIndex);
template ZombossDropZombieActionHandler* GameObject::Create<ZombossDropZombieActionHandler>(PVZDB::TableIndex);
template ZombossEightiesDropSpeakerActionHandler* GameObject::Create<ZombossEightiesDropSpeakerActionHandler>(PVZDB::TableIndex);
template ZombossEightiesFireSpeakerRayActionHandler* GameObject::Create<ZombossEightiesFireSpeakerRayActionHandler>(PVZDB::TableIndex);
template ZombossEightiesSwapJamActionHandler* GameObject::Create<ZombossEightiesSwapJamActionHandler>(PVZDB::TableIndex);
template ZombossFanPullActionHandler* GameObject::Create<ZombossFanPullActionHandler>(PVZDB::TableIndex);
template ZombossFireActionHandler* GameObject::Create<ZombossFireActionHandler>(PVZDB::TableIndex);
template ZombossFreezingWindRowActionHandler* GameObject::Create<ZombossFreezingWindRowActionHandler>(PVZDB::TableIndex);
template ZombossHelmLostActionHandler* GameObject::Create<ZombossHelmLostActionHandler>(PVZDB::TableIndex);
template ZombossHydraLobFireballsActionHandler* GameObject::Create<ZombossHydraLobFireballsActionHandler>(PVZDB::TableIndex);
template ZombossHydraPullActionHandler* GameObject::Create<ZombossHydraPullActionHandler>(PVZDB::TableIndex);
template ZombossHydraSpawnActionHandler* GameObject::Create<ZombossHydraSpawnActionHandler>(PVZDB::TableIndex);
template ZombossHydraSprayActionHandler* GameObject::Create<ZombossHydraSprayActionHandler>(PVZDB::TableIndex);
template ZombossHydraWalkActionHandler* GameObject::Create<ZombossHydraWalkActionHandler>(PVZDB::TableIndex);
template ZombossImpCannonActionHandler* GameObject::Create<ZombossImpCannonActionHandler>(PVZDB::TableIndex);
template ZombossJumpActionHandler* GameObject::Create<ZombossJumpActionHandler>(PVZDB::TableIndex);
template ZombossRobotAirDropZombieActionHandler* GameObject::Create<ZombossRobotAirDropZombieActionHandler>(PVZDB::TableIndex);
template ZombossRobotBaseZombieActionHandler* GameObject::Create<ZombossRobotBaseZombieActionHandler>(PVZDB::TableIndex);
template ZombossRobotSpawnNormalZombieActionHandler* GameObject::Create<ZombossRobotSpawnNormalZombieActionHandler>(PVZDB::TableIndex);
template ZombossRobotSpitOutBallActionHandler* GameObject::Create<ZombossRobotSpitOutBallActionHandler>(PVZDB::TableIndex);
template ZombossRobotThrowCarActionHandler* GameObject::Create<ZombossRobotThrowCarActionHandler>(PVZDB::TableIndex);
template ZombossRobotTrampleActionHandler* GameObject::Create<ZombossRobotTrampleActionHandler>(PVZDB::TableIndex);
template ZombossRocket* GameObject::Create<ZombossRocket>(PVZDB::TableIndex);
template ZombossRushActionHandler* GameObject::Create<ZombossRushActionHandler>(PVZDB::TableIndex);
template ZombossSharkMinionAttackActionHandler* GameObject::Create<ZombossSharkMinionAttackActionHandler>(PVZDB::TableIndex);
template ZombossSkyCityAttackNearByActionHandler* GameObject::Create<ZombossSkyCityAttackNearByActionHandler>(PVZDB::TableIndex);
template ZombossSkyCityBarrageActionHandler* GameObject::Create<ZombossSkyCityBarrageActionHandler>(PVZDB::TableIndex);
template ZombossSkyCityLineShootActionHandler* GameObject::Create<ZombossSkyCityLineShootActionHandler>(PVZDB::TableIndex);
template ZombossSkyCityRushDownActionHandler* GameObject::Create<ZombossSkyCityRushDownActionHandler>(PVZDB::TableIndex);
template ZombossSkyCitySandstormActionHandler* GameObject::Create<ZombossSkyCitySandstormActionHandler>(PVZDB::TableIndex);
template ZombossSkyCitySpawnActionHandler* GameObject::Create<ZombossSkyCitySpawnActionHandler>(PVZDB::TableIndex);
template ZombossSkyCityThrowAircraftActionHandler* GameObject::Create<ZombossSkyCityThrowAircraftActionHandler>(PVZDB::TableIndex);
template ZombossSkyCityWalkActionHandler* GameObject::Create<ZombossSkyCityWalkActionHandler>(PVZDB::TableIndex);
template ZombossSpawnActionHandler* GameObject::Create<ZombossSpawnActionHandler>(PVZDB::TableIndex);
template ZombossSpawnDinoActionHandler* GameObject::Create<ZombossSpawnDinoActionHandler>(PVZDB::TableIndex);
template ZombossSpawnGlacierColumnActionHandler* GameObject::Create<ZombossSpawnGlacierColumnActionHandler>(PVZDB::TableIndex);
template ZombossSpawnShieldActionHandler* GameObject::Create<ZombossSpawnShieldActionHandler>(PVZDB::TableIndex);
template ZombossSteamFireActionHandler* GameObject::Create<ZombossSteamFireActionHandler>(PVZDB::TableIndex);
template ZombossSteamImpCannonActionHandler* GameObject::Create<ZombossSteamImpCannonActionHandler>(PVZDB::TableIndex);
template ZombossSteamJumpActionHandler* GameObject::Create<ZombossSteamJumpActionHandler>(PVZDB::TableIndex);
template ZombossSteamRandomJumpActionHandler* GameObject::Create<ZombossSteamRandomJumpActionHandler>(PVZDB::TableIndex);
template ZombossSteamRestActionHandler* GameObject::Create<ZombossSteamRestActionHandler>(PVZDB::TableIndex);
template ZombossSteamRushActionHandler* GameObject::Create<ZombossSteamRushActionHandler>(PVZDB::TableIndex);
template ZombossSteamSpawnActionHandler* GameObject::Create<ZombossSteamSpawnActionHandler>(PVZDB::TableIndex);
template ZombossSteamThrowActionHandler* GameObject::Create<ZombossSteamThrowActionHandler>(PVZDB::TableIndex);
template ZombossSteamTrainSpawnActionHandler* GameObject::Create<ZombossSteamTrainSpawnActionHandler>(PVZDB::TableIndex);
template ZombossSummonActionHandler* GameObject::Create<ZombossSummonActionHandler>(PVZDB::TableIndex);
template ZombossWalkActionHandler* GameObject::Create<ZombossWalkActionHandler>(PVZDB::TableIndex);

template Effect_BouncingArrow* GameObject::CreateOutsideTable<Effect_BouncingArrow>();
template Effect_HammerEffect* GameObject::CreateOutsideTable<Effect_HammerEffect>();
template Effect_PopAnim* GameObject::CreateOutsideTable<Effect_PopAnim>();
template Effect_StaticImage* GameObject::CreateOutsideTable<Effect_StaticImage>();
