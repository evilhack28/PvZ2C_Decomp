//
//  ArtifactAcid.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-10.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ArtifactAcid::ArtifactAcid()
{
}

ArtifactAcid::~ArtifactAcid()
{
}

/////////////// Logic ///////////////

void ArtifactAcid::Update()
{
	Artifact::Update();
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ArtifactAcid);

void ArtifactAcid::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactAcid);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Artifact);

		REFLECTION_CLASSBUILDER_FIELD(Point, m_mainSrcPoint);
	REFLECTION_CLASSBUILDER_END(ArtifactAcid);
}
