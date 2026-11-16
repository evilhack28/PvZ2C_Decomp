//
//  S2C_GetPlantInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_GetPlantInfo);

void S2C_GetPlantInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_GetPlantInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_BonusInfo>, m_plantChipInfo, pcl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, m_plantList, npl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, nfc, nfc);
	REFLECTION_CLASSBUILDER_END(S2C_GetPlantInfo);

}
