//
//  ZombieTargetGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombieTargetGargantuar.h"

ZombieTargetGargantuarProps::~ZombieTargetGargantuarProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieTargetGargantuar);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieTargetGargantuarProps);

void ZombieTargetGargantuarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieTargetGargantuarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, ImpType);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ProjectileLayersToHide);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, ImpSpawnOffset);
	REFLECTION_CLASSBUILDER_END(ZombieTargetGargantuarProps);
}
