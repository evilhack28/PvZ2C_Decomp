//
//  GeneralTaskBreakGoldenEggListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskBreakGoldenEggListener);

void GeneralTaskBreakGoldenEggListener::onFestivalGoldenEgg_BreakEgg()
{
	CounterAdd();
}

/////////////// Listener ///////////////

void GeneralTaskBreakGoldenEggListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::FestivalGoldenEgg_BreakEgg, Sexy::MakeDelegate(*this, &GeneralTaskBreakGoldenEggListener::onFestivalGoldenEgg_BreakEgg));
	NeedRemoveListener = true;
}

/////////////// Reflection ///////////////

void GeneralTaskBreakGoldenEggListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskBreakGoldenEggListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskBreakGoldenEggListener);

}
