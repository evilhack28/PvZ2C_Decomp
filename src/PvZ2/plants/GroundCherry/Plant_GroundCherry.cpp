//
//  Plant_GroundCherry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_GroundCherry.h"

PlantGroundCherry::PlantGroundCherry()
{
}

PlantGroundCherry::~PlantGroundCherry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGroundCherry);

void PlantGroundCherry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGroundCherry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<Point>, m_vLightUpGridVec);
		REFLECTION_CLASSBUILDER_FIELD(GroundCherryAnimState, m_state);
	REFLECTION_CLASSBUILDER_END(PlantGroundCherry);
}

bool PlantGroundCherry::CanBeTargeted()
{
	return false;
}

bool PlantGroundCherry::CanBeTargetedBy(const BoardEntity* i_arg)
{
	return false;
}

bool PlantGroundCherry::CanApplyPlantfood()
{
	return true;
}
