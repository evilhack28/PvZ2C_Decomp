//
//  ZombieBullRider.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieBullRiderProps::~ZombieBullRiderProps()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieBullRiderProps);

void ZombieBullRiderProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBullRiderProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieBullRiderProps);
}
