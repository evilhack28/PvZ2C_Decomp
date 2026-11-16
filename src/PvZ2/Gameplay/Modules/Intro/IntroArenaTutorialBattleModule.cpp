//
//  IntroArenaTutorialBattleModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "IntroArenaTutorialBattleModule.h"

void IntroArenaTutorialBattleModule::onPostLoad()
{
}

void IntroArenaTutorialBattleModule::CancelTouch()
{
}

bool IntroArenaTutorialBattleModule::preventSave()
{
	return true;
}

void IntroArenaTutorialBattleModule::onGameplayEnded()
{
}

IntroArenaTutorialBattleModule::~IntroArenaTutorialBattleModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroArenaTutorialBattleModule);

void IntroArenaTutorialBattleModule::onPlantLost(class Plant * i_plant)
{
}

void IntroArenaTutorialBattleModule::onZombieVanish(class StandaloneEffect* i_effect)
{
}

#include "IntroArenaTutorialBattleModule.h"
void IntroArenaTutorialBattleModule::onReadyForBrains()
{
	 IntroArenaTutorialBattleModule::createBrains();
}

#include "IntroArenaTutorialBattleModule.h"
void IntroArenaTutorialBattleModule::onTriggerStartTimerOver()
{
	 IntroArenaTutorialBattleModule::TriggerBattleBegin();
}
