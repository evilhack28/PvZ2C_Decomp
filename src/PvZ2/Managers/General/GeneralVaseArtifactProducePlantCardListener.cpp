//
//  GeneralVaseArtifactProducePlantCardListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "GeneralTaskConfig.h"
#include "GameEventMgr.h"
#include "PVZ1ModeUtils.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralVaseArtifactProducePlantCardListener);

/////////////// Listener ///////////////

void GeneralVaseArtifactProducePlantCardListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::VaseArtifactProducePlantCard, Sexy::MakeDelegate(*this, &GeneralVaseArtifactProducePlantCardListener::onVaseArtifactProducePlantCard));
	NeedRemoveListener = true;
}

void GeneralVaseArtifactProducePlantCardListener::onVaseArtifactProducePlantCard(const std::string& i_plantName)
{
	if (GeneralTaskPtr->TaskConfig && GeneralTaskPtr->TaskConfig->Cast<PvZ1AchievementData>() && PVZ1ModeUtils::IsPlayingPVZ1Level())
		CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralVaseArtifactProducePlantCardListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralVaseArtifactProducePlantCardListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralVaseArtifactProducePlantCardListener);
}
