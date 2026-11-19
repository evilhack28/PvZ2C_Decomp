//
//  DNodeWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DNodeWidget.h"
#include "LawnApp.h"

void DNodeWidget::Initialize()
{
}

void DNodeWidget::UserInit()
{
}

void DNodeWidget::debugBtn()
{
}

DNodeWidget::~DNodeWidget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DNodeWidget);

void DNodeWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DNodeWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Widget);

	REFLECTION_CLASSBUILDER_END(DNodeWidget);
}

void DNodeWidget::TouchBegan(const Sexy::Touch& touch)
{
	if (m_bTouchEnable)
		m_touchDispatcher.touchHandle(touch, DTOUCH_BEGAN);
}

void DNodeWidget::TouchMoved(const Sexy::Touch& touch)
{
	if (m_bTouchEnable)
		m_touchDispatcher.touchHandle(touch, DTOUCH_MOVED);
}

void DNodeWidget::TouchEnded(const Sexy::Touch& touch)
{
	if (m_bTouchEnable)
		m_touchDispatcher.touchHandle(touch, DTOUCH_ENDED);
}

void DNodeWidget::Draw(Sexy::Graphics* i_g)
{
	mainNode->visit(i_g);
}

DTransformNode* DNodeWidget::getChildByTag(int tag)
{
	return mainNode->getChildByTag(tag);
}

DTransformNode* DNodeWidget::getChildByName(const std::string& name)
{
	return mainNode->getChildByName(name);
}

void DNodeWidget::addChild(DTransformNode* child, int tag, int zOrder)
{
	mainNode->addChild(child, tag, zOrder);
}

void DNodeWidget::addChild(DTransformNode* child, int zOrder)
{
	mainNode->addChild(child, zOrder);
}

void DNodeWidget::addChild(DTransformNode* child)
{
	mainNode->addChild(child);
}

void DNodeWidget::removeAllChildren(bool cleanup)
{
	mainNode->removeAllChildren(cleanup);
}

void DNodeWidget::removeChild(DTransformNode* child, bool cleanup)
{
	mainNode->removeChild(child, cleanup);
}

void DNodeWidget::removeChildByTag(int tag, bool cleanup)
{
	mainNode->removeChildByTag(tag, cleanup);
}

void DNodeWidget::removeChildByName(const std::string& name, bool cleanup)
{
	mainNode->removeChildByName(name, cleanup);
}

void DNodeWidget::addToWidgetManager(bool focus)
{
	addToWidgetManager(focus, true);
}

void DNodeWidget::load(const std::string& configName, bool editorMode)
{
	mainNode->load(configName, editorMode);
}

void DNodeWidget::loadGroup(const std::string& name)
{
	mainNode->loadGroup(name);
}

void DNodeWidget::reload(const std::string& configName)
{
	removeAllChildren();
	mainNode->reload(configName);
	UserInit();
}

void DNodeWidget::reload()
{
	removeAllChildren();
	mainNode->reload();
	UserInit();
}

void DNodeWidget::addToWidgetManager(bool focus, bool bringToFront)
{
	gLawnApp->mWidgetManager->AddWidget(this);

	if (bringToFront)
		gLawnApp->mWidgetManager->BringToFront(this);

	if (focus)
		gLawnApp->mWidgetManager->SetFocus(this);
}

void DNodeWidget::TouchesCanceled()
{
	if (m_bTouchEnable)
	{
		Sexy::Touch touch;
		m_touchDispatcher.touchHandle(touch, DTOUCH_CANCELLED);
	}
}

void DNodeWidget::removeFromWidgetManager()
{
	gLawnApp->mWidgetManager->RemoveWidget(this);
	gLawnApp->SafeDeleteWidget(this);
	setTouchEnable(false);
}

DVec2 DNodeWidget::getWinSize()
{
	return DVec2(INV_UI_S((float)gLawnApp->mWidth), INV_UI_S((float)gLawnApp->mHeight));
}

void DNodeWidget::setRect(int x, int y, int w, int h)
{
	Resize(UI_S(x), UI_S(y), UI_S(w), UI_S(h));
	mainNode->setContentSize(DVec2(w, h));
	mainNode->setPosition(0, 0);
}

void DNodeWidget::setRect2(int x, int y, int w, int h)
{
	Resize(x, y, w, h);
	mainNode->setContentSize(DVec2(w, h));
	mainNode->setPosition(0, 0);
}

void DNodeWidget::OnGestureLongPress(Sexy::Point i_startingLocation)
{
	if (m_bTouchEnable)
	{
		Sexy::Touch touch;
		touch.event = NULL;
		touch.location.mY = i_startingLocation.mY;
		touch.ident = 0;
		touch.location.mX = i_startingLocation.mX;
		touch.previousLocation.mX = i_startingLocation.mX;
		touch.previousLocation.mY = i_startingLocation.mY;
		touch.tapCount = 1;
		touch.timestamp = 0;
		m_touchDispatcher.touchHandle(touch, DTOUCH_LONGPRESS);
	}
}

DNodeWidget::DNodeWidget()
{
	Resize(gLawnApp->mScreenBounds);
	mainNode->setContentSize(getWinSize());
	mainNode->setTouchDispatcher(&m_touchDispatcher);
}
