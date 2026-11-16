//
//  GeneralTaskListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "GeneralTaskConfig.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskListener);

GeneralTaskListener::GeneralTaskListener()
{
	NeedRemoveListener = false;
	GeneralTaskPtr = NULL;
}

GeneralTaskListener::~GeneralTaskListener()
{
}

void GeneralTaskListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskPtr = i_task;
}

void GeneralTaskListener::RemoveListener()
{
	if (NeedRemoveListener)
	{
		gMessageRouter->Unsubscribe(this);
		NeedRemoveListener = false;
	}
}

void GeneralTaskListener::CounterAdd(int i_num)
{
	CounterSet(i_num + GeneralTaskPtr->TaskProgress);
}

void GeneralTaskListener::CounterSet(int i_num)
{
	if (GeneralTaskPtr)
	{
		if (!GeneralTaskPtr->IsLocked())
		{
			GeneralTaskPtr->TaskProgress = i_num;
			GeneralTaskPtr->CurrentState = 1;
			if (GeneralTaskPtr->TaskConfig->Counter <= i_num)
			{
				GeneralTaskPtr->CurrentState = 2;
				GeneralTaskPtr->OnCompletedTask();
				RemoveListener();
			}
			GeneralTaskPtr->SaveTask();
		}
	}
}

/////////////// Reflection ///////////////

void GeneralTaskListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD(bool, NeedRemoveListener);
	REFLECTION_CLASSBUILDER_END(GeneralTaskListener);

}
