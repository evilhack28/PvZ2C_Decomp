//
//  GeneralTaskPanneyGachaListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskPanneyGachaListener);

/////////////// Listener ///////////////

GeneralTaskPanneyGachaListener::GeneralTaskPanneyGachaListener()
{
}

GeneralTaskPanneyGachaListener::~GeneralTaskPanneyGachaListener()
{
	RemoveListener();
}

void GeneralTaskPanneyGachaListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::FinishPennyGacha, Sexy::MakeDelegate(*this, &GeneralTaskPanneyGachaListener::onFinishGacha));
	NeedRemoveListener = true;
}

void GeneralTaskPanneyGachaListener::onFinishGacha(int type, int size)
{
	CounterAdd(size);
}

int GeneralTaskPanneyGachaListener::JumpToTargetTask()
{
	if (ProfileUtils::HasCompletedLevel("egypt4", false, ProfileMgr::GetInstance().GetCurrentProfile()))
	{
		QuickJumpUtil::GetInstancePtr()->ShowGachaStore();
		return 1;
	}
	return 0;
}

/////////////// Reflection ///////////////

void GeneralTaskPanneyGachaListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskPanneyGachaListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskPanneyGachaListener);

}
