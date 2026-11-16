//
//  PVZGameStateTopHUDController.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "PvZ/PVZGameStateTopHUDController.h"
#include "PvZ/GameEventMgr.h"
#include "PvZ/GameStateMgr.h"
#include "PvZ/LawnApp.h"
#include "PvZ/RenderQueue.h"
#include "PvZ/UIWidget.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/Graphics.h"

/////////////// Construction ///////////////

PVZGameStateTopHUDController::PVZGameStateTopHUDController()
{
	m_fOffset = 0;
	m_hideRequestCount = 0;
	m_loadComplete = false;
	gMessageRouter->Subscribe(Message::HideTopHUD, Sexy::MakeDelegate(*this, &PVZGameStateTopHUDController::onHideTopHUD));
	gMessageRouter->Subscribe(Message::ShowTopHUD, Sexy::MakeDelegate(*this, &PVZGameStateTopHUDController::onShowTopHUD));
}

PVZGameStateTopHUDController::~PVZGameStateTopHUDController()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Class ///////////////

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT_ABSTRACT(PVZGameStateTopHUDController);

void PVZGameStateTopHUDController::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZGameStateTopHUDController);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::Widget);

	REFLECTION_CLASSBUILDER_END(PVZGameStateTopHUDController);
}

/////////////// Accessors ///////////////

bool PVZGameStateTopHUDController::IsLoaded()
{
	return m_loadComplete;
}

void PVZGameStateTopHUDController::setOffset(int offset)
{
	m_fOffset = offset;
}

bool PVZGameStateTopHUDController::isHidden() const
{
	return m_hideRequestCount > 0;
}

void PVZGameStateTopHUDController::onHideTopHUD()
{
	m_hideRequestCount++;
}

void PVZGameStateTopHUDController::onShowTopHUD()
{
	m_hideRequestCount--;
}

bool PVZGameStateTopHUDController::canHandleInput() const
{
	if (!m_loadComplete)
		return false;
	if (gGameStateMgr->IsTransitioning())
		return false;
	return !isHidden();
}

/////////////// Widget ///////////////

void PVZGameStateTopHUDController::Update()
{
	if (!m_loadComplete && UIWidget::IsLoadCompleteForAllWidgets())
		m_loadComplete = true;
	UIWidget::UpdateUI();
	Sexy::Widget::Update();
}

void PVZGameStateTopHUDController::Draw(Sexy::Graphics* i_g)
{
	if (m_loadComplete && m_hideRequestCount <= 0)
	{
		RenderQueue queue(1000);
		UIWidget::AddToRenderQueueForAllWidgets(&queue);
		const std::vector<RenderItem>& items = queue.GetSortedQueue();
		std::vector<RenderItem>::const_iterator it = items.begin();
		std::vector<RenderItem>::const_iterator end = items.end();
		for (; it != end; ++it)
		{
			const RenderItem& item = *it;
			Sexy::GraphicsAutoState state(i_g);
			item.m_renderDelegate(i_g);
		}
	}
}

void PVZGameStateTopHUDController::TouchBegan(const Sexy::Touch& touch)
{
	if (canHandleInput())
		UIWidget::ProcessedMouseDown(touch.location.mX + m_fOffset, touch.location.mY, 200 - 256);
}

void PVZGameStateTopHUDController::TouchMoved(const Sexy::Touch& touch)
{
	if (canHandleInput())
		UIWidget::ProcessedMouseMove(touch.location.mX + m_fOffset, touch.location.mY, 200 - 256);
}

void PVZGameStateTopHUDController::TouchEnded(const Sexy::Touch& touch)
{
	if (canHandleInput())
		UIWidget::ProcessedMouseUp(touch.location.mX + m_fOffset, touch.location.mY, 200 - 256);
}

void PVZGameStateTopHUDController::TouchesCanceled()
{
	if (canHandleInput())
		UIWidget::ProcessedMouseUp(-100, -100, 0);
}
