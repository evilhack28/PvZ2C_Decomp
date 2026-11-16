//
//  GeneralTaskAddCoinListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskAddCoinListener);

/////////////// Listener ///////////////

GeneralTaskAddCoinListener::GeneralTaskAddCoinListener()
{
}

GeneralTaskAddCoinListener::~GeneralTaskAddCoinListener()
{
	RemoveListener();
}

void GeneralTaskAddCoinListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::CoinCurrencyChanged, Sexy::MakeDelegate(*this, &GeneralTaskAddCoinListener::onRefreshTaskInfo));
	NeedRemoveListener = true;
}

void GeneralTaskAddCoinListener::onRefreshTaskInfo(int i_num)
{
	CounterAdd(i_num);
}

/////////////// Reflection ///////////////

void GeneralTaskAddCoinListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskAddCoinListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskAddCoinListener);

}
