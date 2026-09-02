#include "Plant_Jalapeno.h"
#include "Effect_PopAnim.h"
#include "EffectAnimRig_JalapenoFireSquare.h"
#include "Board.h"
#include "LawnApp.h"
#include "BoardTransforms.h"
#include "ResourceHelpers.h"
#include "GameEventMgr.h"
#include "EntityFinder.h"
#include "Zombie.h"
#include "GridItemFlame.h"
#include "ZombieZombossMech_PVZ1_Robot.h"
#include <algorithm>
#include "Effect_WalrusEarthTile.h"

RT_CLASS_IMPLEMENT(PlantJalapeno);

void PlantJalapeno::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantJalapeno);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_explodedAtTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_lastExplosionPropagationDistance);

	REFLECTION_CLASSBUILDER_END(PlantJalapeno);
}

void PlantJalapeno::Initialize()
{
	PlantFramework::Initialize();

	if (m_plant->IsOnBoard())
	{
		m_plant->GetAnimRig()->PlayAttack(
		    PopAnimRig::AnimStoppedReflectionDelegate(m_plant->GetPtr(),
		                                              "onAnimStoppedCallback"));
		m_plant->PlayPositionalSound("Play_Plant_Jalepeno_Attack", 0.0f);
		m_plant->m_doSpecialTime = PVZ_EOT();
	}

	m_lastExplosionPropagationDistance = 0;
	m_explodedAtTime = PVZ_EOT();
}

bool PlantJalapeno::HasShadow()
{
	return PVZ_T() < m_explodedAtTime;
}

void PlantJalapeno::Draw(Graphics* g)
{
	if (PVZ_T() < m_explodedAtTime)
	{
		PlantFramework::Draw(g);
	}
}

bool PlantJalapeno::CanAttackInColumn()
{
	return m_plant->GetCurrentLevel() > 1;
}

void PlantJalapeno::onAnimStoppedCallback(const std::string& i_animLabel)
{
	Explode();
}

void PlantJalapeno::stopSpecialEffect()
{
	for (size_t i = 0; i < m_effectAnims.size(); i++)
	{
		m_effectAnims[i]->GetPopAnimRig()->SetDisabled(true);
	}

	m_effectAnims.clear();
}

void PlantJalapeno::Explode()
{
	Sexy::RtWeakPtr<Sexy::PopAnim> pam = GetPAMByName("POPANIM_EFFECTS_JALAPENO_FIRE");

	for (int column = 0; column < gLawnApp->m_board->m_gridSizeX; column++)
	{
		Sexy::Point boardPos =
		    BoardTransforms::GridToBoardSpace(Sexy::Point(column, m_plant->m_row));
		if (gLawnApp->m_board->m_roofStage)
		{
			float roofOffset =
			    gLawnApp->m_board->calculateRoofOffsetZ((float)boardPos.mX);
			boardPos.mY = (int)(boardPos.mY - roofOffset);
		}

		Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
		effect->CreatePopAnimRig(pam, EffectAnimRig_JalapenoFireSquare::StaticGetClass());
		effect->SetBoardSpaceOrigin(SexyVector3((float)boardPos.mX,
		                                        (float)(boardPos.mY - 30), 0.0f), -1);
		effect->SetCentered(true);
		effect->SetRenderLayerOverride(
		    Board::MakeRenderOrder(RENDER_LAYER_PARTICLE, m_plant->m_row, 1));

		EffectAnimRig_JalapenoFireSquare* rig =
		    effect->GetPopAnimRig()->CastChecked<EffectAnimRig_JalapenoFireSquare>();
		rig->SetFireDelay(abs(column - m_plant->m_column) * 0.075f);
		rig->SetOwningEffect(effect);

		m_effectAnims.push_back(effect);
	}

	if (CanAttackInColumn())
	{
		for (int row = 0; row < gLawnApp->m_board->m_gridSizeY; row++)
		{
			Sexy::Point boardPos =
			    BoardTransforms::GridToBoardSpace(Sexy::Point(m_plant->m_column, row));
			if (gLawnApp->m_board->m_roofStage)
			{
				float roofOffset =
				    gLawnApp->m_board->calculateRoofOffsetZ((float)boardPos.mX);
				boardPos.mY = (int)(boardPos.mY - roofOffset);
			}

			Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
			effect->CreatePopAnimRig(pam, EffectAnimRig_JalapenoFireSquare::StaticGetClass());
			effect->SetBoardSpaceOrigin(SexyVector3((float)boardPos.mX,
			                                        (float)(boardPos.mY - 30), 0.0f), -1);
			effect->SetCentered(true);
			effect->SetRenderLayerOverride(
			    Board::MakeRenderOrder(RENDER_LAYER_PARTICLE, row, 1));

			EffectAnimRig_JalapenoFireSquare* rig =
			    effect->GetPopAnimRig()->CastChecked<EffectAnimRig_JalapenoFireSquare>();
			rig->SetFireDelay(abs(row - m_plant->m_row) * 0.075f);
			rig->SetOwningEffect(effect);

			m_effectAnims.push_back(effect);
		}
	}

	pvztime_t now = PVZ_T();
	m_lastExplosionPropagationDistance = -1;
	m_explodedAtTime = now;
	m_damagedEntities.clear();

	gMessageRouter->Post(Message::RowMissWalrus, m_plant->m_row);
	if (CanAttackInColumn())
	{
		gMessageRouter->Post(Message::ColMissWalrus, m_plant->m_column);
	}
}

void PlantJalapeno::UpdateActions()
{
	if (PVZ_T() < m_explodedAtTime)
	{
		return;
	}

	int minColumn = -1;
	int maxColumn = gLawnApp->m_board->m_gridSizeX + 1;
	int minRow = -1;
	int maxRow = gLawnApp->m_board->m_gridSizeY + 1;

	int distance = (int)((PVZ_T() - m_explodedAtTime) * 13.333333f);

	if (distance > m_lastExplosionPropagationDistance)
	{
		std::vector<BoardEntity*> entities;

		while (distance > m_lastExplosionPropagationDistance)
		{
			m_lastExplosionPropagationDistance++;

			int propagation = m_lastExplosionPropagationDistance;
			int row = m_plant->m_row;
			int top = std::max(row - propagation, minRow);
			int column = m_plant->m_column;
			int left = std::max(column - propagation, minColumn);
			int right = std::min(column + propagation, maxColumn);
			int bottom = std::min(row + propagation, maxRow);

			BoardEntityTypeFlag types = (BoardEntityTypeFlag)2 | (BoardEntityTypeFlag)4;

			EntityFinder::GetEntitiesInGridSquares(entities, types,
			                                       Sexy::Rect(left, row, right - left, 1));
			gMessageRouter->Post(Message::BreakIceBallInGridRect,
			                     Sexy::Rect(left, m_plant->m_row, right - left, 1));

			if (CanAttackInColumn())
			{
				EntityFinder::GetEntitiesInGridSquares(
				    entities, types,
				    Sexy::Rect(m_plant->m_column, top, 1, bottom - top));
				gMessageRouter->Post(
				    Message::BreakIceBallInGridRect,
				    Sexy::Rect(m_plant->m_column, top, 1, bottom - top));
			}
		}

		const PlantAction& action = m_plant->GetProps()->Actions[0];
		DamageInfo damageInfo = m_plant->calcDamageInfoFromPlantAction(action);
		SetFlag(damageInfo.Flags, DAMAGE_PREVENT_DEATH_SPAWNS, true);

		for (size_t i = 0; i < entities.size(); i++)
		{
			bool alreadyDamaged = false;
			for (size_t j = 0; j < m_damagedEntities.size(); j++)
			{
				if (m_damagedEntities[j] == entities[i])
				{
					alreadyDamaged = true;
					break;
				}
			}
			if (alreadyDamaged)
			{
				continue;
			}

			Zombie* zombie = entities[i]->Cast<Zombie>();
			if (zombie)
			{
				if (zombie->CanBeTargetedByPlant(m_plant->GetType(), true))
				{
					damageInfo.DamageGrid =
					    Sexy::Point(zombie->CalcColumnPosition(), m_plant->m_row);
					zombie->TakeDamage(damageInfo);
				}
			}
			else
			{
				GridItem* gridItem = entities[i]->Cast<GridItem>();
				if (gridItem && gridItem->IsDamageableByPlants() &&
				    !gridItem->IsA<GridItemFlame>())
				{
					entities[i]->TakeDamage(damageInfo);
				}
			}

			m_damagedEntities.push_back(entities[i]);
		}
	}

	int propagation = m_lastExplosionPropagationDistance;
	if (m_plant->m_column - propagation < -1 &&
	    m_plant->m_column + propagation > maxColumn &&
	    m_plant->m_row - propagation < -1 &&
	    m_plant->m_row + propagation > maxRow)
	{
		m_plant->KillPlant(true, false, DAMAGE_SUICIDE);
	}
}
