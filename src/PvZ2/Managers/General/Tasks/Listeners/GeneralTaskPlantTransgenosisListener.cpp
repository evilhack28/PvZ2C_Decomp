//
//  GeneralTaskPlantTransgenosisListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskPlantTransgenosisListener);

/////////////// Listener ///////////////

GeneralTaskPlantTransgenosisListener::GeneralTaskPlantTransgenosisListener()
{
}

GeneralTaskPlantTransgenosisListener::~GeneralTaskPlantTransgenosisListener()
{
	RemoveListener();
}

void GeneralTaskPlantTransgenosisListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::PlantTransgenic, Sexy::MakeDelegate(*this, &GeneralTaskPlantTransgenosisListener::FinishPlantTransgenic));
	NeedRemoveListener = true;
}

void GeneralTaskPlantTransgenosisListener::FinishPlantTransgenic(int i_amount)
{
	CounterAdd(i_amount);
}

/////////////// Reflection ///////////////

void GeneralTaskPlantTransgenosisListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskPlantTransgenosisListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskPlantTransgenosisListener);

}
