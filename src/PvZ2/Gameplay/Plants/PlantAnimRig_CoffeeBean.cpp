//
//  PlantAnimRig_CoffeeBean.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CoffeeBean.h"

PlantAnimRig_CoffeeBean::PlantAnimRig_CoffeeBean()
{
}

PlantAnimRig_CoffeeBean::~PlantAnimRig_CoffeeBean()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_CoffeeBean);

void PlantAnimRig_CoffeeBean::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_CoffeeBean);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_CoffeeBean);
}
