//
//  PlantAnimRig_NarcissusShooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_NarcissusShooter.h"

PlantAnimRig_NarcissusShooter::~PlantAnimRig_NarcissusShooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_NarcissusShooter);

void PlantAnimRig_NarcissusShooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_NarcissusShooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_NarcissusShooter);
}

PlantAnimRig_NarcissusShooter::PlantAnimRig_NarcissusShooter()
{
	m_isInWater = 0;
}
