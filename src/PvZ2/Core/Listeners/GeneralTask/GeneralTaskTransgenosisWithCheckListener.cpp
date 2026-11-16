//
//  GeneralTaskTransgenosisWithCheckListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "QuickJumpUtil.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

bool GetSecondWorldLevelCompleted(int);

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskTransgenosisWithCheckListener);

void GeneralTaskTransgenosisWithCheckListener::FinishAvatarTransgenic()
{
	CounterAdd();
}

void GeneralTaskTransgenosisWithCheckListener::FinishPlantTransgenic(int i_amount)
{
	CounterAdd(i_amount);
}

/////////////// Listener ///////////////

void GeneralTaskTransgenosisWithCheckListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::PlantTransgenic, Sexy::MakeDelegate(*this, &GeneralTaskTransgenosisWithCheckListener::FinishPlantTransgenic));
	gMessageRouter->Subscribe(&Message::AvatarTransgenic, Sexy::MakeDelegate(*this, &GeneralTaskTransgenosisWithCheckListener::FinishAvatarTransgenic));
	NeedRemoveListener = true;
}

int GeneralTaskTransgenosisWithCheckListener::JumpToTargetTask()
{
	if (GetSecondWorldLevelCompleted(3))
	{
		QuickJumpUtil::GetInstancePtr()->ShowTransgenosis();
		return 1;
	}
	return 0;
}

/////////////// Reflection ///////////////

void GeneralTaskTransgenosisWithCheckListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskTransgenosisWithCheckListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskTransgenosisWithCheckListener);

}
