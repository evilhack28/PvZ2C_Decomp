//
//  EgyptStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "EgyptStage.h"

#include "AudioMgr.h"
#include "Board.h"
#include "GameEventMgr.h"
#include "LawnApp.h"
#include "LevelDefinition.h"
#include "LevelModuleManager.h"
#include "ObjectTypeDirectory.h"
#include "ProfileUtils.h"
#include "ReflectionBuilder.h"
#include "RtDelegate.h"
#include "ZombieType.h"

RT_CLASS_IMPLEMENT(EgyptStage);
void EgyptStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EgyptStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(EgyptStage);
}

RT_CLASS_IMPLEMENT(EgyptStageProperties);
void EgyptStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EgyptStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(EgyptStageProperties);
}


void EgyptStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterOnLoadComplete(Sexy::MakeDelegate(*this, &EgyptStage::onLoadComplete));
	gMessageRouter->Subscribe(Message::GameWon, Sexy::MakeDelegate(*this, &EgyptStage::onGameWon));
}


void EgyptStage::onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to)
{
	StageModule::onZombieTypeCountChange(i_type, i_from, i_to);

	if (i_type == ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("pharaoh"))
	{
		if (i_from > 0 && i_to <= 0)
			AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_Egypt_Sarcophagus_Mommy", NULL);
		else if (i_from == 0 && i_to > 0)
			AudioMgr::GetInstancePtr()->SendEvent("Play_Zomb_Egypt_Sarcophagus_Mommy", NULL);
	}
}


void EgyptStage::stopZombieGroans()
{
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_Egypt_Sarcophagus_Mommy", NULL);
	StageModule::stopZombieGroans();
}

void EgyptStage::onLoadComplete()
{
	switch (gLawnApp->m_board->GetLevelDefinition()->LevelNumber)
	{
	case 1:
		ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile(FUNNEL_StartsEgyptDay1);
		break;
	case 2:
		ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile(FUNNEL_StartsEgyptDay2);
		break;
	}
}

void EgyptStage::onGameWon()
{
	switch (gLawnApp->m_board->GetLevelDefinition()->LevelNumber)
	{
	case 1:
		ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile(FUNNEL_WinsEgyptDay1);
		break;
	case 2:
		ProfileUtils::TriggerTutorialFunnelEventForCurrentProfile(FUNNEL_WinsEgyptDay2);
		break;
	}
}
