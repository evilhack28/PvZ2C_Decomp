//
//  GridItemArtifactWeatherMonkey.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

GridItemArtifactWeatherMonkey::~GridItemArtifactWeatherMonkey()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemArtifactWeatherMonkey);

void GridItemArtifactWeatherMonkey::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemArtifactWeatherMonkey);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_stage);
		REFLECTION_CLASSBUILDER_FIELD(ProjectilePropertySheetPtr, m_projectilePropPtr);
	REFLECTION_CLASSBUILDER_END(GridItemArtifactWeatherMonkey);
}
