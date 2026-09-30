//
//  PVZLiveConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PVZLiveConfig.h"

PVZLiveConfig::~PVZLiveConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZLiveConfig);

void PVZLiveConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Toggle);
		REFLECTION_CLASSBUILDER_FIELD(bool, Enabled);
	REFLECTION_CLASSBUILDER_END(Toggle);

	REFLECTION_CLASSBUILDER_BEGIN(PVZLiveConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(int, ContentRefreshMinutes);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<Toggle>, Toggles);
		REFLECTION_CLASSBUILDER_FIELD(float, EASquaredAwaitAdRewardTimeout);
	REFLECTION_CLASSBUILDER_END(PVZLiveConfig);
}
