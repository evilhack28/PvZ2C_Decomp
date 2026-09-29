//
//  ZombieNeuropathy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieNeuropathy.h"

ZombieNeuropathyProps::ZombieNeuropathyProps()
{
}

ZombieNeuropathyProps::~ZombieNeuropathyProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieNeuropathy);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieNeuropathyProps);

void ZombieNeuropathyProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieNeuropathyProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieNeuropathyProps);
}
