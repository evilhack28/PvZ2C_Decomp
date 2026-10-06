//
//  ZombieLostCityGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityGargantuar.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieLostCityGargantuar);

void ZombieLostCityGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieLostCityGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuar);

	REFLECTION_CLASSBUILDER_END(ZombieLostCityGargantuar);
}
