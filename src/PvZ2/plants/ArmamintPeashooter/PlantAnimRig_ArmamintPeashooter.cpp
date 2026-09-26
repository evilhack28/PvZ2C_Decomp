//
//  PlantAnimRig_ArmamintPeashooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ArmamintPeashooter.h"

PlantAnimRig_ArmamintPeashooter::~PlantAnimRig_ArmamintPeashooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_ArmamintPeashooter);

void PlantAnimRig_ArmamintPeashooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_ArmamintPeashooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(AttackType, m_type);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_ArmamintPeashooter);
}
