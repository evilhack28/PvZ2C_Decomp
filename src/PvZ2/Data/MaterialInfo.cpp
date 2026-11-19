//
//  MaterialInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "PlayerInfo.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(MaterialInfo);

void MaterialInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MaterialInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

	REFLECTION_CLASSBUILDER_END(MaterialInfo);
}
