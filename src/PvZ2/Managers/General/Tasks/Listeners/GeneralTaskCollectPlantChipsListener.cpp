//
//  GeneralTaskCollectPlantChipsListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskCollectPlantChipsListener);

/////////////// Listener ///////////////

GeneralTaskCollectPlantChipsListener::GeneralTaskCollectPlantChipsListener()
{
}

GeneralTaskCollectPlantChipsListener::~GeneralTaskCollectPlantChipsListener()
{
	RemoveListener();
}

void GeneralTaskCollectPlantChipsListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::ObtainPlantChips, Sexy::MakeDelegate(*this, &GeneralTaskCollectPlantChipsListener::onObtainPlantChip));
	NeedRemoveListener = true;
}

void GeneralTaskCollectPlantChipsListener::onObtainPlantChip(int i_chips)
{
	CounterAdd(i_chips);
}

/////////////// Reflection ///////////////

void GeneralTaskCollectPlantChipsListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskCollectPlantChipsListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskCollectPlantChipsListener);

}
