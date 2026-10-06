//
//  Plant_EscapeRoot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_EscapeRoot.h"

PlantEscapeRoot::PlantEscapeRoot()
{
}

PlantEscapeRoot::~PlantEscapeRoot()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantEscapeRoot);

void PlantEscapeRoot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantEscapeRoot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentDamageRadius>, m_explodeRadius);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isSelected);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_maySelectAfter);
		REFLECTION_CLASSBUILDER_FIELD(int, m_currentPFAttackCount);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_attackType);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_targetPlant);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_plantfoodOffset);
	REFLECTION_CLASSBUILDER_END(PlantEscapeRoot);
}

bool PlantEscapeRoot::CanEndPlantfood()
{
	return false;
}

bool PlantEscapeRoot::HasShadow()
{
	return false;
}
