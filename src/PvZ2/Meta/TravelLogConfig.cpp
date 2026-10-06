//
//  TravelLogConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "TravelLogConfig.h"

TravelLogConfig::TravelLogConfig()
{
}

TravelLogConfig::~TravelLogConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TravelLogConfig);

void TravelLogConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TravelLogConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<RtEmbeddedPtr<TravelLogData RT_COMMA PVZDB::TABLE_TRAVELLOG_CONFIG>>, TravelLogDatas);

	REFLECTION_CLASSBUILDER_END(TravelLogConfig);
}
