//
//  CrazyNPC.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CrazyNPC.h"
#include "GameEventMgr.h"
#include "LawnApp.h"
#include "AudioMgr.h"
#include "ScaledApp.h"
#include "UIHelper.h"
#include "PrimeText_Game.h"
#include "TodCommon.h"
#include "TodLib/TodStringFile.h"
#include "ResourceHelpers.h"
#include "StateMachineTableBuilder.h"

void CrazyNPC::StopHolding()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CrazyNPC);

#include "CrazyNPC.h"
#include "GameEventMgr.h"
void CrazyNPC::Update()
{
	 CrazyNPC::updateStateMachine();
}

/////////////// State machine ///////////////

CrazyNPCState CrazyNPC::getState() const
{
	return m_stateMachine.GetState();
}

bool CrazyNPC::isInState(uint32 i_state) const
{
	return m_stateMachine.GetState() == i_state;
}

void CrazyNPC::updateStateMachine()
{
	m_stateMachine.UpdateState();
}

void CrazyNPC::setStateHelper(const StateDefinition<CrazyNPCState>& i_newStateDefinition)
{
	if (m_stateMachine.SetState(i_newStateDefinition))
	{
		m_stateEnterTime = PVZ_T();
	}
}

void CrazyNPC::onEnterState_Initializing(CrazyNPCState) {}
void CrazyNPC::onEnterState_Ready(CrazyNPCState) {}
void CrazyNPC::onEnterState_Talking(CrazyNPCState) { pickAndPlayTalkingAnimation(); }
void CrazyNPC::onEnterState_HoldingTalking(CrazyNPCState) { pickAndPlayTalkingAnimation(); }
void CrazyNPC::onEnterState_Dead(CrazyNPCState) { UnloadResources(); }

void CrazyNPC::onEnterState_Loading(CrazyNPCState) { StartLoad(); }

void CrazyNPC::updateState_Loading()
{
	if (IsLoadComplete())
	{
		CompleteLoad();
	}
}

void CrazyNPC::updateState_Initializing()
{
	Init();
}

void CrazyNPC::updateState_Ready()
{
	if (m_popAnimRig)
	{
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
}

void CrazyNPC::updateState_Idle()
{
	if (m_popAnimRig)
	{
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
}

void CrazyNPC::updateState_Talking()
{
	if (m_popAnimRig)
	{
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
}

void CrazyNPC::updateState_HoldingIdle()
{
	if (m_popAnimRig)
	{
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
}

void CrazyNPC::updateState_HoldingTalking()
{
	if (m_popAnimRig)
	{
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
}

void CrazyNPC::updateState_Dead() {}

void CrazyNPC::updateState_Entering()
{
	if (m_popAnimRig)
	{
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
	if (m_sheetPtr->DialogStyle != NPCTEXT_SPEECHBUBBLE)
	{
		if (GetNPCName() == "zombossicon")
		{
			if (m_popAnimRig->IsAnimStringActive(std::string("anim_enter")))
			{
				return;
			}
		}
		onEnteringAnimFinished(std::string(""));
	}
}

void CrazyNPC::updateState_Leaving()
{
	if (m_popAnimRig)
	{
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
	if (m_sheetPtr->DialogStyle != NPCTEXT_SPEECHBUBBLE)
	{
		if (GetNPCName() == "zombossicon")
		{
			if (m_popAnimRig->IsAnimStringActive(std::string("anim_leave")))
			{
				return;
			}
		}
		onLeavingAnimFinished(std::string(""));
	}
}

void CrazyNPC::updateState_HoldingEnter()
{
	if (m_popAnimRig)
	{
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
	if (m_sheetPtr->DialogStyle != NPCTEXT_SPEECHBUBBLE)
	{
		onHoldingEnteringAnimFinished(std::string(""));
	}
}

void CrazyNPC::updateState_HoldingEat()
{
	if (m_popAnimRig)
	{
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	}
	if (m_sheetPtr->DialogStyle != NPCTEXT_SPEECHBUBBLE)
	{
		onHoldingEatAnimFinished(std::string(""));
	}
}

/////////////// Events ///////////////

void CrazyNPC::onEnteringAnimFinished(const std::string&)
{
	setState(CNPC_State_Idle);
	gMessageRouter->Post(&Message::NPCFinishedEntering, this);
}

void CrazyNPC::onLeavingAnimFinished(const std::string&)
{
	setState(CNPC_Dead);
	gMessageRouter->Post(&Message::NPCFinishedExiting, this);
}

void CrazyNPC::onHoldingEnteringAnimFinished(const std::string&)
{
	setState(CNPC_State_HoldingIdle);
	gMessageRouter->Post(&Message::NPCFinishedEntering, this);
}

void CrazyNPC::onHoldingEatAnimFinished(const std::string&)
{
	setState(CNPC_State_Idle);
	gMessageRouter->Post(&Message::NPCFinishedEntering, this);
}

void CrazyNPC::onCrazyTalkingAnimFinished(const std::string&) { setState(CNPC_State_Idle); }
void CrazyNPC::onYellTalkingAnimFinished(const std::string&) { setState(CNPC_State_Idle); }
void CrazyNPC::onScreamTalkingAnimFinished(const std::string&) { setState(CNPC_State_Idle); }
void CrazyNPC::onTalkAnimFinished(const std::string&) { setState(CNPC_State_Idle); }
void CrazyNPC::onHoldingTalkingAnimFinished(const std::string&) { setState(CNPC_State_HoldingIdle); }

/////////////// Public interface ///////////////

void CrazyNPC::Enter()
{
	setState(CNPC_State_Entering);
}

void CrazyNPC::Leave()
{
	if (!IsLeaving())
	{
		StopHolding();
		setState(CNPC_State_Leaving);
	}
}

void CrazyNPC::Die()
{
	setState(CNPC_Dead);
}

void CrazyNPC::StartEating(const std::string& i_itemToEat)
{
	m_holdingItem = i_itemToEat;
	setState(CNPC_State_HoldingEat);
}

void CrazyNPC::Terminate()
{
	if (m_popAnimRig)
	{
		delete m_popAnimRig;
		m_popAnimRig = NULL;
	}
}
void CrazyNPC::onExitState_Loading(CrazyNPCState) {}
void CrazyNPC::onExitState_Initializing(CrazyNPCState) {}
void CrazyNPC::onExitState_Ready(CrazyNPCState) {}
void CrazyNPC::onExitState_Entering(CrazyNPCState) {}
void CrazyNPC::onExitState_Leaving(CrazyNPCState) {}
void CrazyNPC::onExitState_Idle(CrazyNPCState) {}
void CrazyNPC::onExitState_Talking(CrazyNPCState) {}
void CrazyNPC::onExitState_HoldingEnter(CrazyNPCState) {}
void CrazyNPC::onExitState_HoldingIdle(CrazyNPCState) {}
void CrazyNPC::onExitState_HoldingTalking(CrazyNPCState) {}
void CrazyNPC::onExitState_HoldingEat(CrazyNPCState) {}
void CrazyNPC::onExitState_Dead(CrazyNPCState) {}

/////////////// Resource management ///////////////

void CrazyNPC::PrepForLoading()
{
	if (isInState(CrazyNPCState_INVALID))
	{
		initLoadingResourcesGroupList();
		setState(CNPC_Loading);
	}
}

void CrazyNPC::StartLoad()
{
	if (!m_loadingResourcesList.empty())
	{
		gLawnApp->LoadGroups(m_loadingResourcesList);
	}
}

bool CrazyNPC::IsLoaded()
{
	if (isInState(CNPC_Loading))
	{
		return false;
	}
	if (IsDead())
	{
		return false;
	}
	return !isInState(CrazyNPCState_INVALID);
}

bool CrazyNPC::IsLoadComplete()
{
	bool r = true;
	if (!m_loadingResourcesList.empty())
	{
		r = gLawnApp->IsGroupLoadComplete(m_loadingResourcesList);
	}
	return r;
}

void CrazyNPC::CompleteLoad()
{
	if (isInState(CNPC_Loading))
	{
		setState(CNPC_Initializing);
	}
}

void CrazyNPC::UnloadResources()
{
	if (!m_loadingResourcesList.empty())
	{
		gLawnApp->DeleteGroups(m_loadingResourcesList);
	}
}

void CrazyNPC::initLoadingResourcesGroupList()
{
	if (m_sheetPtr)
	{
		for (size_t i = 0; i < m_sheetPtr->LoadResourceGroups.size(); ++i)
		{
			addToLoadingResourcesGroupList(m_sheetPtr->LoadResourceGroups[i]);
		}
	}
}

void CrazyNPC::addToLoadingResourcesGroupList(const std::string& i_groupName)
{
	if (std::find(m_loadingResourcesList.begin(), m_loadingResourcesList.end(), i_groupName) == m_loadingResourcesList.end())
	{
		m_loadingResourcesList.push_back(i_groupName);
	}
}

void CrazyNPC::Init()
{
	m_initialized = true;
	if (m_sheetPtr->PopAnim.size())
	{
		m_popAnimRig = PopAnimRig::CreateRigOutsideTable(GetPAMByName(m_sheetPtr->PopAnim).Get(), PopAnimRig::StaticGetClass());
	}
	setState(CNPC_Ready);
	Enter();
}

/////////////// Construction ///////////////

CrazyNPC::CrazyNPC()
{
	m_initialized = false;
	m_nextLineLength = CNPCLL_Automatic;
	m_loadingResourcesList.clear();
	m_messageText.clear();
	m_mood = CNPC_Mood_General;
	m_stateEnterTime = PVZ_EOT();
	m_holdingItem.clear();
	m_popAnimRig = NULL;
}

CrazyNPC::~CrazyNPC()
{
	Terminate();
}

void CrazyNPC::setState(const CrazyNPCState i_newState)
{
	setStateHelper(STATEMACHINE_GET_STATE(CrazyNPCState, i_newState));
}

void CrazyNPC::SetNPCSheet(const NPCDataSheetPtr i_sheetPtr)
{
	if (m_sheetPtr == i_sheetPtr)
	{
		return;
	}
	if (IsLoaded())
	{
		UnloadResources();
	}
	m_sheetPtr = i_sheetPtr;
	m_loadingResourcesList.clear();
	PrepForLoading();
}

void CrazyNPC::StartHolding(const std::string& i_itemToHold)
{
	m_holdingItem = i_itemToHold;
	setState(CNPC_State_HoldingEnter);
}

void CrazyNPC::StartTalking(const SexyString& i_message)
{
	m_messageText = i_message;
	if (IsLoaded())
	{
		if (IsTalking())
		{
			pickAndPlayTalkingAnimation();
		}
		else if (IsHoldingItem())
		{
			setState(CNPC_State_HoldingTalking);
		}
		else
		{
			setState(CNPC_State_Talking);
		}
	}
}

void CrazyNPC::StopTalking()
{
	if (IsHoldingItem())
	{
		setState(CNPC_State_HoldingIdle);
	}
	else if (IsTalking())
	{
		setState(CNPC_State_Idle);
	}
	m_messageText.clear();
	Sexy::PrimeText::Instance()->ClearGlyphCache();
}

void CrazyNPC::Draw(Sexy::Graphics* i_g)
{
	i_g->PushState();
	switch (m_sheetPtr->DialogStyle)
	{
	case NPCTEXT_SPEECHBUBBLE:
		drawSpeechBubbleStyle(i_g);
		break;
	case NPCTEXT_BANNER:
		drawTextBannerStyle(i_g);
		break;
	case NPCTEXT_TOPBANNER:
		drawTextTopBannerStyle(i_g);
		break;
	}
	i_g->PopState();
}

/////////////// State entry ///////////////

void CrazyNPC::onEnterState_Idle(CrazyNPCState)
{
	if (m_sheetPtr->DialogStyle == NPCTEXT_SPEECHBUBBLE)
	{
		m_popAnimRig->PlayAndContinue(std::string("anim_idle"), SELECT_EXACT);
	}
	if (GetNPCName() == "zombossicon")
	{
		std::string anim("anim_idle");
		if (!m_popAnimRig->IsAnimStringActive(anim))
		{
			m_popAnimRig->PlayAndContinue(anim, SELECT_EXACT);
		}
	}
}

void CrazyNPC::onEnterState_HoldingIdle(CrazyNPCState)
{
	if (m_sheetPtr->DialogStyle == NPCTEXT_SPEECHBUBBLE)
	{
		m_popAnimRig->PlayAndContinue(StrFormat("anim_%s_idle", m_holdingItem.c_str()), SELECT_EXACT);
	}
}

void CrazyNPC::onEnterState_HoldingEnter(CrazyNPCState)
{
	if (m_sheetPtr->DialogStyle == NPCTEXT_SPEECHBUBBLE)
	{
		m_popAnimRig->PlayAndStop(StrFormat("anim_%s_enter", m_holdingItem.c_str()), SELECT_EXACT, Sexy::MakeDelegate(*this, &CrazyNPC::onHoldingEnteringAnimFinished));
	}
	m_messageText.clear();
}

void CrazyNPC::onEnterState_HoldingEat(CrazyNPCState)
{
	if (m_sheetPtr->DialogStyle == NPCTEXT_SPEECHBUBBLE)
	{
		m_popAnimRig->PlayAndStop(StrFormat("anim_%s_eat", m_holdingItem.c_str()), SELECT_EXACT, Sexy::MakeDelegate(*this, &CrazyNPC::onHoldingEatAnimFinished));
		AudioMgr::GetInstancePtr()->SendEvent("Play_VO_CrazyDave_Taco_Chomp");
	}
	m_messageText.clear();
}

void CrazyNPC::onEnterState_Entering(CrazyNPCState)
{
	if (m_sheetPtr->DialogStyle == NPCTEXT_SPEECHBUBBLE)
	{
		m_popAnimRig->PlayAndStop(std::string("anim_enter"), SELECT_EXACT, Sexy::MakeDelegate(*this, &CrazyNPC::onEnteringAnimFinished));
		if (GetNPCName() == "crazydave")
		{
			AudioMgr::GetInstancePtr()->SendEvent("Play_CrazyDave_Enter");
		}
		else if (GetNPCName() == "winnie")
		{
			AudioMgr::GetInstancePtr()->SendEvent("Play_VO_TimeMachine_Arrive");
		}
	}
	else if (GetNPCName() == "crazydaveicon")
	{
		m_popAnimRig->PlayAndContinue(std::string("dave"), SELECT_EXACT);
	}
	else if (GetNPCName() == "winnieicon")
	{
		m_popAnimRig->PlayAndContinue(std::string("winnie"), SELECT_EXACT);
	}
	else if (GetNPCName() == "zombossicon")
	{
		if (m_popAnimRig->GetPAM()->mMainAnimDef->mMainSpriteDef->GetLabelFrame(std::string("anim_enter")) != -1)
		{
			m_popAnimRig->PlayAndStop(std::string("anim_enter"), SELECT_EXACT, Sexy::MakeDelegate(*this, &CrazyNPC::onEnteringAnimFinished));
		}
	}
	m_messageText.clear();
}

void CrazyNPC::onEnterState_Leaving(CrazyNPCState)
{
	if (m_sheetPtr->DialogStyle == NPCTEXT_SPEECHBUBBLE)
	{
		if (m_popAnimRig)
		{
			m_popAnimRig->PlayAndStop(std::string("anim_leave"), SELECT_EXACT, Sexy::MakeDelegate(*this, &CrazyNPC::onLeavingAnimFinished));
		}
		if (GetNPCName() == "crazydave")
		{
			AudioMgr::GetInstancePtr()->SendEvent("Play_CrazyDave_Leave");
		}
		else if (GetNPCName() == "winnie")
		{
			AudioMgr::GetInstancePtr()->SendEvent("Play_VO_TimeMachine_Away");
		}
	}
	else if (GetNPCName() == "zombossicon" && m_popAnimRig)
	{
		if (m_popAnimRig->GetPAM()->mMainAnimDef->mMainSpriteDef->GetLabelFrame(std::string("anim_leave")) != -1)
		{
			m_popAnimRig->PlayAndStop(std::string("anim_leave"), SELECT_EXACT, Sexy::MakeDelegate(*this, &CrazyNPC::onLeavingAnimFinished));
		}
	}
	m_messageText.clear();
}

/////////////// Talking ///////////////

void CrazyNPC::pickAndPlayTalkingAnimation()
{
	CrazyNPCLineLength length = m_nextLineLength;
	if (length == CNPCLL_Automatic)
	{
		length = CNPCLL_Short;
		size_t len = m_messageText.length();
		if (len >= 9)
		{
			length = CNPCLL_Medium;
			if (len > 0x33)
			{
				length = CNPCLL_Long;
			}
		}
	}
	if (m_sheetPtr->DialogStyle == NPCTEXT_SPEECHBUBBLE)
	{
		std::string animName;
		PopAnimRig::AnimStoppedDelegate onFinished;
		int mood = GetNPCMood();
		if (IsHoldingItem())
		{
			animName = StrFormat("anim_%s_talk", m_holdingItem.c_str());
			onFinished = Sexy::MakeDelegate(*this, &CrazyNPC::onHoldingTalkingAnimFinished);
		}
		else
		{
			if (mood == CNPC_Mood_Shout || mood == CNPC_Mood_Special3 || mood == CNPC_Mood_Special2)
			{
				animName = "anim_crazyblahblah";
				onFinished = Sexy::MakeDelegate(*this, &CrazyNPC::onCrazyTalkingAnimFinished);
			}
			else
			{
				if (mood == CNPC_Mood_Special1 || mood == CNPC_Mood_Special13)
				{
					animName = "anim_smalltalk";
					onFinished = Sexy::MakeDelegate(*this, &CrazyNPC::onTalkAnimFinished);
				}
				else if (mood == CNPC_Mood_Special7 || mood == CNPC_Mood_Special9 || mood == CNPC_Mood_Special10 || mood == CNPC_Mood_Special12 || mood == CNPC_Mood_Special14 || mood == CNPC_Mood_Special15 || mood == CNPC_Mood_Special16)
				{
					animName = "anim_mediumtalk";
					onFinished = Sexy::MakeDelegate(*this, &CrazyNPC::onTalkAnimFinished);
				}
				else if (mood == CNPC_Mood_Special4 || mood == CNPC_Mood_Special5 || mood == CNPC_Mood_Special6 || mood == CNPC_Mood_Special8 || mood == CNPC_Mood_Special11 || mood == CNPC_Mood_Special17)
				{
					animName = "anim_blahblah";
					onFinished = Sexy::MakeDelegate(*this, &CrazyNPC::onTalkAnimFinished);
				}
				else if (length == CNPCLL_Medium)
				{
					animName = "anim_mediumtalk";
					onFinished = Sexy::MakeDelegate(*this, &CrazyNPC::onTalkAnimFinished);
				}
				else if (length == CNPCLL_Long)
				{
					animName = "anim_blahblah";
					onFinished = Sexy::MakeDelegate(*this, &CrazyNPC::onTalkAnimFinished);
				}
				else if (length == CNPCLL_Short)
				{
					animName = "anim_smalltalk";
					onFinished = Sexy::MakeDelegate(*this, &CrazyNPC::onTalkAnimFinished);
				}
			}
		}
		m_popAnimRig->PlayAndStop(animName, SELECT_EXACT, onFinished);
	}
	pickAndPlayTalkingVO(GetNPCMood(), length);
	m_nextLineLength = CNPCLL_Automatic;
}

void CrazyNPC::pickAndPlayTalkingVO(CrazyNPCMood i_mood, CrazyNPCLineLength i_dialogLength)
{
	std::string eventName;
	bool addLength = true;
	switch (i_mood)
	{
	case CNPC_Mood_General:
		eventName = StrFormat("Play_VO_%s_Emote_General", m_sheetPtr->SoundBankPrefix.c_str());
		break;
	case CNPC_Mood_Excited:
		eventName = StrFormat("Play_VO_%s_Emote_Excited", m_sheetPtr->SoundBankPrefix.c_str());
		break;
	case CNPC_Mood_Playful:
		eventName = StrFormat("Play_VO_%s_Emote_Playful", m_sheetPtr->SoundBankPrefix.c_str());
		break;
	case CNPC_Mood_Tired:
		eventName = StrFormat("Play_VO_%s_Emote_Tired", m_sheetPtr->SoundBankPrefix.c_str());
		break;
	case CNPC_Mood_Shout:
		eventName = StrFormat("Play_VO_%s_Emote_Shout", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special1:
		eventName = StrFormat("Play_VO_%s_Special_01", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special2:
		eventName = StrFormat("Play_VO_%s_Special_02", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special3:
		eventName = StrFormat("Play_VO_%s_Special_03", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special4:
		eventName = StrFormat("Play_VO_%s_Special_04", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special5:
		eventName = StrFormat("Play_VO_%s_Special_05", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special6:
		eventName = StrFormat("Play_VO_%s_Special_06", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special7:
		eventName = StrFormat("Play_VO_%s_Special_07", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special8:
		eventName = StrFormat("Play_VO_%s_Special_08", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special9:
		eventName = StrFormat("Play_VO_%s_Special_09", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special10:
		eventName = StrFormat("Play_VO_%s_Special_10", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special11:
		eventName = StrFormat("Play_VO_%s_Special_11", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special12:
		eventName = StrFormat("Play_VO_%s_Special_12", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special13:
		eventName = StrFormat("Play_VO_%s_Special_13", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special14:
		eventName = StrFormat("Play_VO_%s_Special_14", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special15:
		eventName = StrFormat("Play_VO_%s_Special_15", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special16:
		eventName = StrFormat("Play_VO_%s_Special_16", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	case CNPC_Mood_Special17:
		eventName = StrFormat("Play_VO_%s_Special_17", m_sheetPtr->SoundBankPrefix.c_str());
		addLength = false;
		break;
	default:
		break;
	}
	if (addLength)
	{
		switch (i_dialogLength)
		{
		case CNPCLL_Medium:
			eventName += "_Med";
			break;
		case CNPCLL_Long:
			eventName += "_Long";
			break;
		case CNPCLL_Short:
			eventName += "_Short";
			break;
		default:
			break;
		}
	}
	AudioMgr::GetInstancePtr()->SendEvent(eventName);
}

void CrazyNPC::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CrazyNPC);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;
	REFLECTION_CLASSBUILDER_END(CrazyNPC);

	STATEMACHINE_BUILDER_BEGIN(CrazyNPCState);
		STATEMACHINE_BUILDER_ADDSTATE(Loading, CNPC_Loading);
		STATEMACHINE_BUILDER_ADDSTATE(Initializing, CNPC_Initializing);
		STATEMACHINE_BUILDER_ADDSTATE(Ready, CNPC_Ready);
		STATEMACHINE_BUILDER_ADDSTATE(Entering, CNPC_State_Entering);
		STATEMACHINE_BUILDER_ADDSTATE(Leaving, CNPC_State_Leaving);
		STATEMACHINE_BUILDER_ADDSTATE(Idle, CNPC_State_Idle);
		STATEMACHINE_BUILDER_ADDSTATE(Talking, CNPC_State_Talking);
		STATEMACHINE_BUILDER_ADDSTATE(HoldingEnter, CNPC_State_HoldingEnter);
		STATEMACHINE_BUILDER_ADDSTATE(HoldingIdle, CNPC_State_HoldingIdle);
		STATEMACHINE_BUILDER_ADDSTATE(HoldingTalking, CNPC_State_HoldingTalking);
		STATEMACHINE_BUILDER_ADDSTATE(HoldingEat, CNPC_State_HoldingEat);
		STATEMACHINE_BUILDER_ADDSTATE(Dead, CNPC_Dead);
	STATEMACHINE_BUILDER_END();
}

/////////////// Drawing ///////////////

static CachedResourcePtr<Sexy::Image> IMAGE_UI_CRAZYNPC_SPEECH_BUBBLE("");

void CrazyNPC::drawTextTopBannerStyle(Graphics* i_g)
{
	i_g->mTransX = 0;
	i_g->mTransY = 0;
	bool noMessage = m_messageText.empty();
	float bannerY = 220.0f;
	if (!noMessage)
	{
		Sexy::Rect banner(0, (int)UI_S(bannerY), gLawnApp->mScreenBounds.mWidth, (int)UI_S(110.0f));
		i_g->SetColor(Color(0, 0, 0, 128));
		i_g->FillRect(banner);
		Sexy::Rect textRect(banner);
		float pad = UI_S(6.0f);
		int edge = S(175);
		textRect.mX = (int)(edge + pad);
		textRect.mWidth -= textRect.mX * 2;
		SexyString text = m_messageText;
		if (text.find(L"{SHAKE}") != SexyString::npos)
		{
			text = TodReplaceString(text, L"{SHAKE}", L"");
			banner.mX += S(rand() % 2);
			banner.mY += S(rand() % 2);
		}
		if (text.find(L"{NO_CLICK}") != SexyString::npos)
		{
			text = TodReplaceString(text, L"{NO_CLICK}", L"");
		}
		PrimeTypeface* font;
		switch (m_sheetPtr->FontType)
		{
		case NPCFONT_PICO:
			font = FONT_CONVERSATION_WINNIE;
			break;
		case NPCFONT_BRIANNE:
			font = FONT_CONVERSATION_DAVE;
			break;
		case NPCFONT_ASHLEY:
			font = FONT_CONVERSATION_WINNIE;
			break;
		default:
			font = NULL;
			break;
		}
		WriteWordInRect(i_g, text, textRect, font, Color(Color::White), DS_ALIGN_CENTER_VERTICAL_MIDDLE, true);
	}
	int tx = S(-82) + gLawnApp->mScreenBounds.mWidth / 2;
	float uiY = UI_S(bannerY);
	int dy = S(-160);
	i_g->Translate(tx, (int)(dy + uiY));
	m_popAnimRig->Draw(i_g);
	i_g->Translate(-tx, -S(-160));
}

void CrazyNPC::drawTextBannerStyle(Graphics* i_g)
{
	if (m_messageText.empty())
	{
		return;
	}
	i_g->mTransX = 0;
	i_g->mTransY = (float)gLawnApp->mHeight;
	Sexy::Rect banner(0, (int)-UI_S(210.0f), gLawnApp->mWidth, (int)UI_S(110.0f));
	i_g->SetColor(Color(0, 0, 0, 128));
	i_g->FillRect(banner);
	float bottom = UI_S(155.0f);
	Sexy::Rect textRect(banner);
	float padding = 17.5f;
	float pad = UI_S(padding);
	int edge = UI_S(190);
	textRect.mX = (int)(edge + pad);
	textRect.mWidth -= textRect.mX * 2;
	if (m_sheetPtr->ArtIsMirrored)
	{
		float ox = UI_S(padding);
		int w = UI_S(190);
		int z = UI_S(0);
		int x = ((z - ox) + gLawnApp->mWidth) - w;
		i_g->PushState();
		int h = UI_S(175);
		int cornerY = UI_S(-27);
		i_g->Translate(x, (int)((cornerY - bottom) - (h / 2)));
		m_popAnimRig->Draw(i_g);
		i_g->PopState();
	}
	else
	{
		float ox = UI_S(padding);
		int cornerX = UI_S(-22);
		i_g->PushState();
		int h = UI_S(175);
		int cornerY = UI_S(-29);
		i_g->Translate((int)(cornerX + ox), (int)((cornerY - bottom) - (h / 2)));
		m_popAnimRig->Draw(i_g);
		i_g->PopState();
	}
	SexyString text = m_messageText;
	if (text.find(L"{SHAKE}") != SexyString::npos)
	{
		text = TodReplaceString(text, L"{SHAKE}", L"");
		banner.mX += S(rand() % 2);
		banner.mY += S(rand() % 2);
	}
	if (text.find(L"{NO_CLICK}") != SexyString::npos)
	{
		text = TodReplaceString(text, L"{NO_CLICK}", L"");
	}
	PrimeTypeface* font;
	switch (m_sheetPtr->FontType)
	{
	case NPCFONT_PICO:
		font = FONT_CONVERSATION_WINNIE;
		break;
	case NPCFONT_BRIANNE:
		font = FONT_CONVERSATION_DAVE;
		break;
	case NPCFONT_ASHLEY:
		font = FONT_CONVERSATION_WINNIE;
		break;
	default:
		font = NULL;
		break;
	}
	font->DrawString_Paragraph(i_g, textRect, text, EA::Text::kHACenter, EA::Text::kVACenter, Color::White, NULL);
}

void CrazyNPC::drawSpeechBubbleStyle(Graphics* i_g)
{
	i_g->mTransX = 0;
	i_g->mTransY = (float)gLawnApp->mHeight;
	if (!m_messageText.empty())
	{
		Image* bubble = IMAGE_UI_CRAZYNPC_SPEECH_BUBBLE;
		int offset;
		if (m_sheetPtr->ArtIsMirrored)
		{
			int right = gLawnApp->mWidth - bubble->GetWidth();
			int inset = S(185);
			offset = right + inset * -2;
			i_g->DrawImageMirror(bubble, right - inset, S(-460), true);
		}
		else
		{
			i_g->DrawImage(bubble, S(185), S(-460));
			offset = 0;
		}
		SexyString text = m_messageText;
		int rx = S(197) + offset;
		int ry = S(-460);
		int rw = S(259);
		int rh = S(140);
		Sexy::Rect rect(rx, ry, rw, rh);
		if (text.find(L"{SHAKE}") != SexyString::npos)
		{
			text = TodReplaceString(text, L"{SHAKE}", L"");
			rect.mX += S(rand() % 2);
			rect.mY += S(rand() % 2);
		}
		bool clickable = true;
		if (text.find(L"{NO_CLICK}") != SexyString::npos)
		{
			text = TodReplaceString(text, L"{NO_CLICK}", L"");
			clickable = false;
		}
		PrimeTypeface* font;
		switch (m_sheetPtr->FontType)
		{
		case NPCFONT_PICO:
			font = FONT_CONVERSATION_WINNIE;
			break;
		case NPCFONT_BRIANNE:
			font = FONT_CONVERSATION_DAVE;
			break;
		case NPCFONT_ASHLEY:
			font = FONT_CONVERSATION_WINNIE;
			break;
		default:
			font = NULL;
			break;
		}
		TodDrawStringWrapped(i_g, text, rect, font, Color(Color::Black), DS_ALIGN_CENTER_VERTICAL_MIDDLE, false);
		if (clickable)
		{
			PrimeTypeface* tapFont = FONT_CONVERSATION_TAP_TEXT;
			int tx = S(185);
			int ty = S(-326);
			int tw = S(280);
			tapFont->DrawString_Line(i_g, (float)(tx + offset), (float)ty, (float)tw, TodStringTranslate(L"[CLICK_TO_CONTINUE]"), EA::Text::kHACenter, Color(PrimeText_Game::Color_Conversation_Tap_Text), NULL);
		}
	}
	i_g->mTransX = m_sheetPtr->ArtIsMirrored ? (float)gLawnApp->mWidth : 0.0f;
	int cx = S(m_sheetPtr->ArtCornerPosition.mX);
	int cy = S(m_sheetPtr->ArtCornerPosition.mY);
	i_g->Translate(-cx, -cy);
	m_popAnimRig->Draw(i_g);
}
