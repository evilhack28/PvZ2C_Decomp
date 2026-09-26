//
//  GridItemShadowVanillaShadowEnergy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ShadowVanilla.h"

GridItemShadowVanillaShadowEnergy::~GridItemShadowVanillaShadowEnergy()
{
}

GridItemShadowVanillaShadowEnergyProps::~GridItemShadowVanillaShadowEnergyProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemShadowVanillaShadowEnergy);

void GridItemShadowVanillaShadowEnergy::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemShadowVanillaShadowEnergy);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, _startTime);
	REFLECTION_CLASSBUILDER_FIELD(int, _damage);
	REFLECTION_CLASSBUILDER_FIELD(float, _duration);

	REFLECTION_CLASSBUILDER_END(GridItemShadowVanillaShadowEnergy);
}
