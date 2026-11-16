//
//  GeneralTaskAdventureListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskAdventureListener);

/////////////// Listener ///////////////

GeneralTaskAdventureListener::GeneralTaskAdventureListener()
{
}

GeneralTaskAdventureListener::~GeneralTaskAdventureListener()
{
	RemoveListener();
}

void GeneralTaskAdventureListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::FinishPlantAdventure, Sexy::MakeDelegate(*this, &GeneralTaskAdventureListener::onPlantAdventureFinish));
	NeedRemoveListener = true;
}

void GeneralTaskAdventureListener::onPlantAdventureFinish(int i_worldId)
{
	CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralTaskAdventureListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskAdventureListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskAdventureListener);

}
