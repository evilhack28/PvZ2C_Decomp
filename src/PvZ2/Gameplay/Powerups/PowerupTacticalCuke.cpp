//
//  PowerupTacticalCuke.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-05.
//

#include "SexyAppFramework/Common.h"

#include "PowerupTacticalCuke.h"
#include "LawnApp.h"
#include "AudioMgr.h"
#include "PowerupManager.h"
#include "PowerupType.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "EntityFinder.h"
#include "BoardEntity.h"
#include "GameEventMgr.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "DangerRoomManager.h"
#include "Board.h"
#include "TGALogMgr.h"

static const std::string sPowerupName("poweruptacticalcuke");
static const std::string sMonthlyCardName("monthlycard_tacticalcuke");

/////////////// PowerupTacticalCuke ///////////////

PowerupTacticalCuke::PowerupTacticalCuke()
{
	m_gemBeforeLaunch = 0;
	m_freeGemBeforeLaunch = 0;
	gLawnApp->LoadGroup("TacticalCuke");
	gMessageRouter->Subscribe(&Message::NotifyPowerupUsesChanged, Sexy::MakeDelegate(*this, &PowerupTacticalCuke::OnNotifyPowerupUsesChanged));
}

PowerupTacticalCuke::~PowerupTacticalCuke()
{
	if (m_TCGameObject)
		static_cast<TacticalCukeGameObject*>(m_TCGameObject.GetObject())->Destroy();
	gMessageRouter->Unsubscribe(this);
	gLawnApp->DeleteGroup("TacticalCuke");
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupTacticalCuke);

void PowerupTacticalCuke::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupTacticalCuke);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BasePowerup);

		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_TCGameObject);
	REFLECTION_CLASSBUILDER_END(PowerupTacticalCuke);
}

void PowerupTacticalCuke::onInitialized()
{
	BasePowerup::onInitialized();
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (gLawnApp->m_board->IsDangerRoom())
	{
		SetIgnoreCost(Sexy::LazySingleton<DangerRoomManager>::GetInstancePtr()->GetCukeCount() > 0);
		return;
	}
	if (profile->GetPowerupUsesLeft(sPowerupName) > 0 || profile->GetMonthlyCukeUsesLeft() > 0)
		SetIgnoreCost(true);
}

void PowerupTacticalCuke::OnNotifyPowerupUsesChanged(PowerupRecord* i_record)
{
	if (i_record && (i_record->Name == sPowerupName || i_record->Name == sMonthlyCardName) && i_record->Inventory > 0)
		SetIgnoreCost(true);
}

void PowerupTacticalCuke::Draw(Sexy::Graphics* i_g)
{
	if (m_TCGameObject)
		m_TCGameObject->Draw(i_g);
}

void PowerupTacticalCuke::onExitState_Activated(PowerupState)
{
	if (m_TCGameObject)
		m_TCGameObject->Destroy();
}

void PowerupTacticalCuke::updateState_Selected()
{
	if (gLawnApp->m_board)
		gLawnApp->m_board->IsDangerRoom();
	Activate();
}

void PowerupTacticalCuke::updateState_Activated()
{
	if (m_TCGameObject)
	{
		m_TCGameObject->Update();
		if (!m_TCGameObject->IsActive())
		{
			AudioMgr::GetInstancePtr()->SendEvent("Play_UI_PowerUp_Menu_TimeUp");
			Deactivate();
		}
	}
}

void PowerupTacticalCuke::updateState_Idle()
{
	std::vector<BoardEntity*> zombies;
	EntityFinder::GetEntities(zombies, ENTITYTYPE_ZOMBIE);
	bool warning = true;
	if (zombies.size() < 15)
	{
		warning = false;
		for (std::vector<BoardEntity*>::iterator it = zombies.begin(); it != zombies.end(); ++it)
		{
			if ((*it)->CalcColumnPosition() < 3)
			{
				warning = true;
				break;
			}
		}
	}
	SetIsInWarning(warning);
}

void PowerupTacticalCuke::onEnterState_Selected(PowerupState i_oldState)
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	m_gemBeforeLaunch = profile->GetNumGems(false);
	m_freeGemBeforeLaunch = profile->GetGiveGems();
	gMessageRouter->Subscribe(&Message::UseGemFinish, Sexy::MakeDelegate(*this, &PowerupTacticalCuke::LaunchCuke));
	BasePowerup::onEnterState_Selected(i_oldState);
}

void PowerupTacticalCuke::CreateCukeObjectAndRefreshStatus()
{
	int additionDamage = gLawnApp->m_board->GetPowerupManager()->GetCurrentPowerAdditionDamage(this);
	m_TCGameObject = GameObject::Create(TacticalCukeGameObject::StaticGetClass(), PVZDB::TABLE_GAMEOBJECTS)->GetPtr();
	m_TCGameObject->Activate(true, GetType()->TotalTime, additionDamage);
}

void PowerupTacticalCuke::LaunchCuke(bool success)
{
	if (getState() == POWERUP_Activated || getState() == POWERUP_Selected)
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		int gemCost = profile->GetNumGems(false) - m_gemBeforeLaunch;
		int freeGem = profile->GetGiveGems() - m_freeGemBeforeLaunch;
		TGALogMgr::GetInstance().UseLevelItem("powerupdangerroomtacticalcuke", 0, gemCost);
		gMessageRouter->Post(&Message::LaunchCuke, success, gemCost, freeGem);
		gMessageRouter->Unsubscribe(&Message::UseGemFinish, Sexy::MakeDelegate(*this, &PowerupTacticalCuke::LaunchCuke));
		if (success)
			CreateCukeObjectAndRefreshStatus();
		gLawnApp->m_board->GetPowerupManager()->onUseGemFinished(success);
	}
}
