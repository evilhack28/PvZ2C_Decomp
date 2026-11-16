//
//  GeneralTaskRankListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskRankListener);

/////////////// Listener ///////////////

GeneralTaskRankListener::GeneralTaskRankListener()
{
}

GeneralTaskRankListener::~GeneralTaskRankListener()
{
	RemoveListener();
}

void GeneralTaskRankListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::NewPVPEndDuan, Sexy::MakeDelegate(*this, &GeneralTaskRankListener::onRefreshTaskInfo));
	NeedRemoveListener = true;
}

void GeneralTaskRankListener::onRefreshTaskInfo(int i_duan)
{
	if (i_duan > 1)
		CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralTaskRankListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskRankListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskRankListener);

}
