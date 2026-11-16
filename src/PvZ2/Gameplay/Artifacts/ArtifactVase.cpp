//
//  ArtifactVase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-10.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ArtifactVase::~ArtifactVase()
{
}

/////////////// Accessors ///////////////

bool ArtifactVase::IsGridValid(Point i_arg)
{
	return true;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ArtifactVase);

void ArtifactVase::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactVase);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Artifact);

		REFLECTION_CLASSBUILDER_FIELD(ProbabilitySet<ArtifactVaseConfigProperties>, m_bucket);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_passiveVaseStartTime);
		REFLECTION_CLASSBUILDER_FIELD(float, m_passiveVaseInterval);
	REFLECTION_CLASSBUILDER_END(ArtifactVase);
}
