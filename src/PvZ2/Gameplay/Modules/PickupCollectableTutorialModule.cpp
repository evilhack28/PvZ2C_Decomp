//
//  PickupCollectableTutorialModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PickupCollectableTutorialModule.h"

PickupCollectableTutorialModule::PickupCollectableTutorialModule()
{
}

PickupCollectableTutorialModule::~PickupCollectableTutorialModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PickupCollectableTutorialModule);

void PickupCollectableTutorialModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PickupCollectableTutorialModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(PickupCollectableTutorialModule);
}
