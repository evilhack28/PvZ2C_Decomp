//
//  Plant_ColdSnapdragon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ColdSnapdragon.h"

PlantColdSnapdragon::PlantColdSnapdragon()
{
}

PlantColdSnapdragon::~PlantColdSnapdragon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantColdSnapdragon);

void PlantColdSnapdragon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantColdSnapdragon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentLinearBurst>, m_breathBurst);
	REFLECTION_CLASSBUILDER_END(PlantColdSnapdragon);
}

bool PlantColdSnapdragon::CanApplyPlantfood()
{
	return true;
}
