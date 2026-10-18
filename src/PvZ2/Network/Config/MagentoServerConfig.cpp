//
//  MagentoServerConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "ServerConfig.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

MagentoServerConfig::~MagentoServerConfig()
{
}
/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(MagentoServerConfig);

void MagentoServerConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MagentoServerConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

		REFLECTION_CLASSBUILDER_FIELD(bool, bIsSandBox);
	REFLECTION_CLASSBUILDER_END(MagentoServerConfig);
}
