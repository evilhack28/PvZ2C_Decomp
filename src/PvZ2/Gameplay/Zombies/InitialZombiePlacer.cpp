//
//  InitialZombiePlacer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "InitialZombiePlacer.h"

InitialZombiePlacer::InitialZombiePlacer()
{
}

InitialZombiePlacer::~InitialZombiePlacer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(InitialZombiePlacer);

void InitialZombiePlacer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(InitialZombiePlacer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(InitialZombiePlacer);
}
