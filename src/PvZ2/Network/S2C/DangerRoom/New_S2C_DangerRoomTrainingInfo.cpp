//
//  New_S2C_DangerRoomTrainingInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"
#include "UIDangerRoomSkipLevel.h"

New_S2C_DangerRoomTrainingInfo::New_S2C_DangerRoomTrainingInfo()
{
}

New_S2C_DangerRoomTrainingInfo::~New_S2C_DangerRoomTrainingInfo()
{
}

void New_S2C_DangerRoomTrainingInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_DangerRoomTrainingInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, m_currentTrainingCount, lt);
	REFLECTION_CLASSBUILDER_END(New_S2C_DangerRoomTrainingInfo);
}

RT_CLASS_IMPLEMENT(New_S2C_DangerRoomTrainingInfo);
