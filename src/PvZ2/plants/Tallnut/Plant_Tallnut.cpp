//
//  Plant_Tallnut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Tallnut.h"

PlantTallnut::PlantTallnut()
{
}

PlantTallnut::~PlantTallnut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTallnut);

void PlantTallnut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTallnut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_shieldHealth);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_currentShieldDamageIndex);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_damageTime);
	REFLECTION_CLASSBUILDER_END(PlantTallnut);
}
