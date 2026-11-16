//
//  GeneralTaskDailyConsumeGemsListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "GeneralTaskConfig.h"
#include "LawnApp.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

static time_t ToLocalTimeStamp(time_t i_time)
{
	return i_time;
}

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskDailyConsumeGemsListener);

/////////////// Listener ///////////////

GeneralTaskDailyConsumeGemsListener::GeneralTaskDailyConsumeGemsListener()
{
}

GeneralTaskDailyConsumeGemsListener::~GeneralTaskDailyConsumeGemsListener()
{
	RemoveListener();
}

void GeneralTaskDailyConsumeGemsListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::RefreshSomeTasksData, Sexy::MakeDelegate(*this, &GeneralTaskDailyConsumeGemsListener::onRefreshTaskInfo));
	NeedRemoveListener = true;
	onRefreshTaskInfo();
}

void GeneralTaskDailyConsumeGemsListener::onRefreshTaskInfo()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	time_t realTime = gLawnApp->GetRealBeijingTime();
	time_t t = ToLocalTimeStamp(realTime ? realTime : Sexy::SexyTime() / 1000);
	struct tm* now = gLawnApp->BeijingTime(&t);
	int today = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
	int gems = profile->GetNumGemConsumeRecordedBetween(today, today);
	Sexy::OutputDebugStrF("Gem Consume Currency, date is %d, gems are %d", today, gems);
	GeneralTaskPtr->TaskProgress = gems;
	if (GeneralTaskPtr->TaskConfig->Counter <= gems && GeneralTaskPtr->CurrentState != 3)
	{
		GeneralTaskPtr->CurrentState = 2;
		RemoveListener();
	}
	GeneralTaskPtr->SaveTask();
}

/////////////// Reflection ///////////////

void GeneralTaskDailyConsumeGemsListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskDailyConsumeGemsListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskDailyConsumeGemsListener);

}
