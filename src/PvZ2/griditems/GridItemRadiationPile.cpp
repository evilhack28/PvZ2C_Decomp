//
//  GridItemRadiationPile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_NukeLauncher.h"

GridItemRadiationPile::~GridItemRadiationPile()
{
}

GridItemRadiationPileProps::~GridItemRadiationPileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRadiationPile);

void GridItemRadiationPile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRadiationPile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(GridItemRadiationPile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRadiationPileProps);

void GridItemRadiationPileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRadiationPileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
	REFLECTION_CLASSBUILDER_END(GridItemRadiationPileProps);
}
