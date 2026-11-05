//
//  GeneralTaskBlessListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskBlessListener);

/////////////// Listener ///////////////

GeneralTaskBlessListener::GeneralTaskBlessListener()
{
}

GeneralTaskBlessListener::~GeneralTaskBlessListener()
{
	RemoveListener();
}

void GeneralTaskBlessListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::ArtifactBless, Sexy::MakeDelegate(*this, &GeneralTaskBlessListener::onRefreshTaskInfo));
	NeedRemoveListener = true;
}

void GeneralTaskBlessListener::onRefreshTaskInfo(bool i_isBless)
{
	CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralTaskBlessListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskBlessListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskBlessListener);

}
