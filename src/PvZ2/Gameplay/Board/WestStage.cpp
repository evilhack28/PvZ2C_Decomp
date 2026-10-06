//
//  WestStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "WestStage.h"

#include "AudioMgr.h"
#include "ObjectTypeDirectory.h"
#include "ReflectionBuilder.h"
#include "ZombieType.h"

RT_CLASS_IMPLEMENT(WestStage);
void WestStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WestStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(WestStage);
}

RT_CLASS_IMPLEMENT(WestStageProperties);
void WestStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WestStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(WestStageProperties);
}


void WestStage::onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to)
{
	StageModule::onZombieTypeCountChange(i_type, i_from, i_to);

	if (i_type == ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("chicken"))
	{
		if (i_from > 0 && i_to <= 0)
			AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_WildWest_Chicken_Vox_Cluck", NULL);
	}

	if (i_type == ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("poncho_plate"))
	{
		if (i_from > 0 && i_to <= 0)
			AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_WildWest_Pancho_Vox", NULL);
		else if (i_from == 0 && i_to > 0)
			AudioMgr::GetInstancePtr()->SendEvent("Play_Zomb_WildWest_Pancho_Vox", NULL);
	}
}


void WestStage::stopZombieGroans()
{
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_WildWest_Chicken_Vox_Cluck", NULL);
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_WildWest_Pancho_Vox", NULL);
	StageModule::stopZombieGroans();
}
