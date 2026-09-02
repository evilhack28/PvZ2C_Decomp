//
//  EightiesStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "Common.h"

#include "EightiesStage.h"

#include "GameObject.h"
#include "LawnApp.h"
#include "PVZDB.h"
#include "ReflectionBuilder.h"
#include "SexyVector.h"
#include "ZombieEightiesBass.h"

/////////////// EightiesStageProperties ///////////////

RT_CLASS_IMPLEMENT(EightiesStageProperties);
void EightiesStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EightiesStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(EightiesStageProperties);
}

/////////////// EightiesStage ///////////////

RT_CLASS_IMPLEMENT(EightiesStage);
void EightiesStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EightiesStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(EightiesStage);
}

/////////////// BassRainZombieSpawner ///////////////

RT_CLASS_IMPLEMENT(BassRainZombieSpawner);
void BassRainZombieSpawner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BassRainZombieSpawner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieRainSpawner);

	REFLECTION_CLASSBUILDER_END(BassRainZombieSpawner);
}

RT_CLASS_IMPLEMENT(BassRainZombieSpawnerProps);
void BassRainZombieSpawnerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BassRainZombieSpawnerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieRainSpawnerProps);

	REFLECTION_CLASSBUILDER_END(BassRainZombieSpawnerProps);
}

void BassRainZombieSpawner::PostSpawnZombieSetup(Zombie* i_zombie, SexyVector3 i_destination, float i_fallDuration, float i_startHeight)
{
	ZombieEightiesBass* bass = i_zombie->Cast<ZombieEightiesBass>();
	if (!bass)
		return;

	bass->doFallFromSky(i_destination + SexyVector3(24.0f, 10.0f, 0.0f));
}

/////////////// EightiesStage overrides ///////////////

void EightiesStage::initializeModule()
{
	StageModule::initializeModule();
	m_JamStageMechanic = GameObject::Create<JamStageMechanic>(PVZDB::TABLE_GAMEOBJECTS)->GetPtr();
}

void EightiesStage::StartMusic()
{
	if (!GetShouldStartMusic())
		return;

	std::string musicSuffix = getProps<EightiesStageProperties>()->MusicSuffix;
	AudioMgr::GetInstancePtr()->SetSwitch("LevelStarted", musicSuffix.c_str());

	std::string musicType = getMusicTypeForCurrentLevel();
	std::string musicSwitch = Sexy::StrFormat("Music_%s", musicType.c_str());
	AudioMgr::GetInstancePtr()->SetSwitch("Music_Type", musicSwitch.c_str());

	gLawnApp->PlayMusicCallback("Play_Music_World", &m_jamListener);
	setStageMusicState(STAGEMUSIC_Initial);
}
