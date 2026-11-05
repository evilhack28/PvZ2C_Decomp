//
//  GeneralTaskSuperVIPLoginListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskSuperVIPLoginListener);

void GeneralTaskSuperVIPLoginListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	if (ProfileMgr::GetInstance().GetCurrentProfile()->IsMonthlyCardActivated(E_MC_SUPER))
	{
		if (GeneralTaskPtr->CurrentState != 3)
		{
			GeneralTaskPtr->TaskProgress = 1;
			GeneralTaskPtr->CurrentState = 2;
		}
		GeneralTaskPtr->SaveTask();
	}
}

/////////////// Reflection ///////////////

void GeneralTaskSuperVIPLoginListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskSuperVIPLoginListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskSuperVIPLoginListener);

}
