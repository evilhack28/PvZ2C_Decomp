//
//  GridItemRenaiStatue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemRenaiStatue.h"

GridItemRenaiStatue::~GridItemRenaiStatue()
{
}

GridItemRenaiStatueProps::~GridItemRenaiStatueProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRenaiStatue);

void GridItemRenaiStatue::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRenaiStatue);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTarget);

		REFLECTION_CLASSBUILDER_FIELD(float, m_shakeOffset);
	REFLECTION_CLASSBUILDER_END(GridItemRenaiStatue);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRenaiStatueProps);

void GridItemRenaiStatueProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRenaiStatueProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, ZombieTypeName);
	REFLECTION_CLASSBUILDER_END(GridItemRenaiStatueProps);
}

bool GridItemRenaiStatue::HasGravity()
{
	return true;
}

bool GridItemRenaiStatue::CanBeCarved()
{
	return false;
}

void GridItemRenaiStatue::OnChangeState(StatueState i_arg)
{
}

void GridItemRenaiStatue::onPopAnimCommand(const std::string& i_arg0, pvztime_t i_arg1, const std::string& i_arg2, const std::string& i_arg3)
{
}

PlantingReason GridItemRenaiStatue::GetCantPlantReason() const
{
	return (PlantingReason)99;
}
