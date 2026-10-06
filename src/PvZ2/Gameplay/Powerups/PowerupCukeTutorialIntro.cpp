//
//  PowerupCukeTutorialIntro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupCukeTutorialIntro.h"
#include "StateMachineTableBuilder.h"
#include "PvZ/Board.h"
#include "PvZ/LawnApp.h"
#include "PvZ/ProfileUtils.h"
#include "PvZ/PlayerInfo.h"
#include "PowerupManager.h"
#include "PvZ/Zombie.h"
#include "PvZ/BoardTransforms.h"
#include "PvZ/ProfileMgr.h"
#include "PvZ/RenderQueue.h"
#include "PvZ/UIWidget.h"
#include "PvZ/PowerupTimeUI.h"
#include "PvZ/PlantfoodCursor.h"
#include "PvZ/PowerupUI.h"
#include "PvZ/Effect_BouncingArrow.h"
#include "PvZ/BasePowerup.h"
#include "PvZ/PowerupType.h"
#include "PvZ/AnimationMgr.h"
#include "PvZ/AnimationControllerHelpers.h"
#include "PvZ/Wave.h"
#include "PvZ/SeedBank.h"
#include "PvZ/EntityFinder.h"
#include "PvZ/SunDropperModule.h"
#include "PvZ/LevelModuleManager.h"
#include "PvZ/Plant.h"
#include "PvZ/PlantGroup.h"
#include "PvZ/StageModule.h"
#include "PvZ/CrazyNPCManager.h"
#include "PvZ/ScaledApp.h"
#include "PvZ/StandaloneEffect.h"
#include "PvZ/MetricsCollector.h"

bool PowerupCukeTutorialIntro::needCukeTutorial()
{
	return false;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupCukeTutorialIntro);

/////////////// Empty states ///////////////

#define CUKE_EMPTY_ENTER(s) void PowerupCukeTutorialIntro::onEnterState_##s(PowerupCukeTutorialState) {}
#define CUKE_EMPTY_UPDATE(s) void PowerupCukeTutorialIntro::updateState_##s() {}
#define CUKE_EMPTY_EXIT(s) void PowerupCukeTutorialIntro::onExitState_##s(PowerupCukeTutorialState) {}

CUKE_EMPTY_UPDATE(Start)
CUKE_EMPTY_UPDATE(DaveProlog)
CUKE_EMPTY_UPDATE(ArrowAlert)
CUKE_EMPTY_UPDATE(Advice)
CUKE_EMPTY_UPDATE(Plantfood)
CUKE_EMPTY_UPDATE(PlantfoodEnd)
CUKE_EMPTY_UPDATE(Resume)
CUKE_EMPTY_EXIT(SpawnZombies)
CUKE_EMPTY_EXIT(Start)
CUKE_EMPTY_EXIT(DaveProlog)
CUKE_EMPTY_EXIT(ArrowAlert)
CUKE_EMPTY_EXIT(Advice)
CUKE_EMPTY_EXIT(Plantfood)
CUKE_EMPTY_EXIT(Resume)

/////////////// Small members ///////////////

void PowerupCukeTutorialIntro::onEnterState_Start(PowerupCukeTutorialState)
{
	enterTutorial();
}

void PowerupCukeTutorialIntro::onExitState_WaveTrigger(PowerupCukeTutorialState)
{
	m_waveTriggerTime = 0.0f;
}

void PowerupCukeTutorialIntro::drawLawnOverlays(Graphics* i_g)
{
	m_finger.Draw(i_g);
}

int32 PowerupCukeTutorialIntro::getPowerupCukeTutorialStateSerialization()
{
	return m_powerupCukeTutorialState.GetState();
}

bool PowerupCukeTutorialIntro::isInState(PowerupCukeTutorialState i_state) const
{
	return m_powerupCukeTutorialState.GetState() == i_state;
}

void PowerupCukeTutorialIntro::onEndOfAdvice()
{
	setState(POWERUPCUKETUTORIAL_Resume);
}

void PowerupCukeTutorialIntro::updateState_SpawnZombies()
{
	setState(POWERUPCUKETUTORIAL_DaveProlog);
}

void PowerupCukeTutorialIntro::onEnterState_SpawnZombies(PowerupCukeTutorialState)
{
	setupOpeningZombies();
}

void PowerupCukeTutorialIntro::setState(PowerupCukeTutorialState i_newState)
{
	StateDefinition<PowerupCukeTutorialState> newState =
		StateMachineTableBuilder::GetInstancePtr()->GetTable<PowerupCukeTutorialState>(GetClass())->GetStateDefinition(i_newState);
	newState.SetContext(this);
	m_powerupCukeTutorialState.SetState(newState);
}

void PowerupCukeTutorialIntro::onWaveStarted(int i_wave, WaveType::WaveType i_type, bool i_isFinal)
{
	if (isInState(POWERUPCUKETUTORIAL_Start) && i_wave == 4)
		setState(POWERUPCUKETUTORIAL_WaveTrigger);
}

static const std::string sPowerupName("poweruptacticalcuke");

void PowerupCukeTutorialIntro::update()
{
	if (m_powerupCukeTutorialState.GetState() != -1)
		m_powerupCukeTutorialState.UpdateState();
	m_animationMgr->Update();
}

void PowerupCukeTutorialIntro::startIntro()
{
	gLawnApp->m_board->PutIntoTutorialMode();
	setState(POWERUPCUKETUTORIAL_Plantfood);
}

void PowerupCukeTutorialIntro::enterTutorial()
{
	startStandardIntro(PAN_GAME_START_TO_BOARD_EDGE);
	PlayerInfo* profile = ProfileUtils::Profile();
	if (!profile->GetPowerupUnlockState(sPowerupName))
		return;
	profile->ModifyPowerupUses(sPowerupName, -1000000);
}

void PowerupCukeTutorialIntro::onEnterState_WaveTrigger(PowerupCukeTutorialState)
{
	m_waveTriggerTime = PVZ_T() + 2.0f;
}

void PowerupCukeTutorialIntro::onEndLevel()
{
	m_animationMgr->Clear();
	if (m_animationMgr.IsValid())
		((GameObject*)m_animationMgr.GetObject())->Destroy();
	m_animationMgr.ClearId();
	if (m_bouncingArrow.IsValid())
		((GameObject*)m_bouncingArrow.GetObject())->Destroy();
	m_bouncingArrow.ClearId();
}

void PowerupCukeTutorialIntro::initializeModule()
{
	StandardLevelIntro::initializeModule();
	m_animationMgr = AnimationMgr::Create()->GetPtr();
}

void PowerupCukeTutorialIntro::onPowerupDeactivated(BasePowerup* i_powerup)
{
	gMessageRouter->Unsubscribe(&Message::PowerupDeactivated, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onPowerupDeactivated));
	setState(POWERUPCUKETUTORIAL_Advice);
}

void PowerupCukeTutorialIntro::makeZombieRiseFromGround(Zombie* i_zombie)
{
	int minX = BoardTransforms::GridToBoardSpaceX(0);
	int maxX = BoardTransforms::GridToBoardSpaceX(8);
	int x = minX;
	if (maxX - minX > 0)
		x += Sexy::Rand(maxX - minX);
	SexyVector3 pos = i_zombie->GetPosition();
	pos.x = (float)x;
	i_zombie->RiseFromGround(pos, false);
}

void PowerupCukeTutorialIntro::onNarrationFinished()
{
	if (isInState(POWERUPCUKETUTORIAL_DaveProlog))
		setState(POWERUPCUKETUTORIAL_ArrowAlert);
	else if (isInState(POWERUPCUKETUTORIAL_Plantfood))
		setState(POWERUPCUKETUTORIAL_UsePlantfood);
	else if (isInState(POWERUPCUKETUTORIAL_PlantfoodEnd) && getProps<PowerupCukeTutorialIntroProperties>()->SkipCuke)
		setState(POWERUPCUKETUTORIAL_Start);
}

void PowerupCukeTutorialIntro::onLoadComplete()
{
	const PowerupCukeTutorialIntroProperties* props = getProps<PowerupCukeTutorialIntroProperties>();
	if (props->SkipIntro)
	{
		if (gLawnApp->m_board->GetLevel() == "egypt2" || gLawnApp->m_board->GetLevel() == "egypt6")
		{
			if (!ProfileUtils::HasCompletedCurrentNormalLevel())
				return;
			StandardLevelIntro::onLoadComplete();
		}
		return;
	}
	StandardLevelIntro::onLoadComplete();
}

void PowerupCukeTutorialIntro::onToolAppliedPlantFood(PlantGroup* i_plant)
{
	if (!isInState(POWERUPCUKETUTORIAL_UsePlantfood))
		return;
	if (m_plantPtr.IsValid())
		m_plantPtr->m_canAttack = true;
	m_finger.StopCurvingTutorialFinger();
	m_animationMgr->Clear();
	gLawnApp->m_board->ClearAdviceImmediately();
	m_bUsingPlantfood = true;
	gMessageRouter->Post(&Message::Toturi, TutorialType_PVE, Tutorial_user_plantfood_cabbagepult);
}

void PowerupCukeTutorialIntro::addToRenderQueue(RenderQueue* i_queue)
{
	m_animationMgr->AddToRenderQueue(i_queue);
	i_queue->Add(900001, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::drawLawnOverlays));
}

void PowerupCukeTutorialIntro::setPowerupCukeTutorialStateSerialization(int32 i_state)
{
	if (i_state >= 0)
	{
		StateDefinition<PowerupCukeTutorialState> newState =
			StateMachineTableBuilder::GetInstancePtr()->GetTable<PowerupCukeTutorialState>(GetClass())->GetStateDefinition((PowerupCukeTutorialState)i_state);
		newState.SetContext(this);
		m_powerupCukeTutorialState.SetStateNoTransition(newState);
	}
}

static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

void PowerupCukeTutorialIntro::onEnterState_Resume(PowerupCukeTutorialState)
{
	pauseWave(false);
	RtWeakPtr<UIWidget> pause = UIWidget::GetWidgetPtrBySheetName("UIPauseButton");
	if (pause)
		pause->SetVisible(true);
}

void PowerupCukeTutorialIntro::updateState_WaveTrigger()
{
	if (m_waveTriggerTime > 0.0f && m_waveTriggerTime < PVZ_T())
	{
		if (needCukeTutorial())
			pauseWave(true);
		PlayerInfo* profile = ProfileUtils::Profile();
		profile->SetGameFeatureUnlockState(FEATURE_POWERUP_TACTICALCUKE, true);
		profile->SetPowerupUnlockState(sPowerupName, true);
		if (needCukeTutorial())
			setState(POWERUPCUKETUTORIAL_DaveProlog);
	}
}

void PowerupCukeTutorialIntro::onShowCukeConfirm(bool show)
{
	if (isInState(POWERUPCUKETUTORIAL_ArrowAlert))
	{
		if (m_bouncingArrow.IsValid())
		{
			SexyVector2 origin = m_bouncingArrow->GetScreenSpaceOrigin();
			float d = (float)(show ? -UIScaleNum(70) : UIScaleNum(70));
			origin.y += d;
			m_bouncingArrow->SetScreenSpaceOrigin(origin, 900000);
		}
	}
}

void PowerupCukeTutorialIntro::onExitState_UsePlantfood(PowerupCukeTutorialState)
{
	m_animationMgr->Clear();
	gLawnApp->m_board->ClearAdviceImmediately();
}

void PowerupCukeTutorialIntro::onExitState_PlantfoodEnd(PowerupCukeTutorialState)
{
	m_animationMgr->Clear();
	gLawnApp->m_board->ClearAdviceImmediately();
	RtWeakPtr<UIWidget> pause = UIWidget::GetWidgetPtrBySheetName("UIPauseButton");
	if (pause)
		pause->SetClickable(true);
}

void PowerupCukeTutorialIntro::onEnterState_PlantfoodEnd(PowerupCukeTutorialState)
{
	gLawnApp->GetNarrationSystem()->StartNarrativeID(getProps<PowerupCukeTutorialIntroProperties>()->UsePlantfoodIntro, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onNarrationFinished));
}

void PowerupCukeTutorialIntro::setupOpeningZombies()
{
	for (int i = 0; i < 12; i++)
	{
		Board* board = gLawnApp->m_board;
		ZombiePtr zombie = board->AddZombieInRow(board->GetStage()->GetBasicZombieType(), Sexy::Rand(5), 0)->GetPtr();
		makeZombieRiseFromGround(zombie);
	}
}

void PowerupCukeTutorialIntro::introduceDave()
{
	gLawnApp->GetNarrationSystem()->StartNarrativeID("TACTICAL_CUKE_INTRO", Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onNarrationFinished));
}

void PowerupCukeTutorialIntro::onGameplayStarted()
{
	if (isInState(POWERUPCUKETUTORIAL_Start))
	{
		RtWeakPtr<UIWidget> holder = UIWidget::GetWidgetBySheetName("UIPowerupHolder")->GetPtr();
		holder->SetVisible(false);
	}
}

void PowerupCukeTutorialIntro::onCanApplyPlantfood(PlantGroup* i_plant, bool* o_isCan)
{
	std::vector<PlantPtr>::const_iterator end;
	std::vector<PlantPtr>::const_iterator it;
	if (isInState(POWERUPCUKETUTORIAL_UsePlantfood) && o_isCan)
	{
		if (i_plant)
		{
			it = i_plant->Plants().begin();
			end = i_plant->Plants().end();
			for (; it != end; ++it)
			{
				PlantPtr plant = *it;
				if (plant && m_plantPtr == plant->GetPtr())
				{
					*o_isCan = true;
					return;
				}
			}
		}
		*o_isCan = false;
	}
}

void PowerupCukeTutorialIntro::updateState_UsePlantfood()
{
	m_finger.Update();
	if (m_bUsingPlantfood && m_plantPtr.IsValid())
	{
		bool inPlantfood = m_plantPtr->IsInPlantFoodState();
		if (!inPlantfood)
		{
			RtWeakPtr<UIWidget> pause = UIWidget::GetWidgetPtrBySheetName("UIPauseButton");
			if (pause)
				pause->SetClickable(inPlantfood);
			setState(POWERUPCUKETUTORIAL_PlantfoodEnd);
		}
	}
}

void PowerupCukeTutorialIntro::pauseWave(bool bPause)
{
	UIWidget* plantfood = UIWidget::GetWidgetBySheetName("UIPlantfood");
	if (plantfood)
		plantfood->SetClickable(!bPause);
	gLawnApp->m_board->GetWaveManager()->SetPause(bPause);
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntities(entities, ENTITYTYPE_ZOMBIE | ENTITYTYPE_PLANT);
	for (std::vector<BoardEntity*>::iterator it = entities.begin(), end = entities.end(); it != end; ++it)
	{
		BoardEntity* entity = *it;
		if (entity->IsA<Plant>())
		{
			Plant* plant = entity->Cast<Plant>();
			if (bPause && plant->IsInPlantFoodState())
				plant->DisablePlantfoodAnimation();
			plant->m_canAttack = !bPause;
		}
		else if (entity->IsA<Zombie>())
		{
			Zombie* zombie = entity->Cast<Zombie>();
			if (!zombie->IsDying())
			{
				if (bPause)
					zombie->SetIdleState();
				else
					zombie->SetWalkingState();
			}
		}
	}
	SunDropperModule* sunDropper = gLawnApp->m_board->m_levelModuleManager->GetModuleByClass<SunDropperModule>();
	if (sunDropper)
		sunDropper->SetPaused(bPause);
	SeedBankNew* seedBank = gLawnApp->m_board->GetSeedBank();
	if (seedBank)
		seedBank->SetVisible(!bPause);
}

void PowerupCukeTutorialIntro::onEnterState_DaveProlog(PowerupCukeTutorialState)
{
	RtWeakPtr<UIWidget> pause = UIWidget::GetWidgetPtrBySheetName("UIPauseButton");
	if (pause)
		pause->SetVisible(false);
	m_animationMgr->ResetTime();
	pvztime_t time = m_animationMgr->GetTime();
	m_animationMgr->Add(TimeEvent::Create(GetPtr(), "introduceDave"), time + 1.0f);
}

void PowerupCukeTutorialIntro::onEnterState_Advice(PowerupCukeTutorialState)
{
	ShowAdvice* advice = ShowAdvice::Create(L"[TACTICAL_CUKE_ADVICE_AT_LAST]", (MessageStyle)7);
	TimeEvent* endEvent = TimeEvent::Create()->Init(GetPtr(), "onEndOfAdvice");
	m_animationMgr->ResetTime();
	pvztime_t time = m_animationMgr->GetTime();
	pvztime_t duration = advice->GetDuration();
	m_animationMgr->Add(advice, time);
	m_animationMgr->Add(endEvent, duration + time);
}

void PowerupCukeTutorialIntro::onEnterState_ArrowAlert(PowerupCukeTutorialState)
{
	ProfileUtils::Profile()->ModifyPowerupUses(sPowerupName, 3);
	pointArrowAtPowerupButton();
	gLawnApp->m_board->GetPowerupManager()->GetBasePowerup(ObjectTypeDirectory<PowerupType>::GetInstancePtr()->GetTypeFromTypeName(sPowerupName))->SetIgnoreCost(true);
}

void PowerupCukeTutorialIntro::onEnterState_Plantfood(PowerupCukeTutorialState)
{
	initBoardEntities();
	Plant* plant = gLawnApp->m_board->GetPlantAt(1, 2);
	if (plant)
		m_plantPtr = plant->GetPtr();
	RtWeakPtr<UIWidget> plantfood = UIWidget::GetWidgetPtrBySheetName("UIPlantfood");
	if (plantfood)
	{
		plantfood->SetVisible(true);
		plantfood->SetClickable(true);
		gLawnApp->m_board->SetPlantfoodCount(1);
	}
	gLawnApp->GetNarrationSystem()->StartNarrativeID(getProps<PowerupCukeTutorialIntroProperties>()->EatPlantfoodIntro, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onNarrationFinished));
}

static float ScaleNum(float i_val)
{
	return ((ScaledApp*)gSexyApp)->ScaleNum(i_val);
}

static SexyVector2 ToScreen(SexyVector3 i_position)
{
	return SexyVector2(i_position.x, i_position.y - i_position.z);
}

void PowerupCukeTutorialIntro::onEnterState_UsePlantfood(PowerupCukeTutorialState)
{
	m_animationMgr->Clear();
	m_animationMgr->ResetTime();
	pvztime_t time = m_animationMgr->GetTime();
	m_animationMgr->Add(ShowAdvice::Create(Sexy::UTF8StringToWString(getProps<PowerupCukeTutorialIntroProperties>()->PlantfoodAdvice), (MessageStyle)2), time);
	Sexy::Point boardOffset = gLawnApp->m_board->GetBoardBaseOffset();
	Rect drawRect = UIWidget::GetWidgetBySheetName("UIPlantfood")->GetDrawRect();
	SexyVector2 target = ToScreen(m_plantPtr->m_position) * ScaleNum(1.0f);
	Sexy::Point start(drawRect.GetCenter() - boardOffset);
	gLawnApp->m_board->TranslateScreenPositionToBoardPosition(start);
	m_finger.StartCurvingTutorialFinger();
	m_finger.SetCurvingTutorialFinger((float)(start.mX - UIScaleNum(15)), (float)start.mY, target.x, target.y, 1.0f);
}

static CachedResourcePtr<Sexy::Image> IMAGE_DOWNARROW("IMAGE_DOWNARROW");

void PowerupCukeTutorialIntro::pointArrowAtPowerupButton()
{
	gLawnApp->m_board->AddPowerup(sPowerupName);
	RtWeakPtr<UIWidget> holder = UIWidget::GetWidgetBySheetName("UIPowerupHolder")->GetPtr();
	holder->SetVisible(true);
	for (int i = 0; i < holder->GetChildCount(); i++)
	{
		RtWeakPtr<UIWidget> child = holder->GetChildId(i);
		if (static_cast<PowerupUI*>(child.operator->())->GetPowerupType()->TypeName == sPowerupName)
		{
			static_cast<PowerupTimeUI*>(child.operator->())->setTutorialIntroState(true);
			Rect drawRect = child->GetDrawRect();
			m_bouncingArrow = gLawnApp->m_board->AddEffect<Effect_BouncingArrow>()->GetPtr();
			m_bouncingArrow->SetArrowImage(IMAGE_DOWNARROW);
			m_bouncingArrow->SetVisibility(true);
			Sexy::Point pos(drawRect.mX + drawRect.mWidth / 2 - gLawnApp->m_board->mX, drawRect.mY - gLawnApp->m_board->mY);
			gLawnApp->m_board->TranslateScreenPositionToBoardPosition(pos);
			m_bouncingArrow->SetScreenSpaceOrigin(SexyVector2(pos.mX, pos.mY - UIScaleNum(40)), 900000);
		}
	}
}

void PowerupCukeTutorialIntro::onPowerupSelected(BasePowerup* i_powerup)
{
	RtWeakPtr<UIWidget> holder = UIWidget::GetWidgetBySheetName("UIPowerupHolder")->GetPtr();
	for (int i = 0; i < holder->GetChildCount(); i++)
	{
		RtWeakPtr<UIWidget> child = holder->GetChildId(i);
		if (static_cast<PowerupUI*>(child.operator->())->GetPowerupType()->TypeName == "poweruptacticalcuke")
			static_cast<PowerupTimeUI*>(child.operator->())->setTutorialIntroState(false);
	}
	gMessageRouter->Unsubscribe(&Message::PowerupSelected, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onPowerupSelected));
	gMessageRouter->Post(&Message::UseGemFinish, true);
	m_bouncingArrow->SetVisibility(false);
	gMessageRouter->Post(&Message::TutorialFTUE, egypt2_click_powerup_cuke);
	gMessageRouter->Post(&Message::Toturi, TutorialType_PVE, Tutorial_egypt2_click_powerup_cuke);
}

void PowerupCukeTutorialIntro::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupCukeTutorialIntro);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntro);

		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_NOARGS(onEndOfAdvice, onEndOfAdvice);
		REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_NOARGS(introduceDave, introduceDave);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<Effect_BouncingArrow>, m_bouncingArrow);
		REFLECTION_CLASSBUILDER_FIELD_UNSAFE(RtWeakPtr<RtObject>, m_animationMgr);
		REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_INSTANCE(int32, PowerupCukeTutorialState, getPowerupCukeTutorialStateSerialization, setPowerupCukeTutorialStateSerialization);
	REFLECTION_CLASSBUILDER_END(PowerupCukeTutorialIntro);

	STATEMACHINE_BUILDER_BEGIN(PowerupCukeTutorialState);
		STATEMACHINE_BUILDER_ADDSTATE(SpawnZombies, POWERUPCUKETUTORIAL_SpawnZombies);
		STATEMACHINE_BUILDER_ADDSTATE(DaveProlog, POWERUPCUKETUTORIAL_DaveProlog);
		STATEMACHINE_BUILDER_ADDSTATE(ArrowAlert, POWERUPCUKETUTORIAL_ArrowAlert);
		STATEMACHINE_BUILDER_ADDSTATE(Advice, POWERUPCUKETUTORIAL_Advice);
		STATEMACHINE_BUILDER_ADDSTATE(Plantfood, POWERUPCUKETUTORIAL_Plantfood);
		STATEMACHINE_BUILDER_ADDSTATE(UsePlantfood, POWERUPCUKETUTORIAL_UsePlantfood);
		STATEMACHINE_BUILDER_ADDSTATE(PlantfoodEnd, POWERUPCUKETUTORIAL_PlantfoodEnd);
		STATEMACHINE_BUILDER_ADDSTATE(Start, POWERUPCUKETUTORIAL_Start);
		STATEMACHINE_BUILDER_ADDSTATE(Resume, POWERUPCUKETUTORIAL_Resume);
		STATEMACHINE_BUILDER_ADDSTATE(WaveTrigger, POWERUPCUKETUTORIAL_WaveTrigger);
	STATEMACHINE_BUILDER_END();
}

void PowerupCukeTutorialIntro::registerForEvents()
{
	if (ProfileUtils::HasCompletedCurrentNormalLevel())
	{
		StandardLevelIntro::registerForEvents();
		return;
	}
	getManager()->RegisterHandlesIntro();
	getManager()->RegisterOnLoadComplete(Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onLoadComplete));
	getManager()->RegisterOnIntroStarted(Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::startIntro));
	getManager()->RegisterOnUpdate(Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::update));
	getManager()->RegisterOnLevelEnded(Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onEndLevel));
	getManager()->RegisterOnGameplayStarted(Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onGameplayStarted));
	getManager()->RegisterAddToRenderQueue(Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::addToRenderQueue));
	gMessageRouter->Subscribe(&Message::PowerupSelected, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onPowerupSelected));
	gMessageRouter->Subscribe(&Message::PowerupDeactivated, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onPowerupDeactivated));
	gMessageRouter->Subscribe(&Message::ShowCukeConfirm, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onShowCukeConfirm));
	gMessageRouter->Subscribe(&Message::WaveStarted, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onWaveStarted));
	gMessageRouter->Subscribe(&Message::CanApplyPlantfood, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onCanApplyPlantfood));
	gMessageRouter->Subscribe(&Message::ToolAppliedPlantfood, Sexy::MakeDelegate(*this, &PowerupCukeTutorialIntro::onToolAppliedPlantFood));
}
