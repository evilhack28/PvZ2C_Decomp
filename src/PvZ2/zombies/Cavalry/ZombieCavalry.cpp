//
//  ZombieCavalry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCavalry.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCavalry);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCavalryProps);

void ZombieCavalryProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieCavalryProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, RiderType);
	REFLECTION_CLASSBUILDER_END(ZombieCavalryProps);
}

float ZombieCavalry::GetAmberScale()
{
	return 1.0f;
}
