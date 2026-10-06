//
//  GridItemSmokeManhole.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SmokeManhole.h"

GridItemSmokeManholeProps::~GridItemSmokeManholeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSmokeManhole);

void GridItemSmokeManhole::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSmokeManhole);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_state);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_SmokeManhole>, m_manholeRig);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_SmokePollution>, m_smokeRig);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_mushroom);
	REFLECTION_CLASSBUILDER_END(GridItemSmokeManhole);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSmokeManholeProps);

void GridItemSmokeManholeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSmokeManholeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, ArtCenter);
	REFLECTION_CLASSBUILDER_END(GridItemSmokeManholeProps);
}
