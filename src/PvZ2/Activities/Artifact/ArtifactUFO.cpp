//
//  ArtifactUFO.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-10.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"
#include "ArtifactUFOTools.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ArtifactUFO::~ArtifactUFO()
{
}

/////////////// Logic ///////////////

void ArtifactUFO::onDestroy()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ArtifactUFO);

void ArtifactUFO::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactUFO);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Artifact);

		REFLECTION_CLASSBUILDER_FIELD(float, m_zombieFallDamageAmount);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<UFO>>, m_ufos);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie>>, m_risedZombies);
	REFLECTION_CLASSBUILDER_END(ArtifactUFO);
}
