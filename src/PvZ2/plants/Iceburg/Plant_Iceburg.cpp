#include "Plant_Iceburg.h"
#include "PlantAnimRig_Iceburg.h"
#include "PVZ1WhackZombieModule.h"
#include "Effect_ScreenFade.h"
#include "AudioMgr.h"
#include "StateMachineTableBuilder.h"
#include "EntityFinder.h"
#include "GridItemFlame.h"
#include "ZombieHanabi.h"
#include "GridItemFireCracker.h"
#include "GridItemSummerFireworks.h"
#include "ZombieZombossMech_Steam.h"
#include "ZombieZombossMech_PVZ1_Robot.h"
#include "GameEventMgr.h"
#include "BoardConstants.h"
#include "Achievement.h"
#include "PVZDB.h"
#include "Projectile.h"
#include <algorithm>
#include "BoardTransforms.h"
#include "ResourceHelpers.h"
#include "Board.h"
#include "LawnApp.h"
#include "TodCommon.h"

RT_CLASS_IMPLEMENT(PlantTypeIceburg);
RT_CLASS_IMPLEMENT(PlantIceburg);

void PlantIceburg::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantIceburg);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_exploded);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextLaunchTime);
		REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_INSTANCE(int32, LaunchState, getLaunchStateSerialization, setLaunchStateSerialization);
		REFLECTION_CLASSBUILDER_FIELD(int, m_launchNumbers);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<BoardEntityPtr>, m_validTargets);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<BoardEntityPtr>, m_hittedTargets);

	REFLECTION_CLASSBUILDER_END(PlantIceburg);

	STATEMACHINE_BUILDER_BEGIN(LaunchState);
		STATEMACHINE_BUILDER_ADDSTATE(INIT, LaunchState_INIT);
		STATEMACHINE_BUILDER_ADDSTATE(LAUNCHING, LaunchState_LAUNCHING);
		STATEMACHINE_BUILDER_ADDSTATE(END, LaunchState_END);
	STATEMACHINE_BUILDER_END();
}

void PlantTypeIceburg::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTypeIceburg);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantType);

	REFLECTION_CLASSBUILDER_END(PlantTypeIceburg);
}

int PlantTypeIceburg::GetCost(PlantAvatarType i_avatarType) const
{
	int cost = PlantType::GetCost(i_avatarType);
	if (WhackZombieUtils::IsPlayingWhackZombie())
	{
		return 75;
	}
	return cost;
}

void PlantIceburg::Initialize()
{
	PlantFramework::Initialize();

	m_nextLaunchTime = PVZ_EOT();
	m_exploded = false;
	m_launchNumbers = 0;

	if (m_plant->GetCurrentLevel() > 1)
	{
		m_plant->m_isShooter = true;
	}

	setState(LaunchState_INIT);
}

void PlantIceburg::PostInitialize()
{
	if (WhackZombieUtils::IsPlayingWhackZombie())
	{
		ApplyPlantfood();
	}
}

void PlantIceburg::ApplyPlantfood()
{
	PlantFramework::ApplyPlantfood();

	m_plant->m_state = STATE_PLANTFOOD;
	m_plant->PlayPositionalSound("Play_IcebergLettuce_Freeze_PF", 0.0f);

	Effect_ScreenFade* screenFade = Effect_ScreenFade::Create();
	static const Color iceColor(70, 180, 250, 100);
	static const Color whiteColor(255, 255, 255, 200);
	screenFade->AddFade(FadeOut, iceColor, 0.7f, CURVE_EASE_IN);
	screenFade->AddFade(FadeIn, whiteColor, 1.0f, CURVE_EASE_IN);
}

void PlantIceburg::CancelPlantfood()
{
	PlantFramework::CancelPlantfood();

	m_plant->m_state = STATE_IDLE;
	if (m_plant->GetAvatarEnable())
	{
		setState(LaunchState_LAUNCHING);
	}

	if (WhackZombieUtils::IsPlayingWhackZombie())
	{
		m_plant->KillPlant(true, false, DAMAGE_SUICIDE);
	}
}

bool PlantIceburg::FindTargetAndFire(PlantWeapon i_plantWeapon)
{
	if (m_plant->GetCurrentLevel() > 1 &&
	    (m_plant->m_state == STATE_SHOOT || m_plant->m_state == STATE_IDLE))
	{
		if (PlantFramework::FindTargetAndFire(WEAPON_AVATAR))
		{
			float rate = m_plant->GetExtraAtkRate();
			m_plant->m_launchInterval.SetRange(
				rate * m_plant->GetProps()->Actions[WEAPON_AVATAR].CooldownTimeMin,
				rate * m_plant->GetProps()->Actions[WEAPON_AVATAR].CooldownTimeMax);
			m_plant->m_state = STATE_SHOOT;
			return true;
		}
	}

	return false;
}

Projectile* PlantIceburg::Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon)
{
	if (m_plant->GetCurrentLevel() > 1)
	{
		m_plant->m_currentPlantActionIdx = 2;
		return PlantFramework::Fire(i_targetZombie, i_row, i_plantWeapon);
	}
	return NULL;
}

bool PlantIceburg::CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon)
{
	return !i_zombie->IsBleedingOut();
}

bool PlantIceburg::HasShadow()
{
	return !m_exploded;
}

Sexy::Rect PlantIceburg::GetPlantAttackGridRect(PlantWeapon i_plantWeapon)
{
	Sexy::Rect rect = PlantFramework::GetPlantAttackGridRect(i_plantWeapon);

	const PlantPropertySheet* props = m_plant->GetProps();
	if ((size_t)i_plantWeapon < props->Actions.size())
	{
		const PlantAction& action = props->Actions[i_plantWeapon];
		if (action.Type == PLANT_ACTION_PROJECTILE && action.TriggerType == PLANT_ACTION_TRIGGER_GRID_RECT)
		{
			if (m_plant->GetCurrentLevel() > 2)
			{
				rect.mWidth += 2;
			}
		}
	}

	return rect;
}

Sexy::Rect PlantIceburg::GetPlantAttackRect(PlantWeapon i_plantWeapon)
{
	Sexy::Rect rect = PlantFramework::GetPlantAttackRect(i_plantWeapon);

	const PlantPropertySheet* props = m_plant->GetProps();
	if ((size_t)i_plantWeapon < props->Actions.size())
	{
		const PlantAction& action = props->Actions[i_plantWeapon];
		if (action.Type == PLANT_ACTION_PROJECTILE && action.TriggerType == PLANT_ACTION_TRIGGER_GRID_RECT)
		{
			if (m_plant->GetCurrentLevel() > 2)
			{
				rect.mWidth += 2 * BoardConstants::GRIDSQUARE_WIDTH();
			}
		}
	}

	return rect;
}

bool PlantIceburg::CanApplyPlantfood()
{
	return m_plant->m_state == STATE_IDLE || m_plant->m_state == STATE_SHOOT;
}

CollisionTypeFlags PlantIceburg::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return COLLIDE_GROUND_ZOMBIES | COLLIDE_DYING_ZOMBIES;
}

bool PlantIceburg::TryBlockZombossRush(Zombie* i_zomboss)
{
	return false;
}

void PlantIceburg::Idle()
{
	m_plant->m_state = STATE_IDLE;
	m_plant->GetAnimRig()->PlayIdleLooped();
}

template <typename T>
static T* FindGridItemAt(int i_column, int i_row)
{
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesAtGridSquare(entities, (BoardEntityTypeFlag)4, i_column, i_row);
	for (std::vector<BoardEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		T* gridItem = (*it)->Cast<T>();
		if (gridItem)
		{
			return gridItem;
		}
	}
	return NULL;
}

static SexyVector2 GetSnowballTarget(SexyVector3 i_position)
{
	return SexyVector2(i_position.x, i_position.y - i_position.z);
}

void PlantIceburg::FindValidZombiesAndAttack()
{
	if (m_launchNumbers <= 0)
	{
		setState(LaunchState_END);
		return;
	}

	m_launchNumbers--;

	std::vector<BoardEntity*> entities;
	m_validTargets.clear();

	EntityFinder::GetEntitiesInGridSquares(entities, (BoardEntityTypeFlag)2,
	                                       Sexy::Rect(0, 0, gLawnApp->m_board->m_gridSizeX + 1,
	                                                  gLawnApp->m_board->m_gridSizeY));

	for (size_t i = 0; i < entities.size(); i++)
	{
		Zombie* zombie = entities[i]->Cast<Zombie>();
		if (zombie && !zombie->IsDying() && zombie->IsOnOpposingTeam(m_plant))
		{
			const SexyVector3& position = zombie->GetPosition();
			float x = position.x;
			float y = position.y;
			int column = BoardTransforms::BoardSpaceToGridX(x);
			int row = BoardTransforms::BoardSpaceToGridY(y);
			(void)column;
			(void)row;

			std::vector<BoardEntityPtr>::iterator found =
			    std::find(m_hittedTargets.begin(), m_hittedTargets.end(),
			              entities[i]->GetPtr());
			if (found != m_hittedTargets.end())
			{
				continue;
			}

			m_validTargets.push_back(entities[i]->GetPtr());
		}
	}

	if (m_validTargets.size() != 0)
	{
		BoardEntity* target = m_validTargets[Rand((int)m_validTargets.size())];
		LaunchSnowball(GetSnowballTarget(target->m_position));
		m_hittedTargets.push_back(target->GetPtr());
	}
}

void PlantIceburg::LaunchSnowball(const SexyVector2& i_target)
{
	int row = BoardTransforms::BoardSpaceToGridYKeepOnBoard(i_target.y);
	int boardY = BoardTransforms::GridToBoardSpaceY(row);
	int height = BoardConstants::GRIDSQUARE_HEIGHT();
	float offsetX = RandRangeFloat(-80.0f, 80.0f);

	ProjectilePropertySheetPtr props(Sexy::RtId(Sexy::RtName(L"SnowballDefault"),
	                                           Sexy::RtName(L"ProjectileTypes")));
	float y = (float)(int)(boardY - height * 0.4f);
	Projectile* projectile = gLawnApp->m_board->AddProjectile(offsetX - 100.0f, y, 0.0f,
	                                                          props, m_plant, 0);

	const char* images[3] =
	{
		"IMAGE_EFFECTS_POWER_UP_ICE_PROJECTILE1",
		"IMAGE_EFFECTS_POWER_UP_ICE_PROJECTILE2",
		"IMAGE_EFFECTS_POWER_UP_ICE_PROJECTILE3",
	};
	projectile->SetRenderImage(GetImageByName(images[Rand() % (sizeof(images) / sizeof(images[0]))]));

	float apexHeight = RandRangeFloat(0.0f, 150.0f);
	float timeToHit = RandRangeFloat(0.0f, 0.1f);
	ProjectileHelpers::LaunchAt(projectile, SexyVector3(i_target.x, y, 0.0f),
	                            apexHeight + 550.0f, timeToHit + 1.2f);

	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_PowerUp_SnowBall_Fire", NULL);
}

bool PlantIceburg::OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam)
{
	if (i_animCommand != "freeze")
	{
		return false;
	}

	m_exploded = true;

	switch (m_plant->m_state)
	{
	case STATE_DOINGSPECIAL:
	{
		const PlantAction& action = m_plant->GetProps()->Actions[0];
		DamageInfo damageInfo = m_plant->calcDamageInfoFromPlantAction(action);
		damageInfo.Flags |= GetDamageFlags(WEAPON_PRIMARY);

		ZombiePtr targetZombie = FindTargetZombie(WEAPON_PRIMARY);
		if (targetZombie.IsValid())
		{
			targetZombie->TakeDamage(damageInfo);
			targetZombie->PlayPositionalSound("Play_IcebergLettuce_Freeze", 0.0f);
		}

		std::vector<BoardEntity*> entities;
		EntityFinder::GetEntitiesAtGridSquare(entities, (BoardEntityTypeFlag)4,
		                                      m_plant->m_column, m_plant->m_row);
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i]->IsA<GridItemFlame>())
			{
				entities[i]->TakeDamage(damageInfo);
				entities[i]->PlayPositionalSound("Play_IcebergLettuce_Freeze", 0.0f);
			}
		}
		break;
	}
	case STATE_PLANTFOOD:
	{
		for (int row = 0; row < BoardConstants::NUMBER_OF_ROWS(); row++)
		{
			for (int column = 0; column < BoardConstants::NUMBER_OF_COLUMNS(); column++)
			{
				if (FindGridItemAt<GridItemHanabi>(column, row))
				{
					gMessageRouter->Post(Message::CleanPoison, column, row, true);
				}
				if (FindGridItemAt<GridItemFireCracker>(column, row))
				{
					gMessageRouter->Post(Message::GridItemFireCracker, false);
				}
				if (FindGridItemAt<GridItemSummerFireworks>(column, row))
				{
					gMessageRouter->Post(Message::GridItemSummerFireworks, false);
				}
				GridItemCoalSteamZomboss* coal = FindGridItemAt<GridItemCoalSteamZomboss>(column, row);
				if (coal)
				{
					coal->NotifyDamageByIceburg();
				}
			}
		}

		CollisionTypeFlags collisionFlags = GetCollisionFlags(WEAPON_PRIMARY);
		const PlantAction& action = m_plant->GetProps()->Actions[1];
		DamageInfo damageInfo = m_plant->calcDamageInfoFromPlantAction(action);
		damageInfo.Flags |= GetDamageFlags(WEAPON_SECONDARY);

		int frozenCount = 0;
		gMessageRouter->Post(Message::BreakFireBallOnScreen);
		gMessageRouter->Post(Message::FreezeZombossRobot, m_plant, action.FreezeDuration);

		for (Sexy::RtDbTable::Iterator it =
		         PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
		{
			ZombiePtr zombie = *it;
			if (zombie->IsDying())
			{
				continue;
			}
			if (!zombie->CollidesWithType(collisionFlags))
			{
				continue;
			}
			if (!zombie->IsOnOpposingTeam(m_plant))
			{
				continue;
			}
			if (zombie->IsInvisible())
			{
				continue;
			}
			frozenCount++;
			zombie->TakeDamage(damageInfo);
		}

		for (Sexy::RtDbTable::Iterator it =
		         PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_GRIDITEMS); it; ++it)
		{
			GridItemPtr gridItem = *it;
			if (gridItem->IsA<GridItemFlame>())
			{
				gridItem->TakeDamage(damageInfo);
			}
			frozenCount++;
		}

		if (frozenCount > 19)
		{
			Achievement::Queue("iceberg_ch", 100.0f);
			Achievement::SubmitAll();
		}
		break;
	}
	default:
		break;
	}

	return true;
}

void PlantIceburg::UpdateActions()
{
	m_LaunchState.UpdateState();

	if (m_plant->m_state == STATE_IDLE || m_plant->m_state == STATE_SHOOT)
	{
		ZombiePtr targetZombie = FindTargetZombie(WEAPON_PRIMARY);
		if (targetZombie.IsValid())
		{
			m_plant->m_state = STATE_DOINGSPECIAL;
			m_plant->m_launchInterval.SetRange(m_plant->GetProps()->Actions[0].CooldownTimeMin,
			                                   m_plant->GetProps()->Actions[0].CooldownTimeMax);
			GetRig()->PlayAttack();
			GetRig()->SetState((PlantAnimRigState)PLANTANIM_ICEBURG_SHOOT);
		}

		std::vector<BoardEntity*> entities;
		EntityFinder::GetEntitiesAtGridSquare(entities, (BoardEntityTypeFlag)4,
		                                      m_plant->m_column, m_plant->m_row);
		for (size_t i = 0; i < entities.size(); )
		{
			if (entities[i++]->IsA(GridItemFlame::StaticGetClass()))
			{
				m_plant->m_state = STATE_DOINGSPECIAL;
				GetRig()->PlayAttack();
				GetRig()->SetState((PlantAnimRigState)PLANTANIM_ICEBURG_SHOOT);
				break;
			}
		}
	}
	else if (m_plant->m_state == STATE_DOINGSPECIAL)
	{
		if (!GetRig()->IsPlayingAnything())
		{
			m_plant->KillPlant(false, false, (DamageTypeFlags)1);
		}
	}
}

void PlantIceburg::PlayAttackAnimation()
{
	if (m_plant->m_state == STATE_SHOOT)
	{
		GetRig<PlantAnimRig_Iceburg>()->PlayShootAnimation();
	}
	else
	{
		m_plant->PlayAttackAnimation();
	}
}

void PlantIceburg::onEnterState_LAUNCHING(LaunchState i_fromState)
{
	m_launchNumbers = 5;
	m_nextLaunchTime = PVZ_T();
	gAudioMgr->SendEvent("Play_UI_PowerUp_SnowBall_Start");
}

void PlantIceburg::updateState_LAUNCHING()
{
	if (PVZ_T() > m_nextLaunchTime)
	{
		m_nextLaunchTime = PVZ_T() + 0.1f;
		FindValidZombiesAndAttack();
	}
}

void PlantIceburg::setState(LaunchState i_newState)
{
	StateDefinition<LaunchState> newState =
		StateMachineTableBuilder::GetInstancePtr()->GetTable<LaunchState>(GetClass())->GetStateDefinition(i_newState);
	newState.SetContext(this);
	m_LaunchState.SetState(newState);
}

bool PlantIceburg::isInState(LaunchState i_state) const
{
	return m_LaunchState.GetState() == i_state;
}

void PlantIceburg::setLaunchStateSerialization(int32 i_state)
{
	StateDefinition<LaunchState> newState =
		StateMachineTableBuilder::GetInstancePtr()->GetTable<LaunchState>(GetClass())->GetStateDefinition((LaunchState)i_state);
	newState.SetContext(this);
	m_LaunchState.SetStateNoTransition(newState);
}

int32 PlantIceburg::getLaunchStateSerialization()
{
	return m_LaunchState.GetState();
}

void PlantIceburg::onEnterState_INIT(LaunchState i_fromState)
{
}

void PlantIceburg::updateState_INIT()
{
}

void PlantIceburg::onExitState_INIT(LaunchState i_toState)
{
}

void PlantIceburg::onExitState_LAUNCHING(LaunchState i_toState)
{
}

void PlantIceburg::onEnterState_END(LaunchState i_fromState)
{
	m_validTargets.clear();
	m_hittedTargets.clear();
}

void PlantIceburg::updateState_END()
{
}

void PlantIceburg::onExitState_END(LaunchState i_toState)
{
}
