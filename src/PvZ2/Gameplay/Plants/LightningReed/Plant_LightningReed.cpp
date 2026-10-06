//
//  Plant_LightningReed.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LightningReed.h"

PlantLightningReed::PlantLightningReed()
{
	m_starAttack = 0;
}

PlantLightningReed::~PlantLightningReed()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantLightningReed);

void PlantLightningReed::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantLightningReed);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_starAttack);
		REFLECTION_CLASSBUILDER_FIELD(float, m_chainAttackRate);
	REFLECTION_CLASSBUILDER_END(PlantLightningReed);
}

bool PlantLightningReed::CanApplyPlantfood()
{
	return true;
}
