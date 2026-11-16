//
//  GeneralTaskFightZodiacListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskFightZodiacListener);

/////////////// Listener ///////////////

void GeneralTaskFightZodiacListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::FightZodiac_UseFirework, Sexy::MakeDelegate(*this, &GeneralTaskFightZodiacListener::onFightZodiac_UseFirework));
	NeedRemoveListener = true;
}

void GeneralTaskFightZodiacListener::onFightZodiac_UseFirework(int i_fireWorkNumber, bool i_killedZodiac)
{
	if (i_killedZodiac)
		CounterAdd();
}

/////////////// Reflection ///////////////

void GeneralTaskFightZodiacListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskFightZodiacListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskFightZodiacListener);

}
