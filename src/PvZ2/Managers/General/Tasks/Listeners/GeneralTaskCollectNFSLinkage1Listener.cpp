//
//  GeneralTaskCollectNFSLinkage1Listener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskCollectNFSLinkage1Listener);

/////////////// Listener ///////////////

GeneralTaskCollectNFSLinkage1Listener::GeneralTaskCollectNFSLinkage1Listener()
{
}

GeneralTaskCollectNFSLinkage1Listener::~GeneralTaskCollectNFSLinkage1Listener()
{
	RemoveListener();
}

void GeneralTaskCollectNFSLinkage1Listener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::NFSLinkageTaskReward, Sexy::MakeDelegate(*this, &GeneralTaskCollectNFSLinkage1Listener::onLinkageTaskReward));
	NeedRemoveListener = true;
}

void GeneralTaskCollectNFSLinkage1Listener::onLinkageTaskReward()
{
	CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralTaskCollectNFSLinkage1Listener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskCollectNFSLinkage1Listener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskCollectNFSLinkage1Listener);

}
