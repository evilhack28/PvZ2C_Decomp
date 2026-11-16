//
//  Plant_AppleMortar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_AppleMortar.h"

PlantAppleMortar::PlantAppleMortar()
{
	m_bWalkFire = 0;
	m_bWalkFireStep = 0;
}

PlantAppleMortar::~PlantAppleMortar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAppleMortar);

void PlantAppleMortar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAppleMortar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantAppleMortar);
}

bool PlantAppleMortar::CanApplyPlantfood()
{
	return true;
}
