//
//  FutureStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FutureStage.h"
#include "LawnApp.h"
#include "Board.h"
#include "ZombieType.h"
#include "GameEventMgr.h"
#include "PlantGroup.h"
#include "ObjectTypeDirectory.h"
#include "RenderQueue.h"
#include "RtDelegate.h"
#include "Plant.h"
#include "Zombie.h"
#include "ResourceHelpers.h"
#include "PopAnim.h"
#include "ScaledApp.h"
#include "BoardTransforms.h"
#include "LevelModuleManager.h"
#include "PlantfoodCursor.h"
#include "Graphics.h"
#include "BoardConstants.h"
#include "PlantFramework.h"
#include "TimeMgr.h"
#include "EffectAnimRig_LinkedTile.h"

FutureStage::FutureStage()
{
}

FutureStage::~FutureStage()
{
}

FutureStageProperties::~FutureStageProperties()
{
}

void FutureStage::SetLinkedTiles(const std::vector<LinkedTileEntry>& i_linkedTiles)
{
	for (int i = 0; i < i_linkedTiles.size(); i++)
	{
		addLinkedTile(i_linkedTiles[i]);
	}
	m_linkedTilePropagations.clear();
}

Color FutureStage::GetLinkedTileColor(LinkedTileClass i_class)
{
	if (i_class >= LINKEDTILE_ALPHA && i_class <= LINKEDTILE_EPSILON)
	{
		return getProps<FutureStageProperties>()->LinkedTileColors[i_class];
	}
	return Color::Black;
}

LinkedTileClass FutureStage::GetLinkedTileClassAt(const Sexy::Point& i_gridLoc)
{
	for (size_t i = 0; i < m_linkedTiles.size(); i++)
	{
		const LinkedTileEntry& tile = m_linkedTiles[i];
		if (tile.Location == i_gridLoc)
		{
			return tile.Group;
		}
	}
	return LINKEDTILE_Invalid;
}

Sexy::Point FutureStage::GetRandomLinkedTileLocation() const
{
	if (m_linkedTiles.size() == 0)
	{
		return Sexy::Point(-1, -1);
	}
	Sexy::Point loc = m_linkedTiles[Sexy::Rand((int)m_linkedTiles.size())].Location;
	return loc;
}

bool FutureStage::CanZombieSpawnInRow(int i_row, ZombieTypePtr i_type)
{
	if (i_type->TypeName == "disco_mech")
	{
		return i_row != 0 && i_row != gLawnApp->m_board->m_gridSizeY - 1;
	}
	return true;
}

void FutureStage::DestroyLinkedTileAt(const Sexy::Point& i_gridLoc)
{
	for (int i = 0; i < m_linkedTiles.size(); i++)
	{
		if (m_linkedTiles[i].Location == i_gridLoc)
		{
			destroyLinkedTileAtIndex(i);
			return;
		}
	}
}

void FutureStage::DestroyLinkedNetworkAt(const Sexy::Point& i_gridLoc)
{
	const LinkedTileEntry* tile = NULL;
	for (size_t i = 0; i < m_linkedTiles.size(); i++)
	{
		if (m_linkedTiles[i].Location == i_gridLoc)
		{
			tile = &m_linkedTiles[i];
			break;
		}
	}
	if (tile != NULL)
	{
		propagateFromTile(tile, true);
		DestroyLinkedTileAt(tile->Location);
	}
}

void FutureStage::SetIsBossFight(bool i_isBossFight)
{
	m_isBossFight = i_isBossFight;
}

void FutureStage::onLevelEnded()
{
	gMessageRouter->Unsubscribe(this);
	for (int i = m_linkedTiles.size() - 1; i >= 0; i--)
	{
		destroyLinkedTileAtIndex(i);
	}
}

void FutureStage::gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons)
{
	if (m_isBossFight && i_gridPosition.mX > 7)
	{
		io_plantingReasons->push_back(PLANTING_ONLY_ON_GRAVES);
	}
}

void FutureStage::initializeModule()
{
	StageModule::initializeModule();
	const FutureStageProperties* props = getProps<FutureStageProperties>();
	for (int i = 0; i < props->FactoryArmZombieTypes.size(); i++)
	{
		ZombieTypePtr type = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName(props->FactoryArmZombieTypes[i]);
		m_factoryArmZombieTypes.push_back(type);
	}
	m_isBossFight = false;
}

void FutureStage::onToolAppliedPlantFood(PlantGroup* i_plant)
{
	Sexy::Point gridLoc = i_plant->GridLocation();
	const LinkedTileEntry* tile = NULL;
	for (int i = 0; i < m_linkedTiles.size(); i++)
	{
		if (m_linkedTiles[i].Location == gridLoc)
		{
			tile = &m_linkedTiles[i];
			break;
		}
	}
	if (tile != NULL)
	{
		propagateFromTile(tile, false);
	}
}

void FutureStage::addToRenderQueue(RenderQueue* i_queue)
{
	for (int i = 0; i < m_factoryArms.size(); i++)
	{
		i_queue->Add(BoardEntity::CalcRenderOrderFromPosition(m_factoryArms[i].TargetLocation), Sexy::MakeDelegate(m_factoryArms[i], &FactoryArmStatus::Draw));
	}
}

void FutureStage::onPlantPlanted(Plant* i_plant)
{
	Sexy::Point gridLoc(i_plant->m_column, i_plant->m_row);
	for (int i = 0; i < m_linkedTiles.size(); i++)
	{
		if (m_linkedTiles[i].Location == gridLoc)
		{
			m_linkedTileInstances[i].AnimRigPtr->PlayPlantEnteredTile();
			m_linkedTileInstances[i].AnimRigPtr->SetPlantIsOnTile(true);
			break;
		}
	}
}

void FutureStage::onPlantDied(Plant* i_plant)
{
	Sexy::Point gridLoc(i_plant->m_column, i_plant->m_row);
	for (int i = 0; i < m_linkedTiles.size(); i++)
	{
		if (m_linkedTiles[i].Location == gridLoc)
		{
			m_linkedTileInstances[i].AnimRigPtr->PlayPlantLeftTile();
			m_linkedTileInstances[i].AnimRigPtr->SetPlantIsOnTile(false);
			break;
		}
	}
}

int FutureStage::GetPlantedPacketCount(const std::string& i_packetType)
{
	LinkedTileClass group = LINKEDTILE_Invalid;
	if (i_packetType == "tool_powertile_alpha")
	{
		group = LINKEDTILE_ALPHA;
	}
	else if (i_packetType == "tool_powertile_beta")
	{
		group = LINKEDTILE_BETA;
	}
	else if (i_packetType == "tool_powertile_gamma")
	{
		group = LINKEDTILE_GAMMA;
	}
	else if (i_packetType == "tool_powertile_delta")
	{
		group = LINKEDTILE_DELTA;
	}
	else if (i_packetType == "tool_powertile_epsilon")
	{
		group = LINKEDTILE_EPSILON;
	}

	if (group == LINKEDTILE_Invalid)
	{
		return 0;
	}

	int count = 0;
	for (int i = 0; i < m_linkedTiles.size(); i++)
	{
		if (m_linkedTiles[i].Group == group)
		{
			count++;
		}
	}
	return count;
}

void FutureStage::onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow)
{
	if (i_zombie != NULL)
	{
		ZombieTypePtr type = i_zombie->GetType();
		for (int i = 0; i < m_factoryArmZombieTypes.size(); i++)
		{
			if (m_factoryArmZombieTypes[i] == type)
			{
				m_factoryArms.push_back(FactoryArmStatus());
				FactoryArmStatus& arm = m_factoryArms[m_factoryArms.size() - 1];
				arm.TargetLocation = i_zombie->GetPosition();
				const FutureStageProperties* props = getProps<FutureStageProperties>();
				arm.CoinDropsLeft = props->FactoryArmCoinDropCount;
				arm.CoinDropChance = props->FactoryArmCoinDropChance;
				break;
			}
		}
	}
}

void FutureStage::addLinkedTile(const LinkedTileEntry& i_newTile)
{
	m_linkedTiles.push_back(i_newTile);

	PopAnim* pam;
	switch (i_newTile.Group)
	{
	case LINKEDTILE_ALPHA:
		pam = GetPAMByName("POPANIM_BACKGROUNDS_LINKTILE_01")->Duplicate();
		break;
	case LINKEDTILE_BETA:
		pam = GetPAMByName("POPANIM_BACKGROUNDS_LINKTILE_02")->Duplicate();
		break;
	case LINKEDTILE_GAMMA:
		pam = GetPAMByName("POPANIM_BACKGROUNDS_LINKTILE_03")->Duplicate();
		break;
	case LINKEDTILE_DELTA:
		pam = GetPAMByName("POPANIM_BACKGROUNDS_LINKTILE_04")->Duplicate();
		break;
	case LINKEDTILE_EPSILON:
		pam = GetPAMByName("POPANIM_BACKGROUNDS_LINKTILE_05")->Duplicate();
		break;
	default:
		return;
	}

	if (pam != NULL)
	{
		EffectAnimRig_LinkedTile* rig = PopAnimRig::CreateRig<EffectAnimRig_LinkedTile>(pam);
		rig->PlayIdle();
		LinkedTileInstanceData data;
		data.AnimRigPtr = rig->GetPtr();
		m_linkedTileInstances.push_back(data);
		delete pam;
	}
}

bool FutureStage::UseToolAt(const std::string& i_toolName, int i_mouseX, int i_mouseY, int i_clickCount)
{
	LinkedTileClass group = LINKEDTILE_Invalid;
	if (i_toolName == "tool_powertile_alpha")
	{
		group = LINKEDTILE_ALPHA;
	}
	else if (i_toolName == "tool_powertile_beta")
	{
		group = LINKEDTILE_BETA;
	}
	else if (i_toolName == "tool_powertile_gamma")
	{
		group = LINKEDTILE_GAMMA;
	}
	else if (i_toolName == "tool_powertile_delta")
	{
		group = LINKEDTILE_DELTA;
	}
	else if (i_toolName == "tool_powertile_epsilon")
	{
		group = LINKEDTILE_EPSILON;
	}

	if (group == LINKEDTILE_Invalid)
	{
		return false;
	}

	Sexy::Point gridLoc = BoardTransforms::BoardSpaceToGrid(INV_S((float)i_mouseX), INV_S((float)i_mouseY));
	if (gridLoc.mX >= 0 && gridLoc.mY >= 0)
	{
		for (size_t i = 0, n = m_linkedTiles.size(); i < n; i++)
		{
			if (m_linkedTiles[i].Location == gridLoc)
			{
				return false;
			}
		}

		LinkedTileEntry newTile;
		newTile.Location = gridLoc;
		newTile.Group = group;
		newTile.PropagationDelay = 0.25f;
		addLinkedTile(newTile);
		return true;
	}
	return false;
}

void FutureStage::destroyLinkedTileAtIndex(const int i_index)
{
	Sexy::Point location = m_linkedTiles[i_index].Location;
	m_linkedTiles.erase(m_linkedTiles.begin() + i_index);

	m_linkedTileInstances[i_index].AnimRigPtr->Destroy();
	m_linkedTileInstances.erase(m_linkedTileInstances.begin() + i_index);

	for (int i = (int)m_linkedTilePropagations.size() - 1; i >= 0; --i)
	{
		LinkedTilePropagationInfo& propagation = m_linkedTilePropagations[i];
		if (propagation.TargetLocation == location && !propagation.IsBossPropagation)
		{
			propagation.DestroyTileGlows();
			m_linkedTilePropagations.erase(m_linkedTilePropagations.begin() + i);
		}
	}
}

void FutureStage::onPlantPlantfooded(Plant* i_plant)
{
	Sexy::Point gridLoc(i_plant->m_column, i_plant->m_row);
	const LinkedTileEntry* tile = NULL;
	LinkedTileInstanceData* instance = NULL;
	for (int i = 0; i < m_linkedTiles.size(); i++)
	{
		if (m_linkedTiles[i].Location == gridLoc)
		{
			tile = &m_linkedTiles[i];
			instance = &m_linkedTileInstances[i];
			break;
		}
	}

	if (tile != NULL)
	{
		Color tileColor = GetLinkedTileColor(tile->Group);
		i_plant->SetPlantfoodShineColor(tileColor);
		instance->AnimRigPtr->PlayActivation();
		instance->IsPlantfoodActive = true;

		for (int i = (int)m_linkedTilePropagations.size() - 1; i >= 0; --i)
		{
			LinkedTilePropagationInfo& propagation = m_linkedTilePropagations[i];
			if (propagation.TargetLocation == gridLoc && propagation.IsBossPropagation)
			{
				propagation.DestroyTileGlows();
				m_linkedTilePropagations.erase(m_linkedTilePropagations.begin() + i);
			}
		}
	}
}

void FutureStage::propagateFromTile(const LinkedTileEntry* i_fromTile, bool i_isBossPropagation)
{
	const FutureStageProperties* props = getProps<FutureStageProperties>();
	Sexy::Point sourceLoc = i_fromTile->Location;
	LinkedTileClass group = i_fromTile->Group;
	for (size_t i = 0; i < m_linkedTiles.size(); i++)
	{
		const LinkedTileEntry& tile = m_linkedTiles[i];
		if (tile.Group == group && tile.Location != sourceLoc)
		{
			LinkedTilePropagationInfo propagation;
			propagation.Group = tile.Group;
			propagation.SourceLocation = sourceLoc;
			float distance = Distance2D(sourceLoc.mX, sourceLoc.mY, tile.Location.mX, tile.Location.mY);
			propagation.TotalTime = distance * i_fromTile->PropagationDelay;
			propagation.Timer = propagation.TotalTime;
			propagation.TargetLocation = tile.Location;
			propagation.IsBossPropagation = i_isBossPropagation;
			m_linkedTilePropagations.push_back(propagation);

			Color tint;
			if (i_isBossPropagation)
			{
				tint = Color::Red;
			}
			else
			{
				tint = GetLinkedTileColor(tile.Group);
				tint.mAlpha = props->LinkedTilePropagationAlpha * 255.0f;
			}
			m_linkedTilePropagations[m_linkedTilePropagations.size() - 1].BuildTileGlows(this, tint);
		}
	}
}

void FutureStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterOnUpdate(Sexy::MakeDelegate(*this, &FutureStage::onUpdate));
	getManager()->RegisterOnLevelEnded(Sexy::MakeDelegate(*this, &FutureStage::onLevelEnded));
	getManager()->RegisterAddToRenderQueue(Sexy::MakeDelegate(*this, &FutureStage::addToRenderQueue));
	gMessageRouter->Subscribe(Message::ToolAppliedPlantfood, Sexy::MakeDelegate(*this, &FutureStage::onToolAppliedPlantFood));
	gMessageRouter->Subscribe(Message::ZombieDied, Sexy::MakeDelegate(*this, &FutureStage::onZombieDied));
	gMessageRouter->Subscribe(Message::PlantPlanted, Sexy::MakeDelegate(*this, &FutureStage::onPlantPlanted));
	gMessageRouter->Subscribe(Message::PlantDied, Sexy::MakeDelegate(*this, &FutureStage::onPlantDied));
	gMessageRouter->Subscribe(Message::PlantPlantfooded, Sexy::MakeDelegate(*this, &FutureStage::onPlantPlantfooded));
	gMessageRouter->Subscribe(Message::GatherPlantingRestrictions, Sexy::MakeDelegate(*this, &FutureStage::gatherPlantingRestrictions));
}

void FutureStage::renderBackground(Graphics* i_g)
{
	StageModule::renderBackground(i_g);
	GraphicsAutoState autoState(i_g);
	i_g->SetColorizeImages(true);

	for (size_t i = 0; i < m_linkedTiles.size(); i++)
	{
		const LinkedTileEntry& tile = m_linkedTiles[i];
		Color tileColor = getProps<FutureStageProperties>()->LinkedTileColors[tile.Group];
		Color drawColor = tileColor;
		i_g->SetColor(drawColor);

		Sexy::Rect tileRect;
		static Sexy::Point s_tileOffset(-BoardConstants::GRIDSQUARE_WIDTH(), -BoardConstants::GRIDSQUARE_HEIGHT());
		tileRect = BoardTransforms::GridToBoardSpaceRect(tile.Location.mX, tile.Location.mY, 1, 1);
		tileRect.Offset(s_tileOffset);
		float scale = S(1.0f);
		tileRect.Scale(scale, scale);

		SexyTransform2D transform;
		transform.Translate(tileRect.mX, tileRect.mY);
		m_linkedTileInstances[i].AnimRigPtr->Draw(i_g, transform);
	}

	for (size_t i = 0; i < m_linkedTilePropagations.size(); i++)
	{
		LinkedTilePropagationInfo& propagation = m_linkedTilePropagations[i];
		for (int j = 0; j < propagation.Dots.size(); j++)
		{
			propagation.Dots[j]->Draw(i_g);
		}
	}
}

void FutureStage::onUpdate()
{
	for (size_t i = 0; i < m_linkedTileInstances.size(); i++)
	{
		m_linkedTileInstances[i].AnimRigPtr->UpdateAnim(PVZ_T(), PVZ_Dt());
		if (m_linkedTileInstances[i].IsPlantfoodActive)
		{
			Plant* plant = gLawnApp->m_board->GetPlantAt(m_linkedTiles[i].Location.mX, m_linkedTiles[i].Location.mY);
			if (plant == NULL || !plant->IsInPlantFoodState())
			{
				LinkedTileInstanceData& instance = m_linkedTileInstances[i];
				instance.IsPlantfoodActive = false;
				instance.AnimRigPtr->PlayIdle();
			}
		}
	}

	for (int i = (int)m_linkedTilePropagations.size() - 1; i >= 0; i--)
	{
		LinkedTilePropagationInfo& propagation = m_linkedTilePropagations[i];
		propagation.DotTimeLine.Update(PVZ_Dt());
		for (int j = 0; j < propagation.Dots.size(); j++)
		{
			propagation.Dots[j]->Update();
		}

		if (propagation.Timer > 0.0f)
		{
			propagation.Timer -= PVZ_Dt();
			if (propagation.Timer < 0.0f)
			{
				if (!propagation.IsBossPropagation)
				{
					LinkedTileInstanceData* instance = NULL;
					for (size_t k = 0; k < m_linkedTiles.size(); k++)
					{
						if (m_linkedTiles[k].Location == propagation.TargetLocation)
						{
							instance = &m_linkedTileInstances[k];
						}
					}

					Plant* plant = gLawnApp->m_board->GetPlantAt(propagation.TargetLocation.mX, propagation.TargetLocation.mY);
					if (plant != NULL && plant->CanApplyPlantfood())
					{
						plant->m_plantFramework->ApplyPlantfood();
					}
					else if (instance != NULL)
					{
						instance->AnimRigPtr->PlayPlantEnteredTile();
					}
				}
				else
				{
					DestroyLinkedTileAt(propagation.TargetLocation);
					gLawnApp->m_board->KillPlantAt(propagation.TargetLocation.mX, propagation.TargetLocation.mY);
				}
			}
		}

		if (propagation.IsDone())
		{
			m_linkedTilePropagations[i].DestroyTileGlows();
			m_linkedTilePropagations.erase(m_linkedTilePropagations.begin() + i);
		}
	}

	const FutureStageProperties* props = getProps<FutureStageProperties>();
	for (int i = (int)m_factoryArms.size() - 1; i >= 0; i--)
	{
		m_factoryArms[i].Update(props);
		if (m_factoryArms[i].State == FactoryArmStatus::ARMSTATE_DONE)
		{
			m_factoryArms.erase(m_factoryArms.begin() + i);
		}
	}
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FutureStage);

void FutureStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LinkedTilePropagationInfo);
		REFLECTION_CLASSBUILDER_FIELD(LinkedTileClass, Group);
	REFLECTION_CLASSBUILDER_END(LinkedTilePropagationInfo);

	REFLECTION_CLASSBUILDER_BEGIN(FutureStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<LinkedTileEntry>, m_linkedTiles);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<LinkedTilePropagationInfo>, m_linkedTilePropagations);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isBossFight);
	REFLECTION_CLASSBUILDER_END(FutureStage);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FutureStageProperties);

void FutureStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FutureStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, FactoryArmZombieTypes);
	REFLECTION_CLASSBUILDER_END(FutureStageProperties);
}
