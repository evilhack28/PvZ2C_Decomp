//
//  PowerupTypeVaseBreakerButter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupVaseBreaker.h"

PowerupTypeVaseBreakerButter::PowerupTypeVaseBreakerButter()
{
}

PowerupTypeVaseBreakerButter::~PowerupTypeVaseBreakerButter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupTypeVaseBreakerButter);

void PowerupTypeVaseBreakerButter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupTypeVaseBreakerButter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PowerupType);

	REFLECTION_CLASSBUILDER_END(PowerupTypeVaseBreakerButter);
}
