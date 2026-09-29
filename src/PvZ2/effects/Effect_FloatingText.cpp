//
//  Effect_FloatingText.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Effect_FloatingText.h"

Effect_FloatingText::~Effect_FloatingText()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_FloatingText);

void Effect_FloatingText::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_FloatingText);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

		REFLECTION_CLASSBUILDER_FIELD(SexyString, m_text);
		REFLECTION_CLASSBUILDER_FIELD(Color, m_color);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_paragraphSize);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_style);
	REFLECTION_CLASSBUILDER_END(Effect_FloatingText);
}
