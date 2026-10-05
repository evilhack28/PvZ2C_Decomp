//
//  PoolDaylightStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PoolDaylightStage.h"

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
#include "ResourceHelpers.h"
#include "RestrictionSet.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "ZombieType.h"
#include "ZombiePirateCaptain.h"
#include "ZombiePirateParrot.h"
#include "EntityFinder.h"
#include "Wave.h"
#include "WaveActionToxicWater.h"
#include "GridItem.h"
#include "DamageInfo.h"
#include "Plant.h"
#include "Plant_LilyPad.h"
#include "PlantBoostMgr.h"
#include "NameMapper.h"
#include "PlantPropertySheet.h"

PoolDaylightStage::~PoolDaylightStage()
{
}

PoolDaylightStageProperties::~PoolDaylightStageProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PoolDaylightStage);

void PoolDaylightStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PoolDaylightStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<int32>, m_planks);
	REFLECTION_CLASSBUILDER_END(PoolDaylightStage);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PoolDaylightStageProperties);

void PoolDaylightStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PoolDaylightStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(PoolDaylightStageProperties);
}

void PoolDaylightStage::onWaterAnimEnd()
{
}

void PoolDaylightStage::showToxicWater()
{
}

int PoolDaylightStage::GetPlankStartGridColumn() const
{
	return 5;
}

void PoolDaylightStage::ShowGuides(bool i_show)
{
	m_showingGuides = i_show;
}

void PoolDaylightStage::onLevelEnded()
{
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Bow_Wash_BG", NULL);
}

void PoolDaylightStage::initializeModule()
{
	StageModule::initializeModule();

	m_nextLeftBreaker = m_nextRightBreaker = PVZ_EOT();
	m_playingCaptainAudio = false;
	m_showingGuides = false;
}

void PoolDaylightStage::stopZombieGroans()
{
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Seagull", NULL);
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Imp_Vox", NULL);
	StageModule::stopZombieGroans();
}

void PoolDaylightStage::upWaterGrid(int x, int y)
{
	m_WaterGrid[y][x] = false;
}

void PoolDaylightStage::downWaterGrid(int x, int y)
{
	m_WaterGrid[y][x] = true;
}

int PoolDaylightStage::GetToxicZombieRow()
{
	std::vector<int> rows;
	if (!row_1)
		rows.push_back(1);
	if (!row_2)
		rows.push_back(2);
	if (!row_3)
		rows.push_back(3);

	int row = 0;
	if (rows.size())
	{
		std::random_shuffle(rows.begin(), rows.end());
		row = *rows.begin();
	}
	return row;
}

void PoolDaylightStage::DropZombieInOcean(ZombiePtr i_zombie)
{
	Zombie* zombie = i_zombie;

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

void PoolDaylightStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterOnLoadComplete(Sexy::MakeDelegate(*this, &PoolDaylightStage::onLoadComplete));
	getManager()->RegisterOnUpdate(Sexy::MakeDelegate(*this, &PoolDaylightStage::onUpdate));
	getManager()->RegisterOnLevelEnded(Sexy::MakeDelegate(*this, &PoolDaylightStage::onLevelEnded));
	gMessageRouter->Subscribe(Message::GatherPlantingRestrictions, Sexy::MakeDelegate(*this, &PoolDaylightStage::gatherPlantingRestrictions));
}

void PoolDaylightStage::SpawnWaterSplashEffect(SexyVector2 i_splashPoint, int i_renderOrder)
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

void PoolDaylightStage::generatePlanks()
{
	for (int y = 1; y < 4; y++)
		for (int x = 0; x < 5; x++)
			Continuous[y][x] = gLawnApp->m_board->AddRegion<BoardRegionTideWater>();

	for (int y = 1; y < 4; y++)
		for (int x = 0; x < 9; x++)
			m_WaterGrid[y][x] = true;

	freshenWaterGrid();

	for (int y = 0; y < BoardConstants::NUMBER_OF_ROWS(); y++)
	{
		BoardConstants::NUMBER_OF_COLUMNS();
		for (int x = 0; x < 9; x++)
			gLawnApp->m_board->SetGridSquareType(x, y, GRIDSQUARE_GRASS);
	}
}

void PoolDaylightStage::WaterEffChange(bool state)
{
	if (state)
	{
		if (!row_1 && !row_2 && !row_3)
		{
			AnimationSequence sequence;
			sequence.AddSingleAnimation("idle_02");
			sequence.AddLoopingAnimation("idle_03");
			WaterEffect->PlayAnimationSequence(sequence);
		}
	}
	else
	{
		if (!row_1 && !row_2 && !row_3)
		{
			AnimationSequence sequence;
			sequence.AddSingleAnimation("idle_04");
			sequence.AddLoopingAnimation("idle");
			WaterEffect->PlayAnimationSequence(sequence);
		}
	}
}

void PoolDaylightStage::renderBackground(Graphics* i_g)
{
	StageModule::renderBackground(i_g);

	static SexyVector2 foamRightPos(490.0f, 220.0f);
	SexyTransform2D foamTransform;
	foamTransform.Translate(S(foamRightPos.x), S(foamRightPos.y));

	static SexyVector2 foamLeftPos(580.0f, 300.0f);
	foamTransform.LoadIdentity();
	foamTransform.Translate(S(foamLeftPos.x), S(foamLeftPos.y));

	SexyTransform2D breakerTransform;
	breakerTransform.Translate(S(m_currRightBreakerPos.x), S(m_currRightBreakerPos.y));

	breakerTransform.LoadIdentity();
	breakerTransform.Translate(S(m_currLeftBreakerPos.x), S(m_currLeftBreakerPos.y));
}

class PlantAquaVine
{
public:
	static RtClass* StaticGetClass();
};

void PoolDaylightStage::gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons)
{
	if (i_gridPosition.mY == 0 || i_gridPosition.mY == 4)
	{
		if (i_plantType->PlantFramework == "PlantLilyPad")
			io_plantingReasons->push_back(PLANTING_PLANT_ON_ROAD);
	}

	if (i_gridPosition.mY >= 1 && i_gridPosition.mY <= 3)
	{
		if (i_plantType->PlantFramework == "PlantPowerPlant")
			io_plantingReasons->push_back(PLANTING_POWERPLANT_ON_POOL);

		int plantId = PlantNameMapper::GetInstance().GetIdForType(i_plantType);
		int boost = (int)PlantBoostMgr::GetInstance().GetPlantBoostValue(plantId, WATER_MASTER);
		if (!m_CantPlayAccessory)
			;
		else
			boost = 0;
		if (!((const PlantPropertySheet*)i_plantType->Properties)->CanLiveOnWaves && boost != 1 && m_WaterGrid[i_gridPosition.mY][i_gridPosition.mX] && i_plantType)
		{
			int id = PlantNameMapper::GetInstance().GetIdForType(i_plantType);
			const PlantPropertySheet* props = i_plantType->Properties;
			Plant* plant = gLawnApp->m_board->GetPlantAt(i_gridPosition.mX, i_gridPosition.mY, "");
			if (!EntityFinder::GetGridItemAt<GridItemLilyPad>(i_gridPosition.mX, i_gridPosition.mY) && (!plant || !plant->m_plantFramework->IsA<PlantAquaVine>()))
				io_plantingReasons->push_back(PLANTING_NEED_LILYPAD_FIRST);
		}
	}
}

void PoolDaylightStage::onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to)
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

void PoolDaylightStage::onUpdate()
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
}

void PoolDaylightStage::freshenWaterGrid()
{
	for (int y = 1; y < 4; y++)
		for (int x = 0; x < 5; x++)
			Continuous[y][x]->SetRegionFromGridSquares(Sexy::Rect(0, 0, 0, 0));

	for (int y = 1; y < 4; y++)
	{
		int regionIndex = 0;
		std::vector<int> waterColumns;
		for (int x = 0; x < m_WaterGrid[y].size(); x++)
		{
			if (m_WaterGrid[y][x])
				waterColumns.push_back(x);
		}

		int start = 0;
		int length = 1;
		for (size_t i = 0; i < waterColumns.size(); i++)
		{
			if (i == 0)
				start = waterColumns[0];
			else if (waterColumns[i] == start + length)
				length++;
			else
			{
				Continuous[y][regionIndex]->SetRegionFromGridSquares(Sexy::Rect(start, y, length, 1));
				length = 1;
				start = waterColumns[i];
				regionIndex++;
			}

			if (i == waterColumns.size() - 1)
				Continuous[y][regionIndex]->SetRegionFromGridSquares(Sexy::Rect(start, y, length, 1));
		}
	}
}

void PoolDaylightStage::showFloatIslandsUPDown(int x, int y, bool i_change)
{
	if (y == 1)
	{
		if (i_change)
		{
			AnimationSequence sequence;
			sequence.AddSingleAnimation("start");
			sequence.AddLoopingAnimation("loop");
			mFloatIslands[y][x]->PlayAnimationSequence(sequence);
		}
		else
		{
			AnimationSequence sequence;
			sequence.AddSingleAnimation("end");
			sequence.AddLoopingAnimation("empty");
			mFloatIslands[y][x]->PlayAnimationSequence(sequence);

			std::vector<BoardEntity*> entities;
			Sexy::Rect rect(x, y, 1, 1);
			EntityFinder::GetEntitiesInGridSquares(entities, ENTITYTYPE_GRIDITEM | ENTITYTYPE_PLANT, rect);
			for (size_t i = 0; i < entities.size(); i++)
			{
				Plant* plant = entities[i]->Cast<Plant>();
				if (plant)
				{
					int col = plant->CalcColumnPosition();
					int row = plant->CalcRowPosition();
					std::vector<BoardEntity*> gridItems;
					EntityFinder::GetEntitiesAtGridSquare(gridItems, ENTITYTYPE_GRIDITEM, col, row);
					std::string typeName = plant->GetType()->TypeName;
					PlantTypePtr type = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(typeName);
					int plantId = PlantNameMapper::GetInstance().GetIdForType(type);
					int boost = (int)PlantBoostMgr::GetInstance().GetPlantBoostValue(plantId, WATER_MASTER);
					const PlantPropertySheet* props = type.Get()->Properties;

					bool noLilyPad = true;
					if (gridItems.size())
					{
						for (auto entity : gridItems)
						{
							GridItem* gridItem = entity->Cast<GridItem>();
							if (gridItem)
							{
								std::string gridItemName = gridItem->GetType()->TypeName;
								if (gridItemName == "lilypad")
									noLilyPad = false;
							}
						}
					}

					if (noLilyPad && boost != 1 && !props->CanLiveOnWaves)
						plant->TakeFatalDamage(DamageInfo(0.0f, DAMAGE_INSTANTLY_FATAL));
				}
			}
		}
	}
}

void PoolDaylightStage::onLoadComplete()
{
	std::vector<std::vector<RtWeakPtr<WaveActionProperties> > > waves = gLawnApp->m_board->GetWaveManager()->GetProps()->Waves;
	for (size_t i = 0; i < waves.size(); i++)
	{
		for (size_t j = 0; j < waves[i].size(); j++)
		{
			if (waves[i][j].operator->())
			{
				if (waves[i][j]->Cast<WaveActionPoolTerrainChangeProps>())
					m_CantPlayAccessory = true;
			}
		}
	}

	SetDefaultZombieSpawnPositionXOffset(-20);

	float drawScale = gLawnApp->m_contentResolutionHeight * (1.0f / 1536.0f);
	Sexy::Rect gridRect = gLawnApp->m_board->GetGridBoundingRect();
	SexyVector3 offset(-63.0f, -5.0f, 0.0f);

	bool isNight = false;
	if (gLawnApp->m_board->GetStage())
	{
		if (gLawnApp->m_board->GetStage()->Cast<PoolDaylightStage>())
			isNight = getProps<StageModuleProperties>()->BackgroundImagePrefix == "IMAGE_BACKGROUNDS_POOL_NIGHT";
	}

	for (int y = 1; y < 2; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			Sexy::Point pos = BoardTransforms::GridToBoardSpaceUnbounded(Sexy::Point(x, y));
			pos.mX += offset.x;
			pos.mY += offset.y;

			mFloatIslands[y][x] = gLawnApp->m_board->AddEffect<Effect_PopAnim>()->GetPtr();
			if (x % 2 == 0)
			{
				if (isNight)
					mFloatIslands[y][x]->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_ZOMBIE_POOL_TOXICWATER_UD11"));
				else
					mFloatIslands[y][x]->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_ZOMBIE_POOL_TOXICWATER_UD1"));
			}
			else
			{
				if (isNight)
					mFloatIslands[y][x]->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_ZOMBIE_POOL_TOXICWATER_UD22"));
				else
					mFloatIslands[y][x]->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_ZOMBIE_POOL_TOXICWATER_UD2"));
			}

			mFloatIslands[y][x]->SetBoardSpaceOrigin(SexyVector3(pos.mX, pos.mY, 0.0f), -1);
			mFloatIslands[y][x]->SetKeepAlive(true);

			AnimationSequence sequence;
			sequence.AddSingleAnimation("empty");
			sequence.AddLoopingAnimation("empty");
			mFloatIslands[y][x]->PlayAnimationSequence(sequence);
			mFloatIslands[y][x]->GetPopAnimRig()->SetDrawScale(drawScale);
			mFloatIslands[y][x]->SetRenderLayerOverride(150103);
		}
	}

	Sexy::Point waterPos = BoardTransforms::GridToBoardSpaceUnbounded(Sexy::Point(0, 1));
	WaterEffect = gLawnApp->m_board->AddEffect<Effect_PopAnim>()->GetPtr();
	WaterEffect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_ZOMBIE_POOL_TOXICWATER_CHANGE"));
	WaterEffect->SetBoardSpaceOrigin(SexyVector3(waterPos.mX - 40, waterPos.mY - 43, 0.0f), -1);
	WaterEffect->SetKeepAlive(true);

	AnimationSequence sequence;
	sequence.AddLoopingAnimation("idle");
	WaterEffect->PlayAnimationSequence(sequence);
	WaterEffect->GetPopAnimRig()->SetDrawScale(drawScale);
	WaterEffect->SetRenderLayerOverride(150102);

	generatePlanks();
}
