//
//  S2C_SubGemRequest.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_SubGemRequest);

void S2C_SubGemRequest::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GemRequestInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, mGem, g);
	REFLECTION_CLASSBUILDER_END(GemRequestInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_SubGemRequest);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(GemRequestInfo, m_info, p);
	REFLECTION_CLASSBUILDER_END(S2C_SubGemRequest);

}
