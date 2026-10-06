//
//  ZombieMonkImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMonkImp.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMonkImp);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMonkImpProps);

void ZombieMonkImpProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMonkImpProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, FlySpeedByGrid);
	REFLECTION_CLASSBUILDER_END(ZombieMonkImpProps);
}

float ZombieMonkImp::GetAmberScale()
{
	return 0.53f;
}

