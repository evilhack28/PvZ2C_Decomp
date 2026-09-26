//
//  ComponentOnDeath.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ComponentOnDeath.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentOnDeath);

void ComponentOnDeath::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ComponentOnDeath);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ComponentBase);

	REFLECTION_CLASSBUILDER_END(ComponentOnDeath);
}
