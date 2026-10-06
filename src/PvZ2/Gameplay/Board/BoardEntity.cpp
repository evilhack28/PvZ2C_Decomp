//
//  BoardEntity.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "BoardEntity.h"

#include "Board.h"
#include "BoardConstants.h"
#include "BoardTransforms.h"
#include "ComponentBase.h"
#include "DamageInfo.h"
#include "GameObject.h"
#include "LawnApp.h"
#include "GridItem.h"
#include "PVZDB.h"
#include "ReflectionBuilder.h"
#include "TimeMgr.h"

RT_CLASS_IMPLEMENT(BoardEntity);
void BoardEntity::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(BoardEntityStatType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(damage, BOARDENTITYSTATTYPE_DAMAGE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(armor, BOARDENTITYSTATTYPE_ARMOR);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness, BOARDENTITYSTATTYPE_TOUGHNESS);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(recharge, BOARDENTITYSTATTYPE_RECHARGE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(area, BOARDENTITYSTATTYPE_AREA);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(range, BOARDENTITYSTATTYPE_RANGE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(speed, BOARDENTITYSTATTYPE_SPEED);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(variable, BOARDENTITYSTATTYPE_VARIABLE);
	REFLECTION_ENUMBUILDER_END(BoardEntityStatType);

	REFLECTION_ENUMBUILDER_BEGIN(BoardEntityStatValue);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(damage0, BOARDENTITYSTATVALUE_DAMAGE0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(damage1, BOARDENTITYSTATVALUE_DAMAGE1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(damage2, BOARDENTITYSTATVALUE_DAMAGE2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(damage3, BOARDENTITYSTATVALUE_DAMAGE3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(damage4, BOARDENTITYSTATVALUE_DAMAGE4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(damage5, BOARDENTITYSTATVALUE_DAMAGE5);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(damage6, BOARDENTITYSTATVALUE_DAMAGE6);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(recharge0, BOARDENTITYSTATVALUE_RECHARGE0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(recharge1, BOARDENTITYSTATVALUE_RECHARGE1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(recharge2, BOARDENTITYSTATVALUE_RECHARGE2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(recharge3, BOARDENTITYSTATVALUE_RECHARGE3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(recharge4, BOARDENTITYSTATVALUE_RECHARGE4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(armor0, BOARDENTITYSTATVALUE_ARMOR0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(armor1, BOARDENTITYSTATVALUE_ARMOR1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(armor2, BOARDENTITYSTATVALUE_ARMOR2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(armor3, BOARDENTITYSTATVALUE_ARMOR3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(single, BOARDENTITYSTATVALUE_SINGLE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(square, BOARDENTITYSTATVALUE_SQUARE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(1by4, BOARDENTITYSTATVALUE_1BY4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(3by2, BOARDENTITYSTATVALUE_3BY2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(3by3, BOARDENTITYSTATVALUE_3BY3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(lane, BOARDENTITYSTATVALUE_LANE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(fullboard, BOARDENTITYSTATVALUE_FULLBOARD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(touch, BOARDENTITYSTATVALUE_TOUCH);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(close, BOARDENTITYSTATVALUE_CLOSE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(3tiles, BOARDENTITYSTATVALUE_3TILES);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(straight, BOARDENTITYSTATVALUE_STRAIGHT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(lobbed, BOARDENTITYSTATVALUE_LOBBED);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(frontback, BOARDENTITYSTATVALUE_FRONTBACK);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(multihit, BOARDENTITYSTATVALUE_MULTIHIT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(multilane, BOARDENTITYSTATVALUE_MULTILANE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(5way, BOARDENTITYSTATVALUE_5WAY);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness0, BOARDENTITYSTATVALUE_TOUGHNESS0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness1, BOARDENTITYSTATVALUE_TOUGHNESS1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness2, BOARDENTITYSTATVALUE_TOUGHNESS2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness3, BOARDENTITYSTATVALUE_TOUGHNESS3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness4, BOARDENTITYSTATVALUE_TOUGHNESS4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness5, BOARDENTITYSTATVALUE_TOUGHNESS5);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness6, BOARDENTITYSTATVALUE_TOUGHNESS6);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness7, BOARDENTITYSTATVALUE_TOUGHNESS7);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(toughness8, BOARDENTITYSTATVALUE_TOUGHNESS8);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(speed0, BOARDENTITYSTATVALUE_SPEED0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(speed1, BOARDENTITYSTATVALUE_SPEED1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(speed2, BOARDENTITYSTATVALUE_SPEED2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(speed3, BOARDENTITYSTATVALUE_SPEED3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(speed4, BOARDENTITYSTATVALUE_SPEED4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(speed5, BOARDENTITYSTATVALUE_SPEED5);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(4way, BOARDENTITYSTATVALUE_4WAY);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(variable0, BOARDENTITYSTATVALUE_VARIABLE);
	REFLECTION_ENUMBUILDER_END(BoardEntityStatValue);

	REFLECTION_CLASSBUILDER_BEGIN(BoardEntityStat);
	REFLECTION_CLASSBUILDER_END(BoardEntityStat);

	REFLECTION_ENUMBUILDER_BEGIN(BoardEntityTypeFlag);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(plant, ENTITYTYPE_PLANT);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(zombie, ENTITYTYPE_ZOMBIE);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(griditem, ENTITYTYPE_GRIDITEM);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(other, ENTITYTYPE_OTHERBOARDENTITIES);
	REFLECTION_ENUMBUILDER_END(BoardEntityTypeFlag);

	REFLECTION_ENUMBUILDER_BEGIN(BoardEntityHeight);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(ground, ENTITYHEIGHT_ON_GROUND);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(low, ENTITYHEIGHT_LOW);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(normal, ENTITYHEIGHT_NORMAL);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(tall, ENTITYHEIGHT_TALL);
	REFLECTION_ENUMBUILDER_END(BoardEntityHeight);

	REFLECTION_CLASSBUILDER_BEGIN(BoardEntityBuffInfo);
	REFLECTION_CLASSBUILDER_END(BoardEntityBuffInfo);

	REFLECTION_CLASSBUILDER_BEGIN(BoardEntity);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RealObject);

	REFLECTION_CLASSBUILDER_END(BoardEntity);
}

BoardEntity::BoardEntity()
{
	m_bTransparent = false;
	m_boardEntityFlags = BEFLAG_None;
	m_bIsIntro = false;
	m_bShowHealthBar = false;
	m_inPooyan = false;
	m_currentLevel = 1;
	m_isEntityHolo = false;
}

BoardEntity::BoardEntity(const BoardEntity& i_other) = default;

BoardEntity& BoardEntity::operator=(const BoardEntity& i_other) = default;

BoardEntity::~BoardEntity()
{
	if (m_componentRunner.IsValid())
	{
		m_componentRunner->Clear();
		m_componentRunner->Destroy();
		m_componentRunner.ClearId();
	}
}

// PlaceOnBoard
//	- Sets our initial location
//	- Calls virtual onPlaceOnBoard()
void BoardEntity::PlaceOnBoard(const SexyVector3& i_position)
{
	SetPosition(i_position);
	onPlaceOnBoard();
}

void BoardEntity::SetPosition(const SexyVector3& i_newPosition)
{
	m_position = i_newPosition;
	invalidateCollisionRect();
}

void BoardEntity::MovePosition(const SexyVector3& i_translation)
{
	SetPosition(GetPosition() + i_translation);
}

// Update
//	- ticks the fire / poison damage-over-time debuffs, then calls virtual
//	  onUpdate() and runs the attached components
void BoardEntity::Update()
{
	if (burnDebuff.buffID > 0)
	{
		if (PVZ_T() - burnDebuff.lastHitTime > 0.25f)
		{
			float dmg = burnDebuff.damage;
			DamageInfo damage((PVZ_T() - burnDebuff.lastHitTime) * dmg,
			                  DAMAGE_HAS_FIRE | DAMAGE_DOESNT_CAUSE_FLASH);
			burnDebuff.lastHitTime = PVZ_T();
			damage.Flags = DAMAGE_HAS_FIRE;
			if (burnDebuff.buffID == 1)
				damage.Flags |= DAMAGE_ASH_ON_DEATH;
			TakeDamage(damage);
		}

		if (burnDebuff.endedTime <= PVZ_T())
		{
			if (burnDebuff.lastHitTime < burnDebuff.endedTime)
			{
				DamageInfo damage((burnDebuff.endedTime - burnDebuff.lastHitTime) * burnDebuff.damage,
				                  DAMAGE_HAS_FIRE | DAMAGE_DOESNT_CAUSE_FLASH);
				burnDebuff.lastHitTime = PVZ_T();
				damage.Flags = DAMAGE_HAS_FIRE;
				if (burnDebuff.buffID == 1)
					damage.Flags |= DAMAGE_ASH_ON_DEATH;
				TakeDamage(damage);
			}
			burnDebuff.buffID = -1;
		}
	}

	if (poisonDebuff.buffID > 0)
	{
		if (poisonDebuff.buffID == 1 && PVZ_T() - poisonDebuff.lastHitTime > 0.25f)
		{
			float dmg = poisonDebuff.damage;
			DamageInfo damage((PVZ_T() - poisonDebuff.lastHitTime) * dmg,
			                  DAMAGE_HAS_FIRE | DAMAGE_DOESNT_CAUSE_FLASH);
			poisonDebuff.lastHitTime = PVZ_T();
			damage.Flags = DAMAGE_HAS_FIRE;
			TakeDamage(damage);
		}

		if (poisonDebuff.endedTime <= PVZ_T())
		{
			if (poisonDebuff.lastHitTime < poisonDebuff.endedTime)
			{
				DamageInfo damage((poisonDebuff.endedTime - poisonDebuff.lastHitTime) * poisonDebuff.damage,
				                  DAMAGE_HAS_FIRE | DAMAGE_DOESNT_CAUSE_FLASH);
				poisonDebuff.lastHitTime = PVZ_T();
				damage.Flags = DAMAGE_HAS_FIRE;
				TakeDamage(damage);
			}

			poisonDebuff.buffID = -1;
			if (Cast<GridItem>() && !Cast<GridItem>()->IsDestroyed())
				Cast<GridItem>()->EndCondition((GridItemConditions)7);
		}
	}

	SetHasPlayedImpactSound(false);
	onUpdate();
	if (m_componentRunner.IsValid())
		m_componentRunner->Update();
}

void BoardEntity::Draw(Sexy::Graphics* i_g)
{
	RealObject::Draw(i_g);
	if (m_componentRunner.IsValid())
		m_componentRunner->Draw(i_g);
}

void BoardEntity::TakeDamage(const DamageInfo& i_damage)
{
}

// Healing
void BoardEntity::HealByAmount(float amount)
{
	DamageInfo damage;
	damage.Amount = -amount;
	TakeDamage(damage);
}

void BoardEntity::LevelUp(int i_targetLevel)
{
	if (CanLevelUp(i_targetLevel))
	{
		SetCurrentLevel(i_targetLevel);
		onLevelUp(i_targetLevel);
	}
	else
	{
		onLevelUpFailed(i_targetLevel);
	}
}

void BoardEntity::onLevelUp(int i_targetLevel)
{
}

bool BoardEntity::CanLevelUp(int i_targetLevel)
{
	return true;
}

void BoardEntity::SetCurrentLevel(int i_level)
{
	m_currentLevel = i_level;
}

void BoardEntity::onLevelUpFailed(int i_targetLevel)
{
}

void BoardEntity::onInitialized()
{
	m_componentRunner = GameObject::Create<ComponentRunner>(PVZDB::TABLE_GAMEOBJECTS)->GetPtr();
}

void BoardEntity::onPostLoad()
{
	if (m_componentRunner.IsValid())
		m_componentRunner->OnPostLoad();
}

BoardEntityHeight BoardEntity::GetEntityHeight() const
{
	return ENTITYHEIGHT_NORMAL;
}

// OverrideProjectileCollision
//	- ignore the hit unless the projectile forces it or it comes from an
//	  opposing team
bool BoardEntity::OverrideProjectileCollision(Projectile* i_projectile)
{
	if (i_projectile->GetForceCollision())
		return false;
	return !IsOnOpposingTeam(i_projectile->GetTeamFlags());
}

bool BoardEntity::IntersectsGrid()
{
	Sexy::Rect gridRect = gLawnApp->m_board->GetGridBoundingRect();
	return gridRect.Intersects(calcCollisionRect());
}

bool BoardEntity::IsOnScreen()
{
	Sexy::Rect rect = GetCollisionRect();
	int left = rect.mX - 25;
	int top = rect.mY;
	int width = rect.mWidth + 50;
	int height = rect.mHeight;
	return (left <= 800 & left + width >= 0)
	    && (top <= 600 & top + height >= 0);
}

void BoardEntity::SetHoloParent(RtWeakPtr<BoardEntity> i_holoParent)
{
	m_holoEntityParent = i_holoParent;
}

/////////////// Collision rect ///////////////

const Sexy::Rect& BoardEntity::GetCollisionRect()
{
	if (!TestFlag(m_boardEntityFlags, BEFLAG_CollisionRectIsValid))
	{
		m_collisionRect = calcCollisionRect();
		SetFlag(m_boardEntityFlags, BEFLAG_CollisionRectIsValid, true);
	}
	return m_collisionRect;
}

/////////////// Grid position ///////////////

Sexy::Point BoardEntity::CalcGridPosition() const
{
	return Sexy::Point(CalcColumnPosition(), CalcRowPosition());
}

int BoardEntity::CalcRowPosition() const
{
	return BoardTransforms::BoardSpaceToGridYUnbounded(m_position.y);
}

int BoardEntity::CalcColumnPosition() const
{
	return BoardTransforms::BoardSpaceToGridXUnbounded(m_position.x);
}

bool BoardEntity::IsInRow(int i_row) const
{
	int row = CalcRowPosition();
	int bottomRow = 1 - GetGridExtents().mY + row;
	return bottomRow <= i_row && i_row <= row;
}

bool BoardEntity::IsInCol(int i_col) const
{
	int col = CalcColumnPosition();
	int leftCol = 1 - GetGridExtents().mX + col;
	return leftCol <= i_col && i_col <= col;
}

Sexy::Rect BoardEntity::CalcGridFootprint() const
{
	Sexy::Point grid = CalcGridPosition();
	Sexy::Point extents = GetGridExtents();
	return Sexy::Rect(grid.mX, 1 - extents.mY + grid.mY, extents.mX, extents.mY);
}

/////////////// Hit tracking ///////////////

bool BoardEntity::HasBeHitted(RtWeakPtr<Projectile> i_projectile)
{
	for (size_t i = 0; i < m_hitProjectiles.size(); i++)
	{
		if (m_hitProjectiles[i] == i_projectile)
			return true;
	}
	return false;
}

void BoardEntity::SetHitted(RtWeakPtr<Projectile> i_projectile)
{
	m_hitProjectiles.push_back(i_projectile);
}

/////////////// Sorting ///////////////

bool BoardEntity::BoardEntityLeftToRightSortFunc(BoardEntity* i_a, BoardEntity* i_b)
{
	Sexy::Rect rectA = i_a->GetCollisionRect();
	Sexy::Rect rectB = i_b->GetCollisionRect();
	return rectA.mX < rectB.mX;
}

bool BoardEntity::BoardEntityRightToLeftSortFunc(BoardEntity* i_a, BoardEntity* i_b)
{
	Sexy::Rect rectA = i_a->GetCollisionRect();
	Sexy::Rect rectB = i_b->GetCollisionRect();
	return rectA.mX > rectB.mX;
}

/////////////// Render order ///////////////

int BoardEntity::CalcRenderOrder() const
{
	return CalcRenderOrderFromPosition(m_position);
}

int BoardEntity::CalcRenderOrderFromPosition(const SexyVector3& i_position)
{
	int row = BoardTransforms::BoardSpaceToGridY(i_position.y);
	if (row == -1)
	{
		if (i_position.y > BoardTransforms::GridToBoardSpaceY(3))
			row = BoardConstants::NUMBER_OF_ROWS();
	}

	int baseY = (int)(BoardTransforms::GridToBoardSpaceYUnbounded(row) - 10.f);
	if (i_position.y < baseY)
		return Board::MakeRenderOrder(RENDER_LAYER_GRAVE_STONE, row, -(int)(baseY - i_position.y));
	return Board::MakeRenderOrder(RENDER_LAYER_PARTICLE, row, (int)(i_position.y - baseY) + 1000);
}
