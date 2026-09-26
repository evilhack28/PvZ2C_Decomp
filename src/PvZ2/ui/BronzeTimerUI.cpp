//
//  BronzeTimerUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BronzeTimerUI.h"

BronzeTimerUI::~BronzeTimerUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BronzeTimerUI);

void BronzeTimerUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BronzeTimerUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ChallengeUI);

	REFLECTION_CLASSBUILDER_FIELD(int, m_seconds);

	REFLECTION_CLASSBUILDER_END(BronzeTimerUI);
}

void BronzeTimerUI::SetSeconds(int i_arg)
{
	m_seconds = i_arg;
}
