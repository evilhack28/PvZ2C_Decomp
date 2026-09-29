//
//  WorldMap_PlantSpecialOfferUIButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_PlantSpecialOfferUIButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_PlantSpecialOfferUIButton);

void WorldMap_PlantSpecialOfferUIButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_PlantSpecialOfferUIButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_PlantSpecialOfferUIButton);
}

#include "WorldMap_PlantSpecialOfferUIButton.h"
void WorldMap_PlantSpecialOfferUIButton::onWorldLoaded()
{
	 WorldMap_PlantSpecialOfferUIButton::CheckActivated();
}

void WorldMap_PlantSpecialOfferUIButton::onUpdate()
{
}
