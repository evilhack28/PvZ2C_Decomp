//
//  ZombieAnimRig_Basic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Basic.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieAnimRig_Basic);

void ZombieAnimRig_Basic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Basic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasFlag);
		REFLECTION_CLASSBUILDER_FIELD(HelmType, m_helmType);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_helmDamageIndex);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_helmFlashStart);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Basic);
}
