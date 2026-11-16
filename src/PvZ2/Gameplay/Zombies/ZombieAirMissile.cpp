//
//  ZombieAirMissile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAirMissile.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAirMissile);

void ZombieAirMissile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAirMissile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(int, m_targetRow);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_explodeOnBoard);
	REFLECTION_CLASSBUILDER_END(ZombieAirMissile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAirMissileProps);

void ZombieAirMissileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAirMissileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSkyCityProps);

		REFLECTION_CLASSBUILDER_FIELD(float, hitPlantDamage);
	REFLECTION_CLASSBUILDER_END(ZombieAirMissileProps);
}

bool ZombieAirMissile::allowAshState() const
{
	return false;
}

bool ZombieAirMissile::CollidesWithType(CollisionTypeFlags i_collisionTypes) const
{
	return false;
}

bool ZombieAirMissile::allowElectrocuteState() const
{
	return false;
}
