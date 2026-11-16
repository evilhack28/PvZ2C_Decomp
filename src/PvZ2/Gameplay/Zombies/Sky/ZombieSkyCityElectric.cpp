//
//  ZombieSkyCityElectric.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSkyCityElectric.h"

ZombieSkyCityElectricProps::ZombieSkyCityElectricProps()
{
}

ZombieSkyCityElectricProps::~ZombieSkyCityElectricProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkyCityElectric);

void ZombieSkyCityElectric::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSkyCityElectric);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSkyCity);

		REFLECTION_CLASSBUILDER_FIELD(int, m_iPrevColunm);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_startGlideTime);
		REFLECTION_CLASSBUILDER_FIELD(Effect_Barrage, m_barrage);
	REFLECTION_CLASSBUILDER_END(ZombieSkyCityElectric);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkyCityElectricProps);

void ZombieSkyCityElectricProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSkyCityElectricProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSkyCityProps);

	REFLECTION_CLASSBUILDER_END(ZombieSkyCityElectricProps);
}

#include "ZombieWithActions.h"
void ZombieSkyCityElectric::onZombieInitialize()
{
	 ZombieWithActions::onZombieInitialize();
}
