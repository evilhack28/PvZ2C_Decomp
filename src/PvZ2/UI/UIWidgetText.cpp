//
//  UIWidgetText.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "UIWidgetText.h"
#include "StringHelper.h"

void UIWidgetText::Update()
{
}

UIWidgetText::~UIWidgetText()
{
}

void UIWidgetText::SetFontIndex(int idx)
{
	SetFont(StringHelper::ToFont(idx));
}
