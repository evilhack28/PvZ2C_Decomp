//
//  S2C_DailyAchievementConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_DailyAchievementConfig);

void S2C_DailyAchievementConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_AchieveConfigInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_activatedDate, ad);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, m_achieveList, al);
	REFLECTION_CLASSBUILDER_END(S2C_AchieveConfigInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_DailyAchievementConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_activityStart, st);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_activityEnd, et);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_AchieveInfo>, m_infoList, ai);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_AchieveConfigInfo>, m_configList, ac);
	REFLECTION_CLASSBUILDER_END(S2C_DailyAchievementConfig);

}
