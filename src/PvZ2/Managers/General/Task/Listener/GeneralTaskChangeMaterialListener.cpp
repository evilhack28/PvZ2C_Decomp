//
//  GeneralTaskChangeMaterialListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "NameMapper.h"
#include "GeneralTaskConfig.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskChangeMaterialListener);

/////////////// Listener ///////////////

void GeneralTaskChangeMaterialListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::BeforeChangeMaterialNumber, Sexy::MakeDelegate(*this, &GeneralTaskChangeMaterialListener::onBeforeChangeMaterialNumber));
	NeedRemoveListener = true;
}

void GeneralTaskChangeMaterialListener::onBeforeChangeMaterialNumber(int i_matId, int i_diff)
{
	if (GeneralTaskPtr->TaskConfig)
	{
		BattleOrderTaskData* data = GeneralTaskPtr->TaskConfig->Cast<BattleOrderTaskData>();
		if (data)
		{
			int matId = MaterialItemMapper::GetInstance().GetIdForName(data->MaterialName);
			if (i_matId == matId && i_diff > 0)
				CounterAdd(i_diff);
		}
	}
}

/////////////// Reflection ///////////////

void GeneralTaskChangeMaterialListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskChangeMaterialListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskChangeMaterialListener);

}
