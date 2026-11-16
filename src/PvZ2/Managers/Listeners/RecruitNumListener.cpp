//
//  RecruitNumListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "GameEventMgr.h"
#include "ActivityManager.h"
#include "UIInvitation.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(RecruitNumListener);

void RecruitNumListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::RecruitNum, Sexy::MakeDelegate(*this, &RecruitNumListener::onAddRecruitNum));
	onAddRecruitNum();
}

/////////////// Logic ///////////////

void RecruitNumListener::onAddRecruitNum()
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_InvitationRewards);
	if (item.IsValid() && item.m_bOpen)
	{
		InvitationData data;
		if (item.GetDataSerialized(data))
			CounterSet(data.m_invitationInfo.m_inviteCount);
	}
}

/////////////// Reflection ///////////////

void RecruitNumListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RecruitNumListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(RecruitNumListener);

}
