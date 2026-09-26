// Reconstructed by EvilHack28 on 2026-09-05
#include "StateMachineTableBuilder.h"
#include "RenderQueue.h"
#include "AnimationMgr.h"
#include "BoardConstants.h"
#include "CardGameModule.h"
#include "ArtifactSubsystem.h"
#include "DinosaurStegosaurus.h"
#include "IntroPooyan.h"
#undef __PlantsVersusZombies2__IntroPooyan__
#include "IntroFishing.h"
#include "BasePowerup.h"
#include "Board.h"
#include "Bomb.h"
#include "Collectable.h"
#include "CrazyNPC.h"
#include "Creature.h"
#include "DinosaurAnkylosaurus.h"
#include "DinosaurRunner.h"
#include "DinosaurYounger.h"
#include "FiregourdTutorialIntro.h"
#include "Fuse.h"
#include "GridItemWalrusStatue.h"
#include "HorsebeanPlane.h"
#include "IntroBesiege.h"
#include "IntroChristmasProtect.h"
#include "IntroEliminate.h"
#include "IntroFishing.h"
#include "IntroOakTrain.h"
#include "IntroPVZ1Mode.h"
#include "IntroPooyan.h"
#include "IntroRiverCrossing.h"
#include "IntroSeedRain.h"
#include "IntroSkyCity.h"
#include "IntroThunder.h"
#include "IntroTowerDefend.h"
#include "IntrosSnake.h"
#include "IntrosWhackAMole.h"
#include "MacroStateMachine.h"
#include "Plant_DevilsFlower.h"
#include "Plant_Horsebean.h"
#include "Plant_Iceburg.h"
#include "Plant_MagicShroom.h"
#include "PowerupCukeTutorialIntro.h"
#include "RechargeGiftUI.h"
#include "RewardUI.h"
#include "RiverCrossingDodoRider.h"
#include "RiverEntity.h"
#include "RunningSubway.h"
#include "SalesUI.h"
#include "SharkMinion.h"
#include "Snake.h"
#include "StarvingChomper.h"
#include "UIWidget.h"
#include "ZombieModernNewspaper.h"
#include "ZombieSteamCoalCart.h"

StateMachineTableBuilder::StateMachineTableBuilder()
{
}

StateMachineTableBuilder::~StateMachineTableBuilder()
{
	for (size_t i = 0; i < m_stateMachineTableStorage.size(); ++i)
	{
		StateMachineTableBase* table = m_stateMachineTableStorage[i];
		delete table;
	}

	m_stateMachineTableStorage.clear();
	m_stateMachineTables.clear();
}

template const StateMachineTable<AnkyloState>* StateMachineTableBuilder::GetTable<AnkyloState>(RtClass*);
template StateMachineTable<AnkyloState>& StateMachineTableBuilder::RegisterClass<AnkyloState>(RtClass*);
template const StateMachineTable<BIState>* StateMachineTableBuilder::GetTable<BIState>(RtClass*);
template StateMachineTable<BIState>& StateMachineTableBuilder::RegisterClass<BIState>(RtClass*);
template const StateMachineTable<BombState>* StateMachineTableBuilder::GetTable<BombState>(RtClass*);
template StateMachineTable<BombState>& StateMachineTableBuilder::RegisterClass<BombState>(RtClass*);
template const StateMachineTable<CMPState>* StateMachineTableBuilder::GetTable<CMPState>(RtClass*);
template StateMachineTable<CMPState>& StateMachineTableBuilder::RegisterClass<CMPState>(RtClass*);
template const StateMachineTable<CollectableState>* StateMachineTableBuilder::GetTable<CollectableState>(RtClass*);
template StateMachineTable<CollectableState>& StateMachineTableBuilder::RegisterClass<CollectableState>(RtClass*);
template const StateMachineTable<CrazyNPCState>* StateMachineTableBuilder::GetTable<CrazyNPCState>(RtClass*);
template StateMachineTable<CrazyNPCState>& StateMachineTableBuilder::RegisterClass<CrazyNPCState>(RtClass*);
template const StateMachineTable<CreatureState>* StateMachineTableBuilder::GetTable<CreatureState>(RtClass*);
template StateMachineTable<CreatureState>& StateMachineTableBuilder::RegisterClass<CreatureState>(RtClass*);
template const StateMachineTable<DPEState>* StateMachineTableBuilder::GetTable<DPEState>(RtClass*);
template StateMachineTable<DPEState>& StateMachineTableBuilder::RegisterClass<DPEState>(RtClass*);
template const StateMachineTable<DinoRunnerState>* StateMachineTableBuilder::GetTable<DinoRunnerState>(RtClass*);
template StateMachineTable<DinoRunnerState>& StateMachineTableBuilder::RegisterClass<DinoRunnerState>(RtClass*);
template const StateMachineTable<DinoYoungerState>* StateMachineTableBuilder::GetTable<DinoYoungerState>(RtClass*);
template StateMachineTable<DinoYoungerState>& StateMachineTableBuilder::RegisterClass<DinoYoungerState>(RtClass*);
template const StateMachineTable<ELIIState>* StateMachineTableBuilder::GetTable<ELIIState>(RtClass*);
template StateMachineTable<ELIIState>& StateMachineTableBuilder::RegisterClass<ELIIState>(RtClass*);
template const StateMachineTable<FTIState>* StateMachineTableBuilder::GetTable<FTIState>(RtClass*);
template StateMachineTable<FTIState>& StateMachineTableBuilder::RegisterClass<FTIState>(RtClass*);
template const StateMachineTable<FuseState>* StateMachineTableBuilder::GetTable<FuseState>(RtClass*);
template StateMachineTable<FuseState>& StateMachineTableBuilder::RegisterClass<FuseState>(RtClass*);
template const StateMachineTable<HBPState>* StateMachineTableBuilder::GetTable<HBPState>(RtClass*);
template StateMachineTable<HBPState>& StateMachineTableBuilder::RegisterClass<HBPState>(RtClass*);
template const StateMachineTable<IntroState>* StateMachineTableBuilder::GetTable<IntroState>(RtClass*);
template StateMachineTable<IntroState>& StateMachineTableBuilder::RegisterClass<IntroState>(RtClass*);
template const StateMachineTable<LaunchState>* StateMachineTableBuilder::GetTable<LaunchState>(RtClass*);
template StateMachineTable<LaunchState>& StateMachineTableBuilder::RegisterClass<LaunchState>(RtClass*);
template const StateMachineTable<MSCState>* StateMachineTableBuilder::GetTable<MSCState>(RtClass*);
template StateMachineTable<MSCState>& StateMachineTableBuilder::RegisterClass<MSCState>(RtClass*);
template const StateMachineTable<MSState>* StateMachineTableBuilder::GetTable<MSState>(RtClass*);
template StateMachineTable<MSState>& StateMachineTableBuilder::RegisterClass<MSState>(RtClass*);
template const StateMachineTable<ModernNewspaperZombieState>* StateMachineTableBuilder::GetTable<ModernNewspaperZombieState>(RtClass*);
template StateMachineTable<ModernNewspaperZombieState>& StateMachineTableBuilder::RegisterClass<ModernNewspaperZombieState>(RtClass*);
template const StateMachineTable<MoleState>* StateMachineTableBuilder::GetTable<MoleState>(RtClass*);
template StateMachineTable<MoleState>& StateMachineTableBuilder::RegisterClass<MoleState>(RtClass*);
template const StateMachineTable<OTIState>* StateMachineTableBuilder::GetTable<OTIState>(RtClass*);
template StateMachineTable<OTIState>& StateMachineTableBuilder::RegisterClass<OTIState>(RtClass*);
template const StateMachineTable<PHBState>* StateMachineTableBuilder::GetTable<PHBState>(RtClass*);
template StateMachineTable<PHBState>& StateMachineTableBuilder::RegisterClass<PHBState>(RtClass*);
template const StateMachineTable<PVZ1IState>* StateMachineTableBuilder::GetTable<PVZ1IState>(RtClass*);
template StateMachineTable<PVZ1IState>& StateMachineTableBuilder::RegisterClass<PVZ1IState>(RtClass*);
template const StateMachineTable<PlantState>* StateMachineTableBuilder::GetTable<PlantState>(RtClass*);
template StateMachineTable<PlantState>& StateMachineTableBuilder::RegisterClass<PlantState>(RtClass*);
template const StateMachineTable<PowerupCukeTutorialState>* StateMachineTableBuilder::GetTable<PowerupCukeTutorialState>(RtClass*);
template StateMachineTable<PowerupCukeTutorialState>& StateMachineTableBuilder::RegisterClass<PowerupCukeTutorialState>(RtClass*);
template const StateMachineTable<PowerupState>* StateMachineTableBuilder::GetTable<PowerupState>(RtClass*);
template StateMachineTable<PowerupState>& StateMachineTableBuilder::RegisterClass<PowerupState>(RtClass*);
template const StateMachineTable<RCIState>* StateMachineTableBuilder::GetTable<RCIState>(RtClass*);
template StateMachineTable<RCIState>& StateMachineTableBuilder::RegisterClass<RCIState>(RtClass*);
template const StateMachineTable<RewardAniState>* StateMachineTableBuilder::GetTable<RewardAniState>(RtClass*);
template StateMachineTable<RewardAniState>& StateMachineTableBuilder::RegisterClass<RewardAniState>(RtClass*);
template const StateMachineTable<RiverCrossingDodoRiderState>* StateMachineTableBuilder::GetTable<RiverCrossingDodoRiderState>(RtClass*);
template StateMachineTable<RiverCrossingDodoRiderState>& StateMachineTableBuilder::RegisterClass<RiverCrossingDodoRiderState>(RtClass*);
template const StateMachineTable<RiverEntitiesManagerState>* StateMachineTableBuilder::GetTable<RiverEntitiesManagerState>(RtClass*);
template StateMachineTable<RiverEntitiesManagerState>& StateMachineTableBuilder::RegisterClass<RiverEntitiesManagerState>(RtClass*);
template const StateMachineTable<RunningPlayerState>* StateMachineTableBuilder::GetTable<RunningPlayerState>(RtClass*);
template StateMachineTable<RunningPlayerState>& StateMachineTableBuilder::RegisterClass<RunningPlayerState>(RtClass*);
template const StateMachineTable<SCIState>* StateMachineTableBuilder::GetTable<SCIState>(RtClass*);
template StateMachineTable<SCIState>& StateMachineTableBuilder::RegisterClass<SCIState>(RtClass*);
template const StateMachineTable<SDIState>* StateMachineTableBuilder::GetTable<SDIState>(RtClass*);
template StateMachineTable<SDIState>& StateMachineTableBuilder::RegisterClass<SDIState>(RtClass*);
template const StateMachineTable<SKIState>* StateMachineTableBuilder::GetTable<SKIState>(RtClass*);
template StateMachineTable<SKIState>& StateMachineTableBuilder::RegisterClass<SKIState>(RtClass*);
template const StateMachineTable<SalesButtonState>* StateMachineTableBuilder::GetTable<SalesButtonState>(RtClass*);
template StateMachineTable<SalesButtonState>& StateMachineTableBuilder::RegisterClass<SalesButtonState>(RtClass*);
template const StateMachineTable<SharkMinionState>* StateMachineTableBuilder::GetTable<SharkMinionState>(RtClass*);
template StateMachineTable<SharkMinionState>& StateMachineTableBuilder::RegisterClass<SharkMinionState>(RtClass*);
template const StateMachineTable<SnakeState>* StateMachineTableBuilder::GetTable<SnakeState>(RtClass*);
template StateMachineTable<SnakeState>& StateMachineTableBuilder::RegisterClass<SnakeState>(RtClass*);
template const StateMachineTable<StarvingChomperState>* StateMachineTableBuilder::GetTable<StarvingChomperState>(RtClass*);
template StateMachineTable<StarvingChomperState>& StateMachineTableBuilder::RegisterClass<StarvingChomperState>(RtClass*);
template const StateMachineTable<SteamCoalCartZombieState>* StateMachineTableBuilder::GetTable<SteamCoalCartZombieState>(RtClass*);
template StateMachineTable<SteamCoalCartZombieState>& StateMachineTableBuilder::RegisterClass<SteamCoalCartZombieState>(RtClass*);
template const StateMachineTable<TDIState>* StateMachineTableBuilder::GetTable<TDIState>(RtClass*);
template StateMachineTable<TDIState>& StateMachineTableBuilder::RegisterClass<TDIState>(RtClass*);
template const StateMachineTable<TIState>* StateMachineTableBuilder::GetTable<TIState>(RtClass*);
template StateMachineTable<TIState>& StateMachineTableBuilder::RegisterClass<TIState>(RtClass*);
template const StateMachineTable<WalrusStatueState>* StateMachineTableBuilder::GetTable<WalrusStatueState>(RtClass*);
template StateMachineTable<WalrusStatueState>& StateMachineTableBuilder::RegisterClass<WalrusStatueState>(RtClass*);
template const StateMachineTable<WidgetState>* StateMachineTableBuilder::GetTable<WidgetState>(RtClass*);
template StateMachineTable<WidgetState>& StateMachineTableBuilder::RegisterClass<WidgetState>(RtClass*);
template const StateMachineTable<ZombieState>* StateMachineTableBuilder::GetTable<ZombieState>(RtClass*);
template StateMachineTable<ZombieState>& StateMachineTableBuilder::RegisterClass<ZombieState>(RtClass*);
template const StateMachineTable<CardGameState>* StateMachineTableBuilder::GetTable<CardGameState>(RtClass*);
template StateMachineTable<CardGameState>& StateMachineTableBuilder::RegisterClass<CardGameState>(RtClass*);
template const StateMachineTable<ABEState>* StateMachineTableBuilder::GetTable<ABEState>(RtClass*);
template StateMachineTable<ABEState>& StateMachineTableBuilder::RegisterClass<ABEState>(RtClass*);
template const StateMachineTable<StegoState>* StateMachineTableBuilder::GetTable<StegoState>(RtClass*);
template StateMachineTable<StegoState>& StateMachineTableBuilder::RegisterClass<StegoState>(RtClass*);
template const StateMachineTable<PIState>* StateMachineTableBuilder::GetTable<PIState>(RtClass*);
template StateMachineTable<PIState>& StateMachineTableBuilder::RegisterClass<PIState>(RtClass*);
template const StateMachineTable<FIState>* StateMachineTableBuilder::GetTable<FIState>(RtClass*);
template StateMachineTable<FIState>& StateMachineTableBuilder::RegisterClass<FIState>(RtClass*);

enum TyrannoState
{
	TYRANNOSTATE_PLACEHOLDER
};

template const StateMachineTable<TyrannoState>* StateMachineTableBuilder::GetTable<TyrannoState>(RtClass*);
template StateMachineTable<TyrannoState>& StateMachineTableBuilder::RegisterClass<TyrannoState>(RtClass*);
