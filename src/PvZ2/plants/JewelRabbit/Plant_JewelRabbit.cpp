//
//  Plant_JewelRabbit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_JewelRabbit.h"

PlantJewelRabbit::~PlantJewelRabbit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantJewelRabbit);

void PlantJewelRabbit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantJewelRabbit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_lockedZombie);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_lockedPoint);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_JewelRabbit_pioneer>, m_pioneer);
	REFLECTION_CLASSBUILDER_END(PlantJewelRabbit);
}
