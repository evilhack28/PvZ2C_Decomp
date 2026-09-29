//
//  StageModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StageModule.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StageModule);

void StageModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StageModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_musicTriggerOverride);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_musicState);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_damageFlashStartTime);
		REFLECTION_CLASSBUILDER_FIELD(Color, m_damageFlashColor);
	REFLECTION_CLASSBUILDER_END(StageModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StageModuleProperties);

#include "StageModule.h"
void StageModule::onGameLost()
{
	 StageModule::startLoseMusic();
}

#include "StageModule.h"
void StageModule::onFinalWave()
{
	 StageModule::startFinalWaveMusic();
}

void StageModule::onGamePaused()
{
}

#include "StageModule.h"
void StageModule::onLevelLoaded()
{
	 StageModule::parseImages();
}

void StageModule::onGameUnpaused()
{
}

#include "StageModule.h"
void StageModule::onGameWon()
{
	 StageModule::startWinMusic();
}
