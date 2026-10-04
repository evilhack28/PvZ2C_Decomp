//
//  SpeedChange.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SpeedChange.h"
#include "LawnApp.h"
#include "Board.h"
#include "LevelModuleManager.h"
#include "MetricsCollector.h"
#include "PlayerInfo.h"
#include "ProfileUtils.h"
#include "AnimationControllerHelpers.h"

SpeedChange::SpeedChange()
	: m_isTutorial(false)
	, m_tutorialArrow(nullptr)
{
}

void SpeedChange::onGameplayEnded()
{
	SetClickable(false);
}

void SpeedChange::onCancel()
{
	gLawnApp->KillPVZ2Dialog();
	if (gLawnApp->m_board)
	{
		gLawnApp->ResumeMusic();
		gLawnApp->m_board->Pause(false);
	}
}

void SpeedChange::onRechargeNow()
{
	gLawnApp->KillPVZ2Dialog();
	if (gLawnApp->m_board)
	{
		gLawnApp->ResumeMusic();
		gLawnApp->m_board->Pause(false);
	}
	gLawnApp->ShowCoinStore(STORE_TYPE_GEM);
}

void SpeedChange::onInitialized()
{
	PlayerInfo* profile = ProfileUtils::Profile();
	if (profile && profile->GameFeatureIsUnlocked(FEATURE_GEMS) && !profile->GameFeatureIsUnlocked(FEATURE_CHANGE_SPEED))
		profile->UnlockGameFeature(FEATURE_CHANGE_SPEED);
	m_isTutorial = false;
}

void SpeedChange::updateState_Ready()
{
	if (m_isTutorial && m_tutorialArrow)
		m_tutorialArrow->Update(PVZ_RealT());
}

void SpeedChange::unregisterForEvents()
{
}

void SpeedChange::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SpeedChange);

void SpeedChange::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SpeedChange);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(SpeedChange);
}

SpeedChange::~SpeedChange()
{
	if (m_tutorialArrow)
	{
		if (m_tutorialArrow->GetPtr().IsValid())
			m_tutorialArrow->GetPtr()->Destroy();
		m_tutorialArrow->GetPtr().ClearId();
		m_tutorialArrow = nullptr;
	}
	gMessageRouter->Unsubscribe(this);
}

namespace Message { void TutorialFTUE(int event); }

void SpeedChange::onGameStart()
{
	if (m_isTutorial)
	{
		gLawnApp->m_board->DisplayAdvice(SexyString(L"[CHANGE_SPEED_TUTORIAL]"), MESSAGE_STYLE_BIG_MIDDLE_FAST, ADVICE_PRIORITY_HIGH);
		gMessageRouter->Post(&Message::TutorialFTUE, egypt1_speedup_prompt);
	}
}

static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_SPEEDCHANGE_X1("IMAGE_UI_HUD_INGAME_SPEED");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_SPEEDCHANGE_X2("IMAGE_UI_HUD_INGAME_SPEED_DOWN");

void SpeedChange::Draw(Graphics* i_g)
{
	UIWidget::Draw(i_g);
	GraphicsAutoState state(i_g);
	translateToWidgetPosition(i_g);
	if (TimeMgr::GetInstancePtr()->GetTimeScale() != 1.0f)
		i_g->DrawImage(IMAGE_UI_SPEEDCHANGE_X2, 0, 0);
	else
		i_g->DrawImage(IMAGE_UI_SPEEDCHANGE_X1, 0, 0);
	if (m_isTutorial && m_tutorialArrow)
		m_tutorialArrow->Draw(i_g);
}

void SpeedChange::OnMouseUp(const int i_mouseX, const int i_mouseY)
{
	if (m_tutorialArrow)
	{
		if (m_tutorialArrow->GetPtr().IsValid())
			m_tutorialArrow->GetPtr()->Destroy();
		m_tutorialArrow->GetPtr().ClearId();
		m_tutorialArrow = nullptr;
		gMessageRouter->Post(&Message::TutorialFTUE, egypt1_speedup_buttonclick);
	}
	float newSpeed = TimeMgr::GetInstancePtr()->GetTimeScale() == 1.0f ? 2.0f : 1.0f;
	gMessageRouter->Post(&Message::SpeedChangeButtonPressed, newSpeed);
}

void SpeedChange::registerForEvents()
{
	LevelModuleManager* mgr;
	if (gLawnApp->m_board && (mgr = gLawnApp->m_board->GetLevelModuleManager()))
		mgr->RegisterOnGameplayStarted(Sexy::MakeDelegate(*this, &SpeedChange::onGameStart));
	gMessageRouter->Subscribe(&Message::GameplayEnded, Sexy::MakeDelegate(*this, &SpeedChange::onGameplayEnded));
}
