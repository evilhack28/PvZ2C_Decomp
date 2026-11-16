//
//  PowerupMiniGamePerkSelector.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupMiniGamePerk.h"
#include "PowerupManager.h"
#include "Board.h"
#include "LawnApp.h"
#include "GameEventMgr.h"
#include "PowerupType.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

PowerupMiniGamePerkSelector::PowerupMiniGamePerkSelector()
{
}

PowerupMiniGamePerkSelector::~PowerupMiniGamePerkSelector()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PowerupMiniGamePerkSelector);

/////////////// Logic ///////////////

void PowerupMiniGamePerkSelector::onTouchEnd(const Sexy::Touch& i_touch)
{
}

bool PowerupMiniGamePerkSelector::onTouchBegin(const Sexy::Touch& i_touch)
{
	return true;
}

bool PowerupMiniGamePerkSelector::canActivate()
{
	return true;
}

void PowerupMiniGamePerkSelector::onEnterState_Selected(PowerupState i_fromState)
{
	BasePowerup::onEnterState_Selected(i_fromState);
}

void PowerupMiniGamePerkSelector::updateState_Selected()
{
	if (!canActivate())
	{
		gLawnApp->m_board->GetPowerupManager()->CancelActivePowerup();
		return;
	}
	if (!isInState(POWERUP_Activated))
		Activate();
	activate();
}

void PowerupMiniGamePerkSelector::activate()
{
	std::string name = GetType()->TypeName.substr(8);
	int id = MiniGamePerkMapper::GetInstance().GetIdForName(name);
	gMessageRouter->Post(&Message::NotifyUseButtonClicked, id);
}

void PowerupMiniGamePerkSelector::Draw(Sexy::Graphics* i_g)
{
}
