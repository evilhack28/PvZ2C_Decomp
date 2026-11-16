//
//  ZombieTargetArchmage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieTargetArchmage.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieTargetArchmage);

void ZombieTargetArchmage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieTargetArchmage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieTarget);

	REFLECTION_CLASSBUILDER_END(ZombieTargetArchmage);
}
