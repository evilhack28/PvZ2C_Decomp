//
//  GameStateTransitionController.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GameStateTransitionController.h"
#include "LawnApp.h"
#include "AudioMgr.h"
#include "PopAnimRig.h"
#include "ResourceHelpers.h"
#include "NewPVPUtils.h"
#include "BusyAnimationManager.h"
#include "SexyAppFramework/drivers/crashtracking/CrashTracking.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

GameStateTransitionController::~GameStateTransitionController()
{
}

GameStateTransitionController::GameStateTransitionController()
	: m_outTransition(GAMETRANSITION_None)
	, m_inTransition(GAMETRANSITION_None)
	, m_finalFrameDrawn(false)
	, m_queuedStateChange((GameState)-1)
	, m_fullscreenTransitionType(FS_TRANSITION_None)
	, m_fullScreenTransitionEffect(NULL)
	, m_coveringLoad(false)
{
	setTransitionState(StateDefinition<GameTransitionState>(GAMETRANSITIONSTATE_Off, std::string("GAMETRANSITIONSTATE_Off")));
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(GameStateTransitionController);

/////////////// Accessors ///////////////

void GameStateTransitionController::SetOverlayRenderActive(bool i_active)
{
	gLawnApp->GetTransitionOverlay()->SetRenderActive(i_active);
}

bool GameStateTransitionController::IsTransitioning() const
{
	GameTransitionState state = m_transitionState.GetState();
	return state == GAMETRANSITIONSTATE_Out || state == GAMETRANSITIONSTATE_In;
}

bool GameStateTransitionController::IsTransitioningOut() const
{
	return m_transitionState.GetState() == GAMETRANSITIONSTATE_Out;
}

const GameTransitionState GameStateTransitionController::GetTransitionState()
{
	return m_transitionState.GetState();
}

/////////////// Logic ///////////////

GameTransitionParameters g_transitionParams[] =
{
	{ GAMETRANSITION_None,        TRANSITION_TYPE_COLOR,  Color(),                    0.f },
	{ GAMETRANSITION_QuickWhite,  TRANSITION_TYPE_COLOR,  Color(255, 255, 255, 255), 0.5f },
	{ GAMETRANSITION_QuickBlack,  TRANSITION_TYPE_COLOR,  Color(0, 0, 0, 255),       0.5f },
	{ GAMETRANSITION_SlowWhite,   TRANSITION_TYPE_COLOR,  Color(255, 255, 255, 255), 3.f },
	{ GAMETRANSITION_SlowBlack,   TRANSITION_TYPE_COLOR,  Color(0, 0, 0, 255),       3.f },
	{ GAMETRANSITION_QuickSpiral, TRANSITION_TYPE_SPIRAL, Color(255, 255, 255, 255), 0.5f },
	{ GAMETRANSITION_QuickGrass,  TRANSITION_TYPE_GRASS,  Color(255, 255, 255, 255), 0.5f },
	{ GAMETRANSITION_Matchmaking, TRANSITION_TYPE_SPIRAL, Color(255, 255, 255, 255), 1.f },
};

static std::string s_timeTunnelGroup = "TimeTunnel";

static CachedResourcePtr<Sexy::PopAnim> s_timeTunnelAnim("POPANIM_EFFECTS_TIME_TUNNEL");

static CachedResourcePtr<Sexy::PopAnim> s_timeTunnelPVZ1Anim("POPANIM_EFFECTS_TIME_TUNNEL_PVZ1");

void GameStateTransitionController::setTransitionState(const StateDefinition<GameTransitionState>& i_transitionState)
{
	m_transitionState.SetState(i_transitionState);
	CrashTracking::SetString("GameStateTransitionController TransitionState", m_transitionState.GetStateDefinition().GetDisplayName());
}

void GameStateTransitionController::doQueuedStateChange()
{
	m_gameStateMgr->DoStateChange(m_queuedStateChange);
	m_queuedStateChange = (GameState)-1;
}

void GameStateTransitionController::onExitState_TransitionIn(GameTransitionState i_oldState)
{
	gLawnApp->GetTransitionOverlay()->StopTransition();
}

void GameStateTransitionController::onExitState_TransitionOut(GameTransitionState i_oldState)
{
	if (m_gameStateMgr->GetState() != GAME_WaitForNetworkLoad)
		gLawnApp->GetTransitionOverlay()->StopTransition();
}

void GameStateTransitionController::updateState_TransitionIn()
{
	gLawnApp->GetTransitionOverlay()->SetPaused(m_coveringLoad);
	if (gLawnApp->GetTransitionOverlay()->IsTransitionComplete())
		continueTransition();
}

void GameStateTransitionController::updateState_TransitionOut()
{
	if (gLawnApp->GetTransitionOverlay()->IsTransitionComplete())
	{
		if (m_finalFrameDrawn)
			continueTransition();
		else
			m_finalFrameDrawn = true;
	}
}

void GameStateTransitionController::onExitState_TransitionWarpTunnel(GameTransitionState i_oldState)
{
	gLawnApp->GetTransitionOverlay()->StopTransition();
	gLawnApp->DeleteGroup(s_timeTunnelGroup);
	m_fullscreenTransitionType = FS_TRANSITION_None;
}

void GameStateTransitionController::onExitState_TransitionWarpTunnelPVZ1(GameTransitionState i_oldState)
{
	gLawnApp->GetTransitionOverlay()->StopTransition();
	gLawnApp->DeleteGroup(s_timeTunnelGroup);
	m_fullscreenTransitionType = FS_TRANSITION_None;
}

void GameStateTransitionController::updateState_TransitionWarpTunnel()
{
	PopAnimRig* effect = m_fullScreenTransitionEffect;
	if (effect == NULL)
	{
		if (!m_finalFrameDrawn)
		{
			m_finalFrameDrawn = true;
			return;
		}
	}
	else
	{
		effect->UpdateAnim(PVZ_T(), PVZ_Dt());
		if (!m_fullScreenTransitionEffect->IsPlayingAnything())
		{
			delete m_fullScreenTransitionEffect;
			m_fullScreenTransitionEffect = NULL;
			return;
		}
	}
	continueTransition();
}

void GameStateTransitionController::updateState_TransitionWarpTunnelPVZ1()
{
	PopAnimRig* effect = m_fullScreenTransitionEffect;
	if (effect == NULL)
	{
		if (!m_finalFrameDrawn)
		{
			m_finalFrameDrawn = true;
			return;
		}
	}
	else
	{
		effect->UpdateAnim(PVZ_T(), PVZ_Dt());
		if (!m_fullScreenTransitionEffect->IsPlayingAnything())
		{
			delete m_fullScreenTransitionEffect;
			m_fullScreenTransitionEffect = NULL;
			return;
		}
	}
	continueTransition();
}

void GameStateTransitionController::onEnterState_TransitionWarpTunnel(GameTransitionState i_oldState)
{
	m_gameStateMgr->DoStateChange(GAME_Unloaded);
	gLawnApp->LoadGroup(s_timeTunnelGroup);
	m_fullScreenTransitionEffect = PopAnimRig::CreateRigOutsideTable(s_timeTunnelAnim, PopAnimRig::StaticGetClass());
	m_fullScreenTransitionEffect->PlayAndStop("animation");
	m_finalFrameDrawn = false;
	startTransitionEffect(m_inTransition, false);
	gLawnApp->GetTransitionOverlay()->SetPaused(true);
	gAudioMgr->SendEvent("Play_UI_Vortex_Oneshot");
}

void GameStateTransitionController::onEnterState_TransitionWarpTunnelPVZ1(GameTransitionState i_oldState)
{
	m_gameStateMgr->DoStateChange(GAME_Unloaded);
	gLawnApp->LoadGroup(s_timeTunnelGroup);
	m_fullScreenTransitionEffect = PopAnimRig::CreateRigOutsideTable(s_timeTunnelPVZ1Anim, PopAnimRig::StaticGetClass());
	m_fullScreenTransitionEffect->PlayAndStop("animation");
	m_finalFrameDrawn = false;
	startTransitionEffect(m_inTransition, false);
	gLawnApp->GetTransitionOverlay()->SetPaused(true);
	gAudioMgr->SendEvent("Play_UI_Vortex_Oneshot");
}

void GameStateTransitionController::startTransitionEffect(GameTransitionType i_type, bool i_transitioningOut)
{
	if (i_transitioningOut)
		gLawnApp->GetTransitionOverlay()->QueueScreenFadeOut(g_transitionParams[i_type].FadeType, g_transitionParams[i_type].FadeColor, g_transitionParams[i_type].Duration, false);
	else
		gLawnApp->GetTransitionOverlay()->QueueScreenFadeIn(g_transitionParams[i_type].FadeType, g_transitionParams[i_type].FadeColor, g_transitionParams[i_type].Duration, i_transitioningOut);
	gLawnApp->GetTransitionOverlay()->StartTransition();
}

void GameStateTransitionController::Update()
{
	m_transitionState.UpdateState();
}

void GameStateTransitionController::onEnterState_TransitionOut(GameTransitionState i_oldState)
{
	m_finalFrameDrawn = false;
	startTransitionEffect(m_outTransition, true);
	if (__builtin_expect(!NewPVPUtils::IsPlayingNewPVP(), 1))
	{
		gLawnApp->m_busyManager->StartBusyIcon();
	}
	else if (NewPVPUtils::IsPlayingNewPVP() && m_outTransition != GAMETRANSITION_Matchmaking)
	{
		if (m_inTransition != GAMETRANSITION_Matchmaking)
			gLawnApp->m_busyManager->StartBusyIcon();
		else
			SetOverlayRenderActive(false);
	}
}

void GameStateTransitionController::onEnterState_TransitionIn(GameTransitionState i_oldState)
{
	startTransitionEffect(m_inTransition, false);
	m_gameStateMgr->GetState();
	gLawnApp->GetTransitionOverlay()->SetPaused(m_coveringLoad);
	if (__builtin_expect(!NewPVPUtils::IsPlayingNewPVP(), 1))
	{
		gLawnApp->m_busyManager->StopBusyIcon();
	}
	else if (NewPVPUtils::IsPlayingNewPVP() && m_outTransition != GAMETRANSITION_Matchmaking)
	{
		if (m_inTransition != GAMETRANSITION_Matchmaking)
			gLawnApp->m_busyManager->StopBusyIcon();
		else
			SetOverlayRenderActive(false);
	}
}
