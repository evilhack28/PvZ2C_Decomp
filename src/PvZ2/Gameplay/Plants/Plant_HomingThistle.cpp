//
//  Plant_HomingThistle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HomingThistle.h"

PlantHomingThistle::~PlantHomingThistle()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHomingThistle);

void PlantHomingThistle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHomingThistle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_pfTargets);
	REFLECTION_CLASSBUILDER_END(PlantHomingThistle);
}

bool PlantHomingThistle::CanApplyPlantfood()
{
	return true;
}
