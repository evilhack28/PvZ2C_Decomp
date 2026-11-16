//
//  ArtifactBeehive.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-10.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ArtifactBeehive::~ArtifactBeehive()
{
}

/////////////// Logic ///////////////

void ArtifactBeehive::Update()
{
	Artifact::Update();
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ArtifactBeehive);

void ArtifactBeehive::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactBeehive);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Artifact);

	REFLECTION_CLASSBUILDER_END(ArtifactBeehive);
}
