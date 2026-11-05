//
//  CallofWishObtainIntegralListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "GeneralTask.h"
#include "GameEventMgr.h"
#include "Message.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(CallofWishObtainIntegralListener);

void CallofWishObtainIntegralListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::GenericObtainIntegral, Sexy::MakeDelegate(*this, &CallofWishObtainIntegralListener::OnGenericObtainIntegral));
	NeedRemoveListener = true;
}

/////////////// Logic ///////////////

void CallofWishObtainIntegralListener::OnGenericObtainIntegral(int taskType, int i_num)
{
	if (taskType == 1)
	{
		CounterAdd(i_num);
		if (GeneralTaskPtr->CurrentState == 2)
			gMessageRouter->Post(&Message::CollectIntegralTaskFinish);
	}
}

/////////////// Reflection ///////////////

void CallofWishObtainIntegralListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CallofWishObtainIntegralListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(CallofWishObtainIntegralListener);

}
