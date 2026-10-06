//
//  GridItemArtifactTornado.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

GridItemArtifactTornado::~GridItemArtifactTornado()
{
}

GridItemArtifactTornadoProps::~GridItemArtifactTornadoProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemArtifactTornado);

void GridItemArtifactTornado::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemArtifactTornado);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(float, m_lifeTime);
	REFLECTION_CLASSBUILDER_END(GridItemArtifactTornado);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemArtifactTornadoProps);

void GridItemArtifactTornadoProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemArtifactTornadoProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
		REFLECTION_CLASSBUILDER_FIELD(float, Damage);
	REFLECTION_CLASSBUILDER_END(GridItemArtifactTornadoProps);
}
