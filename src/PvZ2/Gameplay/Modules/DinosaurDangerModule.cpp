//
//  DinosaurDangerModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DinosaurDangerModule.h"

void DinosaurDangerModule::OnLevelEnded()
{
}

void DinosaurDangerModule::GameplayEnded()
{
}

void DinosaurDangerModule::KillEndLevelUI()
{
}

void DinosaurDangerModule::OnLoadComplete()
{
}

void DinosaurDangerModule::postInitialize()
{
}

void DinosaurDangerModule::GameplayStarted()
{
}

void DinosaurDangerModule::OnErrorOK()
{
}

DinosaurDangerModule::DinosaurDangerModule()
{
	mSmallDropCount = 0;
	mBigDropCount = 0;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurDangerModule);

void DinosaurDangerModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinosaurDangerModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(DinosaurDangerModule);
}

void DinosaurDangerModule::OnContinue(TimeChallengeEndLevelUI* ui)
{
}

void DinosaurDangerModule::OnPlantAdded(class Plant* i_plant)
{
}

void DinosaurDangerModule::OnRequestDinosaurDangerEnd(int result)
{
}

void DinosaurDangerModule::Draw(Graphics* i_g)
{
}

void DinosaurDangerModule::Update()
{
}
