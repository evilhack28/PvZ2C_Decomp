//
//  ZombieBallet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBallet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBallet);

void ZombieBalletProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBalletProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, BalletSegmentOffset);
	REFLECTION_CLASSBUILDER_END(ZombieBalletProps);
}
