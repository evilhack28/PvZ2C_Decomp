//
//  Plant_Parsnip.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Parsnip.h"

PlantParsnip::PlantParsnip()
{
}

PlantParsnip::~PlantParsnip()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantParsnip);

void PlantParsnip::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantParsnip);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_attackDirection);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_plantfoodDamageEndTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ParsnipUltraProjectile>, m_currentProjectile);
	REFLECTION_CLASSBUILDER_END(PlantParsnip);
}
