//
//  BasePowerup.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-06.
//

#include "SexyAppFramework/Common.h"

#include "BasePowerup.h"
#include "LawnApp.h"
#include "Board.h"
#include "AudioMgr.h"
#include "StateMachineTableBuilder.h"
#include <algorithm>

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BasePowerup);

void BasePowerup::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BasePowerup);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_INSTANCE(int32, PowerupState, getPowerupStateSerialization, setPowerupStateSerialization);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_powerupType);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_selected);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_demonstration);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_ignoreCost);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isInWarning);
		REFLECTION_CLASSBUILDER_FIELD(float, m_timeRemaining);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_purchasesLeft);
	REFLECTION_CLASSBUILDER_END(BasePowerup);

	STATEMACHINE_BUILDER_BEGIN(PowerupState);
		STATEMACHINE_BUILDER_ADDSTATE(Idle, POWERUP_Idle);
		STATEMACHINE_BUILDER_ADDSTATE(Selected, POWERUP_Selected);
		STATEMACHINE_BUILDER_ADDSTATE(Activated, POWERUP_Activated);
	STATEMACHINE_BUILDER_END();
}

/////////////// BasePowerup ///////////////

BasePowerup::BasePowerup()
	: m_selected(false)
	, m_demonstration(false)
	, m_ignoreCost(false)
	, m_isInWarning(false)
	, m_timeRemaining(0.f)
	, m_purchasesLeft(-1)
{
}

void BasePowerup::onInitialized()
{
	setState(POWERUP_Idle);
}

void BasePowerup::Update()
{
	m_powerupState.UpdateState();
}

void BasePowerup::Select()
{
	setState(POWERUP_Selected);
}

void BasePowerup::Deselect()
{
	setState(POWERUP_Idle);
}

void BasePowerup::Activate()
{
	setState(POWERUP_Activated);
	gLawnApp->m_board->ActivatePowerup();
}

void BasePowerup::Deactivate()
{
	setState(POWERUP_Idle);
	gLawnApp->m_board->DeactivatePowerup();
}

void BasePowerup::SetIsInWarning(bool isInWarning)
{
	if (m_isInWarning != isInWarning)
	{
		m_isInWarning = isInWarning;
		if (isInWarning)
			gMessageRouter->Post(&Message::PowerupWarning, this);
	}
}

void BasePowerup::ResetTimeRemaining()
{
	m_timeRemaining = m_powerupType->TotalTime;
}

void BasePowerup::DecrementTimeByUseCost()
{
	if (!m_demonstration)
	{
		m_timeRemaining = std::max(0.f, m_timeRemaining - m_powerupType->TimePerUse);
		if (m_timeRemaining == 0.f)
			Deactivate();
	}
}

void BasePowerup::setState(PowerupState i_newState)
{
	StateDefinition<PowerupState> newState =
		StateMachineTableBuilder::GetInstancePtr()->GetTable<PowerupState>(GetClass())->GetStateDefinition(i_newState);
	newState.SetContext(this);
	m_powerupState.SetState(newState);
}

PowerupState BasePowerup::getState() const
{
	return m_powerupState.GetState();
}

bool BasePowerup::isInState(uint32 i_state) const
{
	return getState() == i_state;
}

void BasePowerup::setPowerupStateSerialization(int32 i_state)
{
	StateDefinition<PowerupState> newState =
		StateMachineTableBuilder::GetInstancePtr()->GetTable<PowerupState>(GetClass())->GetStateDefinition((PowerupState)i_state);
	newState.SetContext(this);
	m_powerupState.SetStateNoTransition(newState);
}

int32 BasePowerup::getPowerupStateSerialization()
{
	return m_powerupState.GetState();
}

void BasePowerup::onEnterState_Idle(PowerupState i_fromState)
{
	m_timeRemaining = 0.f;
}

void BasePowerup::updateState_Idle()
{
}

void BasePowerup::onExitState_Idle(PowerupState i_toState)
{
}

void BasePowerup::onEnterState_Selected(PowerupState i_fromState)
{
	ResetTimeRemaining();
}

void BasePowerup::updateState_Selected()
{
}

void BasePowerup::onExitState_Selected(PowerupState i_toState)
{
}

void BasePowerup::onEnterState_Activated(PowerupState i_fromState)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_PowerUp_Menu_Select");
}

void BasePowerup::updateState_Activated()
{
	if (!m_demonstration)
	{
		m_timeRemaining -= PVZ_Dt();
		if (m_timeRemaining <= 0.f)
		{
			AudioMgr::GetInstancePtr()->SendEvent("Play_UI_PowerUp_Menu_TimeUp");
			Deactivate();
		}
	}
}

void BasePowerup::onExitState_Activated(PowerupState i_toState)
{
}

PowerupType* BasePowerup::GetType()
{
	return m_powerupType;
}

void BasePowerup::SetPowerupType(PowerupTypePtr i_powerupType)
{
	m_powerupType = i_powerupType;
}
