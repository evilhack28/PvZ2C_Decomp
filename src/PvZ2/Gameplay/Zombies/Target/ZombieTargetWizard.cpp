//
//  ZombieTargetWizard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieTargetWizard.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieTargetWizard);

void ZombieTargetWizard::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieTargetWizard);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieTarget);

	REFLECTION_CLASSBUILDER_END(ZombieTargetWizard);
}
