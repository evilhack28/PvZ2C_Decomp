//
//  Effect_ChallengeFailedMessage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Effect_ChallengeFailedMessage.h"

Effect_ChallengeFailedMessage::Effect_ChallengeFailedMessage()
{
}

Effect_ChallengeFailedMessage::~Effect_ChallengeFailedMessage()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_ChallengeFailedMessage);

void Effect_ChallengeFailedMessage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_ChallengeFailedMessage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

		REFLECTION_CLASSBUILDER_FIELD(SexyString, m_message);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_spawnTime);
	REFLECTION_CLASSBUILDER_END(Effect_ChallengeFailedMessage);
}
