//
//  ZombieLostCityLostPilot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityLostPilot.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieLostCityLostPilot);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieLostCityLostPilotProps);

void ZombieLostCityLostPilotProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieLostCityLostPilotProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(int, HangingAttackRectOffsetY);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, HangingNoEatTimeUntilDrop);
	REFLECTION_CLASSBUILDER_END(ZombieLostCityLostPilotProps);
}

#include "ZombieWithActions.h"
void ZombieLostCityLostPilot::onZombieInitialize()
{
	 ZombieWithActions::onZombieInitialize();
}

#include "ZombieLostCityLostPilot.h"
void ZombieLostCityLostPilot::onExternalControlEvent()
{
	 ZombieLostCityLostPilot::immediatelyCutDown();
}
