//
//  GridItemMeteor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

GridItemMeteor::~GridItemMeteor()
{
}

GridItemMeteorProps::~GridItemMeteorProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMeteor);

void GridItemMeteor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMeteor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Projectile> >, m_affectedProjectiles);
	REFLECTION_CLASSBUILDER_END(GridItemMeteor);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMeteorProps);

void GridItemMeteorProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMeteorProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
	REFLECTION_CLASSBUILDER_END(GridItemMeteorProps);
}

PlantingReason GridItemMeteor::GetCantPlantReason() const
{
	return (PlantingReason)75;
}
