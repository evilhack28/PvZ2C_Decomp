//
//  CottonYetiProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CottonYetiProjectile.h"

bool CottonYetiProjectile::OnCollideGround()
{
	return false;
}

CottonYetiProjectile::CottonYetiProjectile()
{
}

CottonYetiProjectile::~CottonYetiProjectile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CottonYetiProjectile);

void CottonYetiProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CottonYetiProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_hitEntities);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_owner);
		REFLECTION_CLASSBUILDER_FIELD(float, m_extraDpsModifier);
	REFLECTION_CLASSBUILDER_END(CottonYetiProjectile);
}

bool CottonYetiProjectile::OnCollideEntity(BoardEntity* i_entity)
{
	return false;
}

void CottonYetiProjectile::onUpdate(pvztime_t i_dt)
{
}
