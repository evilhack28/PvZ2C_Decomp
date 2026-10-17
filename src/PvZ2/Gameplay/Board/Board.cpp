//
//  Board.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Board.h"
#include "ActionSubSystem.h"
#include "AircraftSubSystem.h"
#include "ArenaEditPlantCursor.h"
#include "AudioMgr.h"
#include "HardLevelModule.h"
#include "Creature.h"
#include "Projectile.h"
#include "LawnMower.h"
#include "UISpringFestivalActivity.h"
#include "MessageWidget.h"
#include "TransitionOverlayWidget.h"
#include "PVPManager.h"
namespace RiftUtils { bool IsPlayingRiftLevel(); int GetZombieLevel(); }
#include "Artifact.h"
#include "ArtifactArcadeTools.h"
#include "ArtifactDinosaurHornTools.h"
#include "ArtifactGashaponTools.h"
#include "ArtifactGuitarTools.h"
#include "ArtifactPrismTowerTools.h"
#include "ArtifactSubsystem.h"
#include "ArtifactUFOTools.h"
#include "BeghouledModule.h"
#include "BoardArtifactButton.h"
#include "ZombiePropertySheet.h"
#include "BoardHeroPlantButton.h"
#include "BoardPropertySheet.h"
#include "BoardTransforms.h"
#include "CardSystem.h"
#include "ComponentPlantLauncher.h"
#include "CthulhuSubSystem.h"
#include "DropShipModule.h"
#include "Effect_BeachWaterWave.h"
#include "Effect_BouncingArrow.h"
#include "Effect_DinoFootShadow.h"
#include "Effect_DinoRun.h"
#include "Effect_FloatingText.h"
#include "Effect_GroundEffects.h"
#include "Effect_PlayFrame.h"
#include "Effect_PopAnim.h"
#include "Effect_StaticImage.h"
#include "Effect_WalrusEarthTile.h"
#include "Effect_ZombieGate.h"
#include "Effect_ZombossCrosshair.h"
#include "Effect_ZombossRocket.h"
#include "FairyTaleFogWaveAction.h"
#include "GoldRoadModule.h"
#include "GridItemMagicMirror.h"
#include "GridItemSnowBall.h"
#include "GridItemTileSubSystem.h"
#include "GridItemWalrusStatue.h"
#include "GridItemZombieBuffTile.h"
#include "GridItemZombieTent.h"
#include "GridSquareAlarmSagittifoliaFencePiece.h"
#include "GridSquareMoonFlowerGlow.h"
#include "HeianStage.h"
#include "HeianWindSystem.h"
#include "HeroPlant.h"
#include "IntrosWhackAMole.h"
#include "LevelDefinition.h"
#include "LevelReplaySubsystem.h"
#include "LevelScoringSubsystem.h"
#include "NewPVPData.h"
#include "NewPVPGame.h"
#include "PirateStage.h"
#include "PlantGroupSubsystem.h"
#include "Plant_AlarmSagittifolia.h"
#include "Plant_BambooSpartan.h"
#include "Plant_Banana.h"
#include "Plant_Beercoconut.h"
#include "Plant_BirthSunflower.h"
#include "Plant_BurdockBatter.h"
#include "Plant_ByttneriaMeteorHammer.h"
#include "Plant_CarrotLauncher.h"
#include "Plant_ChardGuard.h"
#include "Plant_Chilibean_Subsystem.h"
#include "Plant_Citron.h"
#include "Plant_Cobcannon.h"
#include "Plant_Cracker.h"
#include "Plant_Egretflower.h"
#include "Plant_ElectricCurrant.h"
#include "Plant_Electricitea_Subsystem.h"
#include "Plant_Endurian.h"
#include "Plant_Ents.h"
#include "Plant_EscapeRoot.h"
#include "Plant_FireShroom.h"
#include "Plant_Fumeshroom.h"
#include "Plant_Garlic.h"
#include "Plant_GeraniiFencer.h"
#include "Plant_GhostPepper.h"
#include "Plant_Gluttonydragon.h"
#include "Plant_HappyLeek.h"
#include "Plant_HatMushroom.h"
#include "Plant_Inferno.h"
#include "Plant_IntensiveCarrot.h"
#include "Plant_JewelRabbit.h"
#include "Plant_LancerHoya.h"
#include "Plant_Lemon.h"
#include "Plant_LotusShower.h"
#include "Plant_MagicShroom.h"
#include "Plant_Magicbeans.h"
#include "Plant_MagnetShroom.h"
#include "Plant_Mangosteen.h"
#include "Plant_Maybee.h"
#include "Plant_MissileToe.h"
#include "Plant_MoonFlower.h"
#include "Plant_NarcissusShooter.h"
#include "Plant_Nightcap.h"
#include "Plant_NukeLauncher.h"
#include "Plant_Olive.h"
#include "Plant_OrchidMage.h"
#include "Plant_PhatBeet.h"
#include "Plant_PrimalRafflesia.h"
#include "Plant_Rafflesia.h"
#include "Plant_ShadowShroom.h"
#include "Plant_ShadowVanilla.h"
#include "Plant_SporeShroom.h"
#include "Plant_Stephania.h"
#include "Plant_SunBean.h"
#include "Plant_SweetPotato.h"
#include "Plant_TangleKelp.h"
#include "Plant_TupistraStalker.h"
#include "Plant_Waxgourd.h"
#include "Plant_ZoybeanPod.h"
#include "PlantfoodCaptureSubSystem.h"
#include "PowerTileSubsystem.h"
#include "PowerupManager.h"
#include "ReflectionBuilder.h"
#include "RiftTheme.h"
#include "RoofStage.h"
#include "RunningSubway.h"
#include "SeedBankModule.h"
#include "SkyCityStage.h"
#include "SmokeManhole.h"
#include "ThunderSubSystem.h"
#include "TideModule.h"
#include "WormHoleSystem.h"
#include "ZombieBallet.h"
#include "ZombieBlower_SubSystem.h"
#include "ZombieBungee.h"
#include "ZombieGum.h"
#include "ZombieLaneChangingSubsystem.h"
#include "ZombieLostCityGuide.h"
#include "ZombieMechDisco.h"
#include "ZombieMirrorQueen.h"
#include "ZombiePVPSkill_Aid.h"
#include "ZombiePVPSkill_Invisible.h"
#include "ZombiePull_SubSystem.h"
#include "ZombiePumpkinKnight.h"
#include "ZombieRaSubsystem.h"
#include "ZombieStabber_SubSystem.h"
#include "ZombieSurrenderSubsystem.h"
#include "ZombieTosser_SubSystem.h"
#include "ZombieYearMonster.h"
#include "ZombieZombossMech_PVZ1_Robot.h"
#include "Zombie_Camel_Subsystem.h"
#include "Zombie_Chicken_Subsystem.h"
#include "Zombie_IceYearMonster.h"
#include "Zombie_Piano_Subsystem.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(Board);

/////////////// Accessors ///////////////

bool Board::IsMiniBoard()
{
	return false;
}

const std::vector<BaseCursor*>& Board::GetCursors()
{
	return m_cursors;
}

const std::string& Board::GetLevel()
{
	return m_level;
}

std::vector<Sexy::Point>& Board::GetWalrusFoot()
{
	return m_vWalrusFoot;
}

const SunCurrency Board::GetSunCurrency()
{
	return m_sunCurrency;
}

BoardPanLocations* Board::GetBoardPanLocations()
{
	return &m_boardPanLocations;
}

const std::vector<Zombie*>& Board::GetZombies()
{
	return m_cachedZombies;
}

SeedBankModule* Board::GetSeedBankModule()
{
	return m_levelModuleManager->GetModuleByClass<SeedBankModule>();
}

bool Board::IsSunSpawningSuppressed() const
{
	return m_sunSpawningSuppressed;
}

bool Board::IsPlantGrowthAndDecayPaused() const
{
	return m_plantGrowthAndDecayPaused;
}

void Board::SetNeedShineKernelpult(bool i_shine)
{
	m_needShineKernelpults = i_shine;
}

void Board::SetCoinSpecialCollected(int amount)
{
	m_specialCoinCollected = amount;
}

int Board::GetCoinSpecialCollected()
{
	return m_specialCoinCollected;
}

bool Board::GetHasPlayerPreviouslyCompletedLevel()
{
	return m_levelPreviouslyCompleted;
}

void Board::SetHasPlayerPreviouslyCompletedLevel(bool i_override)
{
	m_levelPreviouslyCompleted = i_override;
}

BoardResult Board::GetBoardResult()
{
	return m_boardResult;
}

const BoardPropertySheet* Board::GetBoardProperties() const
{
	return m_boardProps;
}

const LevelDefinition* Board::GetLevelDefinition()
{
	return m_levelDefinition;
}

PowerupManager* Board::GetPowerupManager()
{
	return GetGameSubSystem<PowerupManager>();
}

BoardArtifactManager* Board::GetArtifactManager()
{
	return GetGameSubSystem<BoardArtifactManager>();
}

BoardHeroPlantManager* Board::GetBoardHeroPlantManager()
{
	return GetGameSubSystem<BoardHeroPlantManager>();
}

void Board::SetCollectableID_SunFromSky(const std::string& collectableID)
{
	m_collectableID_SunFromSky = collectableID;
}

bool Board::IsDangerRoom()
{
	if (GetLevelDefinition())
		return GetLevelDefinition()->IsDangerRoom;
	return false;
}

bool Board::IsBattleZ()
{
	if (GetLevelDefinition())
		return GetLevelDefinition()->IsJoust;
	return false;
}

bool Board::IsDisablePeavine()
{
	if (GetLevelDefinition())
		return GetLevelDefinition()->DisablePeavine;
	return false;
}

/////////////// Logic ///////////////

void Board::DestroyZomboss()
{
}

void Board::EndCannonLevel()
{
}

void Board::OnAppResumeFocus()
{
}

void Board::onZombieWarningEffectStarted()
{
}

void Board::OnAppLostFocus()
{
	 Board::PauseOnInterrupt();
}

void Board::OnPauseAdFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason)
{
}

void Board::onAppEnteredBackground()
{
	 Board::PauseOnInterrupt();
}

void Board::OnRechargeCurrencyChanged()
{
	 Board::checkAutoSunCollect();
}

void Board::KeyChar(SexyChar i_char)
{
}

void Board::KeyDown(KeyCode i_key)
{
}

void Board::ResumeGameplay()
{
	m_boardState = BOARDSTATE_PLAYING_LEVEL;
}

void Board::OnLossIsImminent()
{
	m_levelModuleManager->OnLossImminent();
}

void Board::PutIntoCinemaMode()
{
	SetState(BOARDSTATE_CINEMA);
}

void Board::PutIntoTutorialMode()
{
	SetState(BOARDSTATE_TUTORIAL);
}

void Board::SuppressSunSpawners(bool i_suppress)
{
	m_sunSpawningSuppressed = i_suppress;
}

void Board::SetkillZombieProductSunmoneyNum(int amount)
{
	m_killZombieProductSunmoneyNum = amount;
}

int Board::GetkillZombieProductSunmoneyNum()
{
	return m_killZombieProductSunmoneyNum;
}

bool Board::checkForPlayerWinCondition()
{
	if (m_levelModuleManager)
		return m_levelModuleManager->GetWinConditionsSatisfied();
	return false;
}

void Board::onZombossIntroCompleted()
{
	m_bNeedWarning = false;
	SetGameplayObjectPause(false);
}

void Board::AddPendingActivityPresentReward(const std::string& i_presentName)
{
	m_pendingActivityRewards.push_back(i_presentName);
}

void Board::updateState_INIT()
{
}

void Board::updateState_ZOMBOSS()
{
}

bool Board::RowCanHaveZombies(int i_row)
{
	if (i_row < 0 || i_row >= m_gridSizeY)
		return false;
	return m_plantRow[i_row] != PLANTROW_DIRT;
}

bool Board::CanTakeSunMoney(const int i_amount)
{
	return (int)m_sunCurrency + CountSunBeingCollected() >= i_amount;
}

void Board::Resize(int theX, int theY, int theWidth, int theHeight)
{
	Widget::Resize(theX, theY, theWidth, theHeight);
	m_audioListenerX = BoardTransforms::GridToBoardSpaceX(m_gridSizeX / 2);
}

void Board::setReasonPlayEnded(const EndOfPlayReason i_arg)
{
	m_reasonPlayEnded = i_arg;
}

EndOfPlayReason Board::GetReasonPlayEnded() const
{
	return (EndOfPlayReason)m_reasonPlayEnded;
}

uint8 Board::GetPlantfoodCount()
{
	return m_plantfoodCount;
}

uint8 Board::GetPlantfoodMax()
{
	return m_plantfoodCountMax;
}

const Sexy::Point Board::GetBoardBaseOffset()
{
	return m_boardBaseOffset;
}

bool Board::IsStarChallengeActive()
{
	return m_activeStarIndex >= 0;
}

bool Board::IsLevelEnded()
{
	return m_boardState == BOARDSTATE_ENDLEVEL;
}

StageModule* Board::GetStage()
{
	if (m_levelModuleManager)
		return m_levelModuleManager->GetStageModule();
	return nullptr;
}

bool Board::IsThereCachedCursor() const
{
	return m_cachedCursor != nullptr;
}

bool Board::IsCachedCursor(const BaseCursor* i_cursor) const
{
	return m_cachedCursor == i_cursor;
}

bool Board::PlayEndedInVictory() const
{
	return m_reasonPlayEnded == ENDOFPLAYREASON_WON;
}

std::vector<std::string> Board::GetBoardPlants()
{
	return m_boardPlants;
}

int Board::GetNumWaves()
{
	int numWaves;
	if (GetWaveGenerator())
		numWaves = GetWaveGenerator()->GetNumWaves();
	else if (GetWaveManager())
		numWaves = GetWaveManager()->GetWaveCount();
	else
		return 1;
	numWaves++;
	return numWaves > 0 ? numWaves : 1;
}

int Board::GetCurrentWave()
{
	int currentWave;
	if (GetWaveGenerator())
		currentWave = GetWaveGenerator()->GetCurrentWave();
	else
	{
		if (!GetWaveManager())
			return 0;
		currentWave = GetWaveManager()->GetCurrentWave();
	}
	if (currentWave < 0)
		currentWave = 0;
	return currentWave;
}

SunCurrency Board::GetSunCurrencyMax()
{
	if (GetLevelDefinition() && GetLevelDefinition()->IsArenaEdit)
		return PVPManager::GetInstancePtr()->GetPVPSunMax();
	return m_boardProps->MaxSunCurrency;
}

int Board::GetCurrentZombieMaxLevel()
{
	int level;
	bool isRift;
	HardLevelModule* hardModule = m_levelModuleManager ? m_levelModuleManager->GetModuleByClass<HardLevelModule>() : nullptr;
	if (hardModule)
	{
		level = hardModule->GetZombieLevel();
		isRift = RiftUtils::IsPlayingRiftLevel();
	}
	else
	{
		isRift = RiftUtils::IsPlayingRiftLevel();
		level = 1;
	}
	if (__builtin_expect(!!(isRift), 1))
		return RiftUtils::GetZombieLevel();
	return level;
}

void Board::OnZombieWarned(int i_row, int i_col, const std::string& i_narrativeID)
{
	m_finalWarningPointData.col = i_col;
	m_finalWarningPointData.row = i_row;
	SetGameplayObjectPause(true);
	m_warningText = i_narrativeID;
	m_totalWarningNumber = 3;
	setState(IntroState_LAUNCHING);
}

void Board::OnZombieAddedToBoard(Zombie* i_zombie)
{
	if (i_zombie->GetHasPlantFood())
		AudioMgr::GetInstancePtr()->SendEvent("Play_Zomb_Global_Nitro_Mvmt_Glow", nullptr);
}

/////////////// Powerups ///////////////

void Board::AddPowerup(const std::string& i_powerupName)
{
	GetGameSubSystem<PowerupManager>()->AddPowerup(i_powerupName);
}

void Board::RemovePowerup(const std::string& i_powerupName)
{
	GetGameSubSystem<PowerupManager>()->RemovePowerup(i_powerupName);
}

void Board::AddConveyorPowerup(const std::string& i_powerupName)
{
	GetGameSubSystem<PowerupManager>()->AddConveyorPowerup(i_powerupName);
}

void Board::SelectPowerup(const PowerupType* i_powerupType, const bool i_ignoreCost)
{
	GetGameSubSystem<PowerupManager>()->SelectPowerup(i_powerupType, i_ignoreCost);
}

void Board::ActivatePowerup()
{
	GetGameSubSystem<PowerupManager>()->ActivatePowerup();
}

void Board::DeactivatePowerup()
{
	GetGameSubSystem<PowerupManager>()->DeactivatePowerup();
}

void Board::CancelActivePowerup()
{
	GetGameSubSystem<PowerupManager>()->CancelActivePowerup();
}

BasePowerup* Board::GetSelectedPowerup()
{
	return GetGameSubSystem<PowerupManager>()->GetSelectedPowerup();
}

BasePowerup* Board::GetActivePowerup()
{
	return GetGameSubSystem<PowerupManager>()->GetActivePowerup();
}

/////////////// Misc ///////////////

void Board::ToggleShowPig()
{
	m_boardProps->ShowFPSPig = !m_boardProps->ShowFPSPig;
}

bool Board::IsPlayerAtWorldMap()
{
	return gLawnApp->HasPlayerUnlockedFeature(FEATURE_WORLDMAP);
}

bool Board::IsWorldNeedDropKey(std::string& i_worldName)
{
	gLawnApp->GetWorldMapList();
	return true;
}

void Board::RemoveBoardResource()
{
	if (m_levelModuleManager)
		m_levelModuleManager->UnloadAllZombies();
}

void Board::KillBoardFadeOverlay()
{
	m_boardFadeStartTime = m_boardFadeEndTime = PVZ_EOT();
}

void Board::SetLevelNameOverride(const SexyString& i_name)
{
	m_levelNameOverride = i_name;
}

void Board::ClearLowPriorityAdvice()
{
	if (m_currentAdvicePriority == ADVICE_PRIORITY_LOW)
		ClearAdvice();
}

void Board::ClearAdviceImmediately()
{
	ClearAdvice(SexyString(L""));
}

void Board::DisplayAdvice(const SexyString& i_advice, MessageStyle i_messageStyle, AdvicePriority i_advicePriority)
{
	if (i_advicePriority > m_currentAdvicePriority)
		return;
	if (i_messageStyle)
	{
		if (m_adviceDisplayed[i_advice])
			return;
		m_adviceDisplayed[i_advice] = true;
	}
	Sexy::PrimeText::Instance()->ClearGlyphCache();
	m_advice->SetLabel(i_advice, i_messageStyle);
	m_currentAdvice = i_advice;
	m_currentAdvicePriority = i_advicePriority;
}

void Board::DisplayAdviceAgain(const SexyString& i_advice, MessageStyle i_messageStyle, AdvicePriority i_advicePriority)
{
	if (i_messageStyle && m_adviceDisplayed[i_advice])
		m_adviceDisplayed[i_advice] = false;
	DisplayAdvice(i_advice, i_messageStyle, i_advicePriority);
}

ZombieTypePtr Board::GetZombieType(const std::string& i_zombieName)
{
	ZombieTypePtr zombieType = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName(i_zombieName);
	if (!zombieType.IsValid())
		zombieType = gLawnApp->m_board->GetStage()->ResolveZombieType(i_zombieName);
	return zombieType;
}

void Board::Pause(bool i_pauseGame)
{
	if (i_pauseGame)
	{
		if (!m_paused)
		{
			gMessageRouter->Post(&Message::GamePaused);
			if (m_levelModuleManager)
				m_levelModuleManager->OnPauseStateChange(i_pauseGame);
			TimeMgr::GetInstancePtr()->Pause(i_pauseGame);
			gLawnApp->GetTransitionOverlay()->WillStopTransition();
		}
	}
	else if (m_paused)
	{
		TimeMgr::GetInstancePtr()->Pause(i_pauseGame);
		gMessageRouter->Post(&Message::GameUnpaused);
		if (m_levelModuleManager)
			m_levelModuleManager->OnPauseStateChange(i_pauseGame);
	}
	m_paused = i_pauseGame;
}

void Board::DestroyAllMowers()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_BOARDENTITIES); it; ++it)
	{
		LawnMower* mower = Sexy::RtWeakPtr<Sexy::RtObject>(*it)->Cast<LawnMower>();
		if (mower)
			mower->Destroy();
	}
}

void Board::Quit()
{
	setReasonPlayEnded(ENDOFPLAYREASON_QUIT);
	m_boardResult = BOARDRESULT_QUIT;
	gMessageRouter->Post(&Message::GameplayEnded);
	SpringChargeManager::GetInstancePtr()->updateExpPlants();
	if (m_levelModuleManager)
		m_levelModuleManager->OnGameplayEnded();
	EndLevel();
	if (ProfileMgr::GetInstance().GetCurrentProfile()->IsInBossFightLevel())
	{
		switch (GetState())
		{
		case BOARDSTATE_PLAYER_WON_OUTRO:
			gMessageRouter->Post(&Message::CheckBossFightRate, true);
			break;
		case BOARDSTATE_PLAYER_LOST_OUTRO:
			gMessageRouter->Post(&Message::CheckBossFightRate, false);
			break;
		default:
			break;
		}
	}
	gMessageRouter->Post(&Message::MissionFinish);
}

void Board::ShakeBoard(int i_shakeAmountX, int i_shakeAmountY, pvztime_t duration)
{
	if (m_disableShakeBoard)
		return;
	if (__builtin_expect(!(duration > 0.f), 0))
		duration = 0.12f;
	::ShakeBoard* shake = ::ShakeBoard::Create()->Init(duration, i_shakeAmountX, i_shakeAmountY);
	m_animationMgr->Add(shake->GetPtr());
}

void Board::ExplosionShakeBoard(int i_xQuakeness, int i_yQuakeness, pvztime_t i_duration)
{
	::ExplosionShakeBoard* shake = ::ExplosionShakeBoard::Create()->Init(i_duration, i_xQuakeness, i_yQuakeness);
	m_animationMgr->Add(shake->GetPtr());
}

void Board::DestroyAllCreatures()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_CREATURES); it; ++it)
	{
		Sexy::RtWeakPtr<Creature> creature = *it;
		creature->Destroy();
	}
}

void Board::DestroyAllPlants()
{
	std::vector<BoardEntity*> plants;
	EntityFinder::GetEntities(plants, ENTITYTYPE_PLANT);
	size_t i = 0;
	size_t index;
	while (index = i, i++, index < plants.size())
		plants[index]->Destroy();
}

void Board::DestroyAllZombieProjectiles()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PROJECTILES); it; ++it)
	{
		ProjectilePtr projectile = *it;
		if (projectile->IsOnOpposingTeam(TEAM_PLANTS))
			projectile->Destroy();
	}
}

bool Board::IsCurrentLevelBeghouled()
{
	return m_levelModuleManager->GetModuleByClass<BeghouledModule>() != nullptr;
}

void Board::OnStealChristmasProtect()
{
	m_nStealChristmasProtectNum++;
}

/////////////// Street ///////////////

Point Board::GetStreetDimensions(ZombieTypePtr i_zombieType)
{
	const ZombiePropertySheet* props = i_zombieType->GetProps();
	return Point((int)props->StreetSize.x, (int)props->StreetSize.y);
}

Point Board::GetStreetCriticalDimensions(ZombieTypePtr i_zombieType)
{
	const ZombiePropertySheet* props = i_zombieType->GetProps();
	return Point((int)props->StreetCriticalSize.x, (int)props->StreetCriticalSize.y);
}

Point Board::GetStreetOffset(ZombieTypePtr i_zombieType)
{
	const ZombiePropertySheet* props = i_zombieType->GetProps();
	return Point((int)props->StreetOffset.x, (int)props->StreetOffset.y);
}

/////////////// Cursors ///////////////

void Board::ClearCachedCursor()
{
	if (m_cachedCursor)
	{
		m_cachedCursor->Destroy();
		if (m_cachedCursor)
		{
			delete m_cachedCursor;
			m_cachedCursor = nullptr;
		}
	}
}

bool Board::IsGameplayEnded()
{
	bool ended = false;
	if (GetState() == BOARDSTATE_PLAYER_WON_OUTRO || GetState() == BOARDSTATE_PLAYER_LOST_OUTRO || IsLevelEnded())
		ended = true;
	return ended;
}

void Board::Unload()
{
	if (m_levelModuleManager)
		m_levelModuleManager->Unload();
	gLawnApp->DeleteGroups(m_gameplayResources);
	m_gameplayResources.clear();
}

bool Board::HasPlantAt(const Point& i_gridPosition)
{
	PlantGroup* group = GetPlantGroupAt(i_gridPosition);
	if (!group)
		return false;
	return !group->Empty();
}

bool Board::HasPlantAt(Plant* i_plant, const Point& i_gridPosition)
{
	PlantGroup* group = GetPlantGroupAt(i_gridPosition);
	if (!group)
		return false;
	return group->HasPlant(PlantPtr(i_plant->GetPtr()));
}

void Board::SetArenaZombieAnim(PopAnimRig* i_animRig)
{
	if (m_arenaCursorAnimRig)
		delete m_arenaCursorAnimRig;
	m_arenaCursorAnimRig = i_animRig;
}

int Board::MakeGroundRenderOrder(int i_row, int i_layerOffset)
{
	int rowsFromBottom = BoardConstants::NUMBER_OF_ROWS() - i_row;
	return rowsFromBottom * -10000 + 300000 + i_layerOffset;
}

void Board::SetGameplayObjectPause(bool i_paused)
{
	SetSoftPause(i_paused);
	m_pauseGameplayObjects = i_paused;
}

void Board::LoadResourceGroupForGameplay(const std::string& i_groupName)
{
	m_resourceGroupNeedRelease.push_back(i_groupName);
	gLawnApp->LoadGroup(i_groupName);
	m_gameplayResources.push_back(i_groupName);
}

void Board::OnTreasureYetiTutorialFailed()
{
	m_bYetiDie = true;
	SaveGameState(false);
	gLawnApp->ShowYetiEscapeDialog();
}

SexyVector3 Board::GetFinalDestroyedZombiePosition()
{
	return m_finalDestroyedZombiePosition;
}

void Board::Move(int i_newX, int i_newY)
{
	Resize(i_newX, i_newY + m_boardBaseOffset.mY, mWidth, mHeight);
}

/////////////// Touch ///////////////

void Board::CancelTouch(const Sexy::Touch& i_touch, void* i_ignoredDelegateOwner)
{
	if (m_gameInputHandler)
		m_gameInputHandler->CancelTouch(i_touch, i_ignoredDelegateOwner);
}

void Board::UnregisterGesture(void* i_gestureOwner)
{
	if (m_gameInputHandler)
		m_gameInputHandler->UnregisterGesture(i_gestureOwner);
}

void Board::UnregisterLongPress(void* i_longPressOwner)
{
	if (m_gameInputHandler)
		m_gameInputHandler->UnregisterLongPress(i_longPressOwner);
}

void Board::UnregisterTouchGameplayObject(void* i_touchOwner)
{
	if (m_gameInputHandler)
		m_gameInputHandler->UnregisterTouchGameplayObject(i_touchOwner);
}

/////////////// Intro state machine ///////////////

void Board::onEnterState_INIT(IntroState i_fromState)
{
}

void Board::onExitState_INIT(IntroState i_toState)
{
}

void Board::onExitState_LAUNCHING(IntroState i_toState)
{
}

void Board::onEnterState_END(IntroState i_fromState)
{
}

void Board::onExitState_END(IntroState i_toState)
{
}

void Board::onExitState_ZOMBOSS(IntroState i_toState)
{
}

void Board::updateState_END()
{
	if (m_totalWarningNumber > 0)
	{
		m_totalWarningNumber--;
		setState(IntroState_LAUNCHING);
	}
	else
	{
		setState(IntroState_ZOMBOSS);
	}
}

int32 Board::getIntroStateSerialization()
{
	return m_IntroState.GetState();
}

bool Board::isInState(IntroState i_state) const
{
	return m_IntroState.GetState() == i_state;
}

void Board::TouchBegan(const Sexy::Touch& i_touch)
{
	handleTouch(i_touch);
}

void Board::TouchEnded(const Sexy::Touch& i_touch)
{
	handleTouch(i_touch);
}


/////////////// Regions ///////////////

bool Board::AcceptanceCallFunc(BoardRegion* pBoardRegion, BoardRegionFlags regionFlags)
{
	return pBoardRegion->HasFlags(regionFlags);
}

BoardRegion* Board::FindRegionWithFlags(BoardRegionFlags i_flags)
{
	std::vector<RtWeakPtr<BoardRegion> >::iterator it = m_boardRegions.begin();
	std::vector<RtWeakPtr<BoardRegion> >::iterator end = m_boardRegions.end();
	for (; it != end; ++it)
	{
		RtWeakPtr<BoardRegion> region = *it;
		if (region.Get()->HasFlags(i_flags))
			return region;
	}
	return nullptr;
}

BoardRegion* Board::FindRegionWithFlags(const SexyVector3& i_position, BoardRegionFlags i_flags)
{
	return findContainingRegion(i_position, i_flags, AcceptanceCallFunc);
}

BoardRegion* Board::FindRegionWithFlags(const Point& i_gridLoc, BoardRegionFlags i_flags)
{
	Point pos = BoardTransforms::GridToBoardSpaceUnbounded(i_gridLoc);
	return FindRegionWithFlags(SexyVector3(pos.mX, pos.mY, 0), i_flags);
}

bool Board::IsPitOfDoom(const Point& i_gridLoc)
{
	Point pos = BoardTransforms::GridToBoardSpaceUnbounded(i_gridLoc);
	return IsPitOfDoom(SexyVector3(pos.mX, pos.mY, 0));
}

bool Board::IsShallowWater(const Point& i_gridLoc)
{
	Point pos = BoardTransforms::GridToBoardSpaceUnbounded(i_gridLoc);
	return IsShallowWater(SexyVector3(pos.mX, pos.mY, 0));
}

bool Board::IsSky(const Point& i_gridLoc)
{
	Point pos = BoardTransforms::GridToBoardSpaceUnbounded(i_gridLoc);
	return IsSky(SexyVector3(pos.mX, pos.mY, 0));
}

bool Board::IsRoof(const Point& i_gridLoc)
{
	Point pos = BoardTransforms::GridToBoardSpaceUnbounded(i_gridLoc);
	return IsRoof(SexyVector3(pos.mX, pos.mY, 0));
}

bool Board::IsPitOfDoom(const SexyVector3& i_position)
{
	return FindRegionWithFlags(i_position, BOARDREGION_PitOfDoom) != nullptr;
}

bool Board::IsShallowWater(const SexyVector3& i_position)
{
	return FindRegionWithFlags(i_position, BOARDREGION_ShallowWater) != nullptr;
}

bool Board::IsSky(const SexyVector3& i_position)
{
	return FindRegionWithFlags(i_position, BOARDREGION_Sky) != nullptr;
}

bool Board::IsRoof(const SexyVector3& i_position)
{
	return FindRegionWithFlags(i_position, BOARDREGION_Roof) != nullptr;
}

/////////////// Template instantiations ///////////////

template ActionSubSystem* Board::GetGameSubSystem<ActionSubSystem>();
template AircraftSubSystem* Board::GetGameSubSystem<AircraftSubSystem>();
template AlarmSagittifoliaAvatarSkillSystem* Board::GetGameSubSystem<AlarmSagittifoliaAvatarSkillSystem>();
template AlarmSagittifoliaFenceSystem* Board::GetGameSubSystem<AlarmSagittifoliaFenceSystem>();
template ArenaEditPlantCursor* Board::GetCursorByClass<ArenaEditPlantCursor>();
template ArtifactArcadeSubSystem* Board::GetGameSubSystem<ArtifactArcadeSubSystem>();
template ArtifactDragonSubsystem* Board::GetGameSubSystem<ArtifactDragonSubsystem>();
template ArtifactGashaponSubSystem* Board::GetGameSubSystem<ArtifactGashaponSubSystem>();
template ArtifactMowerGuitar_Effect* Board::AddEffect<ArtifactMowerGuitar_Effect>();
template ArtifactPrismTowerSubSystem* Board::GetGameSubSystem<ArtifactPrismTowerSubSystem>();
template ArtifactSnowdriftSubSystem* Board::GetGameSubSystem<ArtifactSnowdriftSubSystem>();
template ArtifactUFOSubSystem* Board::GetGameSubSystem<ArtifactUFOSubSystem>();
template ArtifactWatergunSubSystem* Board::GetGameSubSystem<ArtifactWatergunSubSystem>();
template BananaLauncherSubSystem* Board::GetGameSubSystem<BananaLauncherSubSystem>();
template BeercoconutSubsystem* Board::GetGameSubSystem<BeercoconutSubsystem>();
template BoardArtifactManager* Board::GetGameSubSystem<BoardArtifactManager>();
template BoardHeroPlantManager* Board::FindGameSubSystem<BoardHeroPlantManager>();
template BoardHeroPlantManager* Board::GetGameSubSystem<BoardHeroPlantManager>();
template BoardRegionConcrete* Board::AddRegion<BoardRegionConcrete>();
template BoardRegionDeepWater* Board::AddRegion<BoardRegionDeepWater>();
template BoardRegionDisabledArea* Board::AddRegion<BoardRegionDisabledArea>();
template BoardRegionDrySand* Board::AddRegion<BoardRegionDrySand>();
template BoardRegionOppoent* Board::AddRegion<BoardRegionOppoent>();
template BoardRegionRoof* Board::AddRegion<BoardRegionRoof>();
template BoardRegionSky* Board::AddRegion<BoardRegionSky>();
template BoardRegionTideWater* Board::AddRegion<BoardRegionTideWater>();
template BuffShieldSubsystem* Board::GetGameSubSystem<BuffShieldSubsystem>();
template BungeeCounterSubSystem* Board::GetGameSubSystem<BungeeCounterSubSystem>();
template BurdockBatter_SubSystem* Board::GetGameSubSystem<BurdockBatter_SubSystem>();
template ByttneriaMeteorHammerTossSubSystem* Board::GetGameSubSystem<ByttneriaMeteorHammerTossSubSystem>();
template CannonEntrySubSystem* Board::GetGameSubSystem<CannonEntrySubSystem>();
template CardSystemManager* Board::GetGameSubSystem<CardSystemManager>();
template CarrotMissileSubsystem* Board::GetGameSubSystem<CarrotMissileSubsystem>();
template ContinuousDamageSystem* Board::GetGameSubSystem<ContinuousDamageSystem>();
template CthulhuSubSystem* Board::GetGameSubSystem<CthulhuSubSystem>();
template DropShipEffectAnim* Board::AddEffect<DropShipEffectAnim>();
template DropingImpEffectAnim* Board::AddEffect<DropingImpEffectAnim>();
template EffectCrackerDrop* Board::AddEffect<EffectCrackerDrop>();
template EffectPumpkinKnightBullRunning* Board::AddEffect<EffectPumpkinKnightBullRunning>();
template EffectTupistraAttack* Board::AddEffect<EffectTupistraAttack>();
template Effect_AirflowDown* Board::AddEffect<Effect_AirflowDown>();
template Effect_AirflowUp* Board::AddEffect<Effect_AirflowUp>();
template Effect_BeachWaterWave* Board::AddEffect<Effect_BeachWaterWave>();
template Effect_BigCrash* Board::AddEffect<Effect_BigCrash>();
template Effect_BouncingArrow* Board::AddEffect<Effect_BouncingArrow>();
template Effect_ChilibeanGasCloud* Board::AddEffect<Effect_ChilibeanGasCloud>();
template Effect_DinoFootShadow* Board::AddEffect<Effect_DinoFootShadow>();
template Effect_DinoFootShadow_For_Artifact_Dinosaur_horn* Board::AddEffect<Effect_DinoFootShadow_For_Artifact_Dinosaur_horn>();
template Effect_DinoRun* Board::AddEffect<Effect_DinoRun>();
template Effect_DinoRun_For_Artifact_Dinosaur_horn* Board::AddEffect<Effect_DinoRun_For_Artifact_Dinosaur_horn>();
template Effect_DropInWater* Board::AddEffect<Effect_DropInWater>();
template Effect_FloatingText* Board::AddEffect<Effect_FloatingText>();
template Effect_GarlicStinkLines* Board::AddEffect<Effect_GarlicStinkLines>();
template Effect_GroundEffectStun* Board::AddEffect<Effect_GroundEffectStun>();
template Effect_GumPoisonCloud* Board::AddEffect<Effect_GumPoisonCloud>();
template Effect_JewelRabbit_hole* Board::AddEffect<Effect_JewelRabbit_hole>();
template Effect_JewelRabbit_pioneer* Board::AddEffect<Effect_JewelRabbit_pioneer>();
template Effect_MistDown* Board::AddEffect<Effect_MistDown>();
template Effect_MistUp* Board::AddEffect<Effect_MistUp>();
template Effect_Mole* Board::AddEffect<Effect_Mole>();
template Effect_MusicalBoom* Board::AddEffect<Effect_MusicalBoom>();
template Effect_MusicalNote* Board::AddEffect<Effect_MusicalNote>();
template Effect_PassiveBall* Board::AddEffect<Effect_PassiveBall>();
template Effect_PlayFrame* Board::AddEffect<Effect_PlayFrame>();
template Effect_PoisonGas* Board::AddEffect<Effect_PoisonGas>();
template Effect_PopAnim* Board::AddEffect<Effect_PopAnim>();
template Effect_ProjectileHit* Board::AddEffect<Effect_ProjectileHit>();
template Effect_SmokeManhole* Board::AddEffect<Effect_SmokeManhole>();
template Effect_SmokePollution* Board::AddEffect<Effect_SmokePollution>();
template Effect_Snowdrift* Board::AddEffect<Effect_Snowdrift>();
template Effect_StaticImage* Board::AddEffect<Effect_StaticImage>();
template Effect_WalrusEarthTile* Board::AddEffect<Effect_WalrusEarthTile>();
template Effect_WalrusStatue* Board::AddEffect<Effect_WalrusStatue>();
template Effect_ZombieGate* Board::AddEffect<Effect_ZombieGate>();
template Effect_ZombieIceMove* Board::AddEffect<Effect_ZombieIceMove>();
template Effect_ZombossCrosshair* Board::AddEffect<Effect_ZombossCrosshair>();
template Effect_ZombossRocket* Board::AddEffect<Effect_ZombossRocket>();
template Effect_ZoybeanPodSmoke* Board::AddEffect<Effect_ZoybeanPodSmoke>();
template Effect_evolveLight* Board::AddEffect<Effect_evolveLight>();
template EgretflowerCountSubSystem* Board::GetGameSubSystem<EgretflowerCountSubSystem>();
template ElectricCurrantFenceSystem* Board::GetGameSubSystem<ElectricCurrantFenceSystem>();
template EndurianGasSubsystem* Board::GetGameSubSystem<EndurianGasSubsystem>();
template EntsSubsystem* Board::GetGameSubSystem<EntsSubsystem>();
template EscapeRootSubSystem* Board::GetGameSubSystem<EscapeRootSubSystem>();
template FairyTaleFogSubSystem* Board::GetGameSubSystem<FairyTaleFogSubSystem>();
template FallingStoneEffectAnim* Board::AddEffect<FallingStoneEffectAnim>();
template GarlicSubsystem* Board::GetGameSubSystem<GarlicSubsystem>();
template GeneratedLevelReplaySubsystem* Board::FindGameSubSystem<GeneratedLevelReplaySubsystem>();
template GeneratedLevelReplaySubsystem* Board::GetGameSubSystem<GeneratedLevelReplaySubsystem>();
template GeraniiFencerSubsystem* Board::GetGameSubSystem<GeraniiFencerSubsystem>();
template GhostPepperAttackAnim* Board::AddEffect<GhostPepperAttackAnim>();
template GluttonyFire_Effect* Board::AddEffect<GluttonyFire_Effect>();
template GoldRoadRegion* Board::AddRegion<GoldRoadRegion>();
template GridItemZombieMirrorQueenMirrorSubSystem* Board::GetGameSubSystem<GridItemZombieMirrorQueenMirrorSubSystem>();
template GuideEndDoor* Board::AddEffect<GuideEndDoor>();
template GuideStartDoor* Board::AddEffect<GuideStartDoor>();
template GumPoisonSubsystem* Board::GetGameSubSystem<GumPoisonSubsystem>();
template HappyLeek_badsmelleffect* Board::AddEffect<HappyLeek_badsmelleffect>();
template HatMushroomTransportSubSystem* Board::GetGameSubSystem<HatMushroomTransportSubSystem>();
template HeianSmokeBombSubsystem* Board::GetGameSubSystem<HeianSmokeBombSubsystem>();
template HeianWindSubsystem* Board::GetGameSubSystem<HeianWindSubsystem>();
template HeroPlantTalentSubsystem* Board::GetGameSubSystem<HeroPlantTalentSubsystem>();
template InfernoSubsystem* Board::GetGameSubSystem<InfernoSubsystem>();
template IntensiveCarrotRevivalSubsystem* Board::GetGameSubSystem<IntensiveCarrotRevivalSubsystem>();
template JewelRabbitTossSubSystem* Board::GetGameSubSystem<JewelRabbitTossSubSystem>();
template LemonRainDropperEffectAnim* Board::AddEffect<LemonRainDropperEffectAnim>();
template LemonRainEffectAnim* Board::AddEffect<LemonRainEffectAnim>();
template LevelRecordSubsystem* Board::GetGameSubSystem<LevelRecordSubsystem>();
template LevelReplaySubsystem* Board::FindGameSubSystem<LevelReplaySubsystem>();
template LevelReplaySubsystem* Board::GetGameSubSystem<LevelReplaySubsystem>();
template LevelScoringSubsystem* Board::GetGameSubSystem<LevelScoringSubsystem>();
template LoveTwoSun* Board::AddEffect<LoveTwoSun>();
template MagicHat* Board::AddEffect<MagicHat>();
template MagicMirrorTeleportationArraySubSystem* Board::GetGameSubSystem<MagicMirrorTeleportationArraySubSystem>();
template MagicbeansLauncherSubSystem* Board::GetGameSubSystem<MagicbeansLauncherSubSystem>();
template MagnetShroomSubSystem* Board::GetGameSubSystem<MagnetShroomSubSystem>();
template MangosteenElectricCircle* Board::AddEffect<MangosteenElectricCircle>();
template MangosteenElectricExplode* Board::AddEffect<MangosteenElectricExplode>();
template MissileToeLauncherSubSystem* Board::GetGameSubSystem<MissileToeLauncherSubSystem>();
template MoonFlowerGlowAnimEffect* Board::AddEffect<MoonFlowerGlowAnimEffect>();
template MoonFlowerPoweredTilesSubsystem* Board::GetGameSubSystem<MoonFlowerPoweredTilesSubsystem>();
template NarcissusShooter_Effect_PopAnim* Board::AddEffect<NarcissusShooter_Effect_PopAnim>();
template NewPVPDataSubsystem* Board::GetGameSubSystem<NewPVPDataSubsystem>();
template NewPVPGameSubsystem* Board::GetGameSubSystem<NewPVPGameSubsystem>();
template NewPVPGuideStartDoor* Board::AddEffect<NewPVPGuideStartDoor>();
template NightPoisonSubSystem* Board::GetGameSubSystem<NightPoisonSubSystem>();
template NukeLauncherSubSystem* Board::GetGameSubSystem<NukeLauncherSubSystem>();
template OliveOilSystem* Board::GetGameSubSystem<OliveOilSystem>();
template OrchidMageLauncherSubSystem* Board::GetGameSubSystem<OrchidMageLauncherSubSystem>();
template OrchidMageSubsystem* Board::GetGameSubSystem<OrchidMageSubsystem>();
template PVPAidSubsystem* Board::GetGameSubSystem<PVPAidSubsystem>();
template PVPInvisibleSubsystem* Board::GetGameSubSystem<PVPInvisibleSubsystem>();
template PlantChardGuardTossSystem* Board::GetGameSubSystem<PlantChardGuardTossSystem>();
template PlantChilibeanSubSystem* Board::GetGameSubSystem<PlantChilibeanSubSystem>();
template PlantElectriciteaSubSystem* Board::GetGameSubSystem<PlantElectriciteaSubSystem>();
template PlantFumeshroomSubSystem* Board::GetGameSubSystem<PlantFumeshroomSubSystem>();
template PlantGroupSubsystem* Board::GetGameSubSystem<PlantGroupSubsystem>();
template PlantLancerHoyaTossSystem* Board::GetGameSubSystem<PlantLancerHoyaTossSystem>();
template PlantLauncherSubSystem* Board::GetGameSubSystem<PlantLauncherSubSystem>();
template PlantMaybeeSubSystem* Board::GetGameSubSystem<PlantMaybeeSubSystem>();
template PlantPhatBeetDotSystem* Board::GetGameSubSystem<PlantPhatBeetDotSystem>();
template PlantPhatBeetTossSystem* Board::GetGameSubSystem<PlantPhatBeetTossSystem>();
template PlantShadowShroomSubSystem* Board::GetGameSubSystem<PlantShadowShroomSubSystem>();
template PlantSunBeanSubSystem* Board::GetGameSubSystem<PlantSunBeanSubSystem>();
template PlantTangleKelpTentacle* Board::AddEffect<PlantTangleKelpTentacle>();
template PlantfoodCaptureSubSystem* Board::GetGameSubSystem<PlantfoodCaptureSubSystem>();
template PoisonMistTileSubSystem* Board::GetGameSubSystem<PoisonMistTileSubSystem>();
template PowerTileSubsystem* Board::GetGameSubSystem<PowerTileSubsystem>();
template PowerupManager* Board::GetGameSubSystem<PowerupManager>();
template PrimalRafflesiaSubsystem* Board::GetGameSubSystem<PrimalRafflesiaSubsystem>();
template RafflesiaSubSystem* Board::GetGameSubSystem<RafflesiaSubSystem>();
template SavedLevelReplaySubsystem* Board::GetGameSubSystem<SavedLevelReplaySubsystem>();
template ShadowVanillaWhirlPoolSubSystem* Board::GetGameSubSystem<ShadowVanillaWhirlPoolSubSystem>();
template SilverkeyGateEffect* Board::AddEffect<SilverkeyGateEffect>();
template SpartanBambooMatrixSystem* Board::GetGameSubSystem<SpartanBambooMatrixSystem>();
template SpawnProjectilesSubSystem* Board::GetGameSubSystem<SpawnProjectilesSubSystem>();
template SporeshroomSubsystem* Board::GetGameSubSystem<SporeshroomSubsystem>();
template StephaniaSubsystem* Board::GetGameSubSystem<StephaniaSubsystem>();
template SunRainSubSystem* Board::GetGameSubSystem<SunRainSubSystem>();
template SweetPotatoSubsystem* Board::GetGameSubSystem<SweetPotatoSubsystem>();
template ThunderSubSystem* Board::GetGameSubSystem<ThunderSubSystem>();
template WaterMistTileSubSystem* Board::GetGameSubSystem<WaterMistTileSubSystem>();
template WaxgourdSubsystem* Board::GetGameSubSystem<WaxgourdSubsystem>();
template WormHoleSubsystem* Board::GetGameSubSystem<WormHoleSubsystem>();
template ZombieBalletSubSystem* Board::GetGameSubSystem<ZombieBalletSubSystem>();
template ZombieBlowerSubSystem* Board::GetGameSubSystem<ZombieBlowerSubSystem>();
template ZombieCamelSubSystem* Board::GetGameSubSystem<ZombieCamelSubSystem>();
template ZombieChickenEliteSubsystem* Board::GetGameSubSystem<ZombieChickenEliteSubsystem>();
template ZombieChickenSubsystem* Board::GetGameSubSystem<ZombieChickenSubsystem>();
template ZombieGentlemanTosserSubSystem* Board::GetGameSubSystem<ZombieGentlemanTosserSubSystem>();
template ZombieLaneChangingSubsystem* Board::GetGameSubSystem<ZombieLaneChangingSubsystem>();
template ZombieMechDiscoSubsystem* Board::GetGameSubSystem<ZombieMechDiscoSubsystem>();
template ZombiePianoSubsystem* Board::GetGameSubSystem<ZombiePianoSubsystem>();
template ZombiePullSubSystem* Board::GetGameSubSystem<ZombiePullSubSystem>();
template ZombieRaSubSystem* Board::GetGameSubSystem<ZombieRaSubSystem>();
template ZombieStabberSubSystem* Board::GetGameSubSystem<ZombieStabberSubSystem>();
template ZombieSurrenderSubsystem* Board::GetGameSubSystem<ZombieSurrenderSubsystem>();
template ZombieTosserInSkySubSystem* Board::GetGameSubSystem<ZombieTosserInSkySubSystem>();
template ZombieTosserSubSystem* Board::GetGameSubSystem<ZombieTosserSubSystem>();
template ZombieWalkOutSubSystem* Board::GetGameSubSystem<ZombieWalkOutSubSystem>();
template ZombossRobotRappellingSubSystem* Board::GetGameSubSystem<ZombossRobotRappellingSubSystem>();
