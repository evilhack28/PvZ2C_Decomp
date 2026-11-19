//
//  NetworkTriggerArtifactInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "ArtifactMgr.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(NetworkTriggerArtifactInfo);

void NetworkTriggerArtifactInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NetworkTriggerArtifactInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);
	REFLECTION_CLASSBUILDER_END(NetworkTriggerArtifactInfo);
}
