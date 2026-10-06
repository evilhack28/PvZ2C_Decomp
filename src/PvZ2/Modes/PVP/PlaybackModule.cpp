//
//  PlaybackModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlaybackModule.h"

void PlaybackModule::onGameEnded()
{
}

PlaybackModule::PlaybackModule()
{
	m_recordID = 0;
	m_zombieIndex = 1;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlaybackModule);

void PlaybackModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlaybackModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(PlaybackModule);
}
