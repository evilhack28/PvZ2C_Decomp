//
//  S2C_NoticeInfoGet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_NoticeInfoGet);

void S2C_NoticeInfoGet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_NoticeInfoGet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_id, id);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_readStatus, rs);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_rewardStatus, rws);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_CurrencyInfo, m_currency, ci);
	REFLECTION_CLASSBUILDER_END(S2C_NoticeInfoGet);

}
