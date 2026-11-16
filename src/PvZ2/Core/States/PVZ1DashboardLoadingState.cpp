//
//  PVZ1DashboardLoadingState.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PVZ1DashboardLoadingState.h"

PVZ1DashboardLoadingState::PVZ1DashboardLoadingState()
{
}

PVZ1DashboardLoadingState::~PVZ1DashboardLoadingState()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZ1DashboardLoadingState);

void PVZ1DashboardLoadingState::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ1DashboardLoadingState);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZGameState);

	REFLECTION_CLASSBUILDER_END(PVZ1DashboardLoadingState);
}
