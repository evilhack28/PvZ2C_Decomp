//
//  MoldColonyChallenge.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "MoldColonyChallenge.h"

MoldColonyChallenge::~MoldColonyChallenge()
{
}

MoldColonyChallengeProps::MoldColonyChallengeProps()
{
}

MoldColonyChallengeProps::~MoldColonyChallengeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MoldColonyChallenge);

void MoldColonyChallenge::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BoundMold);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, Owner);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, Mold);
	REFLECTION_CLASSBUILDER_END(BoundMold);

	REFLECTION_CLASSBUILDER_BEGIN(MoldColonyChallenge);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

		REFLECTION_CLASSBUILDER_FIELD(int, m_moldState);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Effect_PopAnim> >, m_mold);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<BoundMold>, m_boundMold);
	REFLECTION_CLASSBUILDER_END(MoldColonyChallenge);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MoldColonyChallengeProps);

void MoldColonyChallengeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MoldColonyChallengeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardGridMapProps>, Locations);
	REFLECTION_CLASSBUILDER_END(MoldColonyChallengeProps);
}
