//
//  ZombieExplosionProofPolice.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieExplosionProofPolice.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieExplosionProofPolice);

void ZombieExplosionProofPolice::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieExplosionProofPolice);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActions);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextCastTime);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_helmDamageIndex);
	REFLECTION_CLASSBUILDER_END(ZombieExplosionProofPolice);
}

void ZombieExplosionProofPolice::onArmorDropped(std::string i_arg)
{
}
