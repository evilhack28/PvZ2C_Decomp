//
//  LawnStringServerConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "ServerConfig.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

LawnStringServerConfig::LawnStringServerConfig()
{
}

LawnStringServerConfig::~LawnStringServerConfig()
{
}

/////////////// Accessors ///////////////

std::string LawnStringServerConfig::GetFileURL()
{
	return ShippingFileURL;
}

std::string LawnStringServerConfig::GetFileInfoURL()
{
	return ShippingFileInfoURL;
}
/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(LawnStringServerConfig);

void LawnStringServerConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LawnStringServerConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_END(LawnStringServerConfig);
}
