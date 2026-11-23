//
//  Projectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-23.
//

#include "SexyAppFramework/Common.h"

#include "Projectile.h"

/////////////// Accessors ///////////////

void Projectile::SetCollideType(CollisionTypeFlags types)
{
	m_collideType = types;
}

void Projectile::SetShouldKeepRoofZ(bool i_flag)
{
	m_shouldKeepRoofZ = i_flag;
}

void Projectile::SetUpdateTimeOverride(pvztime_t i_newTimeStep)
{
	m_timeStepOverride = i_newTimeStep;
}

void Projectile::SetPaused(bool i_paused)
{
	SetFlag(m_propertyFlags, PROJECTILE_FLAG_PAUSED, i_paused);
}

void Projectile::SetShadow(bool i_showShadow)
{
	SetFlag(m_propertyFlags, PROJECTILE_FLAG_HIDESHADOW, !i_showShadow);
}

void Projectile::clearAttachedEffects()
{
	m_attachedEffects.Clear();
}

AttachedBoardEntityNode* Projectile::GetOrCreateAttachedBoardEntity(const std::string& i_entityName)
{
	return (AttachedBoardEntityNode*)&m_attachedBoardEntities.FindOrCreate(i_entityName);
}

bool Projectile::CollidesWithType(CollisionTypeFlags testTypes) const
{
	return (testTypes & m_collideType) != 0;
}

bool Projectile::IsHeadShot() const
{
	return GetProps()->CheckHeadShot;
}

bool Projectile::IsSkipAdditionalAngularVelocity()
{
	return GetProps()->SkipAdditionalAngularVelocity;
}
