//
//  Artifact.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

ArtifactProperties::~ArtifactProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArtifactProperties);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Artifact);

void Artifact::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CommonData);
		REFLECTION_CLASSBUILDER_FIELD(int32, MaxUsedTimes);
		REFLECTION_CLASSBUILDER_FIELD(float, Cooldown);
	REFLECTION_CLASSBUILDER_END(CommonData);

	REFLECTION_CLASSBUILDER_BEGIN(Artifact);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ArtifactProperties>, m_props);
		REFLECTION_CLASSBUILDER_FIELD(CommonData, m_commonData);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextMainFieldTime);
	REFLECTION_CLASSBUILDER_END(Artifact);
}

void Artifact::registerForEvents()
{
}

void Artifact::DisplayPassiveSkill(float i_arg)
{
}

void Artifact::unregisterForEvents()
{
}

bool Artifact::CanGetArtifactBoosts(int i_arg)
{
	return true;
}

void Artifact::ActivateSpeciallyOnDisplayBoard(int i_arg)
{
}
