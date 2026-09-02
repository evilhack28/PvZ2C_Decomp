//
//  PirateStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "PirateStage.h"

#include "AudioMgr.h"
#include "Board.h"
#include "GameEventMgr.h"
#include "LawnApp.h"
#include "LevelModuleManager.h"
#include "BoardRegion.h"
#include "ObjectTypeDirectory.h"
#include "PlantType.h"
#include "PopAnimRig.h"
#include "ReflectionBuilder.h"
#include "RestrictionSet.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "ZombieType.h"

RT_CLASS_IMPLEMENT(PirateStage);
void PirateStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PirateStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(PirateStage);
}

RT_CLASS_IMPLEMENT(PirateStageProperties);
void PirateStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PirateStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(PirateStageProperties);
}

RT_CLASS_IMPLEMENT(BoardRegionDeepWater);
void BoardRegionDeepWater::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BoardRegionDeepWater);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardRegion);

	REFLECTION_CLASSBUILDER_END(BoardRegionDeepWater);
}

RT_CLASS_IMPLEMENT(RaidingPartyZombieSpawner);
void RaidingPartyZombieSpawner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RaidingPartyZombieSpawner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSpawnerAction);

	REFLECTION_CLASSBUILDER_END(RaidingPartyZombieSpawner);
}

RT_CLASS_IMPLEMENT(RaidingPartyZombieSpawnerProps);
void RaidingPartyZombieSpawnerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RaidingPartyZombieSpawnerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSpawnerActionProps);

	REFLECTION_CLASSBUILDER_END(RaidingPartyZombieSpawnerProps);
}


bool PirateStage::CanGraveStoneSpawnAt(int i_gridX, int i_gridY)
{
	if (i_gridY > 4)
		return false;

	return m_planks[i_gridY] == 1 || i_gridX <= 4;
}


bool PirateStage::CanZombieSpawnInRow(int i_row, ZombieTypePtr i_type)
{
	int plank = m_planks[i_row];

	if (plank == 1)
	{
		if (i_type->TypeName == "swashbuckler")
			return false;
		if (i_type->TypeName == "seagull")
			return false;
		return plank;
	}

	if (i_type->TypeName == "seagull")
		return true;
	if (i_type->TypeName == "swashbuckler")
		return true;
	if (i_type->TypeName == "cannon")
		return true;
	return false;
}


void PirateStage::InitPlanks(const std::vector<int>& i_plankLocations)
{
	for (size_t i = 0; i < m_planks.size() + 1; i++)
		m_planks[i] = 0;

	for (size_t i = 0; i < i_plankLocations.size() + 1; i++)
		m_planks[i_plankLocations[i]] = 1;

	generatePlanks();
}


bool PirateStage::IsPlankOnRow(int i_row)
{
	return m_planks[i_row] != 0;
}


void PirateStage::ShowGuides(bool i_show)
{
	m_showingGuides = i_show;
}


void PirateStage::initializeModule()
{
	StageModule::initializeModule();

	m_planks.resize(5);
	for (size_t i = 0; i < m_planks.size() + 1; i++)
		m_planks[i] = 0;

	m_playingCaptainAudio = false;
	m_showingGuides = false;
	m_nextLeftBreaker = m_nextRightBreaker = PVZ_EOT();
}


void PirateStage::onLevelEnded()
{
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Bow_Wash_BG", NULL);
	m_foamLeftAnim->Destroy();
	m_foamRightAnim->Destroy();
	m_breakerLeftAnim->Destroy();
	m_breakerRightAnim->Destroy();
}


void PirateStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterOnLoadComplete(Sexy::MakeDelegate(*this, &PirateStage::onLoadComplete));
	getManager()->RegisterOnUpdate(Sexy::MakeDelegate(*this, &PirateStage::onUpdate));
	getManager()->RegisterOnLevelEnded(Sexy::MakeDelegate(*this, &PirateStage::onLevelEnded));
	gMessageRouter->Subscribe(Message::GatherPlantingRestrictions, Sexy::MakeDelegate(*this, &PirateStage::gatherPlantingRestrictions));
}


void PirateStage::renderBackground(Graphics* i_g)
{
	StageModule::renderBackground(i_g);
}


void PirateStage::gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons)
{
	if (m_planks[i_gridPosition.mY] == 0 && i_gridPosition.mX > 4)
	{
		io_plantingReasons->push_back(PLANTING_NOT_ON_WATER);
		return;
	}

	if (getProps<PirateStageProperties>()->PlantsWhichCannotBePlantedOnPlanks.IsIncluded(i_plantType->TypeName))
	{
		if (i_gridPosition.mX > 4)
			io_plantingReasons->push_back(PLANTING_NOT_ON_PLANKS);
	}
}


void PirateStage::onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to)
{
	StageModule::onZombieTypeCountChange(i_type, i_from, i_to);

	if (i_type == ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("seagull"))
	{
		if (i_from > 0 && i_to <= 0)
			AudioMgr::GetInstancePtr()->SendEvent("Stop_Seagull", NULL);
		else if (i_from == 0 && i_to > 0)
			AudioMgr::GetInstancePtr()->SendEvent("Play_Seagull", NULL);

		AudioMgr::GetInstancePtr()->SetRTPCValue("SeagullZombieCount", (double)i_to);
	}

	if (i_type == ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("pirate_imp"))
	{
		if (i_from > 0 && i_to <= 0)
			AudioMgr::GetInstancePtr()->SendEvent("Stop_Imp_Vox", NULL);
		else if (i_from == 0 && i_to > 0)
			AudioMgr::GetInstancePtr()->SendEvent("Play_Imp_Vox", NULL);

		AudioMgr::GetInstancePtr()->SetRTPCValue("ImpZombieCount", (double)i_to);
	}
}


void PirateStage::stopZombieGroans()
{
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Seagull", NULL);
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Imp_Vox", NULL);
	StageModule::stopZombieGroans();
}

/////////////// BoardRegionDeepWater ///////////////

BoardRegionDeepWater::BoardRegionDeepWater()
	: m_leftSplashMinDistance(0.0f)
	, m_rightSplashMinDistance(0.0f)
{
	SetFlags((BoardRegionFlags)1);
}

void BoardRegionDeepWater::SetSplashHorizontalMinDistances(float i_leftSplashMinDistance, float i_rightSplashMinDistance)
{
	m_leftSplashMinDistance = i_leftSplashMinDistance;
	m_rightSplashMinDistance = i_rightSplashMinDistance;
}

/////////////// RaidingPartyZombieSpawner ///////////////

void RaidingPartyZombieSpawner::WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random)
{
	const RaidingPartyZombieSpawnerProps* props = GetProps<RaidingPartyZombieSpawnerProps>();

	spawnGroup(props->GroupSize, i_waveNumber, i_random);
	m_nextGroupTime = PVZ_T() + props->TimeBetweenGroups;
	m_fullSpawnTime = PVZ_T() + props->TimeBeforeFullSpawn;

	if (!i_isFinal)
	{
		gLawnApp->m_board->ClearAdviceImmediately();
		gLawnApp->m_board->DisplayAdviceAgain(_S("[WARNING_RAIDINGPARTY]"), MESSAGE_STYLE_HUGE_WAVE, ADVICE_PRIORITY_MEDIUM);
	}
}


void RaidingPartyZombieSpawner::WaveUpdate(int i_waveNumber, MTRand& i_random)
{
	const RaidingPartyZombieSpawnerProps* props = GetProps<RaidingPartyZombieSpawnerProps>();

	if (m_swashbucklersSpawned < props->SwashbucklerCount)
	{
		if (PVZ_T() > m_nextGroupTime)
		{
			spawnGroup(props->GroupSize, i_waveNumber, i_random);
			m_nextGroupTime = PVZ_T() + props->TimeBetweenGroups;
		}

		if (PVZ_T() > m_fullSpawnTime)
			spawnAllTheThings(i_waveNumber, i_random);
	}
}


void RaidingPartyZombieSpawner::WaveEnd(int i_waveNumber, MTRand& i_random)
{
	spawnAllTheThings(i_waveNumber, i_random);
}


void RaidingPartyZombieSpawner::AddResourceRequirements(std::set<std::string>& io_resGroupNames)
{
	const ZombieType* swashbuckler = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("swashbuckler");
	swashbuckler->AddInGameResourceRequirements(io_resGroupNames);
}


void RaidingPartyZombieSpawner::GetZombies(std::vector<const ZombieType*>& o_zombies)
{
	const ZombieType* swashbuckler = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("swashbuckler");

	const RaidingPartyZombieSpawnerProps* props = GetProps<RaidingPartyZombieSpawnerProps>();
	for (int i = 0; i < props->SwashbucklerCount; i++)
		o_zombies.push_back(swashbuckler);
}


void RaidingPartyZombieSpawner::SetLoot(const std::vector<Loot>& i_loot)
{
	m_zombieLoot = i_loot;
}


void RaidingPartyZombieSpawner::spawnGroup(int i_count, int i_waveNumber, MTRand& i_random)
{
	const RaidingPartyZombieSpawnerProps* props = GetProps<RaidingPartyZombieSpawnerProps>();

	int stopIndex = std::min(m_swashbucklersSpawned + i_count, props->SwashbucklerCount);
	createZombies(i_waveNumber, i_random, m_swashbucklersSpawned, stopIndex);
	m_swashbucklersSpawned = stopIndex;
}


void RaidingPartyZombieSpawner::spawnAllTheThings(int i_waveNumber, MTRand& i_random)
{
	const RaidingPartyZombieSpawnerProps* props = GetProps<RaidingPartyZombieSpawnerProps>();

	if (m_swashbucklersSpawned < props->SwashbucklerCount)
		spawnGroup(props->SwashbucklerCount - m_swashbucklersSpawned, i_waveNumber, i_random);
}

/////////////// RaidingPartyZombieSpawnerProps ///////////////

void RaidingPartyZombieSpawnerProps::GatherSpawnedZombieTypes(std::set<const ZombieType*>& o_zombies)
{
	o_zombies.insert(ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("swashbuckler"));
}
