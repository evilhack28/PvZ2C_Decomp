//
//  ChallengePlantCounterUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ChallengePlantCounterUI.h"

ChallengePlantCounterUI::~ChallengePlantCounterUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ChallengePlantCounterUI);

void ChallengePlantCounterUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ChallengePlantCounterUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ChallengeUI);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_IsOneCount);

	REFLECTION_CLASSBUILDER_END(ChallengePlantCounterUI);
}

void ChallengePlantCounterUI::SetIsOneCount(bool i_arg)
{
	m_IsOneCount = i_arg;
}

void ChallengePlantCounterUI::SetCount(int i_arg)
{
	m_count = i_arg;
}

void ChallengePlantCounterUI::SetTarget(int i_arg)
{
	m_target = i_arg;
}
