//
//  ArtifactPrismTower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-10.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"
#include "ArtifactPrismTowerTools.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ArtifactPrismTower::~ArtifactPrismTower()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ArtifactPrismTower);

void ArtifactPrismTower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactPrismTower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Artifact);

		REFLECTION_CLASSBUILDER_FIELD(class ArtifactPrismTowerSubSystem*, m_subsystem);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(ArtifactPrismTower);
}
