//
//  New_S2C_MoveResult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"

#include "RichManUIMgr.h"
#include "RichmanDefine.h"
#include "RichmanTileEvent.h"

New_S2C_MoveResult::New_S2C_MoveResult()
{
}

New_S2C_MoveResult::~New_S2C_MoveResult()
{
}

void New_S2C_MoveResult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EventReward);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, ObjectId, i);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, Quantity, q);
	REFLECTION_CLASSBUILDER_END(EventReward);

	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_MoveResult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, m_leftDice, lb);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, m_locationIndex, p);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<EventReward>, m_rewards, b);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<RichmanTileEventConfig>, m_events, event);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, m_type, t);
	REFLECTION_CLASSBUILDER_END(New_S2C_MoveResult);
}

RT_CLASS_IMPLEMENT(New_S2C_MoveResult);
