//
//  RecruitStarNumListener.cpp
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

RT_CLASS_IMPLEMENT(RecruitStarNumListener);

void RecruitStarNumListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::RecruitStarNum, Sexy::MakeDelegate(*this, &RecruitStarNumListener::onAddRecruitNum));
	onAddRecruitNum();
}

/////////////// Logic ///////////////

void RecruitStarNumListener::onAddRecruitNum()
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_InvitationRewards);
	if (item.IsValid() && item.m_bOpen)
	{
		InvitationData data;
		if (item.GetDataSerialized(data))
			CounterSet(data.m_invitationInfo.m_inviteStarCount);
	}
}

/////////////// Reflection ///////////////

void RecruitStarNumListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RecruitStarNumListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(RecruitStarNumListener);

}
