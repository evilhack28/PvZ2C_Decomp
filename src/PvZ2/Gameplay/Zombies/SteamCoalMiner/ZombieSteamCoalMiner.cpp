//
//  ZombieSteamCoalMiner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSteamCoalMiner.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSteamCoalMiner);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSteamCoalMinerProps);

void ZombieSteamCoalMinerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSteamCoalMinerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, TruckAttackRectOffsetX);
		REFLECTION_CLASSBUILDER_FIELD(std::string, CoalItemName);
		REFLECTION_CLASSBUILDER_FIELD(int, MaxHelmHitCount);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, HelmHitPlantList);
	REFLECTION_CLASSBUILDER_END(ZombieSteamCoalMinerProps);
}

bool ZombieSteamCoalMiner::hasHeadParticle() const
{
	return true;
}

#include "Zombie.h"
float ZombieSteamCoalMiner::getHeadDropFraction() const
{
	return Zombie::getHeadDropFraction();
}
