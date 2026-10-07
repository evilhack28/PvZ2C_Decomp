//
//  AgaveSwordLight.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AgaveSwordLight.h"

AgaveSwordLight::AgaveSwordLight()
{
}

AgaveSwordLight::~AgaveSwordLight()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AgaveSwordLight);

void AgaveSwordLight::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AgaveSwordLight);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_hitEntities);
		REFLECTION_CLASSBUILDER_FIELD(Rect, m_collisionRect);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_damageTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_movingHeight);
	REFLECTION_CLASSBUILDER_END(AgaveSwordLight);
}

bool AgaveSwordLight::OnCollideEntity(BoardEntity* i_entity)
{
	return false;
}
