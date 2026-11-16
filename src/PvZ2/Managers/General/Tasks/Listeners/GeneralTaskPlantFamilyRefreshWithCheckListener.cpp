//
//  GeneralTaskPlantFamilyRefreshWithCheckListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskPlantFamilyRefreshWithCheckListener);

void GeneralTaskPlantFamilyRefreshWithCheckListener::OnPlantFamilyRefresh()
{
	CounterAdd();
}

/////////////// Listener ///////////////

void GeneralTaskPlantFamilyRefreshWithCheckListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::PlantFamilyRefresh, Sexy::MakeDelegate(*this, &GeneralTaskPlantFamilyRefreshWithCheckListener::OnPlantFamilyRefresh));
	NeedRemoveListener = true;
}

int GeneralTaskPlantFamilyRefreshWithCheckListener::JumpToTargetTask()
{
	if (ProfileUtils::HasCompletedLevel("egypt10", false, ProfileMgr::GetInstance().GetCurrentProfile()))
	{
		QuickJumpUtil::GetInstancePtr()->ShowPlantFamily();
		return 1;
	}
	return 0;
}

/////////////// Reflection ///////////////

void GeneralTaskPlantFamilyRefreshWithCheckListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskPlantFamilyRefreshWithCheckListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskPlantFamilyRefreshWithCheckListener);

}
