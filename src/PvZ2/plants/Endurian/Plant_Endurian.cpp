//
//  Plant_Endurian.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Endurian.h"

PlantEndurian::PlantEndurian()
{
}

PlantEndurian::~PlantEndurian()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantEndurian);

void PlantEndurian::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantEndurian);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_shieldHealth);
		REFLECTION_CLASSBUILDER_FIELD(int, m_pfDamageHits);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_lastAttack);
	REFLECTION_CLASSBUILDER_END(PlantEndurian);
}
