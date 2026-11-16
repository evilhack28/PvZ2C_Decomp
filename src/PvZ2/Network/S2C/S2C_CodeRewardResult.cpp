//
//  S2C_CodeRewardResult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_CodeRewardResult);

void S2C_CodeRewardResult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_CodeRewardPlantNum);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_plantID, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_num, q);
	REFLECTION_CLASSBUILDER_END(S2C_CodeRewardPlantNum);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_CodeRewardResult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_codeRet, t);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_errMsg, msg);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_CodeRewardPlantNum>, m_plantNumList, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, m_playInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_codeInfo, ct);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_code, c);
	REFLECTION_CLASSBUILDER_END(S2C_CodeRewardResult);

}
