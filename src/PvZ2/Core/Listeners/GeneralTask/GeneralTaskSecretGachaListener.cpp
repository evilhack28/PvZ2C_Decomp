//
//  GeneralTaskSecretGachaListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskSecretGachaListener);

/////////////// Listener ///////////////

void GeneralTaskSecretGachaListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::FinishSecretGacha, Sexy::MakeDelegate(*this, &GeneralTaskSecretGachaListener::onFinishSecretGacha));
	NeedRemoveListener = true;
}

void GeneralTaskSecretGachaListener::onFinishSecretGacha(int number)
{
	CounterAdd(number);
}

/////////////// Reflection ///////////////

void GeneralTaskSecretGachaListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskSecretGachaListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskSecretGachaListener);

}
