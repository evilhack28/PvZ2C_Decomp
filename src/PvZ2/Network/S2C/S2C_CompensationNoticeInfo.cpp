//
//  S2C_CompensationNoticeInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_CompensationNoticeInfo);

void S2C_CompensationNoticeInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_CompensationNoticeInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_type, t);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_resourceNum, n);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_coinNum, ag);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_medalNum, am);
	REFLECTION_CLASSBUILDER_END(S2C_CompensationNoticeInfo);

}
