//
//  ZombieArtifactAcidBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

ZombieArtifactAcidBasic::ZombieArtifactAcidBasic()
{
}

ZombieArtifactAcidBasic::~ZombieArtifactAcidBasic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieArtifactAcidBasic);

void ZombieArtifactAcidBasic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieArtifactAcidBasic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieBasic);

	REFLECTION_CLASSBUILDER_END(ZombieArtifactAcidBasic);
}
