//
//  GeneralTaskBuySecretStoreListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskBuySecretStoreListener);

void GeneralTaskBuySecretStoreListener::OnBuySecretStore()
{
	CounterAdd();
}

/////////////// Listener ///////////////

void GeneralTaskBuySecretStoreListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::BuySecretStore, Sexy::MakeDelegate(*this, &GeneralTaskBuySecretStoreListener::OnBuySecretStore));
	NeedRemoveListener = true;
}

int GeneralTaskBuySecretStoreListener::JumpToTargetTask()
{
	if (ProfileUtils::HasCompletedLevel("egypt14", false, ProfileMgr::GetInstance().GetCurrentProfile()))
	{
		QuickJumpUtil::GetInstancePtr()->ShowSecretStore();
		return 1;
	}
	return 0;
}

/////////////// Reflection ///////////////

void GeneralTaskBuySecretStoreListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskBuySecretStoreListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskBuySecretStoreListener);

}
