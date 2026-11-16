//
//  ZombieSteamStove.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSteamStove.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSteamStove);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSteamStoveProps);

void ZombieSteamStoveProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSteamStoveProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieSteamStoveProps);
}

void ZombieSteamStove::onEndCondition(ZombieConditions i_condition)
{
}

#include "ZombieSteamStove.h"
void ZombieSteamStove::onExplodeAnimDone(const std::string& i_animLabelName)
{
	 ZombieSteamStove::findAndExplodePlant();
}
