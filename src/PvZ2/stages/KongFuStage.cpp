//
//  KongFuStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "KongFuStage.h"

#include "AudioMgr.h"
#include "LevelModuleManager.h"
#include "ObjectTypeDirectory.h"
#include "ReflectionBuilder.h"
#include "RtDelegate.h"
#include "ZombieType.h"

RT_CLASS_IMPLEMENT(KongFuStage);
void KongFuStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(KongFuStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(KongFuStage);
}

RT_CLASS_IMPLEMENT(KongFuStageProperties);
void KongFuStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(KongFuStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(KongFuStageProperties);
}


void KongFuStage::renderBackground(Graphics* i_g)
{
	StageModule::renderBackground(i_g);
}


void KongFuStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterOnLoadComplete(Sexy::MakeDelegate(*this, &KongFuStage::parseGearImages));
}


void KongFuStage::onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to)
{
	StageModule::onZombieTypeCountChange(i_type, i_from, i_to);

	if (i_type == ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("pharaoh"))
	{
		if (i_from > 0 && i_to <= 0)
			AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_KongFu_Sarcophagus_Mommy", NULL);
		else if (i_from == 0 && i_to > 0)
			AudioMgr::GetInstancePtr()->SendEvent("Play_Zomb_KongFu_Sarcophagus_Mommy", NULL);
	}
}


void KongFuStage::stopZombieGroans()
{
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_KongFu_Sarcophagus_Mommy", NULL);
	StageModule::stopZombieGroans();
}


void KongFuStage::onPostLoad()
{
	StageModule::onPostLoad();
	parseGearImages();
}


void KongFuStage::parseGearImages()
{
}
