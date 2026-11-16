//
//  S2C_PlayerInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PlayerInfo);

void S2C_PlayerInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PlayerInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_profileId, pi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::wstring, m_UserName, n);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_uploadKey, uk);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int64, m_profileCreatedTime, regt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_gold, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_Gems, g1);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_gemCost, cg);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_addGem, ag);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_Leafs, l);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_freeGem, fg);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_paidGem, pg);
	REFLECTION_CLASSBUILDER_END(S2C_PlayerInfo);

}
