//
//  GeneralTaskAnyGachaListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskAnyGachaListener);

/////////////// Listener ///////////////

void GeneralTaskAnyGachaListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::FinishPennyGacha, Sexy::MakeDelegate(*this, &GeneralTaskAnyGachaListener::onFinishGacha));
	gMessageRouter->Subscribe(&Message::FinishSecretGacha, Sexy::MakeDelegate(*this, &GeneralTaskAnyGachaListener::onFinishSecretGacha));
	gMessageRouter->Subscribe(&Message::FinishLimitGacha, Sexy::MakeDelegate(*this, &GeneralTaskAnyGachaListener::onFinishLimitGacha));
	NeedRemoveListener = true;
}

void GeneralTaskAnyGachaListener::onFinishGacha(int type, int size)
{
	CounterAdd(size);
}

void GeneralTaskAnyGachaListener::onFinishLimitGacha(int number)
{
	CounterAdd(number);
}

void GeneralTaskAnyGachaListener::onFinishSecretGacha(int number)
{
	CounterAdd(number);
}

/////////////// Reflection ///////////////

void GeneralTaskAnyGachaListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskAnyGachaListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskAnyGachaListener);

}
