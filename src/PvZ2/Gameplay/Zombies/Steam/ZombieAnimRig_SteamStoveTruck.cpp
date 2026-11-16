//
//  ZombieAnimRig_SteamStoveTruck.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSteamStove.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_SteamStoveTruck);

void ZombieAnimRig_SteamStoveTruck::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_SteamStoveTruck);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_customState);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_SteamStoveTruck);
}
