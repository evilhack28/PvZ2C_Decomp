//
//  ZombiesAteYourBrainsOutro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiesAteYourBrainsOutro.h"

ZombiesAteYourBrainsOutro::~ZombiesAteYourBrainsOutro()
{
}

ZombiesAteYourBrainsOutroProperties::~ZombiesAteYourBrainsOutroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiesAteYourBrainsOutro);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiesAteYourBrainsOutroProperties);

void ZombiesAteYourBrainsOutroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiesAteYourBrainsOutroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModuleProperties);

	REFLECTION_CLASSBUILDER_END(ZombiesAteYourBrainsOutroProperties);
}
