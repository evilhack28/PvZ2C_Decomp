//
//  ZombieFairyTaleArmedGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFairyTaleGargantuar.h"

ZombieFairyTaleArmedGargantuarProps::~ZombieFairyTaleArmedGargantuarProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieFairyTaleArmedGargantuar);

void ZombieFairyTaleArmedGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieFairyTaleArmedGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieFairyTaleGargantuar);

	REFLECTION_CLASSBUILDER_END(ZombieFairyTaleArmedGargantuar);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieFairyTaleArmedGargantuarProps);

void ZombieFairyTaleArmedGargantuarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieFairyTaleArmedGargantuarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieFairyTaleGargantuarProps);

	REFLECTION_CLASSBUILDER_END(ZombieFairyTaleArmedGargantuarProps);
}

#include "ZombieFairyTaleGargantuar.h"
void ZombieFairyTaleArmedGargantuar::onInitialized()
{
	 ZombieFairyTaleGargantuar::onInitialized();
}

#include "ZombieFairyTaleGargantuar.h"
void ZombieFairyTaleArmedGargantuar::onZombieInitialize()
{
	 ZombieFairyTaleGargantuar::onZombieInitialize();
}

#include "ZombieFairyTaleGargantuar.h"
void ZombieFairyTaleArmedGargantuar::playDeathAnimation()
{
	 ZombieFairyTaleGargantuar::playDeathAnimation();
}
