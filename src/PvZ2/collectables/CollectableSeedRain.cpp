//
//  CollectableSeedRain.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectableSeedRain.h"

bool CollectableSeedRain::drawCost()
{
	return false;
}

CollectableSeedRain::~CollectableSeedRain()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableSeedRain);

void CollectableSeedRain::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableSeedRain);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Collectable);

		REFLECTION_CLASSBUILDER_FIELD(Point, m_targetGrid);
	REFLECTION_CLASSBUILDER_END(CollectableSeedRain);
}
