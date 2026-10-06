//
//  GridItemOil.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_OlivePit.h"

GridItemOil::~GridItemOil()
{
}

GridItemOilProps::~GridItemOilProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemOil);

void GridItemOil::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemOil);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, m_plantFamilies);
		REFLECTION_CLASSBUILDER_FIELD(ZombieConditions, m_conditionsToApply);
	REFLECTION_CLASSBUILDER_END(GridItemOil);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemOilProps);

void GridItemOilProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemOilProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, OilTime);
	REFLECTION_CLASSBUILDER_END(GridItemOilProps);
}
