//
//  GeneralTaskBreakHappyVaseListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskBreakHappyVaseListener);

void GeneralTaskBreakHappyVaseListener::onHappyVaseBreaker_BreakVase()
{
	CounterAdd();
}

/////////////// Listener ///////////////

void GeneralTaskBreakHappyVaseListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::HappyVaseBreaker_BreakVase, Sexy::MakeDelegate(*this, &GeneralTaskBreakHappyVaseListener::onHappyVaseBreaker_BreakVase));
	NeedRemoveListener = true;
}

/////////////// Reflection ///////////////

void GeneralTaskBreakHappyVaseListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskBreakHappyVaseListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskBreakHappyVaseListener);

}
