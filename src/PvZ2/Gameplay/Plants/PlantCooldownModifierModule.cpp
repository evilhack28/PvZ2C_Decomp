//
//  PlantCooldownModifierModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "PlantCooldownModifierModule.h"
#include "PlantType.h"

/////////////// PlantCooldownModifierModule ///////////////

RT_CLASS_IMPLEMENT(PlantCooldownModifierModule);

float PlantCooldownModifierModule::GetCooldownMultiplier(PlantTypePtr plantType)
{
	const PlantCooldownModifierProperties* props = getProps<PlantCooldownModifierProperties>();
	if (plantType->HomeWorld != "")
	{
		return 1.0f;
	}

	return props->CooldownMultiplier;
}
