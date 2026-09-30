//
//  WorldMap_AcFirstRechargeButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_AcFirstRechargeButton.h"

void WorldMap_AcFirstRechargeButton::BackToMap()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_AcFirstRechargeButton);

void WorldMap_AcFirstRechargeButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_AcFirstRechargeButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_AcFirstRechargeButton);
}

#include "WorldMap_AcFirstRechargeButton.h"
void WorldMap_AcFirstRechargeButton::onWorldLoaded()
{
	 WorldMap_AcFirstRechargeButton::CheckActivated();
}

void WorldMap_AcFirstRechargeButton::OnNotyFirstRechargeSuc(bool i_arg)
{
}
