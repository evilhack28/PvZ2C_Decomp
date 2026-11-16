//
//  GeneralTaskMiniGameListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "GeneralTaskConfig.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskMiniGameListener);

/////////////// Listener ///////////////

GeneralTaskMiniGameListener::GeneralTaskMiniGameListener()
{
}

GeneralTaskMiniGameListener::~GeneralTaskMiniGameListener()
{
	RemoveListener();
}

void GeneralTaskMiniGameListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	HappyVaseBreakerTaskPassSpecialData* data = NULL;
	if (GeneralTaskPtr->TaskConfig)
		data = GeneralTaskPtr->TaskConfig->Cast<HappyVaseBreakerTaskPassSpecialData>();
	if (data)
	{
		gMessageRouter->Subscribe(&Message::LevelEndForTask, Sexy::MakeDelegate(*this, &GeneralTaskMiniGameListener::onLevelEnded));
		NeedRemoveListener = true;
	}
}

void GeneralTaskMiniGameListener::onLevelEnded(LevelDefinitionForTask* i_defTask)
{
	HappyVaseBreakerTaskPassSpecialData* data = NULL;
	if (GeneralTaskPtr->TaskConfig)
		data = GeneralTaskPtr->TaskConfig->Cast<HappyVaseBreakerTaskPassSpecialData>();
	if (data)
	{
		for (size_t i = 0; i < data->Levels.size(); i++)
		{
			if (data->NeedWin == i_defTask->isWin && data->Levels[i].WorldName == i_defTask->levelName && std::find(data->Levels[i].LevelNums.begin(), data->Levels[i].LevelNums.end(), i_defTask->levelNumber) != data->Levels[i].LevelNums.end())
			{
				CounterAdd();
				break;
			}
		}
	}
}

/////////////// Reflection ///////////////

void GeneralTaskMiniGameListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskMiniGameListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskMiniGameListener);

}
