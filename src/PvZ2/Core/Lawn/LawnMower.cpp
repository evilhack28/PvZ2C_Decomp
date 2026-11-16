//
//  LawnMower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-13.
//

#include "SexyAppFramework/Common.h"

#include "LawnMower.h"
#include "LawnMowerModule.h"
#include "LawnApp.h"
#include "Board.h"
#include "BoardConstants.h"
#include "BoardTransforms.h"
#include "EntityFinder.h"
#include "PVZDB.h"
#include "Curve.h"
#include "Zombie.h"
#include "GridItem.h"
#include "PopAnimRig.h"
#include "Effect_PopAnim.h"
#include "ResourceHelpers.h"
#include "TideModule.h"
#include "AudioMgr.h"
#include "Utils.h"
#include "ReflectionBuilder.h"

/////////////// Helpers ///////////////

static CachedResourcePtr<Sexy::Image> IMAGE_PLANTSHADOW("IMAGE_PLANTSHADOW");

static SexyVector2 ToScreen(float i_x, float i_y, float i_z)
{
	return SexyVector2(i_x, i_y - i_z);
}

/////////////// Lifecycle ///////////////

LawnMower::LawnMower()
	: m_touchStartTime(0)
	, m_touch(Sexy::InvalidTouchID)
	, m_explodeAtGridX(-1)
{
}

LawnMower::~LawnMower()
{
}

LawnMowerProperties::LawnMowerProperties()
{
	MowerEntryAnimDuration = 2.5f;
	MowerExplodeAtGridX = -1;
	UnlimitedMowers = false;
}

LawnMowerProperties::~LawnMowerProperties()
{
}

void LawnMower::onInitialized()
{
	BoardEntity::onInitialized();
	m_mowerState = MOWER_INVALID;
	m_fallingIntoWater = false;
	m_numZombiesMowed = 0;
	m_chompTime = -1.0f;
	m_fallingStartTime = -1.0f;
	gMessageRouter->Broadcast(Message::MowerCreated, this);
}

void LawnMower::onDestroy()
{
	gMessageRouter->Post(Message::MowerDie, this);
	if (m_popAnimRig)
	{
		m_popAnimRig->Destroy();
	}
	m_groundEffect.Destroy();
}

void LawnMower::unregisterForEvents()
{
	gLawnApp->UnregisterBoardTouchGameplayObject(this);
}

/////////////// Accessors ///////////////

void LawnMower::SetRow(int i_row)
{
	m_row = i_row;
}

void LawnMower::clearTouch()
{
	m_touch = Sexy::InvalidTouchID;
	m_touchStartTime = 0;
}

SexyVector2 LawnMower::GetArtOffset()
{
	return SexyVector2(118.0f, 135.0f);
}

float LawnMower::getRowToPixelY(int i_row)
{
	return BoardTransforms::GridToBoardSpaceY(i_row) + 22.0f;
}

SexyVector3 LawnMower::GetStartingLocation(int i_rowIndex)
{
	SexyVector3 pos;
	pos.x = 200.0f - BoardConstants::GRIDSQUARE_WIDTH() * 0.5f;
	pos.y = getRowToPixelY(i_rowIndex);
	return pos;
}

void LawnMower::ResetStartingLocation()
{
	SetPosition(GetStartingLocation(m_row));
	m_fallingIntoWater = false;
	m_fallingStartTime = -1.0f;
	gMessageRouter->Broadcast(Message::MowerReset, this);
}

Rect LawnMower::GetAttackRect(const SexyVector2& pos)
{
	return Rect((int)(pos.x - 20.0f), (int)(pos.y - 60.0f), 45, 60);
}

Rect LawnMower::GetAttackRect(int i_row)
{
	SexyVector3 pos = GetStartingLocation(i_row);
	return GetAttackRect(SexyVector2(pos.x, pos.y - pos.z));
}

Rect LawnMower::GetAttackRect()
{
	return GetAttackRect(ToScreen(m_position.x, m_position.y, m_position.z));
}

/////////////// Spawning ///////////////

void LawnMower::LawnMowerInitialize(PopAnim* i_mowerPopAnim, int i_row, const std::string& i_activatedAudioEvent, std::vector<int> i_idleAnimWeights)
{
	SetRow(i_row);
	m_mowerState = MOWER_INITTED;
	m_activatedAudioEvent = i_activatedAudioEvent;
	ResetStartingLocation();
	initializePAM(i_mowerPopAnim, i_idleAnimWeights);
	gMessageRouter->Broadcast(Message::MowerInitialized, this);
}

void LawnMower::SpawnMower()
{
	ResetStartingLocation();
	m_popAnimRig->Play("idle");
	if (m_mowerState == MOWER_INITTED)
	{
		CreateSpawnEffect();
		m_mowerState = MOWER_READY;
		PlayPositionalSound("Play_UI_Game_Mower_Appear_Single", 0.0f);
	}
}

void LawnMower::tryDestroy()
{
	LawnMowerModule* module = gLawnApp->m_board->GetLevelModuleByClass<LawnMowerModule>();
	if (module && module->ShouldRespawnMower(GetRow()))
	{
		m_mowerState = MOWER_INITTED;
		SpawnMower();
		m_popAnimRig->PlayAndContinue("idle");
		return;
	}
	Destroy();
}

void LawnMower::initializePAM(PopAnim* i_mowerPopAnim, std::vector<int> i_animIdleWeights)
{
	if (m_popAnimRig)
	{
		m_popAnimRig->Destroy();
		m_popAnimRig.ClearId();
	}
	m_popAnimRig = PopAnimRig::CreateRig(i_mowerPopAnim, PopAnimRig::StaticGetClass())->GetPtr();
	m_popAnimRig->Play("idle", PLAY_CONTINUOUS, i_animIdleWeights.size() ? SELECT_RANDOM_DISTRIBUTION : SELECT_RANDOM_INDEX, i_animIdleWeights);
	m_popAnimRig->SetAnimRateOverride(1.0f + (-10.0f + Sexy::Rand(20.0f)) * 0.01f);
}

void LawnMower::CreateSpawnEffect()
{
	SexyVector2 artOffset = GetArtOffset();
	Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
	effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_MOWER_SPAWN"));
	effect->SetBoardSpaceOrigin(SexyVector3(ToScreen(m_position.x, m_position.y, m_position.z).x + 20.0f - artOffset.x, ToScreen(m_position.x, m_position.y, m_position.z).y + 5.0f - artOffset.y, 0.0f));
	effect->SetRenderLayerOverride(CalcRenderOrder() + 1);
	effect->PlaySingleAnimation("animation");
}

/////////////// Mowing ///////////////

void LawnMower::updateGroundEffect()
{
	if (m_groundEffect.IsCurrentEffectManual())
	{
		return;
	}
	const SexyVector3& position = GetPosition();
	GroundEffectType groundEffect = GROUND_EFFECT_Invalid;
	if (IsOnWaterTile(position) && ShouldClipWithWater() && position.z <= 0.0f)
	{
		if (m_groundEffect.CurrentEffect() != GROUND_EFFECT_Tide)
		{
			TideModule* tideModule = gLawnApp->m_board->GetLevelModuleByClass<TideModule>();
			if (tideModule)
			{
				AudioMgr::GetInstancePtr()->SetRTPCValue("Board_WaterOnTiles", tideModule->GetWaveCoveredTiles(), this);
				PlayPositionalSound("Play_UI_Game_Mower_Beach_TurnOn", 0.0f);
			}
			m_popAnimRig->PlayAndContinue("attack2");
		}
		groundEffect = GROUND_EFFECT_Tide;
	}
	m_groundEffect.SetGroundEffect(this, groundEffect, false);
}

void LawnMower::StartMower()
{
	if (m_mowerState == MOWER_TRIGGERED)
	{
		return;
	}
	if (m_activatedAudioEvent.length())
	{
		PlayPositionalSound(m_activatedAudioEvent, 0.0f);
	}
	gMessageRouter->Post(Message::MowerTriggered, this);
	if (gLawnApp->m_board->GetWaveGenerator())
	{
		gLawnApp->m_board->m_timeRowGotLawnMowered[m_row] = PVZ_T();
	}
	m_mowerState = MOWER_TRIGGERED;
	m_popAnimRig->PlayAndStop("transition", SELECT_EXACT, PopAnimRig::AnimStoppedReflectionDelegate(GetPtr(), "onAnimStopped"));
	if (IsHidden())
	{
		SetHidden(false);
	}
}

void LawnMower::MowZombie(Zombie* i_zombie)
{
	if (m_mowerState != MOWER_READY && m_mowerState != MOWER_TRIGGERED)
	{
		return;
	}
	if (m_mowerState == MOWER_READY)
	{
		StartMower();
		m_chompTime = PVZ_T() + 0.25f;
	}
	else
	{
		m_chompTime = PVZ_T() + 0.5f;
	}
	PlayPositionalSound("Play_Splat", 0.0f);
	i_zombie->MowDown();
	m_numZombiesMowed++;
	gMessageRouter->Broadcast(Message::ZombieMowed, this);
}

void LawnMower::MowGridItem(GridItem* i_gridItem)
{
	if (m_mowerState == MOWER_TRIGGERED)
	{
		m_chompTime = PVZ_T() + 0.5f;
		i_gridItem->TakeDamage(DamageInfo(0.0f, DAMAGE_FATAL));
	}
}

void LawnMower::onAnimStopped(const std::string& i_animName)
{
	if (i_animName == "transition")
	{
		m_popAnimRig->PlayAndContinue("attack");
	}
}

void LawnMower::onUpdate()
{
	SnapToGround(false);
	if (m_touch != Sexy::InvalidTouchID && m_mowerState == MOWER_READY)
	{
		if (PVZ_T() - m_touchStartTime >= 1.0f)
		{
			if (gLawnApp->m_board->m_mowerLaunchesLeft > 0)
			{
				gLawnApp->m_board->m_mowerLaunchesLeft--;
				StartMower();
				gMessageRouter->Broadcast(Message::MowerLaunched, this);
			}
			clearTouch();
		}
	}
	m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	Board* board = gLawnApp->m_board;
	if (board->IsPlaying())
	{
		Rect attackRect = GetAttackRect();
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
		{
			Zombie* zombie = PVZDB::GetInstance().GetTable(PVZDB::TABLE_ZOMBIES)->GetObjectForId(*it)->Cast<Zombie>();
			if (zombie && zombie->CanBeMowed() && zombie->IsInRow(m_row) && __builtin_expect(!zombie->IsControlled(), 0) && (m_mowerState != MOWER_READY || (!zombie->IsDying() && !zombie->IsBleedingOut()))
				&& (zombie->CollidesWithType(COLLIDE_GRIDITEMS | COLLIDE_ALL_ZOMBIES) || __builtin_expect(zombie->CollidesWithFlying(), 0) || zombie->IsInvisible()) && attackRect.Intersects(zombie->GetCollisionRect()))
			{
				MowZombie(zombie);
			}
		}
		std::vector<BoardEntity*> entities;
		EntityFinder::GetEntitiesTouchingRectangle(entities, ENTITYTYPE_GRIDITEM, attackRect, m_row, m_row);
		for (std::vector<BoardEntity*>::iterator it = entities.begin(), end = entities.end(); it != end; ++it)
		{
			GridItem* gridItem = (*it)->Cast<GridItem>();
			if (gridItem->IsOnTeam(TEAM_ZOMBIES) && gridItem->GetProps()->CanBeMowed)
			{
				MowGridItem(gridItem);
			}
		}
	}
	if (m_mowerState != MOWER_TRIGGERED)
	{
		return;
	}
	updateGroundEffect();
	int gridX = BoardTransforms::BoardSpaceToGridX(ToScreen(m_position.x, m_position.y, m_position.z).x);
	if (!m_fallingIntoWater && gridX >= 0 && board->GetGridSquareType(gridX, m_row) == GRIDSQUARE_WATER)
	{
		m_fallingIntoWater = true;
		m_fallingStartTime = PVZ_T();
		m_popAnimRig->Play("animation");
	}
	else if (m_fallingIntoWater && PVZ_T() >= m_fallingStartTime + 0.5f)
	{
		gLawnApp->m_board->DoPitOfDoomEffects(GetPosition(), this);
		tryDestroy();
		return;
	}
	else if (m_explodeAtGridX > 0 && gridX >= m_explodeAtGridX)
	{
		CreateSpawnEffect();
		tryDestroy();
		return;
	}
	float speed = 200.0f;
	if (PVZ_T() <= m_chompTime)
	{
		float chompSpeed = speed * 0.5f;
		speed = CurveEvaluate(std::min((m_chompTime - PVZ_T()) * 2.0f, 1.0f), speed, chompSpeed, CURVE_BOUNCE_SLOW_MIDDLE);
		if (PVZ_T() > m_chompTime)
		{
			m_chompTime = -1.0f;
		}
	}
	SexyVector3 position = GetPosition();
	if (m_fallingIntoWater)
	{
		float fallTime = PVZ_T() - m_fallingStartTime;
		float rowY = getRowToPixelY(m_row);
		float sunkY = rowY + 150.0f;
		position.y = CurveEvaluate(fallTime, rowY, sunkY, CURVE_EASE_IN);
		speed *= 0.75f;
	}
	else
	{
		position.y = getRowToPixelY(m_row);
	}
	position.x += PVZ_Dt() * speed;
	SetPosition(position);
	if (position.x > BoardConstants::BOARD_WIDTH)
	{
		tryDestroy();
	}
}

/////////////// Touch ///////////////

void LawnMower::registerForEvents()
{
	gLawnApp->m_board->RegisterTouchGameplayObject(Sexy::MakeDelegate(*this, &LawnMower::onTouchEvent), TOUCHPRIORITY_GRIDITEM, GetPtr());
}

bool LawnMower::onTouchEvent(const Sexy::Touch& i_touch)
{
	bool handled = false;
	if (m_mowerState == MOWER_READY)
	{
		handled = gLawnApp->m_board->IsPlaying();
		if (__builtin_expect(handled, 1))
		{
			if ((m_touch == Sexy::InvalidTouchID && i_touch.phase == Sexy::TOUCH_BEGAN) || m_touch == i_touch.ident)
			{
				float x = INV_S((float)i_touch.location.mX);
				float y = INV_S((float)i_touch.location.mY);
				handled = GetAttackRect().Contains((int)x, (int)y);
				if (__builtin_expect(!handled, 0))
				{
					clearTouch();
				}
				else if (i_touch.phase != Sexy::TOUCH_BEGAN)
				{
					if (i_touch.phase == Sexy::TOUCH_ENDED || i_touch.phase == Sexy::TOUCH_CANCELED)
					{
						clearTouch();
					}
				}
				else
				{
					if (gLawnApp->m_board->m_mowerLaunchesLeft > 0)
					{
						pvztime_t now = PVZ_T();
							m_touch = i_touch.ident;
							m_touchStartTime = now;
					}
				}
			}
			else
			{
				handled = false;
			}
		}
	}
	return handled;
}

/////////////// Drawing ///////////////

int LawnMower::CalcRenderOrder() const
{
	if (m_fallingIntoWater)
	{
		return Board::MakeGroundRenderOrder(m_row, 0);
	}
	return Board::MakeRenderOrder(RENDER_LAYER_LAWN_MOWER, m_row, 0);
}

bool LawnMower::ShouldClipWithWater() const
{
	return true;
}

bool LawnMower::ShouldDrawShadow() const
{
	return BoardEntity::ShouldDrawShadow() && !m_fallingIntoWater && m_mowerState != MOWER_INITTED && m_mowerState != MOWER_READY && m_mowerState != MOWER_TRIGGERED;
}

void LawnMower::onDrawShadow(Graphics* i_g)
{
	GraphicsAutoState autoState(i_g);
	SexyVector2 screenPos = ToScreen(m_position.x, m_position.y, m_position.z);
	float origX = i_g->mScaleOrigX;
	float snapX = floorf((S(screenPos.x) - origX) * i_g->mScaleX);
	i_g->mTransX = i_g->mTransX + (double)origX + snapX;
	float origY = i_g->mScaleOrigY;
	float snapY = floorf((S(screenPos.y) - origY) * i_g->mScaleY);
	i_g->mTransY = i_g->mTransY + (double)origY + snapY;
	SexyVector2 offset(-2.0f, -20.0f);
	offset *= S(1.0f);
	SexyTransform2D matrix;
	matrix.Scale(i_g->mScaleX, i_g->mScaleY);
	matrix.Translate(offset.x, offset.y);
	i_g->DrawImageMatrix(IMAGE_PLANTSHADOW, matrix, 0.0f, 0.0f);
}

void LawnMower::onDraw(Graphics* i_g)
{
	if (m_mowerState == MOWER_INITTED)
	{
		return;
	}
	SexyVector2 screenPos = ToScreen(m_position.x, m_position.y, m_position.z);
	float scale = i_g->mScaleX;
	float touchProgress = 0.0f;
	if (m_touch != Sexy::InvalidTouchID)
	{
		touchProgress = std::min(1.0f, std::max(PVZ_T() - m_touchStartTime, 0.0f));
		scale += touchProgress * 0.3f;
	}
	{
		GraphicsAutoState autoState(i_g);
		onApplyDrawClipRect(i_g);
		screenPos.x += 20.0f;
		float origX = i_g->mScaleOrigX;
		float snapX = floorf((S(screenPos.x) - origX) * i_g->mScaleX);
		i_g->mTransX = i_g->mTransX + (double)origX + snapX;
		float origY = i_g->mScaleOrigY;
		float snapY = floorf((S(screenPos.y) - origY) * i_g->mScaleY);
		i_g->mTransY = i_g->mTransY + (double)origY + snapY;
		SexyVector2 artOffset = GetArtOffset();
		if (scale != 1.0f)
		{
			SexyTransform2D transform;
			transform.LoadIdentity();
			transform.Scale(scale, scale);
			transform.Translate(-S(scale * artOffset.x), -S(scale * artOffset.y));
			m_popAnimRig->SetRenderTransform(transform);
		}
		else
		{
			SexyTransform2D transform;
			transform.LoadIdentity();
			m_popAnimRig->SetRenderTransform(transform);
			i_g->Translate((int)-S(artOffset.x), (int)-S(artOffset.y));
		}
		m_popAnimRig->Draw(i_g);
	}
	if (m_touch != Sexy::InvalidTouchID && m_mowerState == MOWER_READY)
	{
		i_g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
		float progress = std::min(1.0f, std::max(PVZ_T() - m_touchStartTime, 0.0f));
		float radius = touchProgress * 20.0f + 90.0f;
		DrawRadialCooldown(i_g, progress, S(screenPos.x - 25.0f), S(screenPos.y - 30.0f), radius - 10.0f, Color(64, 0, 0, 100), Color(255, 180, 180, 100));
		progress -= 3.0f;
		DrawRadialCooldown(i_g, __builtin_fmaxf(progress, 0.0f), S(screenPos.x - 25.0f), S(screenPos.y - 30.0f), radius, Color(64, 0, 0, 100), Color(255, 128, 128, 100));
		i_g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
	}
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(LawnMower);

void LawnMower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LawnMower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_row);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_mowerState);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_popAnimRig);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_chompTime);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_activatedAudioEvent);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_fallingIntoWater);
		REFLECTION_CLASSBUILDER_FIELD(int, m_numZombiesMowed);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_fallingStartTime);
		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
		REFLECTION_CLASSBUILDER_FIELD(int, m_explodeAtGridX);
		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onAnimStopped, onAnimStopped, const std::string&);
	REFLECTION_CLASSBUILDER_END(LawnMower);
}

RT_CLASS_IMPLEMENT(LawnMowerProperties);

void LawnMowerProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LawnMowerProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, MowerEntryAnimDuration);
		REFLECTION_CLASSBUILDER_FIELD(std::string, MowerPopAnim);
		REFLECTION_CLASSBUILDER_FIELD(std::string, MowerActivatedAudioEvent);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, MowerIdleAnimWeights);
		REFLECTION_CLASSBUILDER_FIELD(int, MowerExplodeAtGridX);
		REFLECTION_CLASSBUILDER_FIELD(bool, UnlimitedMowers);
	REFLECTION_CLASSBUILDER_END(LawnMowerProperties);
}
