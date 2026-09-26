//
//  PiratePlankModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PiratePlankModule.h"
#include "LevelModuleManager.h"
#include "PirateStage.h"
#include "RtDelegate.h"

PiratePlankModule::PiratePlankModule()
{
}

PiratePlankModule::~PiratePlankModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PiratePlankModule);

void PiratePlankModule::registerForEvents()
{
	getManager()->RegisterOnLevelInit(Sexy::MakeDelegate(*this, &PiratePlankModule::addPlanks));
}

void PiratePlankModule::addPlanks()
{
	PirateStage* stage = getManager()->GetStageModule()->CastChecked<PirateStage>();
	stage->InitPlanks(getProps<PiratePlankProperties>()->PlankRows);
}
