//
//  PopingWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PopingWidget.h"

void PopingWidget::HideAllButtonAndAnims()
{
}

void PopingWidget::RecoverAllButtonAndAnims()
{
}

void PopingWidget::Draw(Graphics* i_g)
{
}

void PopingWidget::SetPopingTime(pvztime_t i_popingTime)
{
	m_popingTime = i_popingTime;
}

void PopingWidget::SetPopingScales(float i_start, float i_dest)
{
	m_destScale = i_dest;
	m_currentScale = i_start;
	m_startScale = i_start;
}
