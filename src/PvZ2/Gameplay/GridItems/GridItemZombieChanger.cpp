//
//  GridItemZombieChanger.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RiftThemeDrived.h"

GridItemZombieChanger::GridItemZombieChanger()
{
	m_state = (decltype(m_state))0;
	m_changeTimer = PVZ_EOT();
}

GridItemZombieChanger::~GridItemZombieChanger()
{
}

GridItemZombieChangerProps::~GridItemZombieChangerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieChanger);

void GridItemZombieChanger::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieChanger);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemZombieChanger);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieChangerProps);

void GridItemZombieChangerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieChangerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemZombieChangerProps);
}

void GridItemZombieChanger::onTakeDamage(const DamageInfo& i_arg)
{
}
