//
//  JoustDashboardLoadingState.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "JoustDashboardLoadingState.h"

JoustDashboardLoadingState::JoustDashboardLoadingState()
{
	m_firstUpdate = 0;
}

JoustDashboardLoadingState::~JoustDashboardLoadingState()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustDashboardLoadingState);

void JoustDashboardLoadingState::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustDashboardLoadingState);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZGameState);

	REFLECTION_CLASSBUILDER_END(JoustDashboardLoadingState);
}

#include "JoustDashboardLoadingState.h"
void JoustDashboardLoadingState::sendNextInitRequest()
{
	 JoustDashboardLoadingState::checkCurrentDashboardInfo();
}
