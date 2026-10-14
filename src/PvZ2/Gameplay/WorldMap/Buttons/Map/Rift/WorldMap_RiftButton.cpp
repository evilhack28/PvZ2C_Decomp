//
//  WorldMap_RiftButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_RiftButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_RiftButton);

void WorldMap_RiftButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_RiftButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_RiftButton);
}

#include "WorldMap_RiftButton.h"
void WorldMap_RiftButton::onWorldLoaded()
{
	 WorldMap_RiftButton::CheckActivated();
}

void WorldMap_RiftButton::onNetworkError(int erroId)
{
}
