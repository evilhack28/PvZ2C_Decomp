//
//  TimeServerConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "ServerConfig.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

TimeServerConfig::~TimeServerConfig()
{
}
/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(TimeServerConfig);

void TimeServerConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TimeServerConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_END(TimeServerConfig);
}
