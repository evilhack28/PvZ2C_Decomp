//
//  CollectablePlantfood.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectablePlantfood.h"

CollectablePlantfood::~CollectablePlantfood()
{
}

CollectablePlantfoodType::CollectablePlantfoodType()
{
}

CollectablePlantfoodType::~CollectablePlantfoodType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectablePlantfoodType);

void CollectablePlantfoodType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectablePlantfoodType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_CLASSBUILDER_END(CollectablePlantfoodType);
}
