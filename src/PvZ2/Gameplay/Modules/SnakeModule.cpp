//
//  SnakeModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SnakeModule.h"

bool SnakeModule::preventSave()
{
	return true;
}

void SnakeModule::levelStarted()
{
}

void SnakeModule::postInitialize()
{
}

SnakeModule::~SnakeModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SnakeModule);

void SnakeModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SnakeModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(float, m_snakeStep);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, m_BlueInfos);
	REFLECTION_CLASSBUILDER_END(SnakeModule);
}

void SnakeModule::initializeModule()
{
}
