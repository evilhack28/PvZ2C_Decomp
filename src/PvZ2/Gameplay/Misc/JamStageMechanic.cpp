//
//  JamStageMechanic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "JamStageMechanic.h"

JamStageMechanic::~JamStageMechanic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JamStageMechanic);

void JamStageMechanic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JamStageMechanic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(int, m_numberOfJamOverrides);
	REFLECTION_CLASSBUILDER_END(JamStageMechanic);
}
