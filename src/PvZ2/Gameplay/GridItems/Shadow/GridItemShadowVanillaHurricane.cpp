//
//  GridItemShadowVanillaHurricane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ShadowVanilla.h"

GridItemShadowVanillaHurricane::~GridItemShadowVanillaHurricane()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemShadowVanillaHurricane);

void GridItemShadowVanillaHurricane::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemShadowVanillaHurricane);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, _startTime);
	REFLECTION_CLASSBUILDER_FIELD(int, _damage);
	REFLECTION_CLASSBUILDER_FIELD(float, _duration);
	REFLECTION_CLASSBUILDER_FIELD(bool, _shouldCreateShadowEnergy);

	REFLECTION_CLASSBUILDER_END(GridItemShadowVanillaHurricane);
}
