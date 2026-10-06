//
//  GameSubSystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GameSubSystem.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GameSubSystem);

void GameSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GameSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

	REFLECTION_CLASSBUILDER_END(GameSubSystem);
}
