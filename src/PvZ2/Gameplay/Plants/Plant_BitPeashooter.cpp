//
//  Plant_BitPeashooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BitPeashooter.h"

PlantBitPeashooter::PlantBitPeashooter()
{
	m_timer = PVZ_EOT();
}

PlantBitPeashooter::~PlantBitPeashooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBitPeashooter);

void PlantBitPeashooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBitPeashooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_timeToDie);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_random);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timer);
	REFLECTION_CLASSBUILDER_END(PlantBitPeashooter);
}

bool PlantBitPeashooter::CanApplyPlantfood()
{
	return false;
}
