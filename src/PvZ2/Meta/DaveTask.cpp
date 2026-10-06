//
//  DaveTask.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "DaveTask.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "LawnApp.h"

/////////////// Construction ///////////////

DaveTask::DaveTask()
{
	needRemoveListener = false;
}

DaveTask::~DaveTask()
{
}

/////////////// Reflection ///////////////

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT_ABSTRACT(DaveTask);

void DaveTask::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DaveTask);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_END(DaveTask);
}

/////////////// Methods ///////////////

void DaveTask::Init(DaveTaskDataPtr i_taskData)
{
	ID = i_taskData->ID;
	GID = i_taskData->GroupID;
	IsNormal = i_taskData->IsNormalChallange;
	TaskConfig = i_taskData;
	ActivityName = i_taskData->ActivityName;
	LoadState();
	if ((unsigned int)CurrentState <= 1)
		AddListener();
}

void DaveTask::SaveState()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	TravelLogTaskSaveInfo info;
	info.ID = ID;
	info.GroupID = GID;
	info.Progress = TaskProgress;
	info.State = CurrentState;
	info.Creation = CreationDate;
	if (ActivityName == "PENNY")
		profile->UpdatePennyTaskSaveInfo(info);
	else
		profile->UpdateDaveTaskSaveInfo(info);
}

void DaveTask::LoadState()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	TravelLogTaskSaveInfo info;
	if (ActivityName == "PENNY")
		info = profile->GetPennyTaskSaveInfo(ID);
	else
		info = profile->GetDaveTaskSaveInfo(ID);
	if (info.ID == ID)
	{
		TaskProgress = info.Progress;
		CurrentState = info.State;
		CreationDate = info.Creation;
		return;
	}
	TaskProgress = 0;
	CurrentState = 0;
	CreationDate = gLawnApp->GetRealServerTime();
}

void DaveTask::Destory()
{
	RemoveListener();
}

void DaveTask::ForceSetState(int i_state)
{
	ProfileMgr::GetInstance().GetCurrentProfile();
	if (i_state != 3)
		return;
	CurrentState = i_state;
	TaskProgress = TaskConfig->Requirement;
	RemoveListener();
	SaveState();
}

void DaveTask::TaskCompleted()
{
	CurrentState = 3;
	SaveState();
}

time_t DaveTask::GetRemainTime()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	switch (GID)
	{
	case 1:
		if (profile->IsInThisWeek(CreationDate))
		{
			time_t now = gLawnApp->GetRealServerTime();
			return ((((int)now - 0x4d580) / 0x93a80 + 1) * 0x93a80 + 0x4d580) - now;
		}
		break;
	case 2:
		return 0x7fffffff;
	case 0:
		if (profile->IsToday(CreationDate))
		{
			time_t now = gLawnApp->GetRealServerTime();
			return ((((int)now + 0x7080) / 0x15180 + 1) * 0x15180 - 0x7080) - now;
		}
		break;
	}
	return 0;
}
