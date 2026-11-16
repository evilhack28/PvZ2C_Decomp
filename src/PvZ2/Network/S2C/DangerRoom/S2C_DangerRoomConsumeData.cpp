//
//  S2C_DangerRoomConsumeData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_DangerRoomConsumeData);

void S2C_DangerRoomConsumeData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_DangerRoomConsumeData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_gem, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_cuke, ubn);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_plantfood, uebn);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_DangerRoomPlantNum>, m_plantUsed, upnl);
	REFLECTION_CLASSBUILDER_END(S2C_DangerRoomConsumeData);

}
