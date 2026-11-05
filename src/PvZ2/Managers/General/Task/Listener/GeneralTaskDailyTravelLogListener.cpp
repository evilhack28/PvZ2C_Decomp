//
//  GeneralTaskDailyTravelLogListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "QuickJumpUtil.h"
#include "ProfileUtils.h"
#include "ProfileMgr.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskDailyTravelLogListener);

void GeneralTaskDailyTravelLogListener::OnFinishTravelogDailyTask()
{
	CounterAdd();
}

/////////////// Listener ///////////////

void GeneralTaskDailyTravelLogListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::FinishTravelogDailyTask, Sexy::MakeDelegate(*this, &GeneralTaskDailyTravelLogListener::OnFinishTravelogDailyTask));
	NeedRemoveListener = true;
}

int GeneralTaskDailyTravelLogListener::JumpToTargetTask()
{
	if (ProfileUtils::HasCompletedLevel("egypt6", false, ProfileMgr::GetInstance().GetCurrentProfile()))
	{
		QuickJumpUtil::GetInstancePtr()->ShowTravelLog();
		return 1;
	}
	return 0;
}

/////////////// Reflection ///////////////

void GeneralTaskDailyTravelLogListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskDailyTravelLogListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskDailyTravelLogListener);

}
