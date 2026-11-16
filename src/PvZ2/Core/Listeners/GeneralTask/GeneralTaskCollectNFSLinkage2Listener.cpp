//
//  GeneralTaskCollectNFSLinkage2Listener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskCollectNFSLinkage2Listener);

/////////////// Listener ///////////////

GeneralTaskCollectNFSLinkage2Listener::GeneralTaskCollectNFSLinkage2Listener()
{
}

GeneralTaskCollectNFSLinkage2Listener::~GeneralTaskCollectNFSLinkage2Listener()
{
	RemoveListener();
}

void GeneralTaskCollectNFSLinkage2Listener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::NFSLinkageAvatarReward, Sexy::MakeDelegate(*this, &GeneralTaskCollectNFSLinkage2Listener::onLinkageReward2));
	NeedRemoveListener = true;
}

void GeneralTaskCollectNFSLinkage2Listener::onLinkageReward2()
{
	CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralTaskCollectNFSLinkage2Listener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskCollectNFSLinkage2Listener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskCollectNFSLinkage2Listener);

}
