//
//  Effect_DinoFootShadow_For_Artifact_Dinosaur_horn.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ArtifactDinosaurHornTools.h"

Effect_DinoFootShadow_For_Artifact_Dinosaur_horn::~Effect_DinoFootShadow_For_Artifact_Dinosaur_horn()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_DinoFootShadow_For_Artifact_Dinosaur_horn);

void Effect_DinoFootShadow_For_Artifact_Dinosaur_horn::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_DinoFootShadow_For_Artifact_Dinosaur_horn);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

		REFLECTION_CLASSBUILDER_FIELD(float, m_scale);
	REFLECTION_CLASSBUILDER_END(Effect_DinoFootShadow_For_Artifact_Dinosaur_horn);
}
