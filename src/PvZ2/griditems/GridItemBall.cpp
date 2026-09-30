//
//  GridItemBall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

GridItemBall::~GridItemBall()
{
}

GridItemBallProps::~GridItemBallProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBall);

void GridItemBall::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBall);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(float, m_lifeTime);
	REFLECTION_CLASSBUILDER_END(GridItemBall);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBallProps);

void GridItemBallProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBallProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemBallProps);
}

bool GridItemBall::OverrideProjectileCollision(Projectile* i_arg)
{
	return false;
}

bool GridItemBall::CollidesWithType(const CollisionTypeFlags i_arg) const
{
	return true;
}

#include "RealObject.h"
bool GridItemBall::ShouldDrawShadow() const
{
	return RealObject::ShouldDrawShadow();
}

PlantingReason GridItemBall::GetCantPlantReason() const
{
	return (PlantingReason)75;
}
