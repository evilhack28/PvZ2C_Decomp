//
//  PowerupVaseBreakerButter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupVaseBreaker.h"
#include "Zombie.h"
#include "AudioMgr.h"
#include "ScaledApp.h"
#include "LawnApp.h"
#include "Board.h"
#include "PowerupManager.h"
#include "EntityFinder.h"
#include "BoardConstants.h"
#include <limits>

PowerupVaseBreakerButter::PowerupVaseBreakerButter()
{
}

PowerupVaseBreakerButter::~PowerupVaseBreakerButter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupVaseBreakerButter);

Zombie* PowerupVaseBreakerButter::getClosestButterableZombie(const SexyVector2& i_location, float i_maxGridSquareDistance)
{
	Zombie* closestUnbuttered = nullptr;
	Zombie* closestButtered = nullptr;
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesTouchingCircle2D(entities, ENTITYTYPE_ZOMBIE, i_location,
											  BoardConstants::GRIDSQUARE_WIDTH() * i_maxGridSquareDistance);
	float bestUnbuttered = std::numeric_limits<float>::max();
	float bestButtered = std::numeric_limits<float>::max();
	for (size_t i = 0; i < entities.size(); i++)
	{
		Zombie* zombie = entities[i]->CastChecked<Zombie>();
		Sexy::Rect rect(zombie->GetCollisionRect());
		Sexy::Point center = rect.GetCenter();
		if (zombie->IsOnTeam(TEAM_ZOMBIES) && !zombie->IsDying())
		{
			float dist = (i_location - SexyVector2(center.mX, center.mY)).MagnitudeSquared();
			if (!zombie->HasCondition(ZCONDITION_Buttered))
			{
				if (dist < bestUnbuttered)
				{
					bestUnbuttered = dist;
					closestUnbuttered = zombie;
				}
			}
			else if (dist < bestButtered)
			{
				bestButtered = dist;
				closestButtered = zombie;
			}
		}
	}
	return closestUnbuttered ? closestUnbuttered : closestButtered;
}

bool PowerupVaseBreakerButter::onTouchBegin(const Sexy::Touch& i_touch)
{
	Sexy::Point p = i_touch.location;
	SexyVector2 loc(INV_S(p.mX), INV_S(p.mY));
	setHighlightedZombie(getClosestButterableZombie(loc, 1.5f));
	return true;
}

void PowerupVaseBreakerButter::onTouchMoved(const Sexy::Touch& i_touch)
{
	Sexy::Point p = i_touch.location;
	SexyVector2 loc(INV_S(p.mX), INV_S(p.mY));
	setHighlightedZombie(getClosestButterableZombie(loc, 1.5f));
}

void PowerupVaseBreakerButter::onTouchEnd(const Sexy::Touch& i_touch)
{
	if (!m_highlightedZombie.IsValid())
	{
		gLawnApp->m_board->GetPowerupManager()->CancelActivePowerup();
		return;
	}
	Zombie* zombie = m_highlightedZombie;
	setHighlightedZombie(nullptr);
	PowerupTypeVaseBreakerButter* type = GetType()->CastChecked<PowerupTypeVaseBreakerButter>();
	zombie->ApplyCondition(ZCONDITION_Buttered, type->ButterDuration, 0.0f, true);
	if (!isInState(POWERUP_Activated))
		Activate();
	DecrementTimeByUseCost();
}

void PowerupVaseBreakerButter::onTouchCanceled()
{
	setHighlightedZombie(nullptr);
}

void PowerupVaseBreakerButter::updateState_Selected()
{
	if (m_highlightedZombie.IsValid())
		m_highlightedZombie->SetDamageFlash(0.25f);
}

void PowerupVaseBreakerButter::onEnterState_Activated(PowerupState i_fromState)
{
	gAudioMgr->SendEvent("Play_UI_MiniGame_VaseBreak_ButterZombie");
}

void PowerupVaseBreakerButter::setHighlightedZombie(Zombie* i_zombie)
{
	if (m_highlightedZombie.IsValid())
		m_highlightedZombie.ClearId();
	if (i_zombie)
		m_highlightedZombie = i_zombie->GetPtr();
}
