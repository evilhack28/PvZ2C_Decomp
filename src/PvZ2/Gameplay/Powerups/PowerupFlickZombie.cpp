//
//  PowerupFlickZombie.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PowerupFlickZombie.h"
#include "LawnApp.h"
#include "Board.h"
#include "Zombie.h"
#include "ZombiePirateCannon.h"
#include "ZombieTosser_SubSystem.h"
#include "EntityFinder.h"
#include "ZombieFutureJetpack.h"
#include "ZombiePirateSeagull.h"
#include "Effect_PopAnim.h"
#include "BoardConstants.h"

PowerupFlickZombie::~PowerupFlickZombie()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupFlickZombie);

void PowerupFlickZombie::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupFlickZombie);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BasePowerup);

	REFLECTION_CLASSBUILDER_END(PowerupFlickZombie);
}

void PowerupFlickZombie::onEnterState_Selected(PowerupState i_fromState)
{
	BasePowerup::onEnterState_Selected(i_fromState);
}


void PowerupFlickZombie::cancelTouch()
{
	m_touchIdent = Sexy::InvalidTouchID;
}

void PowerupFlickZombie::onEnterState_Idle(PowerupState i_fromState)
{
	BasePowerup::onEnterState_Idle(i_fromState);
	if (i_fromState != -1)
		cancelTouch();
}

void PowerupFlickZombie::registerForEvents()
{
	gLawnApp->m_board->RegisterTouchGameplayObject(Sexy::MakeDelegate(*this, &PowerupFlickZombie::handleTouch), 4, BoardEntityPtr(), Sexy::MakeDelegate(*this, &PowerupFlickZombie::cancelTouch));
}

void PowerupFlickZombie::unregisterForEvents()
{
	gLawnApp->UnregisterBoardTouchGameplayObject(this);
}

/////////////// Targeting ///////////////

bool PowerupFlickZombie::isValidTarget(Zombie* i_zombie)
{
	ZombieTosserSubSystem* tosser = gLawnApp->m_board->GetGameSubSystem<ZombieTosserSubSystem>();
	if (i_zombie->IsBleedingOut())
		return false;
	if (!i_zombie->IsDying() && !i_zombie->IsControlled() || tosser->IsTossed(i_zombie))
	{
		if (!i_zombie->IsFlickedOff())
			return i_zombie->Cast<ZombiePirateCannon>() == NULL;
	}
	return false;
}


/////////////// Touch ///////////////

bool PowerupFlickZombie::handleTouch(const Sexy::Touch& i_touch)
{
	if (isInState(0))
		return false;

	if (m_touchIdent == Sexy::InvalidTouchID && i_touch.phase == Sexy::TOUCH_BEGAN)
	{
begin:
		m_touchIdent = i_touch.ident;
		m_touchStart = SexyVector2(INV_S(i_touch.location.mX), INV_S(i_touch.location.mY));
		return true;
	}

	if (m_touchIdent != i_touch.ident)
		return false;

	switch (i_touch.phase)
	{
	case Sexy::TOUCH_BEGAN:
		goto begin;
	case Sexy::TOUCH_MOVED:
	{
		SexyVector2 cur(INV_S(i_touch.location.mX), INV_S(i_touch.location.mY));
		SexyVector2 delta = cur - m_touchStart;
		if (delta.MagnitudeSquared() > 10000.0f)
			flick(delta);
		return true;
	}
	case Sexy::TOUCH_ENDED:
	{
		SexyVector2 cur(INV_S(i_touch.location.mX), INV_S(i_touch.location.mY));
		SexyVector2 delta = cur - m_touchStart;
		if (delta.MagnitudeSquared() > 625.0f)
			flick(delta);
		cancelTouch();
		return true;
	}
	case Sexy::TOUCH_CANCELED:
		cancelTouch();
		return true;
	default:
		return true;
	}
}

void PowerupFlickZombie::findTargetZombie(const SexyVector2& i_startPoint, const SexyVector2& i_endPoint, std::vector<Zombie*>& o_zombies)
{
	Sexy::Rect searchRect(i_startPoint.x, i_startPoint.y, 1, 1);
	searchRect.ExpandToContain(i_endPoint.x, i_endPoint.y);
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesTouchingRectangle(entities, BoardEntityTypeFlag(2), searchRect, -2, 7);
	SexyVector2 dir = i_endPoint - i_startPoint;
	float invLenSq = 1.0f / dir.Dot(dir);
	for (size_t i = 0; i < entities.size(); i++)
	{
		Zombie* zombie = static_cast<Zombie*>(entities[i]);
		if (zombie->GetType()->TypeName == "pirate_captain_parrot")
			continue;
		Sexy::Rect rect = zombie->GetCollisionRect();
		Sexy::Point center = rect.GetCenter();
		SexyVector2 toZombie = SexyVector2(center.mX, center.mY) - i_startPoint;
		SexyVector2 proj = dir * (dir.Dot(toZombie) * invLenSq);
		SexyVector2 perp = toZombie - proj;
		float distSq = perp.MagnitudeSquared();
		float tolerance = zombie->IsControlled() ? 6400.0f : 1600.0f;
		if (!(distSq <= tolerance))
			continue;
		if (isValidTarget(zombie))
			o_zombies.push_back(zombie);
	}
}

/////////////// Flick ///////////////

void PowerupFlickZombie::flick(const SexyVector2& i_direction)
{
	std::vector<Zombie*> zombies;
	findTargetZombie(m_touchStart, m_touchStart + i_direction, zombies);
	ZombieTosserSubSystem* tosser = gLawnApp->m_board->GetGameSubSystem<ZombieTosserSubSystem>();
	for (size_t i = 0; i < zombies.size(); i++)
	{
		Zombie* zombie = zombies[i];
		const SexyVector3& pos = zombie->GetPosition();
		float posZ = pos.z;
		Sexy::Point center = zombie->GetCollisionRect().GetCenter();
		SexyVector3 offset;
		SexyVector2 norm = i_direction.Normalize();
		if (norm.x > 0.5f)
			offset.x = BoardConstants::GRIDSQUARE_WIDTH() + offset.x;
		else if (norm.x < -0.5f)
			offset.x -= BoardConstants::GRIDSQUARE_WIDTH();
		if (norm.y > 0.5f)
			offset.y = BoardConstants::GRIDSQUARE_HEIGHT() + offset.y;
		else if (norm.y < -0.5f)
			offset.y -= BoardConstants::GRIDSQUARE_HEIGHT();

		if (zombie->IsControlled() && norm.x > 0.0f)
		{
			tosser->ReleaseZombie(zombie);
			zombie->FlickOff(SexyVector3(pos.x + 850.0f, pos.y, std::max(150.0f, pos.z)));
		}
		else
		{
			Sexy::Rect grid = gLawnApp->m_board->GetGridBoundingRect();
			SexyVector3 dest = pos + offset;
			if (zombie->IsControlled())
			{
				dest = tosser->GetTargetPosition(zombie) + offset;
				tosser->ReleaseZombie(zombie);
			}
			float limit;
			if (dest.x < (limit = grid.mX) || (limit = grid.mX + grid.mWidth, limit < dest.x))
				dest.x = limit;
			bool pit = gLawnApp->m_board->IsPitOfDoom(dest);
			if (zombie->Cast<ZombiePirateSeagull>() != NULL || zombie->Cast<ZombieFutureJetpack>() != NULL || !pit)
			{
				while (grid.mY > dest.y)
					dest.y += BoardConstants::GRIDSQUARE_HEIGHT();
				while (grid.mY + grid.mHeight < dest.y)
					dest.y -= BoardConstants::GRIDSQUARE_HEIGHT();
			}
			gLawnApp->m_board->GetGameSubSystem<ZombieTosserSubSystem>()->LaunchZombie(zombie, dest, posZ + 150.0f, 1.25f);
			zombie->PlayPositionalSound("Play_UI_PowerUp_Flick");
		}

		Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>()->CastChecked<Effect_PopAnim>();
		effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_POWER_UP_ZOMBIE_FLICK"), NULL);
		effect->SetCentered(true);
		effect->PlaySingleAnimation("animation");
		effect->SetBoardSpaceOrigin(SexyVector3(center.mX, center.mY, 0), 800000);
		effect->SetOrientation(i_direction);
		gMessageRouter->Post(&Message::ZombieFlicked, zombie);
	}

	if (!zombies.empty())
	{
		if (isInState(1))
			Activate();
		DecrementTimeByUseCost();
		cancelTouch();
	}
}
