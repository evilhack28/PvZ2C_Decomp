//
//  LostNetActivityConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LostNetActivityConfig.h"

LostNetActivityConfig::LostNetActivityConfig()
{
}

LostNetActivityConfig::~LostNetActivityConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LostNetActivityConfig);

void LostNetActivityConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LostNetActivityConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_inited);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, RewardPool);

	REFLECTION_CLASSBUILDER_END(LostNetActivityConfig);
}
