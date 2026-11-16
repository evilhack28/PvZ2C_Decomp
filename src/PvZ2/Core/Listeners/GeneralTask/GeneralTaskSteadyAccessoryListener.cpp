//
//  GeneralTaskSteadyAccessoryListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskSteadyAccessoryListener);

void GeneralTaskSteadyAccessoryListener::OnSteadyAccessory()
{
	CounterAdd();
}

/////////////// Listener ///////////////

void GeneralTaskSteadyAccessoryListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::SteadyAccessory, Sexy::MakeDelegate(*this, &GeneralTaskSteadyAccessoryListener::OnSteadyAccessory));
	NeedRemoveListener = true;
}

int GeneralTaskSteadyAccessoryListener::JumpToTargetTask()
{
	if (ProfileUtils::HasCompletedLevel("egypt5", false, ProfileMgr::GetInstance().GetCurrentProfile()))
	{
		QuickJumpUtil::GetInstancePtr()->ShowAvatarListView();
		return 1;
	}
	return 0;
}

/////////////// Reflection ///////////////

void GeneralTaskSteadyAccessoryListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskSteadyAccessoryListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskSteadyAccessoryListener);

}
