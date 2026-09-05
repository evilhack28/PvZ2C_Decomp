//
//  UIScrollWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "UIScrollWidget.h"

/////////////// UIScrollWidget ///////////////

UIScrollWidget::UIScrollWidget(Sexy::ScrollWidgetListener* i_listener)
	: PVZ2UIScrollingWidget(i_listener)
{
}

UIScrollWidget::~UIScrollWidget()
{
}

Sexy::FPoint UIScrollWidget::GetScrollVelocity()
{
	return mScrollVelocity;
}
