//
//  Plant_BoophoneGeisha.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BoophoneGeisha.h"

PlantBoophoneGeisha::PlantBoophoneGeisha()
{
}

PlantBoophoneGeisha::~PlantBoophoneGeisha()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBoophoneGeisha);

void PlantBoophoneGeisha::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBoophoneGeisha);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_attackCount);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isAttacking);
	REFLECTION_CLASSBUILDER_END(PlantBoophoneGeisha);
}

bool PlantBoophoneGeisha::CanApplyPlantfood()
{
	return true;
}

void PlantBoophoneGeisha::ResetProjectileSlot(uint32 slotIndex)
{
}
