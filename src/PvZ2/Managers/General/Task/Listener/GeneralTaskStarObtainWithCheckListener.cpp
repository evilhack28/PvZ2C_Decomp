//
//  GeneralTaskStarObtainWithCheckListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "GeneralTaskConfig.h"
#include "PlayerInfo.h"
#include "QuickJumpUtil.h"
#include "ProfileUtils.h"
#include "ProfileMgr.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskStarObtainWithCheckListener);

/////////////// Listener ///////////////

void GeneralTaskStarObtainWithCheckListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	int stars = ProfileMgr::GetInstance().GetCurrentProfile()->GetNumStars();
	if (stars >= i_task->TaskConfig->Counter)
	{
		CounterSet(stars);
		NeedRemoveListener = false;
		return;
	}
	gMessageRouter->Subscribe(&Message::ObtainStar, Sexy::MakeDelegate(*this, &GeneralTaskStarObtainWithCheckListener::OnObtainStar));
	NeedRemoveListener = true;
}

int GeneralTaskStarObtainWithCheckListener::JumpToTargetTask()
{
	if (ProfileUtils::HasCompletedLevel("egypt3", false, ProfileMgr::GetInstance().GetCurrentProfile()))
	{
		QuickJumpUtil::GetInstancePtr()->ShowStarConvert();
		return 1;
	}
	return 0;
}

void GeneralTaskStarObtainWithCheckListener::OnObtainStar(int num)
{
	int stars = ProfileMgr::GetInstance().GetCurrentProfile()->GetNumStars();
	CounterSet(stars);
}

/////////////// Reflection ///////////////

void GeneralTaskStarObtainWithCheckListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskStarObtainWithCheckListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskStarObtainWithCheckListener);

}
