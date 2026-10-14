//
//  EffectAnimRig_PlantFoodShine.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_PlantFoodShine.h"

EffectAnimRig_PlantFoodShine::EffectAnimRig_PlantFoodShine()
{
}

EffectAnimRig_PlantFoodShine::~EffectAnimRig_PlantFoodShine()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_PlantFoodShine);

void EffectAnimRig_PlantFoodShine::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_PlantFoodShine);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int32, m_playState);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_PlantFoodShine);
}
