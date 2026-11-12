//
//  S2C_Playback_HistoryList.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_Playback_HistoryList);

void S2C_Playback_HistoryList::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_Playback_HistoryList);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<PlaybackBrief>, m_historyList, fh);
	REFLECTION_CLASSBUILDER_END(S2C_Playback_HistoryList);

}
