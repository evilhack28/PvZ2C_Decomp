//
//  UIMessageBox.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "UIMessageBox.h"
#include "UIWidgetText.h"
#include "UIWidgetImage.h"

/////////////// Accessors ///////////////

void UIMessageBox::SetBackgroundDarken(bool hasBackgroundDarken, float backgroundAlphaPercent)
{
	m_hasBackgroundDarken = hasBackgroundDarken;
	m_backgroundAlphaPercent = backgroundAlphaPercent;
}

void UIMessageBox::SetTextFont(int idx)
{
	if (m_pText)
		m_pText->SetFontIndex(idx);
}

void UIMessageBox::SetBackground(Sexy::Image* pImage)
{
	if (m_pBackground)
		m_pBackground->SetImage(pImage);
}

void UIMessageBox::SetTextColor(Sexy::Color color)
{
	if (m_pText)
		m_pText->SetColor(0, color);
}
