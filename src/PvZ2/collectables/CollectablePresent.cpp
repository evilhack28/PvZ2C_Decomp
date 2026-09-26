//
//  CollectablePresent.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectablePresent.h"

CollectablePresent::~CollectablePresent()
{
}

CollectablePresentType::~CollectablePresentType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectablePresent);

void CollectablePresent::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectablePresent);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Collectable);

	REFLECTION_CLASSBUILDER_END(CollectablePresent);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectablePresentType);

void CollectablePresentType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectablePresentType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_CLASSBUILDER_FIELD(bool, IsShiny);

	REFLECTION_CLASSBUILDER_END(CollectablePresentType);
}
