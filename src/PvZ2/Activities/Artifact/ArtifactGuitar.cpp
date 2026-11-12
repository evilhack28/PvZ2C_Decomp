//
//  ArtifactGuitar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-10.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"
#include "ReflectionBuilder.h"

/////////////// Logic ///////////////

void ArtifactGuitar::onPlantCreate(Plant* i_arg)
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ArtifactGuitar);

void ArtifactGuitar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArtifactGuitar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Artifact);

		REFLECTION_CLASSBUILDER_FIELD(int, m_currentNotesIdx);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_passive2Cooldown);
	REFLECTION_CLASSBUILDER_END(ArtifactGuitar);
}
