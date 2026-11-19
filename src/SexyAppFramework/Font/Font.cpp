//
//  Font.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "Font.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT_ABSTRACT(Font);

void Font::DrawString(Graphics* i_arg0, int i_arg1, int i_arg2, const SexyString& i_arg3, const Color& i_arg4, const Rect& i_arg5)
{
}

int Font::StringWidth(const SexyString& i_arg)
{
	return false;
}

void Font::DrawString_Typesetter(Sexy::Graphics* i_arg0, EA::Text::Typesetter& i_arg1, float i_arg2, bool i_arg3)
{
}
