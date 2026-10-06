//
//  GridItemVenom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ConvallariaChemist.h"

GridItemVenom::~GridItemVenom()
{
}

GridItemVenomProps::~GridItemVenomProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemVenom);

void GridItemVenom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemVenom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(GridItemVenom);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemVenomProps);

void GridItemVenomProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemVenomProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, VenomInfos);
	REFLECTION_CLASSBUILDER_END(GridItemVenomProps);
}
