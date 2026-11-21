//
//  PVZ2UIScrollingPaneWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "PVZ2UIButton.h"
#include "ReflectionBuilder.h"
#include "LawnApp.h"

/////////////// Lifecycle ///////////////

PVZ2UIScrollingPaneWidget::PVZ2UIScrollingPaneWidget(const Sexy::Rect& i_rect, Sexy::Widget* i_parentWidget, Sexy::Widget* i_firstWidget)
{
	m_parentWidget = i_parentWidget;
	Resize(i_rect);
	if (i_firstWidget != NULL)
		m_widgetPanes.push_back(i_firstWidget);
	else
		SetVisible(false);
	m_scrollingState = SCROLLING_NONE;
	m_scrollTimeline.Initialize(0.0f);
	m_drawDarkeningLayerBehind = false;
}

/////////////// Logic ///////////////

bool PVZ2UIScrollingPaneWidget::onlyWidgetPaneLeftIsInvisible()
{
	return m_widgetPanes.size() == 1 && !m_widgetPanes.back()->mVisible;
}

void PVZ2UIScrollingPaneWidget::deleteRightWidget()
{
	Sexy::Widget* aWidget = m_widgetPanes.back();
	RemoveWidget(aWidget);
	delete aWidget;
	m_widgetPanes.pop_back();
}

void PVZ2UIScrollingPaneWidget::Close()
{
	if (m_widgetPanes.empty() || onlyWidgetPaneLeftIsInvisible())
		return;

	int aDepth = GetDepth();
	for (int i = 1; i < aDepth; ++i)
		deleteRightWidget();

	m_scrollingState = SCROLLING_NONE;
	removeAndHide();
}

void PVZ2UIScrollingPaneWidget::removeAndHide()
{
	m_widgetPanes.back()->SetVisible(false);
	gLawnApp->mWidgetManager->RemoveBaseModal(this);
	gLawnApp->mWidgetManager->SetFocus(m_parentWidget);
	SetVisible(false);
}

void PVZ2UIScrollingPaneWidget::ScrollLeft()
{
	if (!m_widgetPanes.empty())
	{
		if (m_widgetPanes.size() == 1)
			removeAndHide();
		else
		{
			const float aStart = 0.0f;
			m_scrollTimeline.Initialize(aStart);
			m_scrollTimeline.AddKeyFrame(PVZ_RealT(), aStart, CURVE_EASE_IN_OUT);
			m_scrollTimeline.AddKeyFrame(PVZ_RealT() + 0.2f, 1.0f, CURVE_EASE_IN_OUT);
			m_scrollingState = SCROLLING_LEFT;
			m_widgetPanes.back()->SetIgnoreMouseInput(true);
			m_widgetPanes[m_widgetPanes.size() - 2]->SetIgnoreMouseInput(true);
		}
	}
}

void PVZ2UIScrollingPaneWidget::ScrollRight(Sexy::Widget* i_scrollingToWidget)
{
	if (m_widgetPanes.empty())
	{
		SetVisible(true);
		gLawnApp->mWidgetManager->AddBaseModal(this);
	}

	if (m_widgetPanes.size() != 0)
	{
		m_widgetPanes.back()->SetIgnoreMouseInput(true);
		i_scrollingToWidget->SetIgnoreMouseInput(true);
		const float aStart = 0.0f;
		m_scrollTimeline.Initialize(aStart);
		m_scrollTimeline.AddKeyFrame(PVZ_RealT(), aStart, CURVE_EASE_IN_OUT);
		m_scrollTimeline.AddKeyFrame(PVZ_RealT() + 0.2f, -1.0f, CURVE_EASE_IN_OUT);
		m_scrollingState = SCROLLING_RIGHT;
		i_scrollingToWidget->Move(m_widgetPanes.back()->mX + m_widgetPanes.back()->mWidth, 0);
	}

	m_widgetPanes.push_back(i_scrollingToWidget);
	AddWidget(i_scrollingToWidget);
	if (m_widgetPanes.size() == 1)
		i_scrollingToWidget->SetIgnoreMouseInput(false);
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PVZ2UIScrollingPaneWidget);

void PVZ2UIScrollingPaneWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ2UIScrollingPaneWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::Widget);

	REFLECTION_CLASSBUILDER_END(PVZ2UIScrollingPaneWidget);
}

PVZ2UIScrollingPaneWidget::~PVZ2UIScrollingPaneWidget()
{
	RemoveAllWidgets(true, true);
}
