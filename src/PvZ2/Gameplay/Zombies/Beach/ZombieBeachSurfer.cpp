//
//  ZombieBeachSurfer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBeachSurfer.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBeachSurfer);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBeachSurferProps);

void ZombieBeachSurferProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBeachSurferProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, BlocksSurfboard);
	REFLECTION_CLASSBUILDER_END(ZombieBeachSurferProps);
}
