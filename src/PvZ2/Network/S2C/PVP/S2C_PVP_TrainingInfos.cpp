//
//  S2C_PVP_TrainingInfos.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PVP_TrainingInfos);

void S2C_PVP_TrainingInfos::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_Training_ZombieData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_serverID, id);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_queueNum, qn);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_firstLeftTime, fl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_haveNum, hn);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(uint64, m_queueOrder, qo);
	REFLECTION_CLASSBUILDER_END(S2C_Training_ZombieData);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP_ZombieData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_serverID, id);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_level, lvl);
	REFLECTION_CLASSBUILDER_END(S2C_PVP_ZombieData);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP_TrainingInfos);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_maxSpace, mc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_Training_ZombieData>, m_trainingList, zi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_PVP_ZombieData>, m_zombieList, cbz);
	REFLECTION_CLASSBUILDER_END(S2C_PVP_TrainingInfos);

}
