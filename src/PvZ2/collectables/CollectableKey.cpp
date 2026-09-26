//
//  CollectableKey.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectableKey.h"

CollectableKeyType::~CollectableKeyType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableKeyType);

void CollectableKeyType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableKeyType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_CLASSBUILDER_END(CollectableKeyType);
}
