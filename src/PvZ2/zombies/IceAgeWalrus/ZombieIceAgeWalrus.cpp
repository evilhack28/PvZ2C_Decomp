//
//  ZombieIceAgeWalrus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeWalrus.h"

ZombieIceAgeWalrusProps::~ZombieIceAgeWalrusProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeWalrus);

void ZombieIceAgeWalrus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeWalrus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(int, m_iPreviousCol);
	REFLECTION_CLASSBUILDER_END(ZombieIceAgeWalrus);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeWalrusProps);

void ZombieIceAgeWalrusProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeWalrusProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieIceAgeWalrusProps);
}
