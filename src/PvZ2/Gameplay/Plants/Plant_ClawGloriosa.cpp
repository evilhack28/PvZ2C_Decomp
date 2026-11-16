//
//  Plant_ClawGloriosa.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ClawGloriosa.h"

PlantClawGloriosa::PlantClawGloriosa()
{
}

PlantClawGloriosa::~PlantClawGloriosa()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantClawGloriosa);

void PlantClawGloriosa::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantClawGloriosa);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_recoveryEndTime);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_originalPosition);
	REFLECTION_CLASSBUILDER_END(PlantClawGloriosa);
}

void PlantClawGloriosa::onEndCondition(PlantConditions i_condition)
{
}

bool PlantClawGloriosa::CanApplyPlantfood()
{
	return true;
}
