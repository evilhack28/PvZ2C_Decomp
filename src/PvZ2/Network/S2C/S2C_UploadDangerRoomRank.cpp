//
//  S2C_UploadDangerRoomRank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_UploadDangerRoomRank);

void S2C_UploadDangerRoomRank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_DangerRoomContent);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, period, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, userId, ui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, rank, r);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, score, s);
	REFLECTION_CLASSBUILDER_END(S2C_DangerRoomContent);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_UploadDangerRoomRank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_DangerRoomContent, m_content, er);
	REFLECTION_CLASSBUILDER_END(S2C_UploadDangerRoomRank);

}
