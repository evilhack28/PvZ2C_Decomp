//
//  Effect_DinoRun_For_Artifact_Dinosaur_horn.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ArtifactDinosaurHornTools.h"

Effect_DinoRun_For_Artifact_Dinosaur_horn::Effect_DinoRun_For_Artifact_Dinosaur_horn()
{
	m_shadowIgnored = 0;
}

Effect_DinoRun_For_Artifact_Dinosaur_horn::~Effect_DinoRun_For_Artifact_Dinosaur_horn()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_DinoRun_For_Artifact_Dinosaur_horn);

void Effect_DinoRun_For_Artifact_Dinosaur_horn::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_DinoRun_For_Artifact_Dinosaur_horn);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

		REFLECTION_CLASSBUILDER_FIELD(int, m_dinosaursNumPerLine);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastUsedDino);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_shadowIgnored);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ArtifactDinosaurHornProperties::TypeToSpawnDes>, m_dinoTypesToSpawn);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Creature>>, m_dinoRunners);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie>>, m_zombiesToBeKilled);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Plant>>, m_plantsToBeKilled);
	REFLECTION_CLASSBUILDER_END(Effect_DinoRun_For_Artifact_Dinosaur_horn);
}
