//
//  ZombieAnimRig_SteamCoalMiner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSteamCoalMiner.h"

ZombieAnimRig_SteamCoalMiner::ZombieAnimRig_SteamCoalMiner()
{
	m_hasTruck = 1;
}

ZombieAnimRig_SteamCoalMiner::~ZombieAnimRig_SteamCoalMiner()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_SteamCoalMiner);

void ZombieAnimRig_SteamCoalMiner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_SteamCoalMiner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasTruck);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_SteamCoalMiner);
}

const bool ZombieAnimRig_SteamCoalMiner::getDieShouldBlend()
{
	return false;
}
