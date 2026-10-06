//
//  ArenaBattleModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArenaBattleModule.h"

void ArenaBattleModule::onPostLoad()
{
}

void ArenaBattleModule::CancelTouch()
{
}

ArenaBattleModule::~ArenaBattleModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArenaBattleModule);

void ArenaBattleModule::onZombieVanish(class StandaloneEffect* i_arg)
{
}

#include "ArenaBattleModule.h"
void ArenaBattleModule::onReadyForBrains()
{
	 ArenaBattleModule::createBrains();
}

#include "ArenaBattleModule.h"
void ArenaBattleModule::onTriggerStartTimerOver()
{
	 ArenaBattleModule::TriggerBattleBegin();
}
