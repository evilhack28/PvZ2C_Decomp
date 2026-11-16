//
//  ZombiePirateBarrelPusher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePirateBarrelPusher.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePirateBarrelPusher);

void ZombiePirateBarrelPusher::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePirateBarrelPusher);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_myBarrel);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bManualPause);
	REFLECTION_CLASSBUILDER_END(ZombiePirateBarrelPusher);
}

#include "ZombiePirateBarrelPusher.h"
void ZombiePirateBarrelPusher::onTakeFatalDamage(const DamageInfo& i_lastDamageReceived)
{
	 ZombiePirateBarrelPusher::disconnectBarrel();
}
