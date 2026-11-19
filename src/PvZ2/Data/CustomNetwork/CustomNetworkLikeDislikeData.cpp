//
//  CustomNetworkLikeDislikeData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "CustomLevelMgr.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(CustomNetworkLikeDislikeData);

void CustomNetworkLikeDislikeData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CustomNetworkLikeDislikeData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);
	REFLECTION_CLASSBUILDER_END(CustomNetworkLikeDislikeData);
}
