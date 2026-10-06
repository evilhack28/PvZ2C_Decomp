//
//  ZombieRomanMedusa.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieRomanMedusa.h"

ZombieRomanMedusaProps::~ZombieRomanMedusaProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRomanMedusa);

void ZombieRomanMedusa::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieRomanMedusa);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieIceAgeTroglobite);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextPetrifyTime);
	REFLECTION_CLASSBUILDER_END(ZombieRomanMedusa);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRomanMedusaProps);

void ZombieRomanMedusaProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieRomanMedusaProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieIceAgeTroglobiteProps);

		REFLECTION_CLASSBUILDER_FIELD(float, PetrifiedZombieHealthMultiplier);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PetrifiedZombieType);
	REFLECTION_CLASSBUILDER_END(ZombieRomanMedusaProps);
}
