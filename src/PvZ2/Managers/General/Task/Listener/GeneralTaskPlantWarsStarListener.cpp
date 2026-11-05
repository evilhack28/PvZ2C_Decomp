//
//  GeneralTaskPlantWarsStarListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskPlantWarsStarListener);

/////////////// Listener ///////////////

GeneralTaskPlantWarsStarListener::GeneralTaskPlantWarsStarListener()
{
}

GeneralTaskPlantWarsStarListener::~GeneralTaskPlantWarsStarListener()
{
	RemoveListener();
}

void GeneralTaskPlantWarsStarListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::PlantWarsStarTask, Sexy::MakeDelegate(*this, &GeneralTaskPlantWarsStarListener::onRefreshTaskInfo));
	NeedRemoveListener = true;
}

void GeneralTaskPlantWarsStarListener::onRefreshTaskInfo()
{
	CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralTaskPlantWarsStarListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskPlantWarsStarListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskPlantWarsStarListener);

}
