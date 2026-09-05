//
//  PlantFramework.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "PlantFramework.h"

#include "Board.h"
#include "BoardPropertySheet.h"
#include "BoardTransforms.h"
#include "CardGameUtils.h"
#include "CustomLevelUtils.h"
#include "EntityFinder.h"
#include "LawnApp.h"
#include "NewPVPUtils.h"
#include "PlantAnimRig.h"
#include "PlantGroup.h"
#include "ProfileUtils.h"
#include "PVP/PVPManager.h"
#include "PVZCheats.h"
#include "PVZDB.h"
#include "ReflectionBuilder.h"
#include "Zombie.h"

// BoardHelpers.h pulls in RiftUtils.h, which needs a header we do not have
namespace BoardHelpers
{
	bool CanProduceSun();
}

RT_CLASS_IMPLEMENT(PlantFramework);

void PlantFramework::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantFramework);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;
	REFLECTION_CLASSBUILDER_END(PlantFramework);
}

PlantFramework::PlantFramework()
{
	m_plant = NULL;
	m_pot = NULL;
	m_callCancelPlantfood = true;
}

PlantPot* PlantFramework::GetPot()
{
	return m_pot;
}

int PlantFramework::Rand()
{
	return m_plant->Rand();
}

int PlantFramework::Rand(int range)
{
	return m_plant->Rand(range);
}

float PlantFramework::Rand(float range)
{
	return m_plant->Rand(range);
}

void PlantFramework::InitializeAnimRig()
{
	m_plant->InitializeAnimRig();
}

void PlantFramework::ShowPlantNewRareAvatarAnim(int i_index)
{
	m_plant->ShowPlantNewRareAvatarAnim(i_index);
}

bool PlantFramework::CanProduceSun()
{
	return BoardHelpers::CanProduceSun();
}

bool PlantFramework::CanBeWatered()
{
	return m_plant->CanApplyPlantfood();
}

bool PlantFramework::IsDelayDestroy()
{
	return false;
}

void PlantFramework::TakeGridItemSmashAttack(GridItemPtr i_srcGridItem)
{
}

bool PlantFramework::TryBlockZombossRush(Zombie* i_zomboss)
{
	return m_plant->IsInvincible();
}

BoardEntityTypeFlag PlantFramework::GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon)
{
	return ENTITYTYPE_ZOMBIE | ENTITYTYPE_GRIDITEM;
}

void PlantFramework::CancelPlantfood()
{
	if (m_callCancelPlantfood)
	{
		m_plant->DisablePlantfoodAnimation();
	}
}

void PlantFramework::ManualCancelPlantfood()
{
	if (m_callCancelPlantfood)
	{
		m_plant->DisablePlantfoodAnimation();
	}
}

void PlantFramework::DisplayAvatar()
{
	ApplyPlantfood();
}

void PlantFramework::TriggerBoost()
{
	ApplyPlantfood();
}

float PlantFramework::GetTideDepthHeightMaxPct()
{
	return gLawnApp->m_board->GetBoardProperties()->DefaultTideMaxHeightPct;
}

void PlantFramework::ApplyCycling()
{
	m_plant->m_state = STATE_CYCLING;
	m_plant->GetAnimRig()->PlayCycling();
}

void PlantFramework::DoSpecialForAvatar(PlantAvatarType eAvatar)
{
	if (eAvatar == E_AVATAR_NORMAL)
	{
		DoSpecialForAvatarNormal();
	}
}

bool PlantFramework::CanTargetGrid(const int i_gridX, const int i_gridY)
{
	GridSquareType gridType = gLawnApp->m_board->GetGridSquareType(i_gridX, i_gridY);
	bool invalidGrid = (gridType == GRIDSQUARE_NONE) | (gridType == GRIDSQUARE_WATER);
	return !invalidGrid;
}

bool PlantFramework::FindTargetAndFire(PlantWeapon i_plantWeapon)
{
	bool bFired = false;

	if (m_plant->CanFindTarget(i_plantWeapon))
	{
		PlayAttackAnimation();
		bFired = true;
	}

	return bFired;
}

void PlantFramework::TakeSmashAttack(ZombiePtr i_srcZombie)
{
	if (m_plant->IsInvincible())
	{
		return;
	}

	m_plant->KillPlant();
}

void PlantFramework::ApplyExhausted(float i_duration)
{
	m_plant->m_state = STATE_EXHAUSTED;
	m_plant->m_stateEndTime = PVZ_T() + i_duration;
	GetRig()->PlayExhaustedStart();
}

void PlantFramework::CancelExhausted()
{
	if (!GetRig()->PlayExhaustedEnd())
	{
		m_plant->m_state = STATE_READY;
	}
}

void PlantFramework::CancelHelped()
{
	m_plant->GetAnimRig()->PlayHelpedEnd();
	m_plant->ResetLaunchTimer(true);
	m_plant->m_state = STATE_READY;
}

void PlantFramework::Idle()
{
	m_callCancelPlantfood = false;
	CancelPlantfood();
	m_callCancelPlantfood = true;
	GetRig()->PlayIdleLooped();
}

void PlantFramework::AddPot(PlantPot* pot)
{
	m_pot = pot;
	m_potPtr = pot->GetPtr();
}

void PlantFramework::onDestroy()
{
	if (m_pot && m_potPtr.IsValid())
	{
		m_pot->KillGridItem();
		m_pot = NULL;
		m_potPtr.ClearId();
	}

	gMessageRouter->Post(Message::PlantDestroyed, m_plant);
}

PlantTargetParams PlantFramework::GetTargetParamsForWeapon(PlantWeapon i_plantWeapon)
{
	return PlantTargetParams(TARGET_PARAMS_DISTANCE_CLOSEST, TARGET_PARAMS_FLAGS_TARGET_BLEEDERS);
}

int PlantFramework::calcZombieTargetWeight(Zombie* i_zombie, PlantTargetParams& i_targetParams)
{
	Rect zombieRect = i_zombie->GetCollisionRect();

	if (i_targetParams.distanceWeight == TARGET_PARAMS_DISTANCE_FARTHEST)
	{
		return zombieRect.mX;
	}

	return -zombieRect.mX;
}

bool PlantFramework::IsArenaBattle() const
{
	if (gLawnApp->m_board && gLawnApp->m_board->GetLevelDefinition())
	{
		return gLawnApp->m_board->GetLevelDefinition()->IsArenaBattle;
	}

	return false;
}

void PlantFramework::PlayChewedOnSound()
{
	m_plant->PlayPositionalSound("Play_Chomp", 0.f);
}

void PlantFramework::GetFinalAttackRect(Rect& i_attackRect)
{
	if (!gLawnApp->m_board || !gLawnApp->m_board->m_reducedRangeData.IsActivated)
	{
		return;
	}

	if (!gLawnApp->m_board->m_reducedRangeData.TargetablePlantTypes.IsIncluded(m_plant))
	{
		return;
	}

	int reducedGrids = gLawnApp->m_board->m_reducedRangeData.ReducedGrids;
	int reducedWidth = i_attackRect.mWidth - reducedGrids * BoardConstants::GRIDSQUARE_WIDTH();
	i_attackRect.mWidth = reducedWidth >= 0 ? reducedWidth : 0;
}

float PlantFramework::GetRefundSunAmount()
{
	float refundSun = 0.f;

	if (!m_plant->GetIsDuplicatePlant())
	{
		refundSun = m_plant->GetType()->GetRefundCost(E_AVATAR_ILLEGAL);
	}

	return refundSun;
}

void PlantFramework::SetAvatarEnable(bool bAvatar)
{
	if (PVPManager::GetInstancePtr()->IsLoadServerPlantData() != Server_Plant_Battle &&
		PVPManager::GetInstancePtr()->IsLoadServerPlantData() != Server_Plant_Occupy_Edit &&
		!CustomLevelUtils::IsCustomLevel() && !NewPVPUtils::IsPlayingNewPVP())
	{
		bAvatar = m_plant->GetPlantAvatarShowIndex() >= 0;
	}

	m_plant->SetAvatarEnable(bAvatar);

	if (GetAnimRig())
	{
		GetAnimRig()->SetAvatarEnable(bAvatar);
	}
}

void PlantFramework::DoProjectileCombo()
{
	Projectile* projectile = m_plant->Fire(ZombiePtr(NULL), m_plant->m_row, WEAPON_PRIMARY);

	if (projectile)
	{
		SexyVector3 projectilePos = projectile->GetPosition();
		projectilePos.x += 30.f;
		projectile->SetPosition(projectilePos);
	}
}

void PlantFramework::ApplyPlantfood()
{
	m_plant->EndCondition(PCONDITION_Paralysis);
	m_plant->EndCondition(PCONDITION_SlowDown);
	m_plant->EndCondition(PCONDITION_Burning);
	m_plant->EndCondition(PCONDITION_Positive);
	m_plant->EndCondition(PCONDITION_Negative);
	m_plant->EndCondition(PCONDITION_MoreSlowDown);

	m_plant->EnablePlantfoodAnimation();
}

void PlantFramework::ApplyHelped()
{
	m_plant->m_state = STATE_BEING_HELPED;
	m_plant->GetAnimRig()->PlayHelpedStart();

	if (GetProps()->HelpedActivationSound.size())
	{
		m_plant->PlayPositionalSound(GetProps()->HelpedActivationSound, 0.f);
	}
}

SexyVector3 PlantFramework::GetFireOriginOffset(const PlantAction& i_action, float i_plantScale)
{
	SexyVector2 spawnOffset = i_action.SpawnOffset;
	float originX = gCheat_X + spawnOffset.x;
	float originY = gCheat_Y + spawnOffset.y;

	return SexyVector3(i_plantScale * originX, 0.f, -originY * i_plantScale);
}

void PlantFramework::onBeThrown()
{
	m_plant->clearRelocationEvents();

	SexyVector2 plantPos = m_plant->GetPosition2D();

	RelocationEvent relocationEvent;
	relocationEvent.m_relocateFromX = plantPos.x;
	relocationEvent.m_relocateFromY = plantPos.y;
	relocationEvent.m_relocateStartTime = PVZ_T();
	relocationEvent.m_relocateEndTime = relocationEvent.m_relocateStartTime + 1.f;
	relocationEvent.m_relocateToX = BoardTransforms::GridToBoardSpaceXUnbounded(BoardTransforms::BoardSpaceToGridXUnbounded(-100));
	relocationEvent.m_relocateToY = relocationEvent.m_relocateFromY;
	relocationEvent.m_relocationType = RelocationEvent::RELOCATION_PUSHED_OFFSCREEN;
	relocationEvent.m_whetherToMovePlant = true;

	m_plant->addRelocationEvent(relocationEvent);
}

float PlantFramework::GetRefundSunAmountForShovel()
{
	if (GetRefundSunForShovel())
	{
		return GetRefundSunAmount();
	}

	if (m_plant->GetIsDuplicatePlant())
	{
		return 0.f;
	}

	return m_plant->GetType()->GetRefundCost(E_AVATAR_ILLEGAL);
}

void PlantFramework::SetPopAnimDelegates(PlantAnimRig* i_rig)
{
	i_rig->SetPopAnimCommandDelegate(MakeDelegate(*m_plant, &Plant::OnAnimCommand));
	i_rig->SetPlantDelegates(MakeDelegate(*m_plant, &Plant::OnUseSpecialAnimCommand),
							 MakeDelegate(*m_plant, &Plant::OnUseActionAnimCommand));
}

void PlantFramework::Initialize()
{
	ProfileUtils::Profile();

	bool avatarEnable;

	if (PVPManager::GetInstancePtr()->IsLoadServerPlantData() == Server_Plant_Battle ||
		PVPManager::GetInstancePtr()->IsLoadServerPlantData() == Server_Plant_Occupy_Edit)
	{
		avatarEnable = PVPManager::GetInstancePtr()->GetTargetPlantAvatar(m_plant->GetType());
	}
	else if (CustomLevelUtils::IsCustomLevel() || NewPVPUtils::IsPlayingNewPVP())
	{
		avatarEnable = false;
	}
	else
	{
		avatarEnable = m_plant->GetPlantAvatarShowIndex() >= 0;
	}

	SetAvatarEnable(avatarEnable);
	GetAnimRig()->SetAvatarEnable(avatarEnable);
	GetAnimRig()->SetPlantLevel(GetCurrentLevel());

	gMessageRouter->Post(Message::PlantCreate, m_plant);
}

ZombiePtr PlantFramework::FindTargetZombieInGridRegion(Rect& i_gridRegion, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams)
{
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesInGridSquares(entities, ENTITYTYPE_ZOMBIE, i_gridRegion);

	return getBestZombieFromEntities(entities, i_targetParams);
}

GridItemPtr PlantFramework::FindTargetDamageableGridItem(Rect& i_gridRect, PlantWeapon i_plantWeapon)
{
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesInGridSquares(entities, ENTITYTYPE_GRIDITEM, i_gridRect);

	return getBestDamageableGridItemFromEntities(entities);
}

ZombiePtr PlantFramework::getBestZombieFromEntities(const std::vector<BoardEntity*> i_entities, PlantTargetParams& i_targetParams)
{
	ZombiePtr bestZombie(NULL);

	for (std::vector<BoardEntity*>::const_iterator it = i_entities.begin(), end = i_entities.end(); it != end; ++it)
	{
		ZombiePtr zombie = (*it)->GetPtr();

		if (!zombie.IsValid())
			continue;

		if (bestZombie.IsValid())
			continue;

		bestZombie = zombie;

		if (i_targetParams.distanceWeight != TARGET_PARAMS_DISTANCE_ANY)
			continue;

		if (bestZombie)
			break;
	}

	return bestZombie;
}

GridItemPtr PlantFramework::getBestDamageableGridItemFromEntities(std::vector<BoardEntity*> entities)
{
	GridItemPtr bestGridItem(NULL);
	int bestColumn = 18;

	for (std::vector<BoardEntity*>::iterator it = entities.begin(), end = entities.end(); it != end; ++it)
	{
		GridItem* gridItem = (*it)->CastChecked<GridItem>();

		if (!gridItem->IsOnOpposingTeam(m_plant))
			continue;

		if (!gridItem->IsDamageableByPlants())
			continue;

		int column = gridItem->GetGridX();

		if (bestColumn <= column)
			continue;

		bestColumn = column;
		bestGridItem = gridItem->GetPtr();
	}

	return bestGridItem;
}

int PlantFramework::damageEntitiesInBoardRect(DamageInfo& i_damage, BoardEntityTypeFlag i_acceptedTypes, Rect i_rect, bool i_sameTeam)
{
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesTouchingRectangle(entities, i_acceptedTypes, i_rect);

	return damageEntities(i_damage, i_acceptedTypes, entities, i_sameTeam);
}

int PlantFramework::damageEntitiesInGridRadius(DamageInfo& i_damage, BoardEntityTypeFlag i_acceptedTypes, float i_gridradius, SexyVector3 i_origin, bool i_sameTeam)
{
	double radius = BoardConstants::GRIDSQUARE_WIDTH() * sqrt(i_gridradius);
	int gridRadius = (int)i_gridradius / 2;
	int topRow = m_plant->m_row - gridRadius;
	int bottomRow = gridRadius + m_plant->m_row;

	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesTouchingCircle2D(entities, i_acceptedTypes, SexyVector2(i_origin.x, i_origin.y),
											  radius, topRow, bottomRow);

	return damageEntities(i_damage, i_acceptedTypes, entities, i_sameTeam);
}

int PlantFramework::damageEntities(DamageInfo& i_damage, BoardEntityTypeFlag i_acceptedTypes, std::vector<BoardEntity*> i_entities, bool i_sameTeam)
{
	ZombieTestFlag zombieTestFlags = ZT_DYING | ZT_DOES_NOT_COLLIDE_WITH_PLANT | ZT_ZOMBIE_CANNOT_BE_TARGETED_BY_PLANT;

	if (i_sameTeam)
	{
		zombieTestFlags |= ZT_OPPOSING_TEAM;
	}
	else
	{
		zombieTestFlags |= ZT_SAME_TEAM;
	}

	int damagedCount = 0;

	for (size_t i = 0; i < i_entities.size(); ++i)
	{
		if (i_entities[i])
		{
			Zombie* zombie = i_entities[i]->Cast<Zombie>();

			if (zombie && zombie->MatchesAny(zombieTestFlags, m_plant))
				continue;
		}

		if (i_entities[i])
		{
			GridItem* gridItem = i_entities[i]->Cast<GridItem>();

			if (gridItem && !gridItem->IsDamageableByPlants())
				continue;
		}

		onEntityDamaged(i_entities[i]);
		i_entities[i]->TakeDamage(i_damage);
		damagedCount++;
	}

	return damagedCount;
}

ZombiePtr PlantFramework::FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams)
{
	ZombiePtr bestZombie(NULL);
	int zombieWeight = 0;
	int bestWeight = 0;

	for (int row = i_region.mY; row < i_region.mY + i_region.mHeight; ++row)
	{
		ZombiePtr zombie = FindTargetZombieInRow(row, i_plantWeapon, &zombieWeight, i_targetParams);

		if (!zombie.IsValid())
			continue;

		if (bestZombie.IsValid())
		{
			if (zombieWeight > bestWeight)
			{
				bestZombie = zombie;
				bestWeight = zombieWeight;
			}

			continue;
		}

		bestZombie = zombie;
		bestWeight = zombieWeight;

		if (i_targetParams.distanceWeight != TARGET_PARAMS_DISTANCE_ANY)
			continue;

		if (bestZombie)
			break;
	}

	return bestZombie;
}

ZombiePtr PlantFramework::FindTargetZombieInRow(int i_row, PlantWeapon i_plantWeapon, int* io_zombieWeight, PlantTargetParams& i_targetParams)
{
	Rect attackRect = GetPlantAttackRect(i_plantWeapon);
	GetFinalAttackRect(attackRect);

	return FindTargetZombieInRow(i_row, i_plantWeapon, io_zombieWeight, i_targetParams, attackRect);
}

std::string PlantFramework::GetFireSoundEvent() const
{
	return GetProps()->Actions[m_plant->m_currentPlantActionIdx].ProjectileLaunchSound;
}

int PlantFramework::CalcRenderOrder()
{
	bool inPlantFood = IsInPlantFoodState();
	RenderLayer renderLayer;

	switch (m_plant->GetMultiPlantDrawLayer())
	{
	case MULTI_PLANT_GRID_LAYER_ARMOR:
		renderLayer = inPlantFood ? RENDER_LAYER_PLANT_ABOVE_ZOMBIES_ARMOR : RENDER_LAYER_PLANT_ARMOR;
		break;

	case MULTI_PLANT_GRID_LAYER_MAIN:
	case MULTI_PLANT_GRID_LAYER_EFFECT:
		if (inPlantFood)
		{
			PlantGroup* plantGroup = gLawnApp->m_board->GetPlantGroupAt(m_plant->m_column, m_plant->m_row);

			if (plantGroup && (plantGroup->HasPlant("pumpkin") || plantGroup->HasPlant("powervine") || plantGroup->HasPlant("peavine")))
			{
				renderLayer = RENDER_LAYER_PLANT;
			}
			else
			{
				renderLayer = RENDER_LAYER_PLANT_ABOVE_ZOMBIES;
			}
		}
		else
		{
			renderLayer = RENDER_LAYER_PLANT;
		}
		break;

	case MULTI_PLANT_GRID_LAYER_POWER:
		renderLayer = inPlantFood ? RENDER_LAYER_PLANT_ABOVE_ZOMBIES_POWER : RENDER_LAYER_PLANT_POWER;
		break;

	case MULTI_PLANT_GRID_LAYER_GROUND:
		renderLayer = inPlantFood ? RENDER_LAYER_PLANT_ABOVE_ZOMBIES_GROUND : RENDER_LAYER_PLANT_GROUND;
		break;
	}

	return Board::MakeRenderOrder(renderLayer, m_plant->m_row, (int)(805.f - m_plant->GetPosition().x));
}

Rect PlantFramework::GetPlantAttackGridRect(PlantWeapon i_plantWeapon)
{
	float plantScale = (CardGameUtils::IsPlayingCardGame() || NewPVPUtils::IsPlayingNewPVP()) ? m_plant->m_baseScale : 1.f;

	const PlantPropertySheet* plantProps = m_plant->GetProps();

	if ((size_t)i_plantWeapon < plantProps->Actions.size())
	{
		const PlantAction& action = plantProps->Actions[i_plantWeapon];

		if (action.TriggerType == PLANT_ACTION_TRIGGER_GRID_RECT)
		{
			return Rect(m_plant->m_column + action.RectTriggerRange.mX, m_plant->m_row + action.RectTriggerRange.mY,
						action.RectTriggerRange.mWidth, action.RectTriggerRange.mHeight);
		}
		else if (action.TriggerType == PLANT_ACTION_TRIGGER_ROW)
		{
			return Rect(0, m_plant->m_row, BoardConstants::NUMBER_OF_COLUMNS(), 1);
		}
		else if (action.TriggerType == PLANT_ACTION_TRIGGER_ENTIRE_BOARD)
		{
			return Rect(0, 0, BoardConstants::NUMBER_OF_COLUMNS(), BoardConstants::NUMBER_OF_ROWS());
		}
		else if (action.TriggerType == PLANT_ACTION_TRIGGER_RECT)
		{
			int gridX = (int)(plantScale * (float)action.RectTriggerRange.mX / BoardConstants::GRIDSQUARE_WIDTH());
			int gridY = (int)(plantScale * (float)action.RectTriggerRange.mY / BoardConstants::GRIDSQUARE_HEIGHT());
			int gridWidth = (int)((plantScale * (float)action.RectTriggerRange.mWidth + BoardConstants::GRIDSQUARE_WIDTH() * 0.8) / BoardConstants::GRIDSQUARE_WIDTH());
			int gridHeight = (int)(plantScale * (float)action.RectTriggerRange.mHeight / BoardConstants::GRIDSQUARE_HEIGHT());

			if (gridWidth <= 0)
				gridWidth = 1;

			if (gridHeight <= 0)
				gridHeight = 1;

			if (gridX + m_plant->m_column + gridWidth > BoardConstants::NUMBER_OF_COLUMNS())
				gridWidth = BoardConstants::NUMBER_OF_COLUMNS() - m_plant->m_column - gridX;

			return Rect(gridX + m_plant->m_column, gridY + m_plant->m_row, gridWidth, gridHeight);
		}
	}

	return Rect(m_plant->m_column, m_plant->m_row, BoardConstants::NUMBER_OF_COLUMNS() - m_plant->m_column, 1);
}

Rect PlantFramework::GetPlantAttackRect(PlantWeapon i_plantWeapon)
{
	int roofOffset = !gLawnApp->m_board->m_roofStage ? 0 : 20;

	float plantScale = (CardGameUtils::IsPlayingCardGame() || NewPVPUtils::IsPlayingNewPVP()) ? m_plant->m_baseScale : 1.f;

	const SexyVector3& plantPosition = m_plant->GetPosition();
	Rect attackRect((int)plantPosition.x, (int)(plantPosition.y - m_plant->GetHeight()), 800, m_plant->GetHeight());

	const PlantPropertySheet* plantProps = m_plant->GetProps();

	if ((size_t)i_plantWeapon < plantProps->Actions.size())
	{
		const PlantAction& action = plantProps->Actions[i_plantWeapon];

		if (action.TriggerType == PLANT_ACTION_TRIGGER_INSTANT)
		{
			attackRect.mWidth = 1;
			attackRect.mHeight = 1;
		}
		else if (action.TriggerType == PLANT_ACTION_TRIGGER_RECT)
		{
			if (m_plant->GetType()->TypeName == "pokra")
			{
				int rectTop = (int)(action.RectTriggerRange.mY + m_plant->GetPosition().y - roofOffset);
				Rect gridRect = BoardTransforms::GridToBoardSpaceRect(m_plant->CalcColumnPosition(), m_plant->CalcRowPosition(), 1, 1);

				attackRect.mY = std::max(rectTop, gridRect.mY);
				attackRect.mX = (int)(action.RectTriggerRange.mX + m_plant->GetPosition().x);
				attackRect.mWidth = (int)(plantScale * action.RectTriggerRange.mWidth);
				attackRect.mHeight = (int)(plantScale * action.RectTriggerRange.mHeight);
			}
			else
			{
				attackRect.mX = (int)(plantScale * action.RectTriggerRange.mX + m_plant->GetPosition().x);
				attackRect.mY = (int)(plantScale * action.RectTriggerRange.mY + (m_plant->GetPosition().y - roofOffset));
				attackRect.mWidth = (int)(plantScale * action.RectTriggerRange.mWidth);
				attackRect.mHeight = (int)(plantScale * action.RectTriggerRange.mHeight);
			}
		}
		else if (action.TriggerType == PLANT_ACTION_TRIGGER_GRID_RECT)
		{
			attackRect.mX = (int)(plantScale * action.RectTriggerRange.mX * BoardConstants::GRIDSQUARE_WIDTH() + m_plant->GetPosition().x);
			attackRect.mY = (int)(plantScale * action.RectTriggerRange.mY * BoardConstants::GRIDSQUARE_HEIGHT() + (m_plant->GetPosition().y - roofOffset));
			attackRect.mWidth = (int)(plantScale * action.RectTriggerRange.mWidth * BoardConstants::GRIDSQUARE_WIDTH());
			attackRect.mHeight = (int)(plantScale * action.RectTriggerRange.mHeight * BoardConstants::GRIDSQUARE_HEIGHT());
		}
		else if (action.TriggerType == PLANT_ACTION_TRIGGER_COLUMN)
		{
			attackRect.mX = BoardTransforms::BoardSpaceToGridX(m_plant->GetPosition().x) * BoardConstants::GRIDSQUARE_WIDTH();
			attackRect.mY = BoardConstants::GRIDSQUARE_HEIGHT();
			attackRect.mWidth = 0;
			attackRect.mHeight = BoardConstants::NUMBER_OF_ROWS() * BoardConstants::GRIDSQUARE_HEIGHT();
		}
		else if (action.TriggerType == PLANT_ACTION_TRIGGER_ROW)
		{
			attackRect.mX = 0;
			attackRect.mY = BoardTransforms::BoardSpaceToGridY(m_plant->GetPosition().y);
			attackRect.mWidth = 800;
			attackRect.mHeight = BoardConstants::GRIDSQUARE_HEIGHT();
			attackRect.mY = attackRect.mY * BoardConstants::GRIDSQUARE_HEIGHT() + 160;
		}
		else if (action.TriggerType == PLANT_ACTION_TRIGGER_ENTIRE_BOARD)
		{
			attackRect.mX = 0;
			attackRect.mWidth = 800;
			attackRect.mY = 0;
			attackRect.mHeight = 600;
		}
	}

	return attackRect;
}

ZombiePtr PlantFramework::FindTargetZombieInRow(int i_row, PlantWeapon i_plantWeapon, int* io_zombieWeight, PlantTargetParams& i_targetParams, Rect i_attackRect)
{
	ZombiePtr bestZombie(NULL);

	if (!gLawnApp->m_board->RowCanHaveZombies(i_row))
	{
		return bestZombie;
	}

	if (io_zombieWeight)
	{
		*io_zombieWeight = 0;
	}

	int bestWeight = 0;

	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesTouchingRectangle(entities, ENTITYTYPE_ZOMBIE, i_attackRect, i_row, i_row);

	for (size_t i = 0; i < entities.size(); ++i)
	{
		Zombie* zombie = entities[i]->CastChecked<Zombie>();

		ZombieTestFlag zombieTestFlags = ZT_DYING | ZT_SAME_TEAM | ZT_PLANT_CANNOT_TARGET_ZOMBIE | ZT_OFF_SCREEN |
										 ZT_ZOMBIE_CANNOT_BE_TARGETED_BY_PLANT | ZT_DOES_NOT_COLLIDE_WITH_PLANT;

		if (i_targetParams.targetFlags == TARGET_PARAMS_FLAGS_None)
		{
			zombieTestFlags |= ZT_BLEEDING_OUT;
		}

		if (zombie->MatchesAny(zombieTestFlags, m_plant))
			continue;

		if (i_targetParams.targetFlags & TARGET_PARAMS_FLAGS_IGNORE_MARKED_FOR_DEATH)
		{
			if (TestFlag(zombie->m_zombieFlags, ZFLAG_IgnoreFindTarget))
				continue;
		}

		if (i_targetParams.targetFlags & TARGET_PARAMS_FLAGS_LIMIT_RIGHT_OF_CENTER)
		{
			if (zombie->GetPosition().x <= m_plant->GetCenterPt().mX)
				continue;
		}

		Rect zombieRect = zombie->GetCollisionRect();
		int zombieWeight = calcZombieTargetWeight(zombie, i_targetParams);

		if (!bestZombie || bestWeight < zombieWeight)
		{
			bestWeight = zombieWeight;
			bestZombie = zombie->GetPtr();
		}
	}

	if (io_zombieWeight)
	{
		*io_zombieWeight = bestWeight;
	}

	return bestZombie;
}

std::vector<BoardEntityPtr> PlantFramework::FindAllTargets(FindTargetFilterFlags i_findFlags, const ZombieTestFlag i_appendZombieTestFlags)
{
	std::vector<BoardEntityPtr> targets;

	for (Sexy::RtDbTable::Iterator it =
	         PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
	{
		ZombiePtr zombie = *it;

		if (zombie->MatchesAny(ZT_DYING | ZT_SAME_TEAM | ZT_OFF_SCREEN | ZT_PLANT_CANNOT_TARGET_ZOMBIE | i_appendZombieTestFlags, m_plant))
		{
			continue;
		}
		if (zombie->HasCondition(ZCONDITION_Icecubed))
		{
			continue;
		}
		if (zombie->HasCondition(ZCONDITION_Squidified))
		{
			continue;
		}
		if (zombie->HasCondition(ZCONDITION_StoneBlocked))
		{
			continue;
		}

		targets.push_back(zombie);
	}

	if (i_findFlags & FIND_TARGET_FILTER_ZOMBIES_ONLY)
	{
		return targets;
	}

	for (Sexy::RtDbTable::Iterator it =
	         PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_GRIDITEMS); it; ++it)
	{
		BoardEntityPtr entity = *it;
		GridItem* gridItem = entity->CastChecked<GridItem>();

		if (!gridItem->IsDamageableByPlants())
		{
			continue;
		}
		if (!gridItem->IsOnOpposingTeam(m_plant))
		{
			continue;
		}
		if (i_findFlags & FIND_TARGET_FILTER_GRIDITEM_ONLY_FORWARD)
		{
			if (gridItem->GetGridX() < m_plant->m_column)
			{
				continue;
			}
		}

		targets.push_back(entity);
	}

	return targets;
}

std::vector<SexyVector3> PlantFramework::FindTargetsGrid(int i_targetsToFind, std::vector<BoardEntityPtr> i_targetsToSkip)
{
	std::vector<SexyVector3> targets;

	for (int found = 0; found < i_targetsToFind; found++)
	{
		int column;
		int row;

		do
		{
			column = m_plant->m_column + Rand() % (gLawnApp->m_board->m_gridSizeX - m_plant->m_column);
			row = Rand() % gLawnApp->m_board->m_gridSizeY;
		}
		while (!CanTargetGrid(column, row));

		targets.push_back(SexyVector3(column, row, 0.f));
	}

	return targets;
}

std::vector<BoardEntityPtr> PlantFramework::FindTargets(int i_targetsToFind, std::vector<BoardEntityPtr> i_targetsToSkip)
{
	std::vector<BoardEntityPtr> targets;
	int found = 0;

	std::vector<BoardEntityPtr> allTargets = FindAllTargets(FIND_TARGET_FILTER_ZOMBIES_ONLY);
	std::random_shuffle(allTargets.begin(), allTargets.end());

	for (std::vector<BoardEntityPtr>::iterator it = allTargets.begin(); it < allTargets.end(); ++it)
	{
		if (i_targetsToFind <= found)
			break;

		ZombiePtr zombie = *it;

		if (zombie->IsDying())
			continue;

		if (zombie->IsBleedingOut())
			continue;

		if (!zombie->IsOnOpposingTeam(m_plant))
			continue;

		if (zombie->GetPosition().x > gLawnApp->m_board->GetBoardProperties()->PlantTargetingXThreshold)
			continue;

		bool alreadyTargeted = false;

		for (size_t i = 0; i < i_targetsToSkip.size(); i++)
		{
			if (i_targetsToSkip[i] == zombie)
			{
				alreadyTargeted = true;
				break;
			}
		}

		if (alreadyTargeted)
			continue;

		found++;
		targets.push_back(zombie);
	}

	for (Sexy::RtDbTable::Iterator it =
	         PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_GRIDITEMS); it && found < i_targetsToFind; ++it)
	{
		GridItemPtr gridItem = *it;

		if (!gridItem->IsDamageableByPlants())
			continue;

		bool alreadyTargeted = false;

		for (size_t i = 0; i < i_targetsToSkip.size(); i++)
		{
			if (i_targetsToSkip[i] == gridItem)
			{
				alreadyTargeted = true;
				break;
			}
		}

		if (alreadyTargeted)
			continue;

		found++;
		targets.push_back(gridItem);
	}

	return targets;
}

std::vector<BoardEntityPtr> PlantFramework::FindAllTargets(FindTargetFilterFlags i_findFlags)
{
	std::vector<BoardEntityPtr> targets;

	for (Sexy::RtDbTable::Iterator it =
	         PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
	{
		ZombiePtr zombie = *it;

		if (!zombie->IsDying() &&
			(!m_plant || zombie->CanBeTargetedByPlant(m_plant->GetType(), false)) &&
			(!m_plant || zombie->IsOnOpposingTeam(m_plant)) &&
			zombie->GetPosition().x <= gLawnApp->m_board->GetBoardProperties()->PlantTargetingXThreshold &&
			(!m_plant || m_plant->m_plantFramework->CanTargetZombie(zombie, WEAPON_PRIMARY)))
		{
			targets.push_back(zombie);
		}
	}

	if (i_findFlags & FIND_TARGET_FILTER_ZOMBIES_ONLY)
	{
		return targets;
	}

	for (Sexy::RtDbTable::Iterator it =
	         PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_GRIDITEMS); it; ++it)
	{
		BoardEntityPtr entity = *it;
		GridItem* gridItem = entity->CastChecked<GridItem>();

		if (!gridItem->IsDamageableByPlants())
		{
			continue;
		}
		if (!gridItem->IsOnOpposingTeam(m_plant))
		{
			continue;
		}
		if (i_findFlags & FIND_TARGET_FILTER_GRIDITEM_ONLY_FORWARD)
		{
			if (gridItem->GetGridX() < m_plant->m_column)
			{
				continue;
			}
		}

		targets.push_back(entity);
	}

	return targets;
}
