//
//  WorldMap_RiftStoreButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_RiftStoreButton.h"

WorldMap_RiftStoreButton::~WorldMap_RiftStoreButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_RiftStoreButton);

void WorldMap_RiftStoreButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_RiftStoreButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_RiftStoreButton);
}
