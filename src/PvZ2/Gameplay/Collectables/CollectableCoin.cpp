//
//  CollectableCoin.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectableCoin.h"

CollectableCoin::CollectableCoin()
{
}

CollectableCoin::~CollectableCoin()
{
}

CollectableCoinType::~CollectableCoinType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableCoinType);

void CollectableCoinType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableCoinType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_CLASSBUILDER_FIELD(int, CoinValue);

	REFLECTION_CLASSBUILDER_END(CollectableCoinType);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableCoin);
