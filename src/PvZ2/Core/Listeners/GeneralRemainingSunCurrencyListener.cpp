//
//  GeneralRemainingSunCurrencyListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "GeneralTaskConfig.h"
#include "GameEventMgr.h"
#include "LawnApp.h"
#include "Board.h"
#include "PVZ1ModeUtils.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralRemainingSunCurrencyListener);

/////////////// Listener ///////////////

void GeneralRemainingSunCurrencyListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::PvZ1FinishLevel, Sexy::MakeDelegate(*this, &GeneralRemainingSunCurrencyListener::onPvZ1FinishLevel));
	NeedRemoveListener = true;
}

void GeneralRemainingSunCurrencyListener::onPvZ1FinishLevel(int levelNodeID, bool isHard)
{
	PvZ1AchievementData* data = NULL;
	if (GeneralTaskPtr->TaskConfig)
		data = GeneralTaskPtr->TaskConfig->Cast<PvZ1AchievementData>();
	if (data && gLawnApp->m_board && PVZ1ModeUtils::IsPlayingPVZ1Level() && gLawnApp->m_board->GetSunCurrency() >= data->RemainingSunCurrency)
		CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralRemainingSunCurrencyListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralRemainingSunCurrencyListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralRemainingSunCurrencyListener);
}
