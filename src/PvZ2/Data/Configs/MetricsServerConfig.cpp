//
//  MetricsServerConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "ServerConfig.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

MetricsServerConfig::~MetricsServerConfig()
{
}
/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(MetricsServerConfig);

void MetricsServerConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MetricsServerConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_END(MetricsServerConfig);
}
