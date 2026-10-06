//
//  Effect_ZoybeanPodSmoke.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ZoybeanPod.h"

Effect_ZoybeanPodSmoke::Effect_ZoybeanPodSmoke()
{
	m_renderDifferenceFromPlant = (decltype(m_renderDifferenceFromPlant))6000;
}

Effect_ZoybeanPodSmoke::~Effect_ZoybeanPodSmoke()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_ZoybeanPodSmoke);

void Effect_ZoybeanPodSmoke::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_ZoybeanPodSmoke);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_ZoybeanPodSmoke);
}
