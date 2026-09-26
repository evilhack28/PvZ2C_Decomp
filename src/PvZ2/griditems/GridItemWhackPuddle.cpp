//
//  GridItemWhackPuddle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemWhackPuddle.h"

bool GridItemWhackPuddle::IsAbleToSpawn()
{
	return true;
}

void GridItemWhackPuddle::registerForEvents()
{
}

GridItemWhackPuddle::GridItemWhackPuddle()
{
}

GridItemWhackPuddle::~GridItemWhackPuddle()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemWhackPuddle);

void GridItemWhackPuddle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemWhackPuddle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemWhackPuddle);
}

void GridItemWhackPuddle::onTakeDamage(const DamageInfo& i_arg)
{
}

PlantingReason GridItemWhackPuddle::GetCantPlantReason() const
{
	return (PlantingReason)67;
}
