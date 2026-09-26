//
//  EffectAnimRig_StarPlantFoodShine.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_StarPlantFoodShine.h"

EffectAnimRig_StarPlantFoodShine::EffectAnimRig_StarPlantFoodShine()
{
}

EffectAnimRig_StarPlantFoodShine::~EffectAnimRig_StarPlantFoodShine()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_StarPlantFoodShine);

void EffectAnimRig_StarPlantFoodShine::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_StarPlantFoodShine);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int32, m_starFoodState);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_StarPlantFoodShine);
}
