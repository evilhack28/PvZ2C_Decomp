//
//  UpdateServerConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "ServerConfig.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

UpdateServerConfig::UpdateServerConfig()
{
}

UpdateServerConfig::~UpdateServerConfig()
{
}

/////////////// Accessors ///////////////

std::string UpdateServerConfig::GetUpdateURL()
{
	return ShippingURL;
}
/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(UpdateServerConfig);

void UpdateServerConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(UpdateServerConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_END(UpdateServerConfig);
}
