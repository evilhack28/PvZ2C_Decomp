//
//  UITest.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "UITest.h"

/////////////// UITest ///////////////

UITest::UITest()
{
}

UITest::~UITest()
{
}

bool UITest::OnCreate()
{
	base_type::OnCreate();
	return true;
}

std::string UITest::GetLayoutName()
{
	return "uitest";
}

void UITest::Draw(Sexy::Graphics* i_g)
{
	base_type::Draw(i_g);
}

void UITest::ButtonDepress(int i_id)
{
}
