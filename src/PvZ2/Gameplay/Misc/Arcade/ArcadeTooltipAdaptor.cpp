//
//  ArcadeTooltipAdaptor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ArcadeTooltipAdaptor.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArcadeTooltipAdaptor);

void ArcadeTooltipAdaptor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArcadeTooltipAdaptor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(ArcadeTooltipAdaptor);
}

#include "HotUIAdaptor.h"
void ArcadeTooltipAdaptor::onAnyTouch()
{
	 HotUIAdaptor::RemoveAndDeleteWidget();
}

/////////////// Lifecycle ///////////////
static int s_tooltipCount;

int ArcadeTooltipAdaptor::GetGlobalTooltipCount()
{
	return s_tooltipCount;
}

ArcadeTooltipAdaptor::ArcadeTooltipAdaptor()
{
	s_tooltipCount++;
}

ArcadeTooltipAdaptor::~ArcadeTooltipAdaptor()
{
	s_tooltipCount--;
}

void ArcadeTooltipAdaptor::SetTitle(const SexyString& i_titleText)
{
	m_titleText = i_titleText;
}

void ArcadeTooltipAdaptor::SetDescription(const SexyString& i_bodyText)
{
	m_bodyText = i_bodyText;
}

void ArcadeTooltipAdaptor::SetTarget(Sexy::Widget* i_targetWidget)
{
	Sexy::Point pos = i_targetWidget->GetAbsPos();
	m_targetRect = i_targetWidget->GetRect();
	m_targetRect.mX = pos.mX;
	m_targetRect.mY = pos.mY;
}

std::string ArcadeTooltipAdaptor::getUIFileName()
{
	return "ArcadeTooltip";
}

#include "HotUIManager.h"
#include "HotUILabel.h"
void ArcadeTooltipAdaptor::onLoadUIView()
{
	HotUIStringMap overrides;
	HotUIFile* file = HotUIManager::GetInstance().LoadUIFile(getUIFileName(), overrides);
	addLinkToUIFile(file);
}

void ArcadeTooltipAdaptor::refreshLabels()
{
	HotUIFile* file = getUIFile();
	HotUILabel* title = file->GetWidgetByName<HotUILabel>("Title");
	title->SetText(m_titleText);
	HotUILabel* body = file->GetWidgetByName<HotUILabel>("Body");
	body->SetText(m_bodyText);
}

#include "ScaledApp.h"
void ArcadeTooltipAdaptor::placeTooltip()
{
	HotUIFile* file = getUIFile();
	HotUIWidget* touchLayer = file->GetWidgetByName("TouchLayer");
	HotUIWidget* tooltip = file->GetWidgetByName("Tooltip");
	HotUIWidget* upCaret = file->GetWidgetByName("UpCaret");
	HotUIWidget* downCaret = file->GetWidgetByName("DownCaret");

	bool below = m_targetRect.mY >= touchLayer->mHeight - (m_targetRect.mY + m_targetRect.mHeight);
	upCaret->SetVisible(!below);
	downCaret->SetVisible(below);

	int x = m_targetRect.mX + m_targetRect.mWidth / 2 - tooltip->mWidth / 2;
	int y;
	if (below)
		y = (int)((float)(m_targetRect.mY - tooltip->mHeight) - UI_S(10.0f));
	else
		y = (int)(UI_S(10.0f) + (float)(m_targetRect.mY + m_targetRect.mHeight));
	tooltip->Move(x, y);
}

void ArcadeTooltipAdaptor::onLinkToUIViewCreated()
{
	HotUIFile* file = getUIFile();
	file->GetWidgetByName<HotUITouchLayer>("TouchLayer")->AddTouchBeganListener(Sexy::MakeDelegate(this, &ArcadeTooltipAdaptor::onAnyTouch));
	placeTooltip();
	refreshLabels();
}
