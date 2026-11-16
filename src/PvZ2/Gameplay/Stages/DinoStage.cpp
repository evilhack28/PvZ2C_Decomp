//
//  DinoStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DinoStage.h"
#include "ReflectionBuilder.h"

static CachedResourcePtr<Sexy::Image> g_dinoPlants("IMAGE_BACKGROUNDS_DINO_PLANTS");

DinoStageProperties::DinoStageProperties()
{
}

DinoStageProperties::~DinoStageProperties()
{
}

DinoStage::DinoStage()
{
}

DinoStage::~DinoStage()
{
}

RT_CLASS_IMPLEMENT(DinoStageProperties);

void DinoStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinoStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(DinoStageProperties);
}

void DinoStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterAddToRenderQueue(Sexy::MakeDelegate(*this, &DinoStage::addForegroundToRenderQueue));
}

void DinoStage::addForegroundToRenderQueue(RenderQueue* i_queue)
{
	i_queue->Add(RENDER_LAYER_TOP, Sexy::MakeDelegate(*this, &DinoStage::renderForeground));
}

void DinoStage::renderForeground(Sexy::Graphics* i_g)
{
	i_g->DrawImage(g_dinoPlants, (int)S(744.5f), (int)S(318.0f));
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinoStage);

void DinoStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinoStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(DinoStage);
}
