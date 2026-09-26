//
//  CollectableUpgrade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectableUpgrade.h"

CollectableUpgrade::CollectableUpgrade()
{
}

CollectableUpgrade::~CollectableUpgrade()
{
}

CollectableUpgradeType::~CollectableUpgradeType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableUpgradeType);

void CollectableUpgradeType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableUpgradeType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_CLASSBUILDER_FIELD(std::string, Upgrade);

	REFLECTION_CLASSBUILDER_END(CollectableUpgradeType);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableUpgrade);
