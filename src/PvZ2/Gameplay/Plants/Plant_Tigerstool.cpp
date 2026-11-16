//
//  Plant_Tigerstool.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Tigerstool.h"
#include "PlantAnimRig_Tigerstool.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "PlantNewAvatarCommon.h"
#include "Plant.h"
#include "PlantPropertySheet.h"
#include "Board.h"
#include "LawnApp.h"
#include "Effect_PopAnim.h"
#include "StandaloneEffect.h"
#include "EntityFinder.h"
#include "Zombie.h"
#include "GridItem.h"
#include "DamageInfo.h"
#include "ResourceHelpers.h"
#include <algorithm>

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTigerstool);

void PlantTigerstool::UpdatePlantfood()
{
}

bool PlantTigerstool::CanApplyPlantfood()
{
	return true;
}

void PlantTigerstool::onPFFinishedCallback(class StandaloneEffect* i_effect)
{
}

void PlantTigerstool::ApplyPlantfood()
{
	PlantFramework::ApplyPlantfood();
	m_plant->m_state = BONKSTATE_PLANTFOOD;
}

void PlantTigerstool::CancelPlantfood()
{
	PlantFramework::CancelPlantfood();
	m_plant->m_state = BONKSTATE_IDLE;
}

bool PlantTigerstool::CanStunZombies()
{
	return m_plant->CalcColumnPosition() < BoardConstants::NUMBER_OF_COLUMNS() - 1;
}

void PlantTigerstool::StunZombies()
{
	int col = m_plant->CalcColumnPosition();
	int row = m_plant->CalcRowPosition();
	gLawnApp->m_board->GetGameSubSystem<TigerstoolSubsystem>()->StunZombies(col + 1, row);
}

void PlantTigerstool::DoSpecialForAvatarNormal()
{
	m_bKoHit = Rand(1.0f) < 0.037f;
}

int PlantTigerstool::CalcRenderOrder()
{
	if (IsInPlantFoodState())
		return Board::MakeRenderOrder(RENDER_LAYER_PLANT_ABOVE_ZOMBIES, m_plant->m_row + 1, 2);

	return PlantFramework::CalcRenderOrder();
}

Sexy::Rect PlantTigerstool::GetPlantAttackRect(PlantWeapon i_plantWeapon)
{
	Sexy::Rect rect = PlantFramework::GetPlantAttackRect(i_plantWeapon);
	if (i_plantWeapon == WEAPON_PRIMARY)
	{
		rect.mWidth = rect.mWidth * 0.5f;
		if (!m_searchingLeft)
			rect.mX += rect.mWidth;
	}
	return rect;
}

ZombiePtr PlantTigerstool::GetZombieTarget(bool i_left)
{
	ZombiePtr target = nullptr;
	m_searchingLeft = i_left;
	target = FindTargetZombie(WEAPON_PRIMARY);
	return target;
}

void PlantTigerstool::UpdateActions()
{
	switch (m_plant->m_state)
	{
	case BONKSTATE_IDLE:
		is_attack = false;
		PF_hurt = false;
		if (!gLawnApp->m_board->IsGameplayEnded())
			FindTargetsAndPlayAttackAnim();
		break;
	case BONKSTATE_ATTACKRIGHT:
	case BONKSTATE_ATTACKLEFT:
		bool isPlaying = m_plant->GetAnimRig()->IsPlayingAnything();
		if (!isPlaying)
		{
			m_time = PVZ_T();
			can_attack = isPlaying;
			m_plant->GetAnimRig()->PlayIdleLooped();
			m_plant->m_state = BONKSTATE_IDLE;
		}
		break;
	}
}

int PlantTigerstool::myrandom()
{
	std::vector<int> numbers;
	for (int i = 1; i <= 100; i++)
		numbers.push_back(i);
	std::random_shuffle(numbers.begin(), numbers.end());
	return *numbers.begin();
}

bool PlantTigerstool::WouldKillTarget(ZombiePtr i_targetZombie)
{
	float damage;
	{
		PlantPropsPtr props = m_plant->GetProps();
		const PlantAction& action = props->Actions[0];
		damage = (int)(m_plant->GetExtraNormalDamage() * m_plant->GetExtraSpecialDamage() * (float)action.Damage * m_plant->GetExtraDPSmodifier() * m_plant->GetAwakenDamage());
	}
	return i_targetZombie->GetHitpointsUntilBleedout() <= damage;
}

bool PlantTigerstool::WouldKillTarget(GridItem* i_targetGridItem)
{
	int damage;
	{
		PlantPropsPtr props = m_plant->GetProps();
		const PlantAction& action = props->Actions[0];
		damage = (int)(m_plant->GetExtraNormalDamage() * m_plant->GetExtraSpecialDamage() * (float)action.Damage * m_plant->GetExtraDPSmodifier() * m_plant->GetAwakenDamage());
	}
	int hitpoints = (int)i_targetGridItem->GetHitpoints();
	return damage >= hitpoints;
}

GridItem* PlantTigerstool::GetGridItemTarget(bool i_left)
{
	int column = i_left ? m_plant->m_column - 1 : m_plant->m_column + 1;
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesAtGridSquare(entities, ENTITYTYPE_GRIDITEM, column, m_plant->m_row);
	if (entities.size() == 0)
		EntityFinder::GetEntitiesAtGridSquare(entities, ENTITYTYPE_GRIDITEM, m_plant->m_column, m_plant->m_row);
	for (size_t i = 0; i < entities.size(); i++)
	{
		GridItem* gridItem = entities[i]->CastChecked<GridItem>();
		if (gridItem->IsDamageableByPlants() && gridItem->IsDamageableByPlant(m_plant))
			return gridItem;
	}
	return nullptr;
}

void PlantTigerstool::Initialize()
{
	PlantFramework::Initialize();
	m_searchingLeft = false;
	m_plant->m_state = BONKSTATE_IDLE;
	m_iAttackCount = 0;
	m_bAttackUppercut = false;
	m_bDoAvatarPull = false;
	m_bKoHit = false;
	m_UppercutCount = 0;
	m_IsSupercut = false;
	m_attackIntervalRate = 1.0f;
	int level = m_plant->GetCurrentLevel();
	if (level == 2)
	{
		m_count = 5;
		t_stunned += 0.25f;
	}
	else if (level > 2)
	{
		m_count = 6;
		t_stunned += 0.5f;
	}
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	int avatarId = PlantNewAvatarMapper::GetInstance().GetIdForName("tigerstool_new_avatar_1");
	if (profile->IsPlantNewAvatarUnLocked(avatarId))
	{
		NewAvatarGeneralSkillBoost* boost = nullptr;
		{
			PlantNewAvatarPtr info = NewAvatar::GetAvatarInfoByAvatarId(avatarId);
			if (info)
				boost = NewAvatar::GetAvatarInfoByAvatarId(avatarId)->Cast<NewAvatarGeneralSkillBoost>();
		}
		if (boost)
			m_attackIntervalRate = 1.0f - boost->BoostRate;
	}
}

bool PlantTigerstool::MayUppercutTarget(GridItem* i_targetGridItem)
{
	return WouldKillTarget(i_targetGridItem);
}

void PlantTigerstool::DoSpecial(int i_extraParam)
{
	if (lethal_t == 0.0f || lethalInterval < PVZ_T() - lethal_t)
		m_isLethal = true;

	if (IsInPlantFoodState())
	{
		if (!PF_hurt)
		{
			if (!is_attack)
			{
				PF_num = 0;
				is_attack = true;
				const SexyVector3& position = m_plant->GetPosition();
				float effectX = position.x - m_plant->GetProps()->ArtCenter.x;
				float effectY = (position.y - position.z) - m_plant->GetProps()->ArtCenter.y;
				Board::MakeRenderOrder(RENDER_LAYER_PARTICLE, m_plant->m_row, 0);
				Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
				effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_TIGERSTOOL_5"));
				effect->SetBoardSpaceOrigin(SexyVector3((float)(int)effectX, (float)(int)effectY, 0.0f), -1);
				if (m_plant->GetAvatarEnable())
					effect->SetCompletionCallback(OnStandaloneEffectCompleted(m_plant->GetPtr(), "onStandaloneEffectFinishedCallback"));
				effect->SetRenderLayerOverride(799999);
				std::vector<int> numbers;
				for (int i = 1; i <= 100; i++)
					numbers.push_back(i);
				std::random_shuffle(numbers.begin(), numbers.end());
				m_plant->PlayPositionalSound(numbers.begin()[0] == 1 ? "T2" : "T1", 0.0f);
				effect->PlaySingleAnimation("c1");
			}
			else if (PF_num != 0)
			{
				is_attack = false;
				PF_hurt = true;
				const SexyVector3& position = m_plant->GetPosition();
				float effectX = position.x - m_plant->GetProps()->ArtCenter.x;
				float effectY = (position.y - position.z) - m_plant->GetProps()->ArtCenter.y;
				Board::MakeRenderOrder(RENDER_LAYER_PARTICLE, m_plant->m_row, 0);
				Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
				effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_TIGERSTOOL_3"));
				effect->SetBoardSpaceOrigin(SexyVector3((float)((int)effectX + 120), (float)((int)effectY - 10), 0.0f), -1);
				effect->SetRenderLayerOverride(799999);
				effect->PlaySingleAnimation("c3");
			}
			else
			{
				PF_num = 1;
				Sexy::Rect searchRect(m_plant->m_column + 1, m_plant->m_row - 1, 3, 3);
				std::vector<BoardEntity*> entities;
				EntityFinder::GetEntitiesInGridSquares(entities, ENTITYTYPE_ZOMBIE | ENTITYTYPE_GRIDITEM, searchRect);
				float damage = (int)((float)(m_plant->GetProps()->Actions[0].Damage * 30) * (m_plant->GetExtraNormalDamage() * m_plant->GetExtraSpecialDamage()) * m_plant->GetExtraDPSmodifier() * m_plant->GetAwakenDamage());
				for (std::vector<BoardEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
				{
					BoardEntity* entity = *it;
					if (entity->IsOnOpposingTeam(TEAM_PLANTS))
					{
						Zombie* zombie = entity->Cast<Zombie>();
						if (zombie)
						{
							zombie->TakeDamage(DamageInfo(damage));
						}
						else
						{
							GridItem* gridItem = entity->Cast<GridItem>();
							if (gridItem && gridItem->CollidesWithType(COLLIDE_GRIDITEMS) && gridItem->IsDamageableByPlants())
								gridItem->TakeDamage(DamageInfo(damage));
						}
					}
				}
			}
		}
		else
		{
			if (!m_plant->GetAvatarEnable())
				return;
			Sexy::Rect searchRect(m_plant->m_column + 1, m_plant->m_row - 1, 3, 3);
			std::vector<BoardEntity*> entities;
			EntityFinder::GetEntitiesInGridSquares(entities, ENTITYTYPE_ZOMBIE | ENTITYTYPE_GRIDITEM, searchRect);
			float damage = (int)((float)m_plant->GetProps()->Actions[0].Damage * 7.5f * m_plant->GetExtraNormalDamage() * m_plant->GetExtraSpecialDamage() * m_plant->GetExtraDPSmodifier() * m_plant->GetAwakenDamage());
			for (std::vector<BoardEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			{
				BoardEntity* entity = *it;
				if (entity->IsOnOpposingTeam(TEAM_PLANTS))
				{
					Zombie* zombie = entity->Cast<Zombie>();
					if (zombie)
					{
						zombie->TakeDamage(DamageInfo(damage));
					}
					else
					{
						GridItem* gridItem = entity->Cast<GridItem>();
						if (gridItem && gridItem->CollidesWithType(COLLIDE_GRIDITEMS) && gridItem->IsDamageableByPlants())
							gridItem->TakeDamage(DamageInfo(damage));
					}
				}
			}
		}
	}
	else
	{
		c_num = 0;
		b_num = -1;
		const SexyVector3& position = m_plant->GetPosition();
		float effectX = position.x - m_plant->GetProps()->ArtCenter.x;
		float effectY = (position.y - position.z) - m_plant->GetProps()->ArtCenter.y;
		Board::MakeRenderOrder(RENDER_LAYER_PARTICLE, m_plant->m_row, 0);
		Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
		effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_TIGERSTOOL_6"));
		effect->SetBoardSpaceOrigin(SexyVector3((float)(int)effectX, (float)(int)effectY, 0.0f), -1);
		effect->SetRenderLayerOverride(799999);
		effect->SetCompletionCallback(OnStandaloneEffectCompleted(m_plant->GetPtr(), "onStandaloneEffectFinishedCallback"));
		effect->PlaySingleAnimation("c1");
		m_plant->PlayPositionalSound("T1", 0.0f);

		ZombiePtr target = GetZombieTarget(false);
		Sexy::Rect searchRect(m_plant->m_column, m_plant->m_row - 1, 3, 3);
		std::vector<BoardEntity*> entities;
		EntityFinder::GetEntitiesInGridSquares(entities, ENTITYTYPE_ZOMBIE, searchRect);
		for (std::vector<BoardEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			BoardEntity* entity = *it;
			if (entity->IsOnOpposingTeam(TEAM_PLANTS))
			{
				Zombie* zombie = entity->Cast<Zombie>();
				if (zombie)
				{
					zombie->ApplyCondition(ZombieConditionsStruct(ZCONDITION_Stunned, t_stunned, m_plant->GetPtr()));
				}
				else
				{
					GridItem* gridItem = entity->Cast<GridItem>();
					if (gridItem && gridItem->CollidesWithType(COLLIDE_GRIDITEMS))
						gridItem->IsDamageableByPlants();
				}
			}
		}
	}
}

bool PlantTigerstool::CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon)
{
	return !i_zombie->IsBleedingOut();
}

void PlantTigerstool::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTigerstool);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onPFFinishedCallback, onPFFinishedCallback, StandaloneEffect*);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_searchingLeft);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_plantfoodDamageEndTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_iAttackCount);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bAttackUppercut);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bDoAvatarPull);
		REFLECTION_CLASSBUILDER_FIELD(int, m_UppercutCount);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_IsSupercut);
	REFLECTION_CLASSBUILDER_END(PlantTigerstool);

}
