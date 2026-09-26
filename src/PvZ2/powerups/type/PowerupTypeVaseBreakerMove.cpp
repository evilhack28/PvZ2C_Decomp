//
//  PowerupTypeVaseBreakerMove.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupVaseBreaker.h"

PowerupTypeVaseBreakerMove::PowerupTypeVaseBreakerMove()
{
}

PowerupTypeVaseBreakerMove::~PowerupTypeVaseBreakerMove()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupTypeVaseBreakerMove);

void PowerupTypeVaseBreakerMove::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupTypeVaseBreakerMove);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PowerupType);

	REFLECTION_CLASSBUILDER_END(PowerupTypeVaseBreakerMove);
}
