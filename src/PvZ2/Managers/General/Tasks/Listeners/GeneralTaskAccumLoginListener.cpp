//
//  GeneralTaskAccumLoginListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskAccumLoginListener);

void GeneralTaskAccumLoginListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	if (ProfileMgr::GetInstance().GetCurrentProfile()->IsFirstPopToday("AccumLoginTask"))
		CounterAdd();
	GeneralTaskPtr->SaveTask();
}

/////////////// Reflection ///////////////

void GeneralTaskAccumLoginListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskAccumLoginListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskAccumLoginListener);

}
