//
//  ChallengeZombieComboUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ChallengeZombieComboUI.h"

ChallengeZombieComboUI::~ChallengeZombieComboUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ChallengeZombieComboUI);

void ChallengeZombieComboUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ChallengeZombieComboUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ChallengeUI);

	REFLECTION_CLASSBUILDER_END(ChallengeZombieComboUI);
}
