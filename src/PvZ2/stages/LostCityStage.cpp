//
//  LostCityStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "LostCityStage.h"

#include "Graphics.h"
#include "LevelModuleManager.h"
#include "Renderable.h"
#include "RenderQueue.h"
#include "ReflectionBuilder.h"
#include "ResourceHelpers.h"
#include "RtDelegate.h"
#include "ScaledApp.h"
#include "ZombieLostCityLostPilot.h"

static CachedResourcePtr<Sexy::Image> g_bushBottomLeft("IMAGE_BACKGROUNDS_LOST_CITY_BUSH_BOTTOM_LEFT");
static CachedResourcePtr<Sexy::Image> g_bushBottomRight("IMAGE_BACKGROUNDS_LOST_CITY_BUSH_BOTTOM_RIGHT");
static CachedResourcePtr<Sexy::Image> g_middleVine("IMAGE_BACKGROUNDS_LOST_CITY_MIDDLE_VINE");

/////////////// LostCityStageProperties ///////////////

RT_CLASS_IMPLEMENT(LostCityStageProperties);
void LostCityStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LostCityStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(LostCityStageProperties);
}

/////////////// LostCityStage ///////////////

RT_CLASS_IMPLEMENT(LostCityStage);
void LostCityStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LostCityStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(LostCityStage);
}

/////////////// ParachuteRainZombieSpawner ///////////////

RT_CLASS_IMPLEMENT(ParachuteRainZombieSpawner);
void ParachuteRainZombieSpawner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ParachuteRainZombieSpawner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieRainSpawner);

	REFLECTION_CLASSBUILDER_END(ParachuteRainZombieSpawner);
}

RT_CLASS_IMPLEMENT(ParachuteRainZombieSpawnerProps);
void ParachuteRainZombieSpawnerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ParachuteRainZombieSpawnerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieRainSpawnerProps);

	REFLECTION_CLASSBUILDER_END(ParachuteRainZombieSpawnerProps);
}

void ParachuteRainZombieSpawner::PostSpawnZombieSetup(Zombie* i_zombie, SexyVector3 i_destination, float i_fallDuration, float i_startHeight)
{
	ZombieLostCityLostPilot* pilot = i_zombie->Cast<ZombieLostCityLostPilot>();
	pilot->doFallFromSky();
	pilot->RiseFromPod(i_destination);
}

/////////////// Rendering ///////////////

void LostCityStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterAddToRenderQueue(Sexy::MakeDelegate(*this, &LostCityStage::addForegroundToRenderQueue));
}

void LostCityStage::addForegroundToRenderQueue(RenderQueue* i_queue)
{
	i_queue->Add(RENDER_LAYER_TOP, Sexy::MakeDelegate(*this, &LostCityStage::renderForeground));
}

void LostCityStage::renderForeground(Sexy::Graphics* i_g)
{
	i_g->DrawImage(g_bushBottomLeft, (int)S(-2.5f), (int)S(462.5f));
	i_g->DrawImage(g_bushBottomRight, (int)S(828.0f), (int)S(510.0f));
	i_g->DrawImage(g_middleVine, (int)S(166.5f), (int)S(-3.5f));
}
