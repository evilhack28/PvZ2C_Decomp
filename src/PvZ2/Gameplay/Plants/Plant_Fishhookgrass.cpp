//
//  Plant_Fishhookgrass.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Fishhookgrass.h"

PlantFishhookgrass::~PlantFishhookgrass()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantFishhookgrass);

void PlantFishhookgrass::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantFishhookgrass);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_currentTarget);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_previousTargetsHit);
	REFLECTION_CLASSBUILDER_END(PlantFishhookgrass);
}

bool PlantFishhookgrass::CanApplyPlantfood()
{
	return true;
}
