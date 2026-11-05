//
//  GeneralTaskConsumeGemsListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskConsumeGemsListener);

/////////////// Listener ///////////////

void GeneralTaskConsumeGemsListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::RefreshSomeTasksData, Sexy::MakeDelegate(*this, &GeneralTaskConsumeGemsListener::onRefreshTaskInfo));
	NeedRemoveListener = true;
	onRefreshTaskInfo();
}

/////////////// Reflection ///////////////

void GeneralTaskConsumeGemsListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskConsumeGemsListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskConsumeGemsListener);

}
