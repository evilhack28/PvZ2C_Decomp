//
//  GeneralTaskRichManRollDiceListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskRichManRollDiceListener);

void GeneralTaskRichManRollDiceListener::onRichMan_RollDice()
{
	CounterAdd();
}

/////////////// Listener ///////////////

void GeneralTaskRichManRollDiceListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::RichMan_RollDice, Sexy::MakeDelegate(*this, &GeneralTaskRichManRollDiceListener::onRichMan_RollDice));
	NeedRemoveListener = true;
}

/////////////// Reflection ///////////////

void GeneralTaskRichManRollDiceListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskRichManRollDiceListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskRichManRollDiceListener);

}
