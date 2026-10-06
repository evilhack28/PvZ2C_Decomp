//
//  LawnBrainModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "LawnBrainModule.h"

LawnBrainModule::LawnBrainModule()
{
}

LawnBrainModule::~LawnBrainModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LawnBrainModule);

void LawnBrainModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LawnBrainModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_nBrainsRemaining);
	REFLECTION_CLASSBUILDER_END(LawnBrainModule);
}

#include "LawnBrainModule.h"
void LawnBrainModule::onReadyForBrains()
{
	 LawnBrainModule::createBrains();
}
