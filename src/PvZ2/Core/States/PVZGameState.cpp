//
//  PVZGameState.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PVZGameState.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT_ABSTRACT(PVZGameState);

PVZGameState::PVZGameState()
{
}

PVZGameState::~PVZGameState()
{
}

/////////////// Reflection ///////////////

void PVZGameState::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZGameState);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

	REFLECTION_CLASSBUILDER_END(PVZGameState);
}
