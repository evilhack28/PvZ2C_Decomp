//
//  Plant_RedStinger.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_RedStinger.h"

PlantRedStinger::PlantRedStinger()
{
}

PlantRedStinger::~PlantRedStinger()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantRedStinger);

void PlantRedStinger::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantRedStinger);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, m_plantfoodEffect);
		REFLECTION_CLASSBUILDER_FIELD(float, m_attackSpeed);
	REFLECTION_CLASSBUILDER_END(PlantRedStinger);
}

bool PlantRedStinger::CanApplyPlantfood()
{
	return true;
}
