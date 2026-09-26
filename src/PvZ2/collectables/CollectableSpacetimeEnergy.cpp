//
//  CollectableSpacetimeEnergy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectableSpacetimeEnergy.h"

CollectableSpacetimeEnergy::~CollectableSpacetimeEnergy()
{
}

CollectableSpacetimeEnergyType::CollectableSpacetimeEnergyType()
{
}

CollectableSpacetimeEnergyType::~CollectableSpacetimeEnergyType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableSpacetimeEnergy);

void CollectableSpacetimeEnergy::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableSpacetimeEnergy);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Collectable);

	REFLECTION_CLASSBUILDER_END(CollectableSpacetimeEnergy);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableSpacetimeEnergyType);

void CollectableSpacetimeEnergyType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableSpacetimeEnergyType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_CLASSBUILDER_END(CollectableSpacetimeEnergyType);
}

CollectableSpacetimeEnergy::CollectableSpacetimeEnergy()
{
	EnergyValue = 0;
}

void CollectableSpacetimeEnergy::setEnergyValue(int i_arg)
{
	EnergyValue = i_arg;
}
