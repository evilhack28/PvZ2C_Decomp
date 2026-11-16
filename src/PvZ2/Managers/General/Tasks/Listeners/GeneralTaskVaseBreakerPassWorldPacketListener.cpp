//
//  GeneralTaskVaseBreakerPassWorldPacketListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogListener.h"
#include "GeneralTask.h"
#include "LevelDefinition.h"
#include "Board.h"
#include "LawnApp.h"
#include "GameEventMgr.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

RT_CLASS_IMPLEMENT(GeneralTaskVaseBreakerPassWorldPacketListener);

/////////////// Listener ///////////////

void GeneralTaskVaseBreakerPassWorldPacketListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::LevelEndForTask, Sexy::MakeDelegate(*this, &GeneralTaskVaseBreakerPassWorldPacketListener::onLevelEnded));
	NeedRemoveListener = true;
}

void GeneralTaskVaseBreakerPassWorldPacketListener::onLevelEnded(LevelDefinitionForTask* i_defTask)
{
	if (i_defTask->isWin && gLawnApp->m_board && gLawnApp->m_board->GetLevelDefinitionPtr())
	{
		if (gLawnApp->m_board->GetLevelDefinitionPtr()->IsVasebreaker && gLawnApp->m_board->GetLevelDefinitionPtr()->FirstRewardParam == "powerupvasebreakerbutter")
			CounterAdd();
	}
}

/////////////// Reflection ///////////////

void GeneralTaskVaseBreakerPassWorldPacketListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskVaseBreakerPassWorldPacketListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskVaseBreakerPassWorldPacketListener);

}
