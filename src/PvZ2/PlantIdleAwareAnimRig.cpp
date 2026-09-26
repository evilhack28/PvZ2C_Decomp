//
//  PlantIdleAwareAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantIdleAwareAnimRig.h"

PlantIdleAwareAnimRig::PlantIdleAwareAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantIdleAwareAnimRig);

void PlantIdleAwareAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantIdleAwareAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(IdleAnimationSelector, m_idleSelector);

	REFLECTION_CLASSBUILDER_END(PlantIdleAwareAnimRig);
}

#include "PlantAnimRig.h"
void PlantIdleAwareAnimRig::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}
