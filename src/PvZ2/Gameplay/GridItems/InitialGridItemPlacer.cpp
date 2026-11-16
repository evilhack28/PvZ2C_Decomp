//
//  InitialGridItemPlacer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "InitialGridItemPlacer.h"

InitialGridItemPlacer::InitialGridItemPlacer()
{
}

InitialGridItemPlacer::~InitialGridItemPlacer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(InitialGridItemPlacer);

void InitialGridItemPlacer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(InitialGridItemPlacer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(InitialGridItemPlacer);
}
