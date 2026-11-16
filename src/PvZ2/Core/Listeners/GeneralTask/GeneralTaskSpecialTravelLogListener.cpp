//
//  GeneralTaskSpecialTravelLogListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "PlayerInfo.h"
#include "TravelLogConfig.h"
#include "QuickJumpUtil.h"
#include "ProfileUtils.h"
#include "ProfileMgr.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskSpecialTravelLogListener);

void GeneralTaskSpecialTravelLogListener::OnFinishTravelogSpecialTask()
{
	CounterAdd();
}

/////////////// Listener ///////////////

void GeneralTaskSpecialTravelLogListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	std::vector<TravelLogTaskSaveInfo> saveInfos = ProfileMgr::GetInstance().GetCurrentProfile()->GetAllTravelLogSaveInfo();
	bool found = false;
	for (size_t i = 0; i < saveInfos.size(); i++)
	{
		if (saveInfos[i].GroupID == TL_GROUP_WEEKLY && saveInfos[i].State == TL_STATUS_REWARDED)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		CounterAdd();
		NeedRemoveListener = false;
	}
	else
	{
		gMessageRouter->Subscribe(&Message::FinishTravelogSpecialTask, Sexy::MakeDelegate(*this, &GeneralTaskSpecialTravelLogListener::OnFinishTravelogSpecialTask));
		NeedRemoveListener = true;
	}
}

int GeneralTaskSpecialTravelLogListener::JumpToTargetTask()
{
	if (ProfileUtils::HasCompletedLevel("egypt6", false, ProfileMgr::GetInstance().GetCurrentProfile()))
	{
		QuickJumpUtil::GetInstancePtr()->ShowTravelLog();
		return 1;
	}
	return 0;
}

/////////////// Reflection ///////////////

void GeneralTaskSpecialTravelLogListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskSpecialTravelLogListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskSpecialTravelLogListener);

}
