//
//  PlantAnimRig_FirePeashooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_FirePeashooter.h"

PlantAnimRig_FirePeashooter::PlantAnimRig_FirePeashooter()
{
}

PlantAnimRig_FirePeashooter::~PlantAnimRig_FirePeashooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_FirePeashooter);

void PlantAnimRig_FirePeashooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_FirePeashooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Effect_PopAnim>>, m_effects);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_FirePeashooter);
}
