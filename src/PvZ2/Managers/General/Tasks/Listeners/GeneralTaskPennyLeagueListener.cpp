//
//  GeneralTaskPennyLeagueListener.cpp
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

namespace RiftUtils { int GetCurrentLeague(); }

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskPennyLeagueListener);

void GeneralTaskPennyLeagueListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	if (GeneralTaskPtr->TaskConfig)
	{
		BattleOrderTaskData* data = GeneralTaskPtr->TaskConfig->Cast<BattleOrderTaskData>();
		if (data)
		{
			Sexy::OutputDebugStrF("RiftUtils::GetCurrentLeague %d, targte PennyLeague %d", RiftUtils::GetCurrentLeague(), data->PennyLeague);
			if (RiftUtils::GetCurrentLeague() >= data->PennyLeague)
			{
			if (GeneralTaskPtr->CurrentState != 3)
			{
				GeneralTaskPtr->TaskProgress = 1;
				GeneralTaskPtr->CurrentState = 2;
			}
			GeneralTaskPtr->SaveTask();
			}
		}
	}
}

/////////////// Reflection ///////////////

void GeneralTaskPennyLeagueListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskPennyLeagueListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskPennyLeagueListener);

}
