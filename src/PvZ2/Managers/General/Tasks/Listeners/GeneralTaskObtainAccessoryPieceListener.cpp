//
//  GeneralTaskObtainAccessoryPieceListener.cpp
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

RT_CLASS_IMPLEMENT(GeneralTaskObtainAccessoryPieceListener);

/////////////// Listener ///////////////

void GeneralTaskObtainAccessoryPieceListener::RegisterListener(GeneralTask* i_task)
{
	GeneralTaskListener::RegisterListener(i_task);
	gMessageRouter->Subscribe(&Message::ObtainAccessoryPieces, Sexy::MakeDelegate(*this, &GeneralTaskObtainAccessoryPieceListener::OnObtainAccessoryPiece));
	NeedRemoveListener = true;
}

void GeneralTaskObtainAccessoryPieceListener::OnObtainAccessoryPiece(int i_pieceId, int i_amount)
{
	CounterAdd(i_amount);
}

int GeneralTaskObtainAccessoryPieceListener::JumpToTargetTask()
{
	return 0;
}

/////////////// Reflection ///////////////

void GeneralTaskObtainAccessoryPieceListener::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GeneralTaskObtainAccessoryPieceListener);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GeneralTaskListener);

	REFLECTION_CLASSBUILDER_END(GeneralTaskObtainAccessoryPieceListener);

}
