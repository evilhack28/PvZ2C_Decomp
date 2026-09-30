//
//  CannonLaser.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CannonLaser.h"

void CannonLaser::onDestroy()
{
}

CannonLaser::~CannonLaser()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CannonLaser);

void CannonLaser::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CannonLaser);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

		REFLECTION_CLASSBUILDER_FIELD(int, m_laserState);
	REFLECTION_CLASSBUILDER_END(CannonLaser);
}

bool CannonLaser::ShouldDrawShadow() const
{
	return false;
}
