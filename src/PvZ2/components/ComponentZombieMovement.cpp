//
//  ComponentZombieMovement.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ComponentZombieMovement.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentZombieMovement);

void ComponentZombieMovement::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ComponentZombieMovement);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ComponentBase);

	REFLECTION_CLASSBUILDER_FIELD(CurveCollection_Float, m_lerpingValues);

	REFLECTION_CLASSBUILDER_END(ComponentZombieMovement);
}
