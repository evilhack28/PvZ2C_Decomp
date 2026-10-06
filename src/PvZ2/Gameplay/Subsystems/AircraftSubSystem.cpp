//
//  AircraftSubSystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AircraftSubSystem.h"

void AircraftSubSystem::Update()
{
}

AircraftSubSystem::AircraftSubSystem()
{
}

AircraftSubSystem::~AircraftSubSystem()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AircraftSubSystem);

void AircraftSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AircraftSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

	REFLECTION_CLASSBUILDER_END(AircraftSubSystem);
}

void AircraftSubSystem::registerForEvents()
{
}

void AircraftSubSystem::onAircraftUpMoveDone(BoardEntity * i_arg)
{
}

void AircraftSubSystem::onAircraftDownMoveDone(BoardEntity * i_arg)
{
}
