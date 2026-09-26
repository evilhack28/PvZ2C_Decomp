//
//  ZombieAnimRig_TutorialSummer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Tutorial.h"

ZombieAnimRig_TutorialSummer::ZombieAnimRig_TutorialSummer()
{
}

ZombieAnimRig_TutorialSummer::~ZombieAnimRig_TutorialSummer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_TutorialSummer);

void ZombieAnimRig_TutorialSummer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_TutorialSummer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Tutorial);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_TutorialSummer);
}
