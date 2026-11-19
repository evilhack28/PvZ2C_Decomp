//
//  PVZ2UIButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVZ2UIButton.h"

void PVZ2UIButton::MouseDown(int i_x, int i_y, int i_btnNum, int i_clickCount)
{
}

void PVZ2UIButton::SetFont(PrimeTypeface* theFont)
{
	ButtonWidget::SetFont(theFont);
}

void PVZ2UIButton::SetContentsRect(const Sexy::Rect& i_rect)
{
	m_contentsRect = i_rect;
}
