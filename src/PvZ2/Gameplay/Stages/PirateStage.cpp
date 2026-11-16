//
//  PirateStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "PirateStage.h"

#include "AudioMgr.h"
#include "Board.h"
#include "BoardTransforms.h"
#include "Effect_PopAnim.h"
#include "EffectAnimRig_WaterSplash.h"
#include "GameEventMgr.h"
#include "LawnApp.h"
#include "LevelModuleManager.h"
#include "BoardRegion.h"
#include "ObjectTypeDirectory.h"
#include "PlantType.h"
#include "PopAnimRig.h"
#include "PVZDB.h"
#include "ReflectionBuilder.h"
#include "ResourceHelpers.h"
#include "RestrictionSet.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "ZombiePirateCaptain.h"
#include "ZombiePirateParrot.h"
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
	if (plank != 1)
	{
		if (i_type->TypeName == "seagull" || i_type->TypeName == "swashbuckler" || i_type->TypeName == "cannon")
			return true;
		return false;
	}
	if (i_type->TypeName == "swashbuckler" || i_type->TypeName == "seagull")
		return false;
	return plank;
}


void PirateStage::onUpdate()
{
	bool hasCaptain = false;
	bool hasParrot = false;
	Board* board = gLawnApp->m_board;

	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
	{
		ZombiePtr zombiePtr = *it;
		ZombiePtr zombieRef = zombiePtr;
		Zombie* zombie = zombiePtr->CastChecked<Zombie>();

		if (zombie->Cast<ZombiePirateCaptain>())
		{
			hasCaptain = true;
			if (zombie->Cast<ZombiePirateCaptain>()->HasBird())
				hasParrot = true;
		}
		else if (zombie->Cast<ZombiePirateParrot>())
			hasParrot = true;

		if (!zombie->IsOnGround())
			continue;

		SexyVector3 pos = zombie->GetPosition();
		int gridX = BoardTransforms::BoardSpaceToGridX(pos.x);
		int gridY = BoardTransforms::BoardSpaceToGridYUnbounded(pos.y);
		if (gridY < 0 || gridY >= board->m_gridSizeY)
			DropZombieInOcean(zombieRef);
		else if (!zombieRef->IsControlled())
		{
			if (board->IsPitOfDoom(Sexy::Point(gridX, gridY)))
				DropZombieInOcean(zombieRef);
		}
	}

	if (gLawnApp->m_board->IsPlaying())
	{
		if (hasCaptain && hasParrot)
		{
			if (!m_playingCaptainAudio)
			{
				AudioMgr::GetInstancePtr()->SendEvent("Play_Captain_Parrot");
				m_playingCaptainAudio = true;
			}
		}
		else if (m_playingCaptainAudio)
		{
			AudioMgr::GetInstancePtr()->SendEvent("Stop_Captain_Parrot");
			m_playingCaptainAudio = false;
		}
	}

	m_foamLeftAnim->UpdateAnim(PVZ_T(), PVZ_Dt());
	m_foamRightAnim->UpdateAnim(PVZ_T(), PVZ_Dt());
	m_breakerLeftAnim->UpdateAnim(PVZ_T(), PVZ_Dt());
	m_breakerRightAnim->UpdateAnim(PVZ_T(), PVZ_Dt());

	const PirateStageProperties* props = getProps<PirateStageProperties>();

	if (PVZ_T() > m_nextLeftBreaker)
	{
		m_breakerLeftAnim->PlayAndStop("water_breaker_left", SELECT_EXACT);
		static SexyVector2 leftBreakerPos(565.0f, 100.0f);
		m_currLeftBreakerPos = leftBreakerPos;
		m_currLeftBreakerPos.y += Sexy::Rand(550.0f);
		m_nextLeftBreaker = PVZ_T() + props->BreakerInterval;
	}

	if (PVZ_T() > m_nextRightBreaker)
	{
		m_breakerRightAnim->PlayAndStop("water_breaker_right", SELECT_EXACT);
		static SexyVector2 rightBreakerPos(490.0f, 100.0f);
		m_currRightBreakerPos = rightBreakerPos;
		m_currRightBreakerPos.y += Sexy::Rand(600.0f);
		m_nextRightBreaker = PVZ_T() + props->BreakerInterval;
	}
}

void PirateStage::onLoadComplete()
{
	const PirateStageProperties* props = getProps<PirateStageProperties>();

	m_foamLeftAnim = PopAnimRig::CreateRig(GetPAMByName("POPANIM_EFFECTS_WATER_FOAM"))->GetPtr();
	m_foamLeftAnim->PlayAndContinue("water_foam_left", SELECT_EXACT);

	m_foamRightAnim = PopAnimRig::CreateRig(GetPAMByName("POPANIM_EFFECTS_WATER_FOAM"))->GetPtr();
	m_foamRightAnim->PlayAndContinue("water_foam_right", SELECT_EXACT);

	m_breakerRightAnim = PopAnimRig::CreateRig(GetPAMByName("POPANIM_EFFECTS_WATER_BREAKER"))->GetPtr();
	m_nextRightBreaker = PVZ_T() + props->BreakerInterval;

	m_breakerLeftAnim = PopAnimRig::CreateRig(GetPAMByName("POPANIM_EFFECTS_WATER_BREAKER"))->GetPtr();
	m_nextLeftBreaker = PVZ_T() + 0.618034f * props->BreakerInterval;

	AudioMgr::GetInstancePtr()->SendEvent("Play_Bow_Wash_BG");
	generatePlanks();
}

void PirateStage::generatePlanks()
{
	int width = gLawnApp->m_board->m_gridSizeX - 5;

	BoardRegionDeepWater* region = gLawnApp->m_board->AddRegion<BoardRegionDeepWater>();
	region->SetRegionFromGridSquares(Sexy::Rect(5, -2, width, 2));
	region->SetSplashHorizontalMinDistances(40.0f, 101.0f);

	region = gLawnApp->m_board->AddRegion<BoardRegionDeepWater>();
	region->SetRegionFromGridSquares(Sexy::Rect(5, gLawnApp->m_board->m_gridSizeY, width, 2));
	region->SetSplashHorizontalMinDistances(40.0f, 101.0f);

	for (int row = 0; row < BoardConstants::NUMBER_OF_ROWS(); row++)
	{
		GridItem* plank = gLawnApp->m_board->GetGridItemAt("plank", 5, row);
		GridSquareType type;
		if (m_planks[row] == 1)
		{
			type = GRIDSQUARE_GRASS;
			if (!plank)
				gLawnApp->m_board->AddGridItem("plank", 5, row);
		}
		else
		{
			type = GRIDSQUARE_WATER;
			region = gLawnApp->m_board->AddRegion<BoardRegionDeepWater>();
			region->SetRegionFromGridSquares(Sexy::Rect(5, row, width, 1));
			region->SetSplashHorizontalMinDistances(40.0f, 101.0f);
		}

		int numColumns = BoardConstants::NUMBER_OF_COLUMNS();
		for (int col = 5; col < numColumns; col++)
			gLawnApp->m_board->SetGridSquareType(col, row, type);

		if (m_planks[row] == 0 && plank)
			plank->Destroy();
	}
}

void PirateStage::InitPlanks(const std::vector<int>& i_plankLocations)
{
	for (int i = 0; i < m_planks.size(); i++)
		m_planks[i] = 0;

	for (int i = 0; i < i_plankLocations.size(); i++)
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
	for (int i = 0; i < m_planks.size(); i++)
		m_planks[i] = 0;

	m_nextLeftBreaker = m_nextRightBreaker = PVZ_EOT();
	m_playingCaptainAudio = false;
	m_showingGuides = false;
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


static CachedResourcePtr<Sexy::Image> IMAGE_PIRATE_CANNON_GUIDE_LEFT("IMAGE_PIRATE_CANNON_GUIDE_LEFT");
static CachedResourcePtr<Sexy::Image> IMAGE_PIRATE_CANNON_GUIDE_RIGHT("IMAGE_PIRATE_CANNON_GUIDE_RIGHT");

void PirateStage::renderBackground(Graphics* i_g)
{
	StageModule::renderBackground(i_g);

	static SexyVector2 foamRightPos(490.0f, 220.0f);
	SexyTransform2D foamTransform;
	foamTransform.Translate(S(foamRightPos.x), S(foamRightPos.y));
	m_foamRightAnim->Draw(i_g, foamTransform);

	static SexyVector2 foamLeftPos(580.0f, 300.0f);
	foamTransform.LoadIdentity();
	foamTransform.Translate(S(foamLeftPos.x), S(foamLeftPos.y));
	m_foamLeftAnim->Draw(i_g, foamTransform);

	SexyTransform2D breakerTransform;
	breakerTransform.Translate(S(m_currRightBreakerPos.x), S(m_currRightBreakerPos.y));
	m_breakerRightAnim->Draw(i_g, breakerTransform);

	breakerTransform.LoadIdentity();
	breakerTransform.Translate(S(m_currLeftBreakerPos.x), S(m_currLeftBreakerPos.y));
	m_breakerLeftAnim->Draw(i_g, breakerTransform);

	if (m_showingGuides)
	{
		static SexyVector2 guideLeftPos(520.0f, 350.0f);
		SexyTransform2D guideLeftTransform;
		guideLeftTransform.Translate(S(guideLeftPos.x), S(guideLeftPos.y));
		i_g->DrawImageMatrix(IMAGE_PIRATE_CANNON_GUIDE_LEFT, guideLeftTransform, 0, 0);

		static SexyVector2 guideRightPos(770.0f, 350.0f);
		SexyTransform2D guideRightTransform;
		guideRightTransform.Translate(S(guideRightPos.x), S(guideRightPos.y));
		i_g->DrawImageMatrix(IMAGE_PIRATE_CANNON_GUIDE_RIGHT, guideRightTransform, 0, 0);
	}
}



void PirateStage::gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons)
{
	bool onWater = m_planks[i_gridPosition.mY] == 0;
	if (onWater && i_gridPosition.mX > 4)
		io_plantingReasons->push_back(PLANTING_NOT_ON_WATER);
	else if (GetPropsPtr()->Cast<PirateStageProperties>()->PlantsWhichCannotBePlantedOnPlanks.IsIncluded(i_plantType->TypeName))
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
	SetFlags(BOARDREGION_PitOfDoom);
}

void BoardRegionDeepWater::DoEntityEnteredEffects(const SexyVector3& i_boardLocation, BoardEntity* i_enteringEntity)
{
	SexyVector2 splashPoint(i_boardLocation.x, i_boardLocation.y);
	FRect region = GetRegion();
	region.mX = m_leftSplashMinDistance + region.mX;
	region.mWidth = region.mWidth - m_leftSplashMinDistance - m_rightSplashMinDistance;
	region.Clamp(splashPoint, 0, 0);

	SexyVector3 offset(-95.0f, -90.0f, 0.0f);
	SexyVector3 position(splashPoint.x, splashPoint.y, 0.0f);
	position += offset;

	Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
	effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_WATER_SPLASH"), EffectAnimRig_WaterSplash::StaticGetClass());
	effect->SetBoardSpaceOrigin(position, -1);
	effect->SetRenderLayerOverride(Board::MakeGroundRenderOrder(BoardTransforms::BoardSpaceToGridYUnbounded(splashPoint.y), 0));

	std::string anim = Sexy::Rand(2) == 0 ? "water_splash_01" : "water_splash_02";
	effect->PlaySingleAnimation(anim, SELECT_EXACT);

	AudioMgr::GetInstancePtr()->RegisterForAudio(effect);
	AudioMgr::GetInstancePtr()->SendPositionalAudioValue(effect, i_boardLocation);
	AudioMgr::GetInstancePtr()->SendEvent("Play_Zombie_Splash", effect);
	AudioMgr::GetInstancePtr()->UnregisterForAudio(effect);
}

void BoardRegionDeepWater::SetSplashHorizontalMinDistances(float i_leftSplashMinDistance, float i_rightSplashMinDistance)
{
	m_leftSplashMinDistance = i_leftSplashMinDistance;
	m_rightSplashMinDistance = i_rightSplashMinDistance;
}

/////////////// RaidingPartyZombieSpawner ///////////////

void RaidingPartyZombieSpawner::initializeAction(MTRand& i_random, int i_waveNumber)
{
	const RaidingPartyZombieSpawnerProps* props = GetProps<RaidingPartyZombieSpawnerProps>();
	int numRows = gLawnApp->m_board->m_gridSizeY;

	std::vector<int> rows;
	for (int i = 0; i < numRows; i++)
		rows.push_back(i);

	int column = gLawnApp->m_board->m_gridSizeX - 1;
	for (int i = 0; i < props->SwashbucklerCount; i++)
	{
		int row;
		if (!rows.empty())
		{
			int index = i_random.Next() % (int)rows.size();
			row = rows[index];
			rows.erase(rows.begin() + index);
		}
		else
			row = i_random.Next() % numRows;

		m_swashbucklerTargets.push_back(Sexy::Point(column, row));
	}
}

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


void RaidingPartyZombieSpawner::createZombies(int i_waveNumber, MTRand& i_random, int i_startIndex, int i_stopIndex)
{
	RtWeakPtr<ZombieType> type = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("swashbuckler");

	for (int i = i_startIndex; i < i_stopIndex; i++)
	{
		Zombie* zombie = gLawnApp->m_board->SpawnZombie(type, i_waveNumber);
		zombie->SetHasPlantFood(false);
		zombie->SetLoot(m_zombieLoot[i]);
		zombie->SetIsFlagZombie(false);
		zombie->PlaceOnBoard(SexyVector3(zombie->GetProps()->HitRect.mWidth + 820, BoardTransforms::GridToBoardSpaceY(m_swashbucklerTargets[i].mY), 0));
	}
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

void PirateStage::SpawnWaterSplashEffect(SexyVector2 i_splashPoint, int i_renderOrder)
{
	i_splashPoint.x = ClampFloat(i_splashPoint.x, 560.0f, 675.0f);
	SexyVector3 offset(-95.0f, -90.0f, 0.0f);
	SexyVector3 position(i_splashPoint.x, i_splashPoint.y, 0.0f);
	position += offset;

	Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
	effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_WATER_SPLASH"), EffectAnimRig_WaterSplash::StaticGetClass());
	effect->SetBoardSpaceOrigin(position, -1);
	effect->SetRenderLayerOverride(i_renderOrder);
	effect->PlaySingleAnimation("water_splash_01", SELECT_RANDOM_INDEX);
}

void PirateStage::DropZombieInOcean(ZombiePtr i_zombie)
{
	Zombie* zombie = i_zombie;
	gMessageRouter->Post(&Message::ZombieInOcean, zombie);

	const SexyVector3& pos = zombie->GetPosition();
	SexyVector2 splashPoint(pos.x, pos.y);
	SpawnWaterSplashEffect(splashPoint, zombie->CalcRowPosition() - gLawnApp->m_board->GetGridBoundingRect().mHeight + RENDER_LAYER_GROUND);

	if (i_zombie->GetType()->TypeName == "swashbuckler")
		AudioMgr::GetInstancePtr()->SendEvent("Play_Zombie_HitWater", zombie);
	else
		AudioMgr::GetInstancePtr()->SendEvent("Play_Zombie_Splash", zombie);

	if (!zombie->IsDying())
		gMessageRouter->Post(&Message::ZombieDied, zombie, nullptr);
	zombie->Destroy();
}

int PirateStage::GetPlankStartGridColumn() const
{
	return 5;
}
