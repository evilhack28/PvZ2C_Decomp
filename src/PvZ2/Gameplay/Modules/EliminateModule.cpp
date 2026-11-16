//
//  EliminateModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EliminateModule.h"

bool EliminateModule::preventSave()
{
	return true;
}

void EliminateModule::onLevelStarted()
{
}

void EliminateModule::onNarrationFinished()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EliminateModule);

void EliminateModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EliminateModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(EliminateModule);
}

void EliminateModule::onFallDone(BoardEntity * target)
{
}

void EliminateModule::initializeModule()
{
}
