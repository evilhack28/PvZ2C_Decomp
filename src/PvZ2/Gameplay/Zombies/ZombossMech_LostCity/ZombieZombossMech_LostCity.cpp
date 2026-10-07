//
//  ZombieZombossMech_LostCity.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_LostCity.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieZombossMechLostCityProps::ZombieZombossMechLostCityProps()
{
}

ZombieZombossMechLostCityProps::~ZombieZombossMechLostCityProps()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieZombossMechLostCityProps);

void ZombieZombossMechLostCityProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMechLostCityProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMechProps);

	REFLECTION_CLASSBUILDER_END(ZombieZombossMechLostCityProps);
}
