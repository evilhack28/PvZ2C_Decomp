//
//  GeneralTaskGemsRechargeDailyListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "UIHappyVaseBreaker.h"
#include "ActivityManager.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskGemsRechargeDailyListener);

void GeneralTaskGemsRechargeDailyListener::OnGemsRecharge(int num)
{
	CounterSet(num);
}

GeneralTaskGemsRechargeDailyListener::GeneralTaskGemsRechargeDailyListener()
{
}

GeneralTaskGemsRechargeDailyListener::~GeneralTaskGemsRechargeDailyListener()
{
	RemoveListener();
}

void GeneralTaskGemsRechargeDailyListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_HappyVaseBreaker);
	if (item.IsValid() && item.m_bOpen)
	{
		HappyVaseBreakerData data;
		if (item.GetDataSerialized(data))
			CounterSet(data.DailyGemsRecharge);
	}
	NeedRemoveListener = false;
}

/////////////// Reflection ///////////////

void GeneralTaskGemsRechargeDailyListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskGemsRechargeDailyListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskGemsRechargeDailyListener);

}
