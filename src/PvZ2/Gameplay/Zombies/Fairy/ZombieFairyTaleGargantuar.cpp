//
//  ZombieFairyTaleGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFairyTaleGargantuar.h"

ZombieFairyTaleGargantuarProps::~ZombieFairyTaleGargantuarProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieFairyTaleGargantuar);

void ZombieFairyTaleGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieFairyTaleGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuar);

	REFLECTION_CLASSBUILDER_END(ZombieFairyTaleGargantuar);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieFairyTaleGargantuarProps);

void ZombieFairyTaleGargantuarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieFairyTaleGargantuarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuarProps);

		REFLECTION_CLASSBUILDER_FIELD(bool, HasImp);
		REFLECTION_CLASSBUILDER_FIELD(std::string, SpawnShieldName);
	REFLECTION_CLASSBUILDER_END(ZombieFairyTaleGargantuarProps);
}

#include "ZombieGargantuar.h"
void ZombieFairyTaleGargantuar::onInitialized()
{
	 ZombieGargantuar::onInitialized();
}

bool ZombieFairyTaleGargantuar::isImpReadyToBeThrown()
{
	return false;
}
