//
//  CollectableMoneyBag.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectableMoneyBag.h"

CollectableMoneyBagType::~CollectableMoneyBagType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableMoneyBagType);

void CollectableMoneyBagType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableMoneyBagType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_CLASSBUILDER_FIELD(std::string, ContentsType);
	REFLECTION_CLASSBUILDER_FIELD(int, ContentsCount);

	REFLECTION_CLASSBUILDER_END(CollectableMoneyBagType);
}
