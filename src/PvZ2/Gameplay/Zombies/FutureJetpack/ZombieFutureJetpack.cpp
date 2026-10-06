//
//  ZombieFutureJetpack.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFutureJetpack.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieFutureJetpack);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieFutureJetpackProps);

void ZombieFutureJetpackProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieFutureJetpackProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(bool, DiscoMode);
	REFLECTION_CLASSBUILDER_END(ZombieFutureJetpackProps);
}
