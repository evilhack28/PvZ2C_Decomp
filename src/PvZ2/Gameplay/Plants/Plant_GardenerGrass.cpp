//
//  Plant_GardenerGrass.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_GardenerGrass.h"

PlantGardenerGrass::PlantGardenerGrass()
{
}

PlantGardenerGrass::~PlantGardenerGrass()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGardenerGrass);

void PlantGardenerGrass::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGardenerGrass);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(Rect, m_damageRectNormal);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<class EffectObject_GardenerGrass>, m_attackNormal);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_originalPosition);
	REFLECTION_CLASSBUILDER_END(PlantGardenerGrass);
}

void PlantGardenerGrass::onEndCondition(PlantConditions i_condition)
{
}

bool PlantGardenerGrass::CanApplyPlantfood()
{
	return true;
}
