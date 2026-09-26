//
//  ArtifactModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArtifactModule.h"

ArtifactModule::ArtifactModule()
{
}

ArtifactModule::~ArtifactModule()
{
}

ArtifactModuleProperties::ArtifactModuleProperties()
{
}

ArtifactModuleProperties::~ArtifactModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArtifactModule);

void ArtifactModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(ArtifactModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArtifactModuleProperties);

void ArtifactModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, LevelBlacklist);

	REFLECTION_CLASSBUILDER_END(ArtifactModuleProperties);
}
