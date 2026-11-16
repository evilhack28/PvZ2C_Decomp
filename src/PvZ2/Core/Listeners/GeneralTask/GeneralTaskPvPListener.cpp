//
//  GeneralTaskPvPListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskPvPListener);

/////////////// Listener ///////////////

GeneralTaskPvPListener::GeneralTaskPvPListener()
{
}

GeneralTaskPvPListener::~GeneralTaskPvPListener()
{
	RemoveListener();
}

void GeneralTaskPvPListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::LevelEndForTask, Sexy::MakeDelegate(*this, &GeneralTaskPvPListener::onLevelEnded));
	NeedRemoveListener = true;
}

void GeneralTaskPvPListener::onLevelEnded(LevelDefinitionForTask* i_defTask)
{
	if (i_defTask->isPvP)
		CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralTaskPvPListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskPvPListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskPvPListener);

}
