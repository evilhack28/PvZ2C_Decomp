//
//  CollectableSunBomb.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CollectableSunBomb.h"

CollectableSunBomb::CollectableSunBomb()
{
}

CollectableSunBombType::CollectableSunBombType()
{
}

CollectableSunBombType::~CollectableSunBombType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableSunBomb);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableSunBombType);

void CollectableSunBombType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableSunBombType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableSunType);

	REFLECTION_CLASSBUILDER_END(CollectableSunBombType);
}

void CollectableSunBomb::onBeamAnimDone_Destroy(StandaloneEffect* i_effect)
{
}
