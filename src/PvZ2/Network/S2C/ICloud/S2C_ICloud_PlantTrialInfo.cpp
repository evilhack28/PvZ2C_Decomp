//
//  S2C_ICloud_PlantTrialInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_PlantTrialInfo);

void S2C_ICloud_PlantTrialInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_PlantTrialInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, m_playerInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_PlantListInfo>, m_plantList, pl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_BonusInfo>, m_plantChipInfo, pcl);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_PlantTrialInfo);
}
