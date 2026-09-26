//
//  ServerConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ServerConfig.h"

ServerConfig::ServerConfig()
{
}

ServerConfig::~ServerConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ServerConfig);

void ServerConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ServerConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_END(ServerConfig);
}
