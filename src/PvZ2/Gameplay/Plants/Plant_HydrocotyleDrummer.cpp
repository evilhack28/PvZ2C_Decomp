//
//  Plant_Hydrocotyledrummer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HydrocotyleDrummer.h"

PlantHydrocotyledrummer::PlantHydrocotyledrummer()
{
	m_recoveryEndTime = PVZ_EOT();
}

PlantHydrocotyledrummerProps::~PlantHydrocotyledrummerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHydrocotyledrummer);

void PlantHydrocotyledrummer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHydrocotyledrummer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_recoveryEndTime);
	REFLECTION_CLASSBUILDER_END(PlantHydrocotyledrummer);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHydrocotyledrummerProps);

void PlantHydrocotyledrummerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HydrocotyledrummerParams);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, EffectDuration);
	REFLECTION_CLASSBUILDER_END(HydrocotyledrummerParams);

	REFLECTION_CLASSBUILDER_BEGIN(PlantHydrocotyledrummerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, Level5_healRatio);
		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, PlantLevel5HealRestriction);
	REFLECTION_CLASSBUILDER_END(PlantHydrocotyledrummerProps);
}

bool PlantHydrocotyledrummer::CanApplyPlantfood()
{
	return true;
}
