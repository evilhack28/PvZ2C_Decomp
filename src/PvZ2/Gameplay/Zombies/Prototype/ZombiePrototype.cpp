//
//  ZombiePrototype.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombiePrototype.h"

ZombiePrototypeProps::ZombiePrototypeProps()
{
}

ZombiePrototypeProps::~ZombiePrototypeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePrototypeProps);

void ZombiePrototypeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePrototypeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_FIELD(std::string, StaticArtImageAsset);
	REFLECTION_CLASSBUILDER_FIELD(float, ArtScale);

	REFLECTION_CLASSBUILDER_END(ZombiePrototypeProps);
}
