//
//  GridItemCthulhuActiniaTentacleArtifact.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

GridItemCthulhuActiniaTentacleArtifact::~GridItemCthulhuActiniaTentacleArtifact()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCthulhuActiniaTentacleArtifact);

void GridItemCthulhuActiniaTentacleArtifact::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCthulhuActiniaTentacleArtifact);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCthulhuActiniaTentacle);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<AddCthulhuEnergyEffect>, m_darkEffect);
	REFLECTION_CLASSBUILDER_END(GridItemCthulhuActiniaTentacleArtifact);
}
