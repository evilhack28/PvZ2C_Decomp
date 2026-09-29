//
//  ZombiePirateSeagull.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePirateSeagull.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePirateSeagull);

void ZombiePirateSeagull::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePirateSeagull);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

	REFLECTION_CLASSBUILDER_END(ZombiePirateSeagull);
}
