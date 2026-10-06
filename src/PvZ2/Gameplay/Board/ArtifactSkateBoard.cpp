//
//  ArtifactSkateBoard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

ArtifactSkateBoardProperties::~ArtifactSkateBoardProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArtifactSkateBoard);

void ArtifactSkateBoard::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactSkateBoard);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Artifact);

	REFLECTION_CLASSBUILDER_END(ArtifactSkateBoard);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArtifactSkateBoardProperties);

void ArtifactSkateBoardProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactSkateBoardProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ArtifactProperties);

	REFLECTION_CLASSBUILDER_END(ArtifactSkateBoardProperties);
}

void ArtifactSkateBoardProperties::GatherResourceRequirements(std::set<std::string>& i_arg) const
{
}
