//
//  S2C_PlaybackData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PlaybackData);

void S2C_PlaybackData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PlaybackData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(uint64, m_battleID, hi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_info, fh);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_infoMD5, md);
	REFLECTION_CLASSBUILDER_END(S2C_PlaybackData);

}
