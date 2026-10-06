//
//  Plant_XShot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_XShot.h"

PlantXShot::~PlantXShot()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantXShot);

void PlantXShot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantXShot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_plantfoodShouldFire);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_potentialTargets);
	REFLECTION_CLASSBUILDER_END(PlantXShot);
}

bool PlantXShot::CanApplyPlantfood()
{
	return true;
}
