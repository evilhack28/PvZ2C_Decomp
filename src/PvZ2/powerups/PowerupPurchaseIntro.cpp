//
//  PowerupPurchaseIntro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupPurchaseIntro.h"
#include "PvZ/Board.h"
#include "PvZ/LawnApp.h"
#include "PvZ/CrazyNPCManager.h"
#include "PvZ/ProfileUtils.h"

void PowerupPurchaseIntro::onLevelEnded()
{
}

PowerupPurchaseIntro::PowerupPurchaseIntro()
{
}

PowerupPurchaseIntro::~PowerupPurchaseIntro()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupPurchaseIntro);

void PowerupPurchaseIntro::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupPurchaseIntro);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntro);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_fadeStart);
	REFLECTION_CLASSBUILDER_END(PowerupPurchaseIntro);
}

void PowerupPurchaseIntro::initializeModule()
{
	StandardLevelIntro::initializeModule();
	m_inIntro = false;
}

bool PowerupPurchaseIntro::suppressReadySetGo() const
{
	return !ProfileUtils::HasCompletedCurrentNormalLevel();
}

void PowerupPurchaseIntro::onHijackedReadySetPlantFinished()
{
	gLawnApp->m_board->StartLevel();
}

void PowerupPurchaseIntro::onStandardIntroComplete()
{
	if (ProfileUtils::HasCompletedCurrentNormalLevel())
		StandardLevelIntro::onStandardIntroComplete();
	else
		begin();
}

void PowerupPurchaseIntro::registerForEvents()
{
	StandardLevelIntro::registerForEvents();
	if (!ProfileUtils::HasCompletedCurrentNormalLevel())
	{
		getManager()->RegisterOnLevelEnded(Sexy::MakeDelegate(*this, &PowerupPurchaseIntro::onLevelEnded));
		getManager()->RegisterAddToRenderQueue(Sexy::MakeDelegate(*this, &PowerupPurchaseIntro::addToRenderQueue));
	}
}

void PowerupPurchaseIntro::addToRenderQueue(RenderQueue* i_queue)
{
	if (m_inIntro)
	{
		int order = Board::MakeRenderOrder(RENDER_LAYER_FOG, 0, 0);
		i_queue->Add(order, Sexy::MakeDelegate(*this, &PowerupPurchaseIntro::onDraw));
	}
}

void PowerupPurchaseIntro::onDraw(Graphics* i_g)
{
	GraphicsAutoState state(i_g);
	float start = m_fadeStart;
	int from = m_fadeIn ? 0 : 127;
	int to = m_fadeIn ? 127 : 0;
	int alpha = CurveLerp<int>(start, start + 0.5f, PVZ_T(), from, to, CURVE_EASE_IN_OUT_WEAK);
	i_g->SetColor(Color(0, 0, 0, alpha));
	i_g->PushState();
	i_g->mTransX = 0;
	i_g->mTransY = 0;
	i_g->FillRect(gLawnApp->mScreenBounds);
	i_g->PopState();
	if (alpha == to && !m_fadeIn)
		m_inIntro = false;
}

void PowerupPurchaseIntro::onTutNarrationFinished()
{
	AnimationMgr* animMgr = gLawnApp->m_board->m_animationMgr;
	pvztime_t endTime = animMgr->GetTime();
	AddReadySetPlantToAnimMgr(animMgr, endTime, Sexy::MakeDelegate(*this, &PowerupPurchaseIntro::onHijackedReadySetPlantFinished), false);
	m_fadeIn = false;
	m_fadeStart = PVZ_T();
	UIWidget::GetWidgetBySheetName("UIPowerupHolder")->SetVisible(true);
	UIWidget* gemBank = UIWidget::GetWidgetBySheetName("UIGemBank");
	if (gemBank)
		gemBank->SetClickable(true);
	UIWidget* pause = UIWidget::GetWidgetBySheetName("UIPauseButton");
	if (pause)
		pause->SetClickable(true);
	UIWidget* speed = UIWidget::GetWidgetBySheetName("UIChangeSpeedButton");
	if (speed)
		speed->SetClickable(true);
}

void PowerupPurchaseIntro::begin()
{
	gLawnApp->m_board->PutIntoTutorialMode();
	ProfileMgr::GetInstance().GetCurrentProfile()->SetPowerupUnlockState("powerupwizardfinger", true);
	gLawnApp->m_board->AddPowerup("powerupwizardfinger");
	UIWidget::GetWidgetBySheetName("UIPowerupHolder")->SetVisible(false);
	UIWidget* gemBank = UIWidget::GetWidgetBySheetName("UIGemBank");
	if (gemBank)
	{
		gemBank->SetVisible(true);
		gemBank->SetClickable(false);
	}
	UIWidget* pause = UIWidget::GetWidgetBySheetName("UIPauseButton");
	if (pause)
		pause->SetClickable(false);
	UIWidget* speed = UIWidget::GetWidgetBySheetName("UIChangeSpeedButton");
	if (speed)
	{
		speed->SetVisible(true);
		speed->SetClickable(false);
	}
	gLawnApp->GetNarrationSystem()->StartNarrativeID(getProps<PowerupPurchaseIntroProperties>()->Narrative, Sexy::MakeDelegate(*this, &PowerupPurchaseIntro::onTutNarrationFinished));
	m_inIntro = true;
	m_fadeIn = true;
	m_fadeStart = PVZ_T();
}
