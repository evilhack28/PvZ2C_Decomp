//
//  GridItem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-02.
//

#include "SexyAppFramework/Common.h"

#include "GridItem.h"
#include "GameEventMgr.h"
#include "Board.h"
#include "BoardTransforms.h"
#include "LawnApp.h"
#include "PoolDaylightStage.h"
#include "Effect_GroundEffects.h"
#include "StandaloneEffect.h"
#include "Artifact.h"

/////////////// GridItem ///////////////

EntityCondition& GridItem::ApplyCondition(GridItemConditions i_condition, pvztime_t i_duration)
{
	return m_conditionTracker.ApplyCondition(this, i_condition, i_duration);
}

void GridItem::EndCondition(GridItemConditions i_condition)
{
	m_conditionTracker.EndCondition(this, i_condition);
}

void GridItem::ClearConditions()
{
	m_conditionTracker.ClearConditions(this);
}

void GridItem::EndLossLife()
{
	m_bIsLossLife = false;
	m_tLossLifeTime = PVZ_EOT();
	m_iLossLifePerFrame = 0.0f;
}

void GridItem::NotifyHoloEnd()
{
	if (m_isEntityHolo)
		KillGridItem();
}

void GridItem::onDestroy()
{
	m_attachedEffects.Clear();
}

void GridItem::onGridItemPostInitialize()
{
}

void GridItem::onTakeDamage(const DamageInfo& i_damage)
{
}

AttachedEffectManager& GridItem::GetAttachedEffectManager()
{
	return m_attachedEffects;
}

AttachedBoardEntityManager& GridItem::GetAttachedBoardEntityManager()
{
	return m_attachedBoardEntities;
}

GridItemConditionTracker& GridItem::GetConditionTracker()
{
	return m_conditionTracker;
}

void GridItem::SetConditionTracker(GridItemConditions i_condition, float i_additionalValue)
{
	m_conditionTracker.SetAdditionalValue(i_condition, i_additionalValue);
}

void GridItem::SetGridLocation(Sexy::Point i_gridLocation, const bool i_recalculatePosition)
{
	SetGridLocationUnbounded(i_gridLocation, i_recalculatePosition);
}

void GridItem::SetGridLocation(int i_gridX, int i_gridY)
{
	SetGridLocation(Sexy::Point(i_gridX, i_gridY));
}

bool GridItem::isSameLocation(const Sexy::Point& i_atLocation)
{
	return i_atLocation == GetGridLocation();
}

void GridItem::onGatherPlantingRestrictions(const Sexy::Point& i_atLocation, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingErrors)
{
	if (isSameLocation(i_atLocation))
		GatherPlantingRestrictions(i_plantType, io_plantingErrors);
}

void GridItem::StartLossLife(pvztime_t duration, float percentOfMaxHealth)
{
	m_bIsLossLife = true;
	m_tLossLifeTime = PVZ_T() + duration;
	m_iLossLifePerFrame = GetMaxHitpoints() * PVZ_Dt() * percentOfMaxHealth;
}

/////////////// GridItemType ///////////////

GridItemType::GridItemType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemType);

void GridItemType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

		REFLECTION_CLASSBUILDER_FIELD(std::string, GridItemClass);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ResourceGroups);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<GridItemPropertySheet>, Properties);
	REFLECTION_CLASSBUILDER_END(GridItemType);
}

RT_CLASS_IMPLEMENT(GridItem);

void GridItem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_type);
		REFLECTION_CLASSBUILDER_FIELD(float, m_health);
		REFLECTION_CLASSBUILDER_FIELD(float, m_healthMax);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_gridLocation);
		REFLECTION_CLASSBUILDER_FIELD(AttachedEffectManager, m_attachedEffects);
		REFLECTION_CLASSBUILDER_FIELD(AttachedBoardEntityManager, m_attachedBoardEntities);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_tLossLifeTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bIsLossLife);
		REFLECTION_CLASSBUILDER_FIELD(float, m_iLossLifePerFrame);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isSleepping);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_sleepingEndTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isOnBoard);
	REFLECTION_CLASSBUILDER_END(GridItem);
}

bool GridItem::IsInvincible() const
{
	return m_bIsInvincible;
}

bool GridItem::HasCondition(GridItemConditions i_condition) const
{
	return m_conditionTracker.HasCondition(i_condition);
}

BoardEntityHeight GridItem::GetEntityHeight() const
{
	return GetProps()->Height;
}

void GridItem::GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons) const
{
	GetProps<GridItemPropertySheet>()->PlantingRestrictions.GatherPlantingRestrictions(i_plantType, io_plantingReasons);
}

GridItemPropsPtr GridItemType::GetPropsPtr() const
{
	return Properties;
}

const GridItemPropertySheet* GridItemType::GetProps() const
{
	return Properties.operator->();
}

void GridItemType::AddResourceRequirements(std::set<std::string>& io_resourceGroups) const
{
	io_resourceGroups.insert(ResourceGroups.begin(), ResourceGroups.end());
}

GridItem::GridItem()
{
	m_bIsLossLife = false;
	m_isSleepping = false;
	m_isOnBoard = true;
	m_health = 0.0f;
	m_healthMax = 0.0f;
	m_iLossLifePerFrame = 0.0f;
	m_tLossLifeTime = PVZ_EOT();
	m_sleepingEndTime = PVZ_EOT();
}

GridItem::~GridItem()
{
	m_attachedEffects.Clear();
	m_attachedBoardEntities.Clear();
}

void GridItem::TakeFatalDamage(const DamageInfo& i_damage)
{
	DamageInfo fatalDamage(i_damage);
	fatalDamage.Amount = GetHitpoints();
	fatalDamage.Flags |= DAMAGE_FATAL;
	TakeDamage(fatalDamage);
}

void GridItem::GridItemInitialize(GridItemTypePtr i_newType, int i_gridX, int i_gridY, int i_level)
{
	m_type = i_newType;
	SetGridLocation(i_gridX, i_gridY);
	m_health = 0.0f;
	m_healthMax = 0.0f;
	m_tLossLifeTime = PVZ_EOT();
	m_bIsLossLife = false;
	m_iLossLifePerFrame = 0.0f;
	m_isSleepping = false;
	m_sleepingEndTime = PVZ_EOT();
	SetCurrentLevel(i_level);
	onGridItemInitialize();
	onGridItemPostInitialize();
}

void GridItem::GridItemInitializeUnbounded(GridItemTypePtr i_type, int i_gridX, int i_gridY, int i_level)
{
	m_type = i_type;
	SetGridLocationUnbounded(Sexy::Point(i_gridX, i_gridY));
	m_health = 0.0f;
	m_healthMax = 0.0f;
	SetCurrentLevel(i_level);
	onGridItemInitialize();
	onGridItemPostInitialize();
}

void GridItem::GridItemDestroyedEntity(GridItem* i_gridItem)
{
	if (m_isEntityHolo)
	{
		if (m_holoEntityParent.IsValid())
		{
			if (m_holoEntityParent == i_gridItem->GetPtr())
				KillGridItem();
		}
	}
}

void GridItem::KillGridItem()
{
	gMessageRouter->Broadcast(Message::GridItemDestroyed, std::string(m_type->TypeName));
	gMessageRouter->Broadcast(Message::GridItemDestroyedEntity, this);
	onKilled();
	Destroy();
}

void GridItem::SetGridLocationUnbounded(Point i_gridLocation, const bool i_recalculatePosition)
{
	m_gridLocation = i_gridLocation;
	if (i_recalculatePosition)
	{
		SexyVector3 position = GetPosition();
		position.x = (float)BoardTransforms::GridToBoardSpaceXUnbounded(i_gridLocation.mX);
		position.y = (float)BoardTransforms::GridToBoardSpaceYUnbounded(i_gridLocation.mY);
		SetPosition(position);
		if (gLawnApp->m_board && gLawnApp->m_board->m_roofStage)
			SnapToGround(false);
	}
}

Sexy::Rect GridItem::calcCollisionRect()
{
	int x = BoardTransforms::GridToBoardSpaceXUnbounded(m_gridLocation.mX);
	int y = BoardTransforms::GridToBoardSpaceYUnbounded(m_gridLocation.mY);
	if (gLawnApp->m_board && gLawnApp->m_board->m_roofStage)
		y = (int)((float)y - gLawnApp->m_board->calculateRoofOffsetZ((float)x));
	int width = BoardConstants::GRIDSQUARE_WIDTH();
	int height = BoardConstants::GRIDSQUARE_HEIGHT();
	Sexy::Rect rect(x - width / 2, y - 25 - height / 2, width, height);
	const GridItemPropertySheet* props = GetProps<GridItemPropertySheet>();
	rect.mX += props->HitRectOffsetX;
	rect.mWidth += props->HitRectOffsetWidth;
	rect.mY += props->HitRectOffsetY;
	rect.mHeight += props->HitRectOffsetHeight;
	return rect;
}

void GridItem::NotifyEndCondition(GridItemConditions i_condition)
{
	if (!HasCondition(GCONDITION_Haunted))
		m_attachedEffects.Remove("haunted");

	if (i_condition == GCONDITION_Firecracker_pg02 || i_condition == GCONDITION_Firecracker_lv5_02)
		m_attachedEffects.Remove("firecracker");
}

static int __attribute__((noinline)) LevelPassThrough(int i_level) { return i_level; }

float GridItem::GetExtraHitPointsmodifier() const
{
	int idx = LevelPassThrough(m_currentLevel) - 1;
	if (idx >= 0 && (size_t)idx < GetProps()->GridItemLevelStats.size())
		return GetProps()->GridItemLevelStats[idx].HitPointsLevel;

	return 1.0f;
}

SexyVector3 GridItem::CalcPlantProjectileTargetLocation(float i_inTime)
{
	Sexy::Rect rect = GetCollisionRect();
	const SexyVector3& position = GetPosition();
	float z = (position.y - (float)rect.mY) - 0.333333f * (float)rect.mHeight;
	SexyVector3 result((float)rect.GetCenter().mX, position.y, z);
	return result;
}

namespace MiniGameCollectionUtils { int GetMiniGameCollectionType(); }
namespace BoardHelpers { float ApplyMiniGamePerkBuffValue(float i_value, int i_collectionType, int i_perkType, const PlantType* i_plantType = nullptr); }

float GridItemType::GetPacketCoolDown() const
{
	return Properties->PacketCooldown * std::max(1.0f - BoardHelpers::ApplyMiniGamePerkBuffValue(0.0f, MiniGameCollectionUtils::GetMiniGameCollectionType(), 1), 0.0f);
}

bool GridItem::IsDamageableByPlant(const Plant* i_plant) const
{
	const GridItemPropertySheet* props = GetProps().operator->();
	if (props->PlantsCanAttackList.empty())
		return IsDamageableByPlants();
	std::vector<std::string>::const_iterator end = props->PlantsCanAttackList.end();
	return end != std::find(props->PlantsCanAttackList.begin(), props->PlantsCanAttackList.end(),
	                        i_plant->GetType()->TypeName);
}

void GridItem::registerForEvents()
{
	gMessageRouter->Subscribe(Message::GatherPlantingRestrictions, Sexy::MakeDelegate(*this, &GridItem::onGatherPlantingRestrictions));
	gMessageRouter->Subscribe(Message::NotifyHoloEnd, Sexy::MakeDelegate(*this, &GridItem::NotifyHoloEnd));
	gMessageRouter->Subscribe(Message::GridItemDestroyedEntity, Sexy::MakeDelegate(*this, &GridItem::GridItemDestroyedEntity));
}

void GridItem::DrawCollisionInfo(Sexy::Graphics* g)
{
	g->SetColor(Sexy::Color(0, 0, 255));
	Sexy::Rect rect = GetCollisionRect();
	float origX = g->mScaleOrigX;
	float sx = (float)S(rect.mX);
	float scaleX = g->mScaleX;
	float origY = g->mScaleOrigY;
	rect.mX = (int)(floorf((sx - origX) * scaleX) + (double)origX);
	float sy = (float)S(rect.mY);
	float scaleY = g->mScaleY;
	rect.mY = (int)(floorf((sy - origY) * scaleY) + (double)origY);
	rect.mWidth = (int)((float)S(rect.mWidth) * scaleX);
	rect.mHeight = (int)((float)S(rect.mHeight) * scaleY);
	g->DrawRect(rect);
}

void GridItem::TakeCure(int value, bool playEffect)
{
	float h = (float)value + m_health;
	m_health = h < m_healthMax ? h : m_healthMax;
	if (playEffect)
	{
		AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate("cureup");
		effect.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_PEACH_CURE_UP"));
		effect.PlayAnimAndDestroy("peach_effect");
		effect.Attach(this, Sexy::SexyVector3(0.0f, 0.0f, 0.0f), 1);
	}
}

bool GridItem::MatchesAny(const GridItemTestFlag i_flags) const
{
	if (TestFlag(GT_ANY, i_flags))
		return true;
	if (!TestFlag(GT_OFF_SCREEN, i_flags))
	{
		if (TestFlag(GT_ON_SCREEN, i_flags) && !(GetPosition().x > 800.0f))
			return true;
	}
	else if (GetPosition().x > 800.0f || TestFlag(GT_ON_SCREEN, i_flags))
		return true;
	if (TestFlag(GT_IS_DAMAGABLE, i_flags) && IsDamageable())
		return true;
	if (TestFlag(GT_IS_NOT_DAMAGABLE, i_flags) && !IsDamageable())
		return true;
	if (TestFlag(GT_IS_DAMAGABLE_BY_PLANTS, i_flags) && IsDamageableByPlants())
		return true;
	if (TestFlag(GT_IS_NOT_DAMAGABLE_BY_PLANTS, i_flags))
		return !IsDamageableByPlants();
	return false;
}

void GridItem::SetInvincible(bool is_invincible, bool is_needEffect, pvztime_t i_time)
{
	m_bIsInvincible = is_invincible;

	if (is_invincible)
	{
		m_InvincibleTime = PVZ_T() + i_time;

		if (is_needEffect)
		{
			AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate("cureshield");
			effect.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_PEACH_SHIELD"));
			effect.PlayAnimLooped("peach_shield");
			effect.Attach(this, Sexy::SexyVector3(0.0f, 0.0f, 0.0f), 1);
		}
	}
}

bool GridItem::MatchesAny(const GridItemTestFlag i_flags, const BoardEntity* i_entity) const
{
	if (TestFlag(GT_IS_TARGETABLE_BY_ENTITY, i_flags) && i_entity != NULL && CanBeTargetedBy(i_entity))
		return true;
	if (TestFlag(GT_IS_NOT_TARGETABLE_BY_ENTITY, i_flags) && i_entity != NULL && !CanBeTargetedBy(i_entity))
		return true;
	if (TestFlag(GT_OPPOSING_TEAM, i_flags) && i_entity != NULL && IsOnOpposingTeam(i_entity))
		return true;
	if (TestFlag(GT_SAME_TEAM, i_flags) && i_entity != NULL && !IsOnOpposingTeam(i_entity))
		return true;
	if (TestFlag(GT_IN_ROW, i_flags) && i_entity != NULL && IsInRow(i_entity->CalcRowPosition()))
		return true;
	if (TestFlag(GT_NOT_IN_ROW, i_flags) && i_entity != NULL && !IsInRow(i_entity->CalcRowPosition()))
		return true;
	if (TestFlag(GT_IN_COL, i_flags) && i_entity != NULL && IsInCol(i_entity->CalcColumnPosition()))
		return true;
	if (TestFlag(GT_NOT_IN_COL, i_flags) && i_entity != NULL && !IsInCol(i_entity->CalcColumnPosition()))
		return true;
	return MatchesAny(i_flags);
}

bool GridItem::CanBeTargetedBy(const BoardEntity* i_entity) const
{
	return true;
}

void GridItem::TakeDamage(const DamageInfo& i_damage)
{
	if (IsInvincible() || !IsDamageable())
		return;

	if (i_damage.Instigator != NULL)
	{
		if (!IsOnOpposingTeam(i_damage.Instigator))
			return;
		if (i_damage.Instigator->IsA<Plant>() && (!IsDamageableByPlants() || !IsDamageableByPlant(i_damage.Instigator->Cast<Plant>())))
			return;
	}
	for (size_t i = 0; i < i_damage.GridItem_Conditions.size(); i++)
		ApplyCondition(i_damage.GridItem_Conditions[i].first, i_damage.GridItem_Conditions[i].second);

	float damage;
	if (TestFlag(i_damage.Flags, DAMAGE_FATAL))
	{
		damage = m_health;
		m_health = 0.0f;
	}
	else
	{
		damage = i_damage.Amount;
		m_health -= damage;
	}

	DamageInfo info(i_damage);
	info.Amount = damage;
	onTakeDamage(info);

	if (m_health <= 0.0f)
	{
		if (GetPtr())
			KillGridItem();
	}
}

void GridItem::onUpdate()
{
	if (ShouldClipWithWater())
	{
		SnapToGround(false);
		SetUseGroundClipRect(true);
	}

	if (PVZ_T() > m_InvincibleTime)
	{
		m_bIsInvincible = false;
		m_InvincibleTime = PVZ_EOT();
		m_attachedEffects.Remove("cureshield");
	}

	m_conditionTracker.Update(this);
	m_attachedEffects.Update(PVZ_Dt());

	if (m_bIsLossLife)
	{
		DamageInfo info;
		info.Amount = m_iLossLifePerFrame;
		TakeDamage(info);
	}

	if (PVZ_T() > m_tLossLifeTime)
		EndLossLife();

	if (IsSleepping() && m_sleepingEndTime < PVZ_T())
		SetIsSleepping(false, -1.0f);
}

void GridItem::SetIsSleepping(bool i_isSleepping, float durationTime)
{
	m_isSleepping = i_isSleepping;
	m_sleepingEndTime = PVZ_EOT();

	if (m_attachedEffects.Contains("sleepping"))
		m_attachedEffects.Remove("sleepping");

	if (m_isSleepping)
	{
		if (!m_attachedEffects.Contains("sleepping"))
		{
			AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate("sleepping");
			effect.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_SLEEPPING_PLANT_EFFECT"));
			effect.PlayAnimLooped("animation", SELECT_RANDOM_INDEX);
			effect.Attach(this, Sexy::SexyVector3(0.0f, 0.0f, 0.0f), 1);
		}
		if (durationTime > 0.0f)
			m_sleepingEndTime = PVZ_T() + durationTime;
	}
}

void GridItem::onGridItemInitialize()
{
	if (!ShouldClipWithWater())
		return;

	const SexyVector3& position = GetPosition();
	BoardRegion* region = gLawnApp->m_board->FindRegionWithFlags(position, BOARDREGION_ShallowWater);
	PoolDaylightStage* poolStage = NULL;
	if (gLawnApp->m_board->GetStage() != NULL)
		poolStage = gLawnApp->m_board->GetStage()->Cast<PoolDaylightStage>();

	if (region == NULL)
		return;

	RtWeakPtr<Effect_PopAnim> effect;
	effect = StandaloneEffect::CreateEffect<Effect_GroundEffectTide>()->GetPtr();
	CachedResourcePtr<PopAnim> anim("POPANIM_BACKGROUNDS_WATER_ZOMBIE_RIPPLE");
	effect->CreatePopAnimRig(anim, NULL);
	const SexyVector3& offset = SexyVector3(-100.0f, -78.0f, 0.0f);
	effect->SetAttached(this, offset, 1);
	effect->PlayLoopingAnimation("ripple", PVZ_EOT(), SELECT_EXACT);
	effect->GetPopAnimRig()->RandomizeCurrentAnimFrame();

	if (poolStage != NULL && BoardTransforms::BoardSpaceToGridYUnbounded(position.y) == 3)
	{
		Sexy::Rect clipRect;
		clipRect.mX = 0;
		clipRect.mY = 0;
		clipRect.mWidth = S(1000);
		clipRect.mHeight = S(460);
		effect->SetClipRect(clipRect);
	}
}

void GridItem::NotifyApplyCondition(GridItemConditions i_condition)
{
	switch (i_condition)
	{
	case GCONDITION_Haunted:
		if (!m_attachedEffects.Contains("haunted"))
		{
			AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate("haunted");
			effect.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_GHOSTPEPPER_ATTACK_GHOSTS"));
			effect.PlayAnimLooped("animation", SELECT_RANDOM_INDEX);
			effect.Attach(this, Sexy::SexyVector3(0.0f, 0.0f, 30.0f), 1);
			effect.GetEffect()->SetScale(0.5f, 0.5f);
		}
		break;
	case GCONDITION_Firecracker_pg02:
	case GCONDITION_Firecracker_lv5_02:
		if (!m_attachedEffects.Contains("firecracker"))
		{
			AttachedEffect& effect = (AttachedEffect&)m_attachedEffects.FindOrCreate("firecracker");
			effect.InitializeWithAnimation(GetPAMByName("POPANIM_EFFECTS_FIRECRACKERFLOWER_PROJECTILE"));
			effect.PlayAnimLooped(i_condition == GCONDITION_Firecracker_pg02 ? std::string("pg02") : std::string("lv5_02"), SELECT_RANDOM_INDEX);
			effect.Attach(this, Sexy::SexyVector3(0.0f, 0.0f, 30.0f), 1);
			effect.GetEffect()->SetScale(1.0f, 1.0f);
		}
		break;
	default:
		break;
	}
}

/////////////// GetProps instances ///////////////

template const GridItemAcidProps* GridItem::GetProps<GridItemAcidProps>() const;
template const GridItemMeteorProps* GridItem::GetProps<GridItemMeteorProps>() const;
template const GridItemPropertySheet* GridItem::GetProps<GridItemPropertySheet>() const;
template const GridItemAnimationProps* GridItem::GetProps<GridItemAnimationProps>() const;
template const GridItemArtifactTornadoProps* GridItem::GetProps<GridItemArtifactTornadoProps>() const;
template const GridItemBreakableTargetProps* GridItem::GetProps<GridItemBreakableTargetProps>() const;
template const GridItemRailcartPropertySheet* GridItem::GetProps<GridItemRailcartPropertySheet>() const;
template const GridItemArtifactSilverkeyGateProps* GridItem::GetProps<GridItemArtifactSilverkeyGateProps>() const;
